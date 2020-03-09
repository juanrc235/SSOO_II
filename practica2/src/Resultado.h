#include <iostream>
#include <string>

class Resultado {

  private:
  int num_hilo, l_inicio, l_final;

  public:
    Resultado (int num_hilo, int l_inicio, int l_final);
    void add_resultado(int n_linea, std::string linea);
    void imprimir_resultado();
};

Resultado::Resultado (int num_hilo, int l_inicio, int l_final) {
  this->num_hilo = num_hilo;
  this->l_inicio = l_inicio;
  this->l_final = l_final;
}

void Resultado::imprimir_resultado() {
  std::cout << "Hola\n";
}
