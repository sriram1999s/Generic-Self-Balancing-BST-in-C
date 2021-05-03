#include <iostream>
using namespace std;
#include "dispatcher.hpp"

void Dispatcher::dispatch(int x)
{
  switch(x)
  {
    case 1:
      v1.disp();
      break;
    case 2:
      v2.disp();
      break;
    default:
      cout << "invalid input\n";
  }
}
