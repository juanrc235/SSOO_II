#include "Linea.h"
#include <string>

Linea::Linea (int nlinea, std::string strlinea) {
  this->nlinea = nlinea;
  this->strlinea = strlinea;
}

int Linea::get_nlinea(){
  return this->nlinea;
}

std::string Linea::get_strlinea(){
  return this->strlinea;
}
