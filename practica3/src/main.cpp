#ifndef SOLICITUD
  #define SOLICITUD
  #include "Solicitud.hpp"
#endif

#ifndef CLIENTE
  #define CLIENTE
  #include "Cliente.hpp"
#endif

#include "Taquilla.hpp"
#include "Sistema_pago.hpp"
#include "Banner.hpp"

#include <iostream>
#include <cstdlib>
#include <queue>
#include <thread>
#include <chrono>
#include <string>
#include <condition_variable>

std::queue<std::thread> queue_t_office;
std::queue<std::thread> queue_t_food;

std::queue<Solicitud> qeue_request_office;

std::mutex s_office, s_solicitar_taquilla, s_wait_tickets, s_payment;
std::mutex mutex_payment, confirmation_payment, s_tickets_payment;

std::condition_variable turn_tickets;

int client_to_pay, turn = -1;

void client_life_cycle (Cliente& c);
void ticket_office_life_cycle(Taquilla& ticket_office);
void payment_system_life_cycle(Sistema_pago& payment_system);

int main(int argc, char const *argv[]) {

  s_solicitar_taquilla.lock();
  s_wait_tickets.lock();
  s_payment.lock();
  confirmation_payment.lock();
  s_tickets_payment.lock();

  clean_screen();
  print_banner();

  Sistema_pago payment_system;
  Taquilla ticket_office (1);

  std::thread t_ticket_office(ticket_office_life_cycle, std::ref(ticket_office));
  std::thread t_pay_sys(payment_system_life_cycle, std::ref(payment_system));

  std::this_thread::sleep_for (std::chrono::milliseconds(300));
  std::cout << MAGENTA << "\nPress [ENTER] to start the simulation ..." << RESET << std::endl;
  std::cin.get();

  int i;
  for (i = 1; i < 11; i++) {
    Cliente c (i);
    turn = i;
    queue_t_office.push(std::thread(client_life_cycle, std::ref(c)));
    std::this_thread::sleep_for (std::chrono::milliseconds(300));
    s_tickets_payment.lock();
  }

  t_ticket_office.join();
  t_pay_sys.join();

  return 0;
}

void client_life_cycle(Cliente& c) {

  int id = c.get_nCliente();
  std::unique_lock<std::mutex> lk (s_office);
  turn_tickets.wait(lk, [id]{return (turn == id);}); // clients waits for their turn

  c.generar_solicitud_taquilla();
  std::cout << YELLOW << "\n[CLIENT " << std::to_string(c.get_nCliente()) + "]" << RESET <<" Turn obtained and ticket request generated" << std::endl;
  std::cout << GREEN << c.get_solicitud().to_string() << RESET << std::endl;
  lk.unlock();

  qeue_request_office.push(c.get_solicitud());
  s_solicitar_taquilla.unlock();
  s_wait_tickets.lock();

  s_office.unlock();

  std::cout << YELLOW << "[CLIENT " << std::to_string(c.get_nCliente()) + "]" << RESET <<" I have my tickets, now I can go for popcorns" << std::endl;
  s_tickets_payment.unlock();

}

void ticket_office_life_cycle(Taquilla& ticket_office) {

  std::cout << RED << "[TICKET OFFICE]" << RESET << " Open and waiting for clients ..." << std::endl;
  while (true) {
    s_solicitar_taquilla.lock(); // nos bloqueamos a la espera de alguna solicitud

    Solicitud solicitud = qeue_request_office.front();
    qeue_request_office.pop();

    if ( ticket_office.pedir_asientos(solicitud) ){
        std::cout << RED << "[TICKET OFFICE]" << RESET << " Request of " << YELLOW << "[CLIENT " + std::to_string(solicitud.get_nCliente()) +
        "]" << RESET << " attended" << std::endl;
    }
    std::cout << ticket_office.dibujar_sala() << std::endl;

    // Payment simulation
    mutex_payment.lock();
    client_to_pay = solicitud.get_nCliente();
    s_payment.unlock(); // wake up payment system
    confirmation_payment.lock(); // wait for confirmation
    mutex_payment.unlock();

    // The client has paid and can pick up the tickets
    s_wait_tickets.unlock();
  }
}

void payment_system_life_cycle(Sistema_pago& payment_system) {
  std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << " Created and ready to work ..." << std::endl;

  while (true) {
    s_payment.lock();
    std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << "Received payment request ... "  << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    std::cout << BLUE << "[PAYMENT SYSTEM]" << YELLOW << "[CLIENT "+ std::to_string(client_to_pay) + "]" << RESET << " has paid"  << std::endl;
    confirmation_payment.unlock();
  }

}
