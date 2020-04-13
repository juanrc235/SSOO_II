#include <string>
#include <vector>

#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

#define FILAS 6
#define COLUMNAS 12
#define ASIENTO_LIBRE 0
#define ASIENTO_OCUPADO 1

// En la array sala
// 1 ---> ocupado
// 0 ---> libre

class Taquilla {

private:
  int sala[FILAS][COLUMNAS] = {0};
  int libres;

public:
  Taquilla ();
  bool pedir_asientos(Solicitud s);
  std::string dibujar_sala();
};
