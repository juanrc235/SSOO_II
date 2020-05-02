#ifndef FOOD_REQUEST
  #define FOOD_REQUEST
  //#include "Food_request.hpp"
#endif

#define MAX_FOOD 20
#define MAX_POPCORNS 20

class Food_Stand {

private:
  int id;
  int nPopcorn;
  int nDrink;
  // Supplier supplier;
  void call_supplier();

public:
  Food_Stand (int id);
  int get_id();
  //void request_food(Food_request fr);
};
