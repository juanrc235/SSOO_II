#ifndef SOLICITUD
  #define SOLICITUD
  #include "Solicitud.hpp"
#endif
#include "Taquilla.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char const *argv[]) {
  
  std::vector<Solicitud> vector_solicitudes;

  int i, nAsientos, zona_v, zona_h;
  for (i = 1; i <= 10; i++) {
    nAsientos = (std::rand() % 5) + 1;
    zona_h = std::rand() % 3;
    zona_v = std::rand() % 3;
    vector_solicitudes.push_back(Solicitud (i, nAsientos, zona_vertical[zona_v], zona_horizontal[zona_h]));
  }

  for (Solicitud &s: vector_solicitudes) {
    std::cout << s.to_string() << std::endl;
  }

  Taquilla t;
  std::cout << t.dibujar_sala() << std::endl;

  return 0;
}
