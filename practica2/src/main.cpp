#include "Resultado.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>

int main(int argc, char const *argv[]) {

  std::string palabra(argv[1]);
  Resultado resultado_hilo_1 (1, 25, 75);
  std::cout << resultado_hilo_1.devolver_resultado() << std::endl;

  std::string line;
  std::ifstream fd ("fichero_casos.txt");
  std::string reg_exp = palabra + "[ .,?!]";
  std::regex p(reg_exp, std::regex_constants::ECMAScript | std::regex_constants::icase);
  std::string tmp;

  if (fd.is_open()) {
    while ( getline (fd, line) ) {
      if ( std::regex_search(line, p) ) {
        tmp = std::regex_replace(line, p, "\e[3m$&\e[0m");
        std::cout << tmp << std::endl;
      }
    }
    fd.close();
  } else {
    std::cout << "[ERROR] No se puede abrir el fichero";
  }

  return 0;
}
