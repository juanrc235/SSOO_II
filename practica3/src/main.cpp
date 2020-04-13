#ifndef SOLICITUD
  #define SOLICITUD
  #include "Solicitud.hpp"
#endif
#include "Taquilla.hpp"
#include "Cliente.hpp"
#include <iostream>
#include <cstdlib>
#include <queue>
#include <thread>
#include <chrono>
#include <string>

void print_banner() {
  std::string b1 = "███╗   ███╗██╗   ██╗██╗  ████████╗██╗ ██████╗██╗███╗   ██╗███████╗███████╗    ███████╗███████╗ ██████╗  ██████╗ ██╗██╗";
  std::string b2 = "████╗ ████║██║   ██║██║  ╚══██╔══╝██║██╔════╝██║████╗  ██║██╔════╝██╔════╝    ██╔════╝██╔════╝██╔═══██╗██╔═══██╗██║██║";
  std::string b3 = "██╔████╔██║██║   ██║██║     ██║   ██║██║     ██║██╔██╗ ██║█████╗  ███████╗    ███████╗███████╗██║   ██║██║   ██║██║██║";
  std::string b4 = "██║╚██╔╝██║██║   ██║██║     ██║   ██║██║     ██║██║╚██╗██║██╔══╝  ╚════██║    ╚════██║╚════██║██║   ██║██║   ██║██║██║";
  std::string b5 = "██║ ╚═╝ ██║╚██████╔╝███████╗██║   ██║╚██████╗██║██║ ╚████║███████╗███████║    ███████║███████║╚██████╔╝╚██████╔╝██║██║";
  std::string b6 = "╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝   ╚═╝ ╚═════╝╚═╝╚═╝  ╚═══╝╚══════╝╚══════╝    ╚══════╝╚══════╝ ╚═════╝  ╚═════╝ ╚═╝╚═╝";

  std::cout << b1 << std::endl;
  std::cout << b2 << std::endl;
  std::cout << b3 << std::endl;
  std::cout << b4 << std::endl;
  std::cout << b5 << std::endl;
  std::cout << b6 << std::endl;
}

void clean_screen() {
  std::cout << "\033[2J\033[1;1H";
}

int main(int argc, char const *argv[]) {

  std::queue <Cliente> fila_espera;

  int i;
  for (i = 1; i < 11; i++) {
    fila_espera.push(Cliente (i));
  }

  Taquilla taquilla;
  Cliente tmp_c;
  Solicitud tmp_s;

  clean_screen();
  for (i = 1; i < 11; i++) {
    print_banner();

    tmp_c = fila_espera.front();
    tmp_s = tmp_c.get_solicitud();

    std::cout << "\n" + tmp_s.to_string() + "\n" << std::endl;
    taquilla.pedir_asientos(tmp_s);
    fila_espera.pop(); // remove the element

    std::cout << taquilla.dibujar_sala() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (i < 10) {
      clean_screen();
    }
  }

  return 0;
}
