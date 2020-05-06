#include "Ticket_request.hpp"


Ticket_request::Ticket_request (int nCliente, int nAsientos) {
  this->nCliente = nCliente;
  this->nAsientos = nAsientos;
  this->attended = true;
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

bool Ticket_request::is_attended() {
  return this->attended;
}

void Ticket_request::set_not_attended() {
  this->attended = false;
}
