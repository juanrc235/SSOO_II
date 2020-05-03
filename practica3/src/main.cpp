#ifndef SOLICITUD
  #define SOLICITUD
  #include "Ticket_request.hpp"
#endif

#ifndef CLIENTE
  #define CLIENTE
  #include "Client.hpp"
#endif

#include "Ticket_Office.hpp"
#include "Payment_system.hpp"
#include "Banner.hpp"
#include "Food_Stand.hpp"

#include <iostream>
#include <cstdlib>
#include <queue>
#include <thread>
#include <chrono>
#include <string>
#include <condition_variable>
#include <mutex>

#define FOOD_STANDS 3
#define MAX_CLIENTS 10

std::queue<std::thread> main_queue_t;
std::queue<std::thread> food_stand_t_queue;

std::queue<Ticket_request> qeue_request_office;
std::queue<Food_request> qeue_request_food;

std::mutex s_office, s_solicitar_taquilla, s_wait_tickets, s_payment;
std::mutex mutex_payment, confirmation_payment, s_tickets_payment;
std::mutex s_client_food, mutex_food, s_total;

std::condition_variable turn_tickets;
std::condition_variable turn_food;
std::condition_variable attended_food;

int client_to_pay, turn = -1, total_client_attended;

void client_life_cycle (Client& c);
void ticket_office_life_cycle(Ticket_Office& ticket_office);
void payment_system_life_cycle(Payment_system& payment_system);
void food_stand_life_cycle(Food_Stand& food_stand);

int main(int argc, char const *argv[]) {

  s_solicitar_taquilla.lock();
  s_wait_tickets.lock();
  s_payment.lock();
  confirmation_payment.lock();
  s_tickets_payment.lock();

  clean_screen();
  print_banner();

  Payment_system payment_system;
  Ticket_Office ticket_office (1);

  int i;

  std::thread t_ticket_office(ticket_office_life_cycle, std::ref(ticket_office));
  std::this_thread::sleep_for (std::chrono::milliseconds(200));
  std::thread t_pay_sys(payment_system_life_cycle, std::ref(payment_system));
  std::this_thread::sleep_for (std::chrono::milliseconds(200));

  for (i = 0; i < FOOD_STANDS; i++) {
    Food_Stand fs(i+1);
    food_stand_t_queue.push(std::thread (food_stand_life_cycle, std::ref(fs)));
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
  }

  std::this_thread::sleep_for (std::chrono::milliseconds(300));
  std::cout << CYAN << "\nPress [ENTER] to start the simulation ..." << RESET << std::endl;
  std::cin.get();


  for (i = 1; i < MAX_CLIENTS+1; i++) {
    Client c (i);
    turn = i;
    main_queue_t.push(std::thread(client_life_cycle, std::ref(c)));
    std::this_thread::sleep_for (std::chrono::milliseconds(300));
    s_tickets_payment.lock();
  }

  t_ticket_office.join();
  t_pay_sys.join();

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

  s_office.unlock();

  std::cout << header << "I have my tickets, now I can go for popcorns" << std::endl;
  s_tickets_payment.unlock();

  c.generate_food_request();
  std::cout << header << GREEN << c.get_foodrequest().to_string() << RESET << std::endl;
  qeue_request_food.push(c.get_foodrequest());

  turn_food.notify_one();

  //wait for food stand
  std::cout << header << "Waiting for the food" << RESET << std::endl;
  std::unique_lock<std::mutex> lk_food (s_wait_food);
  attended_food.wait(lk_food);

  std::cout << header << WHITE << "I have FINISHED" << RESET << std::endl;
  s_total.lock();
  total_client_attended ++;
  s_total.unlock();
}

void ticket_office_life_cycle(Ticket_Office& ticket_office) {

  std::cout << RED << "[TICKET OFFICE]" << RESET << " Open and waiting for clients ..." << std::endl;
  while (true) {
    s_solicitar_taquilla.lock(); // nos bloqueamos a la espera de alguna Ticket_request

    Ticket_request Ticket_request = qeue_request_office.front();
    qeue_request_office.pop();

    if ( ticket_office.pedir_asientos(Ticket_request) ){
        std::cout << RED << "[TICKET OFFICE]" << RESET << " Request of " << YELLOW << "[CLIENT " + std::to_string(Ticket_request.get_nCliente()) +
        "]" << RESET << " attended" << std::endl;
    }
    std::this_thread::sleep_for (std::chrono::milliseconds(2000));
    //std::cout << ticket_office.dibujar_sala() << std::endl;

    // Payment simulation
    mutex_payment.lock();
    client_to_pay = Ticket_request.get_nCliente();
    s_payment.unlock(); // wake up payment system
    confirmation_payment.lock(); // wait for confirmation
    mutex_payment.unlock();

    // The client has paid and can pick up the tickets
    s_wait_tickets.unlock();

    if (total_client_attended == MAX_CLIENTS) {
      break;
    }
  }
  std::cout << RED << "[TICKET OFFICE]" << RESET << " CLOSED" << std::endl;
}

void payment_system_life_cycle(Payment_system& payment_system) {
  std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << " Created and ready to work ..." << std::endl;

  while (true) {
    s_payment.lock();
    std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << "Received payment request ... "  << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    std::cout << BLUE << "[PAYMENT SYSTEM]" << YELLOW << "[CLIENT "+ std::to_string(client_to_pay) + "]" << RESET << " has paid"  << std::endl;
    confirmation_payment.unlock();
    if (total_client_attended == MAX_CLIENTS) {
      break;
    }
  }
  std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << " CLOSED" << std::endl;
}

void food_stand_life_cycle(Food_Stand& food_stand) {

  std::string header = "\e[1;35m[FOOD STAND " + std::to_string(food_stand.get_id()) + "]\e[0m ";

  std::cout << header << " Open and waiting for clients ..." << std::endl;

  std::unique_lock<std::mutex> lk (s_client_food);

  while (true) {
    turn_food.wait(lk, []{return !qeue_request_food.empty();});

    mutex_food.lock();
    Food_request food_request = qeue_request_food.front();
    qeue_request_food.pop();
    food_stand.request_food(food_request);
    mutex_food.unlock();

    lk.unlock();

    std::this_thread::sleep_for (std::chrono::milliseconds(2000));
    std::cout << header << YELLOW << "[CLIENT " + std::to_string(food_request.get_client()) +
    "]" << RESET << " attended" << std::endl;

    // Payment simulation
    mutex_payment.lock();
    client_to_pay = food_request.get_client();
    s_payment.unlock(); // wake up payment system
    confirmation_payment.lock(); // wait for confirmation
    mutex_payment.unlock();

    food_request.attended();
    attended_food.notify_all();
    lk.lock();

    if (total_client_attended == MAX_CLIENTS) {
      break;
    }

  }
}
