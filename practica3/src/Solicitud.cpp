#include <string>

#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

Solicitud::Solicitud (int nCliente, int nAsientos) {
  this->nCliente = nCliente;
  this->nAsientos = nAsientos;
}

Solicitud::Solicitud () {}

std::string Solicitud::to_string(){
  return "SOLICITUD ENTRADAS :: Cliente: " + std::to_string(this->nCliente)
        + " || Asientos: " + std::to_string(this->nAsientos);
}

int Solicitud::get_nCliente() {
  return this->nCliente;
}

int Solicitud::get_nAsientos(){
  return this->nAsientos;
}
