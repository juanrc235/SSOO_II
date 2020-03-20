#include <iostream>
#include <string>
#include <list>
#include "Linea.h"

class Resultado {

  private:
    int num_hilo, l_inicio, l_final;
    std::list<Linea> apariciones;
    std::list<Linea>::iterator itr;

  public:
    Resultado (int num_hilo, int l_inicio, int l_final);
    void add_resultado(int n_linea, std::string linea);
    std::string devolver_resultado();

};
