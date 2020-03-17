#include <iostream>
#include <string>

class Resultado {

  private:
  int num_hilo, l_inicio, l_final;

  public:
    Resultado (int num_hilo, int l_inicio, int l_final);
    void add_resultado(int n_linea, std::string linea);
    void devolver_resultado();

};
