#include "Resultado.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
#include <algorithm>

void escanear_documento (std::string fichero, int inicio, int final, Resultado resultado, std::regex p) {

  int nlinea = 0;
  std::string strlinea;
  std::ifstream fd (fichero);

  fd.seekg(inicio, std::ios::beg);
  if (fd.is_open()) {
    while ( getline (fd, strlinea) ) {
      if ( std::regex_search(strlinea, p) ) {
        resultado.add_resultado(nlinea, std::regex_replace(strlinea, p, "\e[3m$&\e[0m"));
      }
      nlinea++;
      if (nlinea == final) {
        break;
      }
    }
    fd.close();
  } else {
    std::cout << "[ERROR] No se puede abrir el fichero";
  }

}

int main(int argc, char const *argv[]) {

  std::string palabra(argv[1]);


  std::string strlinea;
  std::ifstream fd (argv[2]);
  int nlineas = std::count(std::istreambuf_iterator<char>(fd), std::istreambuf_iterator<char>(),'\n');

  std::string reg_exp = palabra + "[ .,?!]";
  std::regex p(reg_exp, std::regex_constants::ECMAScript | std::regex_constants::icase);

  Resultado resultado(1, 0, 5);
  escanear_documento(argv[2], 0, 5, resultado, p);
  Resultado resultado1(2, 5, nlineas);
  escanear_documento(argv[2], 5, nlineas, resultado1, p);

  std::cout << resultado.devolver_resultado() << std::endl;
  std::cout << resultado1.devolver_resultado() << std::endl;

  return 0;
}
