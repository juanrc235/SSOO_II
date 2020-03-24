#include "Resultado.h"
#include "Banner.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <mutex>

/* lista de objetos Resultado, uno por hilo */
auto resultados = std::map<int, Resultado> {};
std::mutex sem_map;

std::string parsear_resultado(std::string linea, std::regex p, std::string palabra) {
  std::string str_bonita;
  unsigned int pos = 0, size;

  std::regex p1(palabra, std::regex_constants::ECMAScript);

  std::istringstream iss(linea);
  std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

  for(auto it = results.begin(); it != results.end(); ++it) {
    if ( std::regex_search((*it), p1) ) {
      break;
    }
    pos++;
  }

  size = results.size();
  if (pos == 0 && size >= 2) {
    str_bonita = "... " + results[pos] + " " + results[pos + 1] + " ...";
  } else if (pos == size - 1 && size >=2) {
    str_bonita = "... " + results[pos-1] + " " + results[pos] + " ...";
  } else if (size >= 3) {
    str_bonita = "... " + results[pos-1] + " " + results[pos] + " " + results[pos+1] + " ...";
  } else {
    str_bonita = linea;
  }

  return str_bonita;
}

void escanear_documento (std::string fichero, int inicio, int final, int hilo, std::regex p, std::string palabra) {

  int nlinea = 0;
  std::string strlinea;
  std::ifstream fd (fichero);
  Resultado resultado (hilo, inicio, final);

  while ( getline (fd, strlinea) ) {
    if ( std::regex_search(strlinea, p) &&  nlinea >= inicio) {
      //strlinea = std::regex_replace(parsear_resultado(strlinea, p, palabra), p, "\e[3;1;31m$&\e[0m");
      strlinea = std::regex_replace(strlinea, p, "\e[3;1;31m$&\e[0m");
      resultado.add_resultado(nlinea, strlinea);
    }
    nlinea++;
    if (nlinea == final) {
      break;
    }
  }
  fd.close();

  sem_map.lock();
  resultados.insert({hilo, resultado});
  sem_map.unlock();
}

void mostrar_banner() {

  std::cout << banner1 << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << banner2 << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << banner3 << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << banner4 << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << banner5 << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << banner6 << std::endl;

}

/* TODO
  - control de errores argumentos
  - hacer main.cpp más OO en main
  - dividirlo .... p1 palabra p2 ...
  - destructores
*/

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

  std::cout << "\n[MANAGER] Fichero: " + ruta + "\n" +
               "[MANAGER] Parabra: " + palabra + "\n" +
               "[MANAGER] Nº hilos: " + std::to_string(nhilos) << std::endl;

  int nlineas = std::count(std::istreambuf_iterator<char>(fd), std::istreambuf_iterator<char>(),'\n'), i;
  int nlineas_hilo = nlineas/nhilos, linea_i = 0;
  int linea_f = nlineas_hilo;

  std::cout << "[MANAGER] El fichero contiene " + std::to_string(nlineas) +
               " líneas :: " + std::to_string(nlineas_hilo) + " líneas por hilo" << std::endl;

  /* Expresion regular para encontrar la palabra */
  //std::regex p(reg_exp, std::regex_constants::ECMAScript | std::regex_constants::icase);
  std::regex p("[¿!-( ]" + palabra + "[ .,:;-?!)]", std::regex_constants::ECMAScript | std::regex_constants::icase);
  std::string strlinea;

  /* lista de hilos */
  std::vector<std::thread> vector_hilos;

  std::cout << "[MANAGER] Reparto de tareas" << std::endl;
  /* Creamos hilos y resultados*/
  for (i = 1; i <= nhilos; i++) {

    vector_hilos.push_back(std::thread(escanear_documento, ruta, linea_i, linea_f, i, p, palabra));

    linea_i = linea_f + 1;
    linea_f += nlineas_hilo;
    if (i == nhilos - 1 ) {
      linea_f = nlineas;
    }
  }

  std::cout << "[MANAGER] Esperando a la terminación de los hilos " << std::endl;
  /* Esperamos a los hilos */
  for (std::thread & hilo : vector_hilos) {
		if (hilo.joinable()){
      hilo.join();
    }
	}

  int total = 0;
  std::cout << "\n############################### Resultados #######################################\n" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  for (const auto &entry: resultados) {
		auto key = entry.second;
	  std::cout << key.devolver_resultado() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    total+= key.get_subtotal();
	}
  std::cout << "[MANAGER] La palabra \e[3;1;31m" +palabra +
               "\e[0m aparece \e[3;1;32m" + std::to_string(total) +
               "\e[0m veces" << std::endl;

  return 0;
}
