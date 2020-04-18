#include <mutex>
#ifndef CLIENTE
  #define CLIENTE
  #include "Cliente.hpp"
#endif


class Sistema_pago {

private:
  std::mutex s_pago;

public:
  Sistema_pago();
  bool pagar(Cliente c);

};
