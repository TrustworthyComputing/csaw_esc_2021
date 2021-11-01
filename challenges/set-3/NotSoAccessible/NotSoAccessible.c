#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../simpleserial/simpleserial.h"

// DUMMY VAL
static const uint16_t round_keys[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
  18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void simon_encrypt(uint16_t* ctxt) {
  const uint8_t rounds = 32;
  const uint16_t word_size = 16;

  for(uint8_t i = 0; i < rounds; i++) {
    if (i == 25) {
      trigger_high();
    }
    uint16_t rol_1 = (ctxt[1] << 1) | (ctxt[1] >> (word_size - 1));
    uint16_t rol_2 = (ctxt[1] << 2) | (ctxt[1] >> (word_size - 2));
    uint16_t rol_8 = (ctxt[1] << 8) | (ctxt[1] >> (word_size - 8));

    uint16_t temp = (rol_1 & rol_8) ^ ctxt[0] ^ rol_2;
    ctxt[0] = ctxt[1];
    ctxt[1] = temp ^ round_keys[i];
    if (i == 25) {
      trigger_low();
    }
  }
}

void simon_decrypt(uint16_t* ptxt) {
  const uint8_t rounds = 32;
  const uint16_t word_size = 16;

  for(int8_t i = rounds - 1; i >= 0; i--) {
    uint16_t rol_1 = (ptxt[0] << 1) | (ptxt[0] >> (word_size - 1));
    uint16_t rol_2 = (ptxt[0] << 2) | (ptxt[0] >> (word_size - 2));
    uint16_t rol_8 = (ptxt[0] << 8) | (ptxt[0] >> (word_size - 8));

    uint16_t temp = (rol_1 & rol_8) ^ ptxt[1] ^ rol_2;
    ptxt[1] = ptxt[0];
    ptxt[0] = temp ^ round_keys[i];
  }
}

uint8_t encrypt(uint8_t* data, uint8_t dlen) {
  uint16_t ctxt[2] = {0,0};
  for (int i = 0; i < 2; i++) {
    ctxt[0] += ((uint16_t)(data[i] << 8*i) & 0xFFFF);
    ctxt[1] += ((uint16_t)(data[i+2] << 8*i) & 0xFFFF);
  }
  simon_encrypt(ctxt);
  for (int i = 0; i < 2; i++) {
    data[i] = (uint8_t)(ctxt[0] >> 8*i) & 0xFF;
    data[i+2] = (uint8_t)(ctxt[1] >> 8*i) & 0xFF;
  }
  simpleserial_put('r', 4, data);
  return 0x00;
}

uint8_t decrypt(uint8_t* data, uint8_t dlen) {
  uint16_t ptxt[2] = {0,0};
  for (int i = 0; i < 2; i++) {
    ptxt[0] += ((uint16_t)(data[i] << 8*i) & 0xFFFF);
    ptxt[1] += ((uint16_t)(data[i+2] << 8*i) & 0xFFFF);
  }
  simon_decrypt(ptxt);
  for (int i = 0; i < 2; i++) {
    data[i] = (uint8_t)(ptxt[0] >> 8*i) & 0xFF;
    data[i+2] = (uint8_t)(ptxt[1] >> 8*i) & 0xFF;
  }
  simpleserial_put('r', 4, data);
  return 0x00;
}

uint8_t verify(uint8_t* data, uint8_t dlen) {
  uint8_t result = 1;
  uint8_t* last_rkey;
  for (int i = 0; i < dlen; i++) {
    last_rkey[i] = (round_keys[31] >> 8*i) & 0xFF;
    result *= (last_rkey[i] == data[i]);
  }
  simpleserial_put('r', 1, &result); // GOAL is to output 1
}


int main(void) {
  // RG9lcyBTQVR1cm4gaGF2ZSAyNiByaW5ncz8=
  // OOPS! Half of the secret key was leaked: 0x19181110...
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  simpleserial_addcmd('e', 4, encrypt);
  simpleserial_addcmd('d', 4, decrypt);
  simpleserial_addcmd('a', 2, verify);

  while(1) simpleserial_get();

  return 0;
}
