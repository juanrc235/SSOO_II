#include <string>

class Solicitud {

private:
  int nCliente;
  int nAsientos;
  std::string zona_v;
  std::string zona_h;

public:
  Solicitud (int nCliente, int nAsientos, std::string zona_v, std::string zona_h);
  std::string to_string();
  int get_nCliente();
  int get_nAsientos();
  std::string get_zonaV();
  std::string get_zonaH();
};
