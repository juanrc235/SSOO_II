#include "Resultado.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>

int main(int argc, char const *argv[]) {

  std::string palabra(argv[1]);
  Resultado resultado_hilo_1 (1, 25, 75);
  std::cout << resultado_hilo_1.devolver_resultado() << std::endl;

  int nlinea = 0;
  std::string strlinea;
  std::ifstream fd (argv[2]);
  std::string reg_exp = palabra + "[ .,?!]";
  std::regex p(reg_exp, std::regex_constants::ECMAScript | std::regex_constants::icase);

  if (fd.is_open()) {
    while ( getline (fd, strlinea) ) {
      if ( std::regex_search(strlinea, p) ) {
        resultado_hilo_1.add_resultado(nlinea, std::regex_replace(strlinea, p, "\e[3m$&\e[0m"));
      }
      nlinea++;
    }
    fd.close();
  } else {
    std::cout << "[ERROR] No se puede abrir el fichero";
  }

  std::cout << resultado_hilo_1.devolver_resultado() << std::endl;

  return 0;
}
