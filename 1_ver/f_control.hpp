#ifndef FCONTROL
#define FCONTROL
#include "dispatcher.hpp"
class FrontController
{
  private:
    Dispatcher d;
  public:
    void request(int x);
};
#endif
