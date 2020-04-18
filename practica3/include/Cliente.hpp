#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

#include <vector>

class Cliente {

private:
  Solicitud mi_solicitud;

public:
  Cliente (int nCliente);
  Cliente ();
  Solicitud get_solicitud();
};
