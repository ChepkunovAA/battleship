#include <iostream>
#include "App.hpp"


int main() {
  ConsoleInterface interface;
  App my_app(interface);
  my_app.Execute();
  return 0;
}
