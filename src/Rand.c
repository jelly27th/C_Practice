#include "Rand.h"
#include <time.h>
#include <windows.h>

// hardware delay generation the random number
bool Rand(unsigned int num)
{
  srand((unsigned)time(NULL));
  Sleep(1000);//delay 1S
  return rand() % num;//scope is 0~(num-1)
}
//generate the random number from lower and upper
int RandInt(int lower, int upper)
{
  srand((unsigned)time(NULL));
  Sleep(1000);//滞后1S
  return rand() % (upper+1-lower)+lower;
}
