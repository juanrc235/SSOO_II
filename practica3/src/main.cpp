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


std::queue<std::thread> cola_hilos_office;
std::queue<std::thread> cola_hilos_comida;

std::queue<Solicitud> cola_solicitudes_t;

std::mutex s_office, s_solicitar_taquilla, s_wait_tickets, s_payment;
std::mutex mutex_payment, confirmation_payment;

int client_to_pay;

void ciclo_vida_cliente (Cliente& c);
void ciclo_vida_taquilla(Taquilla& taquilla);
void ciclo_vida_sistema_pago(Sistema_pago& pago);

int main(int argc, char const *argv[]) {

  s_solicitar_taquilla.lock();
  s_wait_tickets.lock();
  s_payment.lock();
  confirmation_payment.lock();


  clean_screen();
  print_banner();

  Sistema_pago sistema_pago;
  Taquilla taquilla (1);

  std::thread hilo_taquilla(ciclo_vida_taquilla, std::ref(taquilla));
  std::thread t_pay_sys(ciclo_vida_sistema_pago, std::ref(sistema_pago));

  int i;
  for (i = 1; i < 11; i++) {
    Cliente c (i);
    cola_hilos_office.push(std::thread(ciclo_vida_cliente, std::ref(c)));
    std::this_thread::sleep_for (std::chrono::milliseconds(300));
  }

  hilo_taquilla.join();
  t_pay_sys.join();

  return 0;
}

void ciclo_vida_cliente(Cliente& c) {

  s_office.lock();
  c.generar_solicitud_taquilla();
  std::cout << YELLOW << "[CLIENTE " << std::to_string(c.get_nCliente()) + "]" << RESET <<" Turn obtained and ticket request generated" << std::endl;
  std::cout << c.get_solicitud().to_string() << std::endl;
  cola_solicitudes_t.push(c.get_solicitud());
  s_solicitar_taquilla.unlock();
  s_wait_tickets.lock();

  s_office.unlock();

}

void ciclo_vida_taquilla(Taquilla& taquilla) {

  std::cout << RED << "[TAQUILLA]" << RESET << " Open and waiting for clients ..." << std::endl;
  while (true) {
    s_solicitar_taquilla.lock(); // nos bloqueamos a la espera de alguna solicitud

    Solicitud solicitud = cola_solicitudes_t.front();
    cola_solicitudes_t.pop();

    if ( taquilla.pedir_asientos(solicitud) ){
        std::cout << RED << "[TAQUILLA]" << RESET << " Petición de [CLIENTE " + std::to_string(solicitud.get_nCliente()) +
        "] atendida" << std::endl;
         s_wait_tickets.unlock();
    }
    //std::cout << taquilla.dibujar_sala() << std::endl;

    // Payment simulation
    mutex_payment.lock();
    client_to_pay = solicitud.get_nCliente();
    s_payment.unlock(); // wake up payment system
    confirmation_payment.lock(); // wait for confirmation
    mutex_payment.unlock();
  }
}

void ciclo_vida_sistema_pago(Sistema_pago& pago) {
  std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << " Created and ready to work ..." << std::endl;

  while (true) {
    s_payment.lock();
    std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << "Received payment request ... "  << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(500));
    std::cout << BLUE << "[PAYMENT SYSTEM]" << RESET << "[CLIENT "+ std::to_string(client_to_pay) + "] has paid"  << std::endl;
    confirmation_payment.unlock();
  }

}
