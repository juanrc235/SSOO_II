#include <string>
#include <queue>
#include <thread>
#include <mutex>

#ifndef SOLICITUD
  #define SOLICITUD
  #include "Ticket_request.hpp"
#endif

#ifndef CLIENTE
  #define CLIENTE
  #include "Client.hpp"
#endif

#define ROWS 2 // 6
#define COLUMNS 4 // 12
#define FREE 0
#define NOT_FREE 1

// En la array sala
// 1 ---> ocupado
// 0 ---> libre

class Ticket_Office {

private:
  int sala[ROWS][COLUMNS] = {0};
  int libres;
  int id;
  std::queue<std::thread> cola;
  std::mutex s_seats;

public:
  Ticket_Office (int id);
  std::string dibujar_sala();
  bool pedir_asientos(Ticket_request s);
};
