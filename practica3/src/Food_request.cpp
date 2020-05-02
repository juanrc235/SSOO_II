#ifndef FOOD_REQUEST
  #define FOOD_REQUEST
  #include "Food_request.hpp"
#endif

#include <string>

Food_request::Food_request (int nDrink, int nPopcorn){
  this->nDrink = nDrink;
  this->nPopcorn = nPopcorn;
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
