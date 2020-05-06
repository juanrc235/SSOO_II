#ifndef FOOD_REQUEST
  #define FOOD_REQUEST
  #include "Food_request.hpp"
#endif
#ifndef SUPPLIER
  #define SUPPLIER
  #include "Supplier.hpp"
#endif
#include <string>
#include <mutex>

class Food_Stand {

private:
  int id;
  int nPopcorn;
  int nDrink;
  void call_supplier();
  std::mutex s_request;

public:
  Food_Stand (int id, int drink, int popcorn);
  int get_id();
  bool request_food(Food_request fr);
  std::string to_string();
  void refill();
};
