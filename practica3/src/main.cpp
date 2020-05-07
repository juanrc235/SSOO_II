#ifndef SOLICITUD
  #define SOLICITUD
  #include "Ticket_request.hpp"
#endif

#ifndef CLIENTE
  #define CLIENTE
  #include "Client.hpp"
#endif

#ifndef SUPPLIER
  #define SUPPLIER
  #include "Supplier.hpp"
#endif

#include "Ticket_Office.hpp"
#include "Payment_system.hpp"
#include "Banner.hpp"
#include "Food_Stand.hpp"


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <thread>
#include <chrono>
#include <string>
#include <condition_variable>
#include <mutex>
#include <exception>
#include <csignal>

#define FOOD_STANDS 1
#define MAX_CLIENTS 10

std::queue<std::thread> main_queue_t;
std::vector<std::thread> food_stand_t_vector;

std::queue<Ticket_request> qeue_request_office;
std::queue<Food_request> qeue_request_food;

std::mutex s_office, s_solicitar_taquilla, s_wait_tickets, s_payment, s_supplier;
std::mutex mutex_payment, confirmation_payment, s_tickets_payment, confirmation_supply;
std::mutex s_client_food, mutex_food, s_total, s_ticket_request_attended, s_log;

std::condition_variable turn_tickets;
std::condition_variable turn_food;
std::condition_variable attended_food;

int client_to_pay, food_stand_to_supply, turn = -1, total_client_attended;
int continue_clients[MAX_CLIENTS]; // 0 waits 1 -> no 2 -> si
bool errLog_created = false;
Supplier supplier(1);

void client_life_cycle (Client& c);
void ticket_office_life_cycle(Ticket_Office& ticket_office);
void payment_system_life_cycle(Payment_system& payment_system);
void food_stand_life_cycle(Food_Stand& food_stand);
void make_payment(int client_ID);
void supplier_life_cycle(Supplier &supplier);
void write_errLog(std::string errMsg);
void signalHandler(int signum);

int main(int argc, char const *argv[]) {

  signal(SIGINT, signalHandler);

  s_solicitar_taquilla.lock();
  s_wait_tickets.lock();
  s_payment.lock();
  s_supplier.lock();
  confirmation_supply.lock();
  confirmation_payment.lock();
  s_tickets_payment.lock();

  clean_screen();
  print_banner();

  Payment_system payment_system;
  Ticket_Office ticket_office (1);
  Supplier supplier(1);

  int i;

  try {

  } catch (std::exception& e) {
    write_errLog("In ticket office creation");
    write_errLog(e.what());
  }
  std::thread t_ticket_office(ticket_office_life_cycle, std::ref(ticket_office));
  std::this_thread::sleep_for (std::chrono::milliseconds(200));
  std::thread t_pay_sys(payment_system_life_cycle, std::ref(payment_system));
  std::this_thread::sleep_for (std::chrono::milliseconds(200));

  for (i = 0; i < FOOD_STANDS; i++) {
    Food_Stand fs(i+1, 20, 20);
    food_stand_t_vector.push_back(std::thread (food_stand_life_cycle, std::ref(fs) ) );
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
  }
  std::thread t_supplier(supplier_life_cycle, std::ref(supplier));
  std::this_thread::sleep_for (std::chrono::milliseconds(300));

  std::cout << YELLOW << "\nPress [ENTER] to start the simulation ..." << RESET << std::endl;
  std::cin.get();

  std::unique_lock<std::mutex> lk (s_office);
  for (i = 1; i < MAX_CLIENTS+1; i++) {
    if (i > 1) {
      lk.lock();
    }
    Client c (i);
    turn = i;
    main_queue_t.push(std::thread(client_life_cycle, std::ref(c)));
    std::this_thread::sleep_for (std::chrono::milliseconds(300));
    turn_tickets.notify_all();
    lk.unlock();
    // the client locks the ticker office and the payment system
    s_tickets_payment.lock();
  }

  std::cout << WHITE << "\n####################### SIMULATION ENDS #######################" << std::endl;
  _Exit(0);
  return 0;
}

void client_life_cycle(Client& c) {
  std::mutex s_wait_food;
  int id = c.get_nClient();
  std::string header = "\e[1;33m[CLIENT " + std::to_string(id) + "]\e[0m ";

  std::unique_lock<std::mutex> lk (s_office);
  turn_tickets.wait(lk, [id]{return (turn == id);}); // clients waits for their turn

  c.generate_ticket_request();
  std::cout << header << "Turn obtained and ticket request generated" << std::endl;
  std::cout << header << GREEN << c.get_ticket_request().to_string() << RESET << std::endl;
  lk.unlock();

  qeue_request_office.push(c.get_ticket_request());
  s_solicitar_taquilla.unlock();
  s_wait_tickets.lock();

  while(continue_clients[c.get_nClient()] == 0);

  if (continue_clients[c.get_nClient()] == 1) {
    std::cout << header << "There is no enought ticket for me. I go home" << std::endl;
    s_tickets_payment.unlock();
  } else if (continue_clients[c.get_nClient()] == 2)  {
    std::cout << header << "I have my tickets, now I can go for popcorns" << std::endl;
    // the client frees the ticket office and the payment system
    s_tickets_payment.unlock();

    // client generates the food request
    c.generate_food_request();
    std::cout << header << GREEN << c.get_foodrequest().to_string() << RESET << std::endl;
    qeue_request_food.push(c.get_foodrequest());

    // the client tell that another can continue
    turn_food.notify_one();

    //wait for food stand
    std::unique_lock<std::mutex> lk_food (s_wait_food);
    attended_food.wait(lk_food);
  }
  // increment the number of clients done
  s_total.lock();
  total_client_attended ++;
  s_total.unlock();

  std::cout << header << WHITE << "I have FINISHED" << RESET << std::endl;
}

