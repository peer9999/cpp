#include <iostream>

void f(int (& mass)[15][20],int x,int y) {
  mass[1][1] = 42;
}

int main() {
  int mass[15][20] = { 0 };
  f(mass,15,20);
  std::cout << mass[1][1] << std::endl;
  return 0;
}
