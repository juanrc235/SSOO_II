#include <string>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#ifndef CLIENTE
  #define CLIENTE
  #include "Client.hpp"
#endif

Client::Client (int nClient) {
  this->nClient = nClient;
}

Client::Client () {}

Ticket_request Client::get_ticket_request() {
  return this->ticket_request;
}

Food_request Client::get_foodrequest() {
  return this->food_request;
}

int Client::get_nClient() {
  return this->nClient;
}

void Client::generate_ticket_request() {
  std::srand((unsigned) time(0));
  this->ticket_request = Ticket_request (this->nClient, (std::rand() % 10)+1);
  // sleep for simulation purpose
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
}

void Client::generate_food_request() {
  std::srand((unsigned) time(0));
  this->food_request = Food_request((std::rand() % 5)+1, (std::rand() % 5)+1, this->nClient);
  // sleep for simulation purpose
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
}
