#include "Resultado.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <vector>
#include <algorithm>

/* lista de objetos Resultado, uno por hilo */
auto resultados = std::map<int, Resultado> {};
void escanear_documento (std::string fichero, int inicio, int final, int hilo, std::regex p) {

  int nlinea = 0;
  std::string strlinea;
  std::ifstream fd (fichero);
  Resultado resultado (hilo, inicio, final);

  while ( getline (fd, strlinea) ) {
    if ( std::regex_search(strlinea, p) &&  nlinea >= inicio) {
      resultado.add_resultado(nlinea, std::regex_replace(strlinea, p, "\e[3m$&\e[0m"));
    }
    nlinea++;
    if (nlinea == final) {
      break;
    }
  }
  fd.close();
  resultados.insert({hilo, resultado});
}

void mostrar_banner() {
  std::ifstream fd ("logo.txt");
  std::string strlinea;
  while ( getline (fd, strlinea) ) {
    std::cout << strlinea << '\n';
  }
  fd.close();
}

int main(int argc, char const *argv[]) {

  std::string palabra(argv[1]);
  std::string ruta(argv[2]);
  std::stringstream str;
  str <<  argv[3];
  int nhilos;
  str >> nhilos;

  std::ifstream fd (ruta);
  if (!fd.is_open()) {
    std::cout << "No se puede abrir el archivo: " + ruta <<std::endl;
    return 0;
  }

  mostrar_banner();

  std::cout << "\nFichero: " + ruta + "\n" +
               "Parabra: " + palabra + "\n" +
               "Nº hilos: " + std::to_string(nhilos) << std::endl;

  int nlineas = std::count(std::istreambuf_iterator<char>(fd), std::istreambuf_iterator<char>(),'\n'), i;
  int nlineas_hilo = nlineas/nhilos, linea_i = 0;
  int linea_f = nlineas_hilo;

  std::cout << "[MANAGER] El fichero contiene " + std::to_string(nlineas) +
               " líneas :: " + std::to_string(nlineas_hilo) + " líneas por hilo" << std::endl;

  /* Expresion regular para encontrar la palabra */
  std::string reg_exp = palabra + "[ .,?!)]";
  std::regex p(reg_exp, std::regex_constants::ECMAScript | std::regex_constants::icase);
  std::string strlinea;

  /* lista de hilos */
  std::vector<std::thread> vector_hilos;

  std::cout << "[MANAGER] Reparto de tareas" << std::endl;
  /* Creamos hilos y resultados*/
  for (i = 1; i <= nhilos; i++) {

    vector_hilos.push_back(std::thread(escanear_documento, ruta, linea_i, linea_f, i, p));

    linea_i = linea_f + 1;
    linea_f += nlineas_hilo;
    if (i == nhilos - 1 ) {
      linea_f = nlineas;
    }
  }

  std::cout << "[MANAGER] Esperando a la terminación de los hilos" << std::endl;
  /* Esperamos a los hilos */
  for (std::thread & hilo : vector_hilos) {
		if (hilo.joinable()){
      hilo.join();
    }
	}


  std::cout << "\n############################### Resultados #######################################\n" << std::endl;
  for (const auto &entry: resultados) {
		auto key = entry.second;
	  std::cout << key.devolver_resultado() << std::endl;
	}

  return 0;
}
