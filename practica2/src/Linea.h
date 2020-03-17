#include <iostream>
#include <string>

class Linea {

  private:
  int nlinea;
  std::string strlinea;

  public:
    Linea (int nlinea, std::string strlinea);
    Linea ();
    int get_nlinea();
    std::string get_strlinea();

};
