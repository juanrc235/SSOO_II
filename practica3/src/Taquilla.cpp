#include <string>
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
      if (sala[i][j] == 1) {
        dibujo += ocupado + " ";
      } else {
        dibujo += libre + " ";
      }
    }
    dibujo += "\n\n";
  }
  dibujo += "[TAQUILLA] Quedan " + std::to_string(this->libres) + " asientos libres\n";
  return dibujo;
}

std::string Taquilla::pedir_asientos(Solicitud s) {
  std::string asientos;



  return asientos;
}
