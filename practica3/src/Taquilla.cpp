#include <string>
#include "Solicitud.hpp"
#include "Taquilla.hpp"

Taquilla::Taquilla() {

}

std::string  Taquilla::dibujar_sala() {
  std::string dibujo;
  int i, j;
  for (i = 0; i < FILAS; i++) {
    for (j = 0; j < COLUMNAS; j++) {
      dibujo += std::to_string(sala[i][j]) + " ";
    }
    dibujo += "\n";
  }
  return dibujo;
}
