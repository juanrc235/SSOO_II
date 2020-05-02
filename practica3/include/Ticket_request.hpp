#include <string>

class Ticket_request {

private:
  int nCliente;
  int nAsientos;

public:
  Ticket_request (int nCliente, int nAsientos);
  Ticket_request ();
  std::string to_string();
  int get_nCliente();
  int get_nAsientos();
};
