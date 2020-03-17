#include "Resultado.h"
#include <iostream>
#include <string>

Resultado::Resultado (int num_hilo, int l_inicio, int l_final) {
  this->num_hilo = num_hilo;
  this->l_inicio = l_inicio;
  this->l_final = l_final;
}

std::string Resultado::devolver_resultado() {
  std::string cabecera = "[HILO " +
                          std::to_string(this->num_hilo) +
                          " :: Inicio: " + std::to_string(this->l_inicio) +
                          " -- Final: " + std::to_string(l_final) + "] ";
  return cabecera;
}
