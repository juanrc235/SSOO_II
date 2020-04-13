
#include <string>
#include "Cliente.hpp"

std::string zona_vertical[] = {"Cerca", "Medio", "Lejos"};
std::string zona_horizontal[] = {"Izquierda", "Centro", "Derecha"};

Cliente::Cliente (int nCliente) {
  std::srand((int) time(0));
  this->mi_solicitud = Solicitud (nCliente, (std::rand() % 5)+1, zona_vertical[std::rand()%3], zona_horizontal[std::rand()%3]);
}

Cliente::Cliente () {}

Solicitud Cliente::get_solicitud() {
  return this->mi_solicitud;
}


void Cliente::set_asientos(std::vector<int> asientos){
  this->mis_asientos = asientos;
}
