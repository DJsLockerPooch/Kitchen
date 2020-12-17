#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "thread.h"
#include "Kitchen.h"

/*
   To compile:
   g++ -Wall -D_POSIX_PTHREAD_SEMANTICS KitchenMain.cpp Kitchen.cpp CV.cpp Lock.cpp thread.c -lpthread
*/

void *drinkSomeMilk(void *milkPointer){
  Kitchen *fridge = (Kitchen *)milkPointer;                   // Setting the milkPointer to a Kitchen variable
  fridge = new Kitchen();                                     // Initilizing our new Kitchen
  fridge->drinkMilkAndBuyIfNeeded();                          // Calling the drinkMilkAndBuyIfNeeded function in our kitchen
  return NULL;                                                // Returning NULL
}

int main(void){
  srand(time(NULL));                                          // Seeding the randomizer
  int numRoom8 = rand() % 8 + 2;                              // Generating a random number between 0-8, and adding 2 to get to 2-10 roommates
  Kitchen *fridge[1];                                         // Creating the kitchen variable
  thread_t roommates[numRoom8];                               // Creating the list of "roommate" threads
  printf("Num roommates: %d\n", numRoom8);                    // Letting the user know how many roo,mates there are

  for (int i = 0; i < numRoom8; i++){                         // For as many roommates as there are
    thread_create_p(&roommates[i], drinkSomeMilk, fridge[0]); // Creating threads with the drinkSomeMilk function and the single fridge
  }

  for (int i = 0; i < numRoom8; i++){                         // For as many roomates as there are
    thread_join(roommates[i]);                                // Join the threads
  }

  for (int i = 0; i < numRoom8; i++){                         // For as many roomates as there are
    int checkForMilk = rand() % 4 + 1;                        // Getting a random number of times each roommate will check the fridge between 1-5
    for (int j = 0; j < checkForMilk; j++){                   // For as many times as the roommate will check the fridge
      drinkSomeMilk(fridge[0]);                               // They will try to drink the milk
    }
  }
  return 1;                                                   // Return 1
}
