#ifndef DISPATCHER
#define DISPATCHER
#include "view1.hpp"
#include "view2.hpp"

class Dispatcher
{
  private:
    View1 v1;
    View2 v2;
  public:
    void dispatch(int );
};

#endif
