#ifndef SOLICITUD
  #define SOLICITUD
  #include "Solicitud.hpp"
#endif
#include "Taquilla.hpp"
#include "Cliente.hpp"
#include <iostream>
#include <cstdlib>
#include <queue>

int main(int argc, char const *argv[]) {

  std::queue <Cliente> fila_espera;

  int i;
  for (i = 1; i < 11; i++) {
    fila_espera.push(Cliente (i));
  }

  Taquilla t;
  std::cout << "\n############## SALA ###############\n" <<  std::endl;
  std::cout << t.dibujar_sala() << std::endl;
  std::cout << "###################################\n" <<  std::endl;

  return 0;
}
