#include "Resultado.h"
#include <string>

Resultado::Resultado (int num_hilo, int l_inicio, int l_final) {
  this->num_hilo = num_hilo;
  this->l_inicio = l_inicio;
  this->l_final = l_final;
  this->itr = this->apariciones.begin();
}

void Resultado::add_resultado(int nlinea, std::string strlinea){
  Linea linea_aparicion (nlinea, strlinea);
  this->apariciones.insert(itr, linea_aparicion);
}

int Resultado::get_subtotal() {
  return this->apariciones.size();
}

std::string Resultado::devolver_resultado() {
  std::string cabecera = "[HILO " +
                          std::to_string(this->num_hilo) +
                          " :: Inicio: " + std::to_string(this->l_inicio) +
                          " -- Final: " + std::to_string(l_final) + "] ";
  std::string salida;
  Linea tmp();
  for(this->itr = apariciones.begin(); this->itr != apariciones.end(); this->itr++) {
    salida += cabecera + " :: línea " + std::to_string((*itr).get_nlinea())
                       + " :: " + (*itr).get_strlinea() + "\n";
  }
  return salida;
}
