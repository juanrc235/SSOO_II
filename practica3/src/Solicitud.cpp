#include <string>
#include "Solicitud.hpp"

Solicitud::Solicitud (int nCliente, int nAsientos, std::string zona_v, std::string zona_h) {
  this->nCliente = nCliente;
  this->nAsientos = nAsientos;
  this->zona_v = zona_v;
  this->zona_h = zona_h;
}

std::string Solicitud::to_string(){
  return "SOLICITUD ENTRADAS: " + std::to_string(this->nCliente) + " " +
        std::to_string(this->nAsientos) + " " +  this->zona_v + " " +
        this->zona_h;
}

int Solicitud::get_nCliente() {
  return this->nCliente;
}

int Solicitud::get_nAsientos(){
  return this->nAsientos;
}

std::string Solicitud::get_zonaV(){
  this->zona_v;
}

std::string Solicitud::get_zonaH(){
  this->zona_h;
}
