#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif
#include "Cliente.hpp"

#include <vector>

std::string zona_vertical[] = {"Cerca", "Medio", "Lejos"};
std::string zona_horizontal[] = {"Izquierda", "Centro", "Derecha"};

Cliente::Cliente (int nCliente) {
  std::srand((int) time(0));
  int nAsientos = (std::rand() % 5) + 1;
  int zona_h = std::rand() % 3;
  int zona_v = std::rand() % 3;
  this->mi_solicitud = Solicitud (nCliente, nAsientos, zona_vertical[zona_v], zona_horizontal[zona_h]);
}

Solicitud Cliente::get_solicitud() {
  return this->mi_solicitud;
}

void Cliente::set_asientos(std::vector<int[]> asientos){
  this->mis_asientos = asientos;
}
