#include <functional>
#include <iostream>

#include "Bindable.h"

int main() {
  Bindable<int> bind1 = 10;
  Bindable<int> bind2 = 20;
  Bindable<int> bind3 = 30;

  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 10
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 20
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 30

  // Subscribing bind2 and bind3 to bind1
  bind1.Subscribe([&]() { return bind2.Value() + bind3.Value(); }, bind2,
                  bind3);

  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 50
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 20
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 30

  // Modifying bind2 will automatically update bind1

  bind2 = 40;

  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 70
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 40
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 30

  // Modifying bind3 will affect bind1 too
  bind3 = 60;

  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 100
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 40
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 60

  // Bind bind1 to bind2, all other bindings are cleared
  bind1 = bind2;

  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 40
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 40
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 60

  bind2 = 20;
  bind3 = 30;

  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 20
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 20
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 30

  bind2 = bind1;
  bind1.Subscribe([&]() { return bind2.Value() + bind3.Value(); }, bind2,
                  bind3);

  // Bind loop detected! More than 2 loops. Aborting update.
  std::cout << "bind1: " << bind1 << " ";        // Output: bind1: 110
  std::cout << "bind2: " << bind2 << " ";        // Output: bind2: 110
  std::cout << "bind3: " << bind3 << std::endl;  // Output: bind3: 30

  return 0;
}
