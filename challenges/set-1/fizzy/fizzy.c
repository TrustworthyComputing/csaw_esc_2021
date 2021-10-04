#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
uint8_t arr[] = {26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t zero = 0;
  uint8_t one = 1;
  for (int i = 0; i < 27; i++) {
    if (arr[i] != data[i]) {
      simpleserial_put('r', 1, &zero);
      return 0x00;
    }
  }
  simpleserial_put('r', 1, &one); // GOAL
  return 0x01;
}

void swap(uint8_t *xp, uint8_t *yp) {
  uint8_t temp = *xp;
  *xp = *yp;
  *yp = temp;
  volatile int x = 1234;
  for (volatile int i = 0; i < 10; i++) {
    x = x * i;
  }
}

void super_efficient_sort(uint8_t* arr, int n) {
  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}

uint8_t sort(uint8_t* data, uint8_t dlen) {
  trigger_high();
  int n = sizeof(arr)/sizeof(arr[0]);
  super_efficient_sort(arr, n);
  simpleserial_put('r', n, arr);
  trigger_low();
  return 0;
}

int main(void) {

  // WARNING: Do not call verify and sort from the same python process
  // Just call one at a time

  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();
  simpleserial_addcmd('a', 27, verify);
  simpleserial_addcmd('s', 0, sort);

  while(1) {
		simpleserial_get();
  }

  return 0;
}
