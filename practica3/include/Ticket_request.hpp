#include <string>
#include <mutex>

class Ticket_request {

private:
  int nCliente;
  int nAsientos;
  bool attended;


public:
  Ticket_request (int nCliente, int nAsientos);
  Ticket_request ();
  std::string to_string();
  int get_nCliente();
  int get_nAsientos();
  bool is_attended();
  void set_not_attended();
  //void can_continue();
};
