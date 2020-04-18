#include <string>
#include <ctime>
#include "Cliente.hpp"

Cliente::Cliente (int nCliente) {
  std::srand((unsigned) time(0));
  this->mi_solicitud = Solicitud (nCliente, (std::rand() % 10)+1);
}

Cliente::Cliente () {}

Solicitud Cliente::get_solicitud() {
  return this->mi_solicitud;
}
