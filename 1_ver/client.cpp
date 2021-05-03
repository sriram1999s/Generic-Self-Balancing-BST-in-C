#include <iostream>
using namespace std;
#include "f_control.hpp"

int main()
{
  FrontController f;
  f.request(1);
  f.request(2);
  f.request(3);
}
