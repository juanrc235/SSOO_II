#include "Buscador.h"

/* TODO
  - control de errores argumentos
  - dividirlo .... p1 palabra p2 ...
  - destructores
*/

int main(int argc, char const *argv[]) {

  std::string palabra(argv[1]);
  std::string fichero(argv[2]);
  std::stringstream str;
  str <<  argv[3];
  int nhilos;
  str >> nhilos;

  Buscador mi_buscador(palabra, fichero, nhilos);
  mi_buscador.buscar();

  for (const auto &entry: mi_buscador.get_resultados()) {
		auto key = entry.second;
	  std::cout << key.devolver_resultado() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

  std::cout << mi_buscador.get_apariciones() + "\n" << std::endl;

  return 0;
}
