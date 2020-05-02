#ifndef SOLICITUD
#define SOLICITUD
  #include "Ticket_request.hpp"
#endif

#include <mutex>
#include <condition_variable>

class Client {

private:
  Solicitud mi_solicitud;
  std::mutex en_cola;
  int nClient;

public:
  Client (int nClient);
  Client ();
  Solicitud get_solicitud();
  int get_nClient();
  void generar_solicitud_taquilla();
};
