#include "Resultado.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>

int main(int argc, char const *argv[]) {

  Resultado resultado_hilo_1 (1, 25, 75);
  std::cout << resultado_hilo_1.devolver_resultado() << std::endl;

  std::string line;
  std::ifstream fd ("fichero_casos.txt");
  std::regex p("casa", std::regex_constants::ECMAScript | std::regex_constants::icase);

  if (fd.is_open()) {
    while ( getline (fd, line) ) {
      if ( std::regex_search(line, p) ) {
        std::cout << line << std::endl;
      }
    }
    fd.close();
  } else {
    std::cout << "[ERROR] No se puede abrir el fichero";
  }

  return 0;
}
