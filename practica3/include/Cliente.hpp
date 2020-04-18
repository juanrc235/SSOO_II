#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

#include <mutex>

class Cliente {

private:
  Solicitud mi_solicitud;
  std::mutex en_cola;
  int nCliente;

public:
  Cliente (int nCliente);
  Cliente ();
  Solicitud get_solicitud();
  void esperar_taquilla();
};
