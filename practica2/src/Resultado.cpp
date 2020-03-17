#include "Resultado.h"
#include <iostream>

Resultado::Resultado (int num_hilo, int l_inicio, int l_final) {
  this->num_hilo = num_hilo;
  this->l_inicio = l_inicio;
  this->l_final = l_final;
}

void Resultado::devolver_resultado() {
  std::cout << "Hola\n";
}
