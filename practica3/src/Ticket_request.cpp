#include <string>
#include "Ticket_request.hpp"


Ticket_request::Ticket_request (int nCliente, int nAsientos) {
  this->nCliente = nCliente;
  this->nAsientos = nAsientos;
}

Ticket_request::Ticket_request () {}

std::string Ticket_request::to_string(){
  return "TICKET REQUEST :: Client ID " + std::to_string(this->nCliente)
        + " || Seats: " + std::to_string(this->nAsientos);
}

int Ticket_request::get_nCliente() {
  return this->nCliente;
}

int Ticket_request::get_nAsientos(){
  return this->nAsientos;
}
