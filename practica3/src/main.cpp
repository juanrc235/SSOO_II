#include "Solicitud.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {

  Solicitud sol1 (1, 1, "a", "a");
  std::cout <<  sol1.to_string() << std::endl;

  return 0;
}
