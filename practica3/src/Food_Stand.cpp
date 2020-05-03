#include "Food_Stand.hpp"

Food_Stand::Food_Stand (int id) {
  this->id = id;
  this->nDrink = MAX_DRINKS;
  this->nPopcorn = MAX_POPCORNS;
}

int Food_Stand::get_id() {
  return this->id;
}

void Food_Stand::request_food(Food_request fr) {
  if ((fr.get_nDrink() > this->nDrink) || (fr.get_nPopcorn() > this->nPopcorn) ) {
    // hacer esperar
    call_supplier();
  }
  this->nDrink -= fr.get_nDrink();
  this->nPopcorn -= fr.get_nPopcorn();
}

void Food_Stand::call_supplier() {

}
