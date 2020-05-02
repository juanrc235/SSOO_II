#include <string>

class Solicitud {

private:
  int nCliente;
  int nAsientos;

public:
  Solicitud (int nCliente, int nAsientos);
  Solicitud ();
  std::string to_string();
  int get_nCliente();
  int get_nAsientos();
};
