#include "Resultado.h"
#include <string>
#include <map>

class Buscador {

  private:
    std::string palabra;
    std::string fichero;
    int nhilos;
    int total_aparciones;
    std::map<int, Resultado> resultados;
    void esperar_hilos();
    void repatir_tareas();

  public:
    Buscador (std::string palabra, std::string fichero, int nhilos);
    int buscar();
    std::map<int, Resultado>  get_resultados();
    int get_apariciones();

};
