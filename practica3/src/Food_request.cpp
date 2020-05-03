#ifndef FOOD_REQUEST
  #define FOOD_REQUEST
  #include "Food_request.hpp"
#endif

#include <string>

Food_request::Food_request (int nDrink, int nPopcorn, int client){
  this->nDrink = nDrink;
  this->nPopcorn = nPopcorn;
  this->client = client;
  this->request_attended = false;
}

Food_request::Food_request (){}

std::string Food_request::to_string(){
  return "FOOD REQUEST :: Drinks: " + std::to_string(this->nDrink)
        + " || Popcorns: " + std::to_string(this->nPopcorn);
}

int Food_request::get_nDrink() {
  return this->nDrink;
}

int Food_request::get_nPopcorn() {
  return this->nPopcorn;
}

int Food_request::get_client() {
  return this->client;
}

void Food_request::attended() {
  this->request_attended = true;
}

bool Food_request::is_attended() {
  return request_attended;
}
