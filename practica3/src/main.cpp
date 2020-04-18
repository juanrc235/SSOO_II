#ifndef SOLICITUD
  #define SOLICITUD
  #include "Solicitud.hpp"
#endif
#include "Taquilla.hpp"
#ifndef CLIENTE
  #define CLIENTE
  #include "Cliente.hpp"
#endif
#include "Sistema_pago.hpp"
#include "Banner.hpp"

#include <iostream>
#include <cstdlib>
#include <queue>
#include <thread>
#include <chrono>
#include <string>


int main(int argc, char const *argv[]) {

  clean_screen();
  print_banner();

  Taquilla taquilla;
  Sistema_pago sistema_pago;
  std::queue <Cliente> fila_espera;

  int i;
  for (i = 1; i < 11; i++) {
    Cliente c;
    fila_espera.push(c);
    std::cout << "CLIENTE ha llegado a la fila de la taquilla" << '\n';
  }


  return 0;
}
