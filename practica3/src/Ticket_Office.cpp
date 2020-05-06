#include <string>
#include <iostream>
#include <queue>
#include <thread>

#include "Ticket_Office.hpp"

Ticket_Office::Ticket_Office(int id) {
  this->libres = ROWS*COLUMNS;
  this->id = id;
}

std::string  Ticket_Office::dibujar_sala() {
  std::string dibujo;
  std::string ocupado = "\e[1;31m██\e[0m";
  std::string libre = "\e[1;32m██\e[0m";
  int i, j, libres = 0;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLUMNS; j++) {
      if (this->sala[i][j] == NOT_FREE) {
        //dibujo += "(" + std::to_string(i) + "," + std::to_string(j)+ ") " + ocupado + " ";
        dibujo += ocupado + " ";
      } else if (this->sala[i][j] == FREE) {
        //dibujo += "(" + std::to_string(i) + "," + std::to_string(j)+ ") " + libre + " ";
        dibujo += libre + " ";
      }
    }
    dibujo += "\n\n";
  }
  dibujo += "[TICKET OFFICE] There are " + std::to_string(this->libres) + " free seats\n";
  return dibujo;
}

bool Ticket_Office::pedir_asientos(Ticket_request s) {

  std::lock_guard<std::mutex> lock(this->s_seats);
  if (this->libres < s.get_nAsientos()) {
    return false;
  }

  int i, j, asientos_ocupados = 0;
  for (i = 0; i < ROWS && asientos_ocupados < s.get_nAsientos(); i++) {
    for (j = 0; j < COLUMNS && asientos_ocupados < s.get_nAsientos(); j++) {
        if (this->sala[i][j] != NOT_FREE) {
          this->sala[i][j] = NOT_FREE;
          asientos_ocupados++;
        }
    }
  }

  this->libres -= s.get_nAsientos();

  return true;
}
