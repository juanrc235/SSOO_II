#include <string>

#define FILAS 6
#define COLUMNAS 12

// En la array sala
// 1 ---> ocupado
// 0 ---> libre

class Taquilla {

private:
  int sala[FILAS][COLUMNAS] = {0};

public:
  Taquilla ();
  std::string pedir_asientos();
  std::string dibujar_sala();
};
