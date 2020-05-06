#include <mutex>

class Supplier {
private:
  int id;
  std::mutex s_supplier;

public:
  Supplier (int id);
  void supply();
  int get_id();
};
