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

  Sistema_pago sistema_pago;
  std::queue<std::thread> cola_taquilla;

  int i;
  for (i = 1; i < 11; i++) {
    Cliente c(i);
    cola_taquilla.push( std::thread(&Cliente::esperar_taquilla, &c) );
    std::this_thread::sleep_for (std::chrono::milliseconds(300));
  }

  Taquilla taquilla;
  std::thread hilo_taquilla(&Taquilla::abrir, &taquilla);

  hilo_taquilla.join();
  return 0;
}