void ticket_office_life_cycle(Ticket_Office& ticket_office) {

  std::cout << RED << "[TICKET OFFICE]" << RESET << " Open and waiting for clients ..." << std::endl;
  while (total_client_attended != MAX_CLIENTS) {
    if (total_client_attended == MAX_CLIENTS) { break; }
    s_solicitar_taquilla.lock(); // nos bloqueamos a la espera de alguna Ticket_request

    Ticket_request Ticket_request = qeue_request_office.front();
    qeue_request_office.pop();

    std::this_thread::sleep_for (std::chrono::milliseconds(2000));

    if ( !ticket_office.pedir_asientos(Ticket_request) ){
      continue_clients[Ticket_request.get_nCliente()] = 1;
      std::cout << RED << "[TICKET OFFICE]" << RESET << " Request of " << YELLOW << "[CLIENT " + std::to_string(Ticket_request.get_nCliente()) +
      "]" << RESET << " not attended" << std::endl;
    } else {
      continue_clients[Ticket_request.get_nCliente()] = 2;
      std::cout << RED << "[TICKET OFFICE]" << RESET << " Request of " << YELLOW << "[CLIENT " + std::to_string(Ticket_request.get_nCliente()) +
      "]" << RESET << " attended" << std::endl;
      std::cout << ticket_office.dibujar_sala() << std::endl;
      make_payment(Ticket_request.get_nCliente());
    }
    // Another client can use the ticket office
    s_wait_tickets.unlock();
  }
}

void payment_system_life_cycle(Payment_system& payment_system) {
  std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << " Created and ready to work ..." << std::endl;
  while (true) {
    if (total_client_attended == MAX_CLIENTS) { break; }
    s_payment.lock();
    std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << "Received payment request ... "  << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    std::cout << BLUE << "[PAYMENT SYSTEM]" << YELLOW << "[CLIENT "+ std::to_string(client_to_pay) + "]" << RESET << " has paid"  << std::endl;
    confirmation_payment.unlock();
  }
}

void food_stand_life_cycle(Food_Stand& food_stand) {

  std::string header = "\e[1;35m[FOOD STAND " + std::to_string(food_stand.get_id()) + "]\e[0m ";
  std::cout << header << " Open and waiting for clients :: ";
  std::cout << food_stand.to_string() << '\n';
  std::unique_lock<std::mutex> lk (s_client_food);

  while (true) {
    if (total_client_attended == MAX_CLIENTS) { break; }
    turn_food.wait(lk, []{return !qeue_request_food.empty();});

    // get a new food request [exclusive access]
    mutex_food.lock();
    Food_request food_request = qeue_request_food.front();
    qeue_request_food.pop();
    mutex_food.unlock();

    lk.unlock();

    // real function that request the food
    // if no food it blocks until there is food
    if ( !food_stand.request_food(food_request) ) {
      food_stand_to_supply = food_stand.get_id();
      s_supplier.unlock();
      confirmation_supply.lock();
      food_stand.refill();
      // request food again
      food_stand.request_food(food_request);
    }
    std::cout << header << food_stand.to_string() << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(2000));

    std::cout << header << YELLOW << "[CLIENT " + std::to_string(food_request.get_client()) +
    "]" << RESET << " attended" << std::endl;

    make_payment(food_request.get_client());

    // next clients can go to the food stands
    attended_food.notify_all();
    food_request.attended();
    lk.lock();
  }
}

void supplier_life_cycle(Supplier &supplier) {
  std::string header = "\e[1;36m[SUPPLIER " + std::to_string(supplier.get_id()) + "]\e[0m";
  std::cout << header << " Ready and waiting to supply ..." << '\n';
  while(1) {
    s_supplier.lock();
    std::cout << header << " Suppliying \e[1;35m[FOOD STAND " + std::to_string(food_stand_to_supply) +
    "]\e[0m" << std::endl;
    supplier.supply();
    confirmation_supply.unlock();
    if (total_client_attended == MAX_CLIENTS) { break; }
  }
}

void make_payment(int id) {
  // Payment simulation
  mutex_payment.lock();
  client_to_pay = id;
  s_payment.unlock(); // wake up payment system
  confirmation_payment.lock(); // wait for confirmation
  mutex_payment.unlock();
}

void write_errLog(std::string errMsg) {
  s_log.lock();
  std::ofstream myfile;
  if (!errLog_created) {
    myfile.open ("errLog.txt", std::ios::trunc);
    myfile << "################ ERROR LOG ##############" << std::endl;
    errLog_created = true;
  }
  myfile.open ("errLog.txt", std::ios::app);
  myfile << errMsg << std::endl;
  std::cout << RED << "[ERROR] " << RESET <<  errMsg  << std::endl;
  myfile.close();
  s_log.unlock();
}

void signalHandler( int signum ) {
  std::cout << '\n';
  write_errLog("Program aborted by user (Ctrl+C)");
  _Exit(0);
}
