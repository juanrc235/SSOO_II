#include <string>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include "Cliente.hpp"

Cliente::Cliente (int nCliente) {
  this->nCliente = nCliente;
}

Cliente::Cliente () {}

Solicitud Cliente::get_solicitud() {
  return this->mi_solicitud;
}

int Cliente::get_nCliente() {
  return this->nCliente;
}

void Cliente::generar_solicitud_taquilla() {
  std::srand((unsigned) time(0));
  this->mi_solicitud = Solicitud (this->nCliente, (std::rand() % 10)+1);
  // simular generación de solicitud
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
}
