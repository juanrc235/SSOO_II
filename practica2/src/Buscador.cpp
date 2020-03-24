#include "Buscador.h"
#include "Banner.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <mutex>

Buscador::Buscador (std::string palabra, std::string fichero, int nhilos) {
  this->palabra = palabra;
  this->fichero = fichero;
  this->nhilos = nhilos;
  this->p = std::regex("[¿!-( ]" + palabra + "[ .,:;-?!)]", std::regex_constants::ECMAScript | std::regex_constants::icase);
  this->fd = std::ifstream (this->fichero);
  this->total_aparciones = 0;
}

void Buscador::esperar_hilos() {
  /* Esperamos a los hilos */
  for (std::thread & hilo : this->vector_hilos) {
		if (hilo.joinable()){
      hilo.join();
    }
	}
}

void Buscador::escanear_documento (int inicio, int final, int hilo) {

  int nlinea = 0;
  std::string strlinea;
  std::ifstream fd (fichero);
  Resultado resultado (hilo, inicio, final);

  while ( getline (fd, strlinea) ) {
    if ( std::regex_search(strlinea, p) &&  nlinea >= inicio) {
      //strlinea = std::regex_replace(parsear_resultado(strlinea, p, palabra), p, "\e[3;1;31m$&\e[0m");
      strlinea = std::regex_replace(strlinea, this->p, "\e[3;1;31m$&\e[0m");
      resultado.add_resultado(nlinea, strlinea);
      this->total_aparciones++;
    }
    nlinea++;
    if (nlinea == final) {
      break;
    }
  }
  fd.close();

  this->sem_map.lock();
  this->resultados.insert(std::make_pair(hilo, resultado));
  this->sem_map.unlock();
}

void Buscador::repartir_tareas() {

  int nlineas = std::count(std::istreambuf_iterator<char>(this->fd), std::istreambuf_iterator<char>(),'\n');
  int i;
  int nlineas_hilo = nlineas/nhilos, linea_i = 0;
  int linea_f = nlineas_hilo;

  for (i = 1; i <= nhilos; i++) {
   this->vector_hilos.push_back(std::thread(&Buscador::escanear_documento, this, linea_i, linea_f, i));

   linea_i = linea_f + 1;
   linea_f += nlineas_hilo;
   if (i == nhilos - 1 ) {
     linea_f = nlineas;
   }
  }

}

int Buscador::buscar() {
  this->mostrar_banner();

  std::cout << MANAGER + " Fichero: " + this->fichero + "\n" +
               MANAGER + " Parabra: " + this->palabra + "\n" +
               MANAGER + " Nº hilos: " + std::to_string(this->nhilos) + "\n" << std::endl;

  this->repartir_tareas();
  this->esperar_hilos();
  return 0;
}

std::map<int, Resultado>  Buscador::get_resultados() {
  return this->resultados;
}

std::string Buscador::get_apariciones(){
  std::string str = MANAGER + " La palabra \e[3;1;31m" + palabra +
             "\e[0m aparece \e[3;1;32m" + std::to_string(this->total_aparciones) +
             "\e[0m veces";
  return str;
}

void Buscador::mostrar_banner() {

  std::cout << "\n" << std::endl;
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
  std::cout << banner6 + "\n" << std::endl;
}
