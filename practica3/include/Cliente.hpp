#ifndef SOLICITUD
#define SOLICITUD
#include "Solicitud.hpp"
#endif

#include <vector>

class Cliente {

private:
  std::vector<int> mis_asientos;
  Solicitud mi_solicitud;

public:
  Cliente (int nCliente);
  Cliente ();
  Solicitud get_solicitud();
  void set_asientos(std::vector<int> asientos);
};
