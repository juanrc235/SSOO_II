#include <string>

class Food_request {
private:
  int nDrink;
  int nPopcorn;

public:
  Food_request (int nDrink, int nPopcorn);
  Food_request ();
  std::string to_string();
  int get_nDrink();
  int get_nPopcorn();
};
