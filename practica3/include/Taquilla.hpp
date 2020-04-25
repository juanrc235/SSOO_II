#include <string>
#include <queue>
#include <thread>

#ifndef SOLICITUD
  #define SOLICITUD
  #include "Solicitud.hpp"
#endif

#ifndef CLIENTE
  #define CLIENTE
  #include "Cliente.hpp"
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
  int id;
  std::queue<std::thread> cola;

public:
  Taquilla (int id);
  std::string dibujar_sala();
  bool pedir_asientos(Solicitud s);
};
