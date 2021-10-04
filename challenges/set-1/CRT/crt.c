#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include "../simpleserial/simpleserial.h"

uint64_t modular_mul(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t result = 0;
    for (uint64_t current_term = a; b; b >>= 1) {
        if (b & 1) {
            result = (result + current_term) % mod;
        }
        current_term = 2 * current_term % mod;
    }
    return result;
}

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    for (uint64_t current_factor = base; exp; exp >>= 1) {
        if (exp & 1) {
            result = modular_mul(result, current_factor, mod);
        }
        current_factor = modular_mul(current_factor, current_factor, mod);
    }
    return result;
}

static void rsa(int x)
{
  // GOAL: Can you find P and Q?
  
  // ACTUAL VALUES HAVE BEEN REDACTED
  uint64_t p = 0x123456789;
  uint64_t q = 0x987654321;
  uint64_t dp = 0x123456789;
  uint64_t dq = 0x987654321;

  // // CRT Decryption
  uint64_t mp = mod_exp(x, dp, p);
  uint64_t mq = mod_exp(x, dq, q);

  // Transmit mp and mq
  uint8_t out[16];
  for (int i = 0; i < 8; i++) {
    out[i] = (mp >> (8*i)) & 0xFF;
    out[i+8] = (mq >> (8*i)) & 0xFF;
  }
  simpleserial_put('r', 16, out);
}

uint8_t rsa_init(uint8_t* data, uint8_t dlen)
{
  int ptxt = 0;
  for (int i = 0; i < dlen; i++) {
    ptxt += (data[i] << (i*8));
  }
  trigger_high();
  rsa(ptxt);
  trigger_low();

  return 0x00;
}

int main(void)
{
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  simpleserial_addcmd('s', 4, rsa_init);

  while(1)
		simpleserial_get();
  return 0;
}
