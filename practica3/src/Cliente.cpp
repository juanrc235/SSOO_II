#include <string>
#include <ctime>
#include <mutex>
#include <iostream>
#include "Cliente.hpp"

Cliente::Cliente (int nCliente) {
  std::srand((unsigned) time(0));
  this->mi_solicitud = Solicitud (nCliente, (std::rand() % 10)+1);
  this->nCliente = nCliente;
}

Cliente::Cliente () {}

Solicitud Cliente::get_solicitud() {
  return this->mi_solicitud;
}

void Cliente::esperar_taquilla() {
  std::cout << "Cliente " + std::to_string(this->nCliente) +
  " esperando en la cola de la taquilla" << std::endl;
  while(1);
}
