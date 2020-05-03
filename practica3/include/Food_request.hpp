#include <string>

class Food_request {
private:
  int nDrink;
  int nPopcorn;
  int client;
  bool request_attended;

public:
  Food_request (int nDrink, int nPopcorn, int client);
  Food_request ();
  std::string to_string();
  int get_nDrink();
  int get_nPopcorn();
  int get_client();
  bool is_attended();
  void attended();
};
