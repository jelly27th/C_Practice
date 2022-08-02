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