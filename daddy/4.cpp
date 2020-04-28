#include <iostream>

using namespace std;

extern void populate(int* data, unsigned long size);

const unsigned long ARRAY_SIZE = 2048 * 2048;

int d1 [ARRAY_SIZE];

long f1()
{
  populate(d1, ARRAY_SIZE);
  long ret = 0;
  for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
    ret += d1[i];
  }
  return ret;
}

long f2()
{
  int d2 [ARRAY_SIZE];
  populate(d2, ARRAY_SIZE);
  long ret = 0;
  for (unsigned long i = 0; i < ARRAY_SIZE; ++i) {
    ret += d2[i];
  }
  return ret;
}

int main()
{
  cout << f1() << endl;
  cout << f2() << endl;
  return 0;
}
