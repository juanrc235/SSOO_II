#ifndef SOLICITUD
#define SOLICITUD
  #include "Ticket_request.hpp"
#endif
#ifndef FOOD_REQUEST
  #define FOOD_REQUEST
  #include "Food_request.hpp"
#endif


class Client {

private:
  Ticket_request ticket_request;
  Food_request food_request;
  int nClient;

public:
  Client (int nClient);
  Client ();
  Ticket_request get_ticket_request();
  Food_request get_foodrequest();
  int get_nClient();
  void generate_ticket_request();
  void generate_food_request();
};
