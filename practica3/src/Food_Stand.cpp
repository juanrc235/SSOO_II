#include "Food_Stand.hpp"
#include <iostream>

Food_Stand::Food_Stand (int id, int drink, int popcorn) {
  this->id = id;
  this->nDrink = drink;
  this->nPopcorn = popcorn;
}

int Food_Stand::get_id() {
  return this->id;
}

bool Food_Stand::request_food(Food_request fr) {
  this->s_request.lock();
  if ((fr.get_nDrink() > this->nDrink) || (fr.get_nPopcorn() > this->nPopcorn) ) {
    this->s_request.unlock();
    return false;
  }
  this->nDrink = this->nDrink - fr.get_nDrink();
  this->nPopcorn = this->nPopcorn - fr.get_nPopcorn();
  this->s_request.unlock();
  return true;
}

std::string Food_Stand::to_string() {
  std::string str = "Drinks: " + std::to_string(this->nDrink) + " || Popcorns: " +
  std::to_string(this->nPopcorn);
  return str;
}

void Food_Stand::refill() {
  this->nDrink = 20;
  this->nPopcorn = 20;
}
