#include "Buscador.h"
#include <string>

/* TODO
  - dividirlo .... p1 palabra p2 ...
*/

int main(int argc, char const *argv[]) {

  std::string err_msg = "\e[1;31m[ERROR]\e[0m ";

  if (argc != 4) {
    std::cout << err_msg + "Uso: SSOOGLEII <palabra> <fichero> <nhilos>" << std::endl;
    return 0;
  }

  std::string palabra(argv[1]);
  std::string fichero(argv[2]);
  std::stringstream str;
  str <<  argv[3];
  int nhilos;
  str >> nhilos;

  if (nhilos < 1) {
    std::cout << err_msg + "El número de hilos debe ser un número mayor que uno" << std::endl;
    return 0;
  }

  Buscador mi_buscador(palabra, fichero, nhilos);

  if (!mi_buscador.test_file()) {
    std::cout << err_msg + "El fichero <" + fichero + "> no se puede abrir." << std::endl;
    return 0;
  }

  mi_buscador.buscar();

  std::cout << mi_buscador.get_apariciones() + "\n" << std::endl;

  for (const auto &entry: mi_buscador.get_resultados()) {
		auto key = entry.second;
    std::cout << key.devolver_resultado() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

  return 0;
}
