#include "Resultado.h"
#include <fstream>
#include <regex>
#include <thread>
#include <vector>
#include <mutex>

class Buscador {

  private:
    std::string palabra;
    std::string fichero;
    int nhilos;
    int total_aparciones;
    std::mutex sem_map;
    std::map<int, Resultado> resultados;
    std::vector<std::thread> vector_hilos;
    std::regex p;
    std::ifstream fd;
    void esperar_hilos();
    void repartir_tareas();
    void escanear_documento (int inicio, int final, int hilo);
    void mostrar_banner();
    std::string plinea(std::string strlinea);

  public:
    Buscador (std::string palabra, std::string fichero, int nhilos);
    int buscar();
    std::map<int, Resultado>  get_resultados();
    std::string get_apariciones();
    bool test_file();

};
