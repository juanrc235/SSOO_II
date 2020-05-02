#include <mutex>
#ifndef CLIENTE
  #define CLIENTE
  #include "Client.hpp"
#endif

class Payment_system {

private:
  std::mutex s_pago;

public:
  Payment_system();
  bool pagar(Client c);

};
