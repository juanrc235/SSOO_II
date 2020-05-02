#include <string>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include "Client.hpp"

Client::Client (int nClient) {
  this->nClient = nClient;
}

Client::Client () {}

Solicitud Client::get_solicitud() {
  return this->mi_solicitud;
}

int Client::get_nClient() {
  return this->nClient;
}

void Client::generar_solicitud_taquilla() {
  std::srand((unsigned) time(0));
  this->mi_solicitud = Solicitud (this->nClient, (std::rand() % 10)+1);
  // simular generación de solicitud
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
}
