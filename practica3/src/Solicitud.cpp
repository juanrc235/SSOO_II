#include <string>

#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

Solicitud::Solicitud (int nCliente, int nAsientos, std::string zona_v, std::string zona_h) {
  this->nCliente = nCliente;
  this->nAsientos = nAsientos;
  this->zona_v = zona_v;
  this->zona_h = zona_h;
}

Solicitud::Solicitud () {}

std::string Solicitud::to_string(){
  return "SOLICITUD ENTRADAS :: Cliente: " + std::to_string(this->nCliente)
        + " || Asientos: " + std::to_string(this->nAsientos)
        + " || Zona vertical: " +  this->zona_v + " || Zona horizontal: " +
        this->zona_h;
}

int Solicitud::get_nCliente() {
  return this->nCliente;
}

int Solicitud::get_nAsientos(){
  return this->nAsientos;
}

std::string Solicitud::get_zonaV(){
  return this->zona_v;
}

std::string Solicitud::get_zonaH(){
  return this->zona_h;
}
