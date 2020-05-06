#ifndef SUPPLIER
  #define SUPPLIER
  #include "Supplier.hpp"
#endif

#include <thread>
#include <chrono>

Supplier::Supplier (int id) {
  this->id = id;
}

void Supplier::supply(){
  this->s_supplier.lock();
  std::this_thread::sleep_for (std::chrono::milliseconds(3000));
  this->s_supplier.unlock();
}

int Supplier::get_id() {
  return this->id;
}
