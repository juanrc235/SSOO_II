#include <string>
#include <iostream>

#include "Taquilla.hpp"

Taquilla::Taquilla() {
  this->libres = FILAS*COLUMNAS;
}

std::string  Taquilla::dibujar_sala() {
  std::string dibujo;
  std::string ocupado = "\e[1;31m██\e[0m";
  std::string libre = "\e[1;32m██\e[0m";
  int i, j, libres = 0;

  for (i = 0; i < FILAS; i++) {
    for (j = 0; j < COLUMNAS; j++) {
      if (this->sala[i][j] == ASIENTO_OCUPADO) {
        dibujo += "(" + std::to_string(i) + "," + std::to_string(j)+ ") " + ocupado + " ";
      } else if (this->sala[i][j] == ASIENTO_LIBRE) {
        dibujo += "(" + std::to_string(i) + "," + std::to_string(j)+ ") " + libre + " ";
      }
    }
    dibujo += "\n\n";
  }
  dibujo += "[TAQUILLA] Quedan " + std::to_string(this->libres) + " asientos libres\n";
  return dibujo;
}

bool Taquilla::pedir_asientos(Solicitud s) {

  std::string zona_vertical[] = {"Cerca", "Medio", "Lejos"};
  std::string zona_horizontal[] = {"Izquierda", "Centro", "Derecha"};

  if (this->libres < s.get_nAsientos()) {
    return false;
  }

  int start_i, start_j, j, i, tmp_asientos = 0;

  for (i = 0; i < 3; i++) {
    if (zona_vertical[i].compare(s.get_zonaV()) == 0) {
      start_i = i*2;
    }
    if (zona_horizontal[i].compare(s.get_zonaH()) == 0) {
      start_j = i*4;
    }
  }

  for (j = start_j; j < COLUMNAS && tmp_asientos < s.get_nAsientos(); j++) {
    if (this->sala[start_i][j] != ASIENTO_OCUPADO) {
      this->sala[start_i][j] = ASIENTO_OCUPADO;
      tmp_asientos++;
      this->libres--;
    }
    if (j == COLUMNAS - 1) {
      j = start_j - 1;
      start_i++;
    }
  }

  return true;
}
