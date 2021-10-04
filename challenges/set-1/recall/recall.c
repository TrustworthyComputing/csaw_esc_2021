#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
uint8_t correct_mem[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t mem_different = 0;
  uint8_t zero = 0, one = 1;

  trigger_high();
  for (uint8_t i = 0; i < sizeof(correct_mem); i++) {
    if (correct_mem[i] != data[i]) {
      mem_different = 1;
      break;
    }
  }
  trigger_low();

  if (mem_different) {
    simpleserial_put('r', 1, &zero);
  } else {
    simpleserial_put('r', 1, &one); // GOAL
  }
}

int main(void) {
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  simpleserial_addcmd('a', 16, verify);

  while(1) {
    simpleserial_get();
  }

  return 0;
}
