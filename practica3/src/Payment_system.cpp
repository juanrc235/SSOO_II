#include "Payment_system.hpp"
#include <thread>
#include <chrono>
#include <iostream>

Payment_system::Payment_system() {
}

bool Payment_system::pagar (Client c) {
  this->s_pago.lock();

  /* Simulamos cálculos en el pago */
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "[SISTEMA DE PAGO] Cliente " +
  std::to_string((c.get_ticket_request()).get_nCliente()) + " ha pagado " << std::endl;

  this->s_pago.unlock();
}
