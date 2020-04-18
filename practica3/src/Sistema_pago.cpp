#include "Sistema_pago.hpp"
#include <thread>
#include <chrono>
#include <iostream>

Sistema_pago::Sistema_pago() {
  std::cout << "[SISTEMA DE PAGO] Creado ..." << std::endl;
}

bool Sistema_pago::pagar (Cliente c) {
  this->s_pago.lock();

  /* Simulamos cálculos en el pago */
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::cout << "[SISTEMA DE PAGO] Cliente " +
  std::to_string((c.get_solicitud()).get_nCliente()) + " ha pagado " << std::endl;

  this->s_pago.unlock();
}
