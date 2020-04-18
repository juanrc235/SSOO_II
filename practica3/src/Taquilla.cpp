#include <string>
#include <iostream>
#include <queue>
#include <thread>

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
        //dibujo += "(" + std::to_string(i) + "," + std::to_string(j)+ ") " + ocupado + " ";
        dibujo += ocupado + " ";
      } else if (this->sala[i][j] == ASIENTO_LIBRE) {
        //dibujo += "(" + std::to_string(i) + "," + std::to_string(j)+ ") " + libre + " ";
        dibujo += libre + " ";
      }
    }
    dibujo += "\n\n";
  }
  dibujo += "[TAQUILLA] Quedan " + std::to_string(this->libres) + " asientos libres\n";
  return dibujo;
}

bool Taquilla::pedir_asientos(Solicitud s) {

  if (this->libres < s.get_nAsientos()) {
    return false;
  }

  int i, j, asientos_ocupados = 0;
  for (i = 0; i < FILAS && asientos_ocupados < s.get_nAsientos(); i++) {
    for (j = 0; j < COLUMNAS && asientos_ocupados < s.get_nAsientos(); j++) {
        if (this->sala[i][j] != ASIENTO_OCUPADO) {
          this->sala[i][j] = ASIENTO_OCUPADO;
          asientos_ocupados++;
        }
    }
  }

  this->libres -= s.get_nAsientos();

  return true;
}

void Taquilla::abrir() {
  std::cout << "[TAQUILLA] .... HEMOS ABIERTO !! ...." << std::endl;

  while (true) {
    // coger una peticion de la cola
    // pedir_asientos()
    // SISTEMA PAGO
    // transferir hilo a la cola de la comida
  }

}
