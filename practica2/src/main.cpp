#include "Resultado.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <vector>
#include <algorithm>

void escanear_documento (std::string fichero, int inicio, int final, int hilo, std::regex p) {

  int nlinea = 0;
  std::string strlinea;
  std::ifstream fd (fichero);
  Resultado resultado (hilo, inicio, final);

  while ( getline (fd, strlinea) ) {
    if ( std::regex_search(strlinea, p) && nlinea >= inicio) {
      resultado.add_resultado(nlinea, std::regex_replace(strlinea, p, "\e[3m$&\e[0m"));
      //std::cout << "Línea " + std::to_string(nlinea) + " :: " +
                    //std::regex_replace(strlinea, p, "\e[3m$&\e[0m") << '\n';
    }
    nlinea++;
    if (nlinea == final) {
      break;
    }
  }
  fd.close();
  std::cout << resultado.devolver_resultado() << std::endl;
}

void imprimir (int i) {
  std::cout << "Hilo :: " + std::to_string(i) << std::endl;
}

int main(int argc, char const *argv[]) {

  std::string palabra(argv[1]);
  std::string ruta(argv[2]);
  std::stringstream str;
  str <<  argv[3];
  int nhilos;
  str >> nhilos;

  std::cout << "[MANAGER] \nFichero: " + ruta + "\n" +
                          "Parabra: " + palabra + "\n" +
                          "Nº hilos: " + std::to_string(nhilos) << std::endl;

  std::ifstream fd (ruta);
  if (fd.is_open()) {

    int nlineas = std::count(std::istreambuf_iterator<char>(fd), std::istreambuf_iterator<char>(),'\n'), i;
    int nlineas_hilo = nlineas/nhilos, linea_i = 0;
    int linea_f = nlineas_hilo;

    std::cout << "[MANAGER] El fichero contiene " + std::to_string(nlineas) +
                 " líneas :: " + std::to_string(nlineas_hilo) + " líneas por hiloconv" << std::endl;

    /* Expresion regular para encontrar la palabra */
    std::string reg_exp = palabra + "[ .,?!)]";
    std::regex p(reg_exp, std::regex_constants::ECMAScript | std::regex_constants::icase);
    std::string strlinea;

    /* lista de objetos Resultado, uno por hilo */
    std::vector<Resultado> vector_resultado;

    /* lista de hilos */
    std::vector<std::thread> vector_hilos;

    std::cout << "[MANAGER] Reparto de tareas #" << std::endl;
    /* Creamos hilos y resultados*/
    for (i = 1; i <= nhilos; i++) {

      vector_hilos.push_back(std::thread(escanear_documento, ruta, linea_i, linea_f, i, p));

      linea_i = linea_f + 1;
      linea_f += nlineas_hilo;
      if (i == nhilos - 1 ) {
        linea_f = nlineas;
      }

    }

    std::cout << "[MANAGER] Esperando a la terminación de los hilos #" << std::endl;
    /* Esperamos a los hilos */
    for (std::thread & hilo : vector_hilos) {
  		if (hilo.joinable()){
        hilo.join();
      }
  	}
    std::cout << "[MANAGER] Todos los hilos han acabado #" << std::endl;

  } else {
    std::cout << "No se puede abrir el archivo: " + ruta <<std::endl;
  }

  return 0;
}
