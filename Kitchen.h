#ifndef _KITCHEN_H_
#define _KITCHEN_H_
#include "CV.h"
#include "thread.h"
#include "Lock.h"

class Kitchen{
  Lock l;
  CV milkDrank;
  CV milkBought;
  int milk;

public:
  Kitchen();
  ~Kitchen(){};
  int drinkMilkAndBuyIfNeeded();
};
#endif
