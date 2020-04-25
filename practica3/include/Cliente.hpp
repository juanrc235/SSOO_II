#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

#include <mutex>
#include <condition_variable>

class Cliente {

private:
  Solicitud mi_solicitud;
  std::mutex en_cola;
  int nCliente;

public:
  Cliente (int nCliente);
  Cliente ();
  Solicitud get_solicitud();
  int get_nCliente();
  void generar_solicitud_taquilla();
};
