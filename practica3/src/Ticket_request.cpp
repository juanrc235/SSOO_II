#include <string>

#ifndef SOLICITUD
#define SOLICITUD
#include "Ticket_request.hpp"
#endif

Solicitud::Solicitud (int nCliente, int nAsientos) {
  this->nCliente = nCliente;
  this->nAsientos = nAsientos;
}

Solicitud::Solicitud () {}

std::string Solicitud::to_string(){
  return "TICKET REQUEST :: Client ID " + std::to_string(this->nCliente)
        + " || Seats: " + std::to_string(this->nAsientos);
}

int Solicitud::get_nCliente() {
  return this->nCliente;
}

int Solicitud::get_nAsientos(){
  return this->nAsientos;
}
