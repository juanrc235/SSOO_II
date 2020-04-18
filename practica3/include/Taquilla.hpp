#include <string>
#include <queue>
#include <thread>

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
  bool pedir_asientos(Solicitud s);

public:
  Taquilla ();
  std::string dibujar_sala();
  void abrir();
};
