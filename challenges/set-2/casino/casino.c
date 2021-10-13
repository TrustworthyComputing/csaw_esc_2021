#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"

// Correct values but random permutation.
uint8_t arr[] = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150};

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t result = 1;
  for (int i = 0; i < 15; i++) {
    result *= (arr[i] == data[i]);
  }
  simpleserial_put('r', 1, &result); // GOAL is to output 1
  return result;
}

void draw(uint8_t* arr, int n) {
  volatile int x = 1234;
  for (int i = 0; i < n; i++) {
    for (volatile int j = 0; j < arr[i]; j++) {
      x = x * j;
    }
  }
}

uint8_t casino(uint8_t* data, uint8_t dlen) {
  trigger_high();
  int n = sizeof(arr)/sizeof(arr[0]);
  draw(arr, n);
  simpleserial_put('r', n, arr);
  trigger_low();
  return 0;
}

int main(void) {

  // WARNING: Do not call verify and casino from the same python process
  // Just call one at a time

  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();
  simpleserial_addcmd('a', 16, verify);
  simpleserial_addcmd('s', 0, casino);
  while(1) {
		simpleserial_get();
  }

  return 0;
}
