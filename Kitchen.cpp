#include <assert.h>
#include <pthread.h>
#include "Kitchen.h"
#include <iostream>

int Kitchen::drinkMilkAndBuyIfNeeded(){
  int toReturn = -1;                          // Initialize toReturn
  l.acquire();                                // Acquire the lock
  // Critical section
  while (milk == 0){                          // While the fridge is empty
    milkBought.wait(&l);                      // Wait until the milk has been bought
  }
  if (rand() % 100 <= 20){                    // If the random number is less than or equal to 20%
    milk = 0;                                 // Drink the milk
  }
  if (milk == 1){                             // If there is milk in the fridge
    toReturn =  1;                            // Most likely one of the roommates already bought the milk
    std::cout << "Milk is in the fridge!\n";  // Because there is milk in the fridge, we print that
  } else {                                    // Else there is no milk in the fridge
    milk = 1;                                 // Buy milk
    toReturn = 0;                             // Since we bought the milk, toReturn is 0
    std::cout << "Off to the store :/\n";     // Prompting that we will buy the milk
  }
  l.release();                                // Relaease the lock
  milkDrank.signal();                         // Signal that the milk can be drank now
  return toReturn;                            // Return who bought the milk
}

Kitchen::Kitchen(){
  milk = 1;                                   // Initializing milk in the fridge
}
