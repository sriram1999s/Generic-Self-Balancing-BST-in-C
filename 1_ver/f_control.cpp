#include <iostream>
using namespace std;
#include "f_control.hpp"

void FrontController::request(int x)
{
  d.dispatch(x);
}
