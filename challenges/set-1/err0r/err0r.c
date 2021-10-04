#include "hal.h"
#include <stdint.h>
#include <stdlib.h>

#include "simpleserial.h"

// DUMMY VAL
uint8_t win_code[] = {0,1,2,3};

uint32_t crc32_for_byte(uint32_t r) {
  for(int j = 0; j < 8; ++j) {
    r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
  }
  return r ^ (uint32_t)0xFF000000L;
}

void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
  static uint32_t table[0x100];
  if(!*table) {
    for(size_t i = 0; i < 0x100; ++i) {
      table[i] = crc32_for_byte(i);
    }
  }
  for(size_t i = 0; i < n_bytes; ++i) {
    *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
  }
}

uint8_t hash_loop(uint8_t* txt, uint8_t len) {
    uint32_t crc = 0;
    uint32_t crc_2 = 0;
    char buf[8]="";
    for(int i=0;i<8;i++){
      buf[i]=txt[i];
    }
    trigger_high();
    crc32(buf, sizeof(buf), &crc);
    crc32(buf, sizeof(buf), &crc_2);
    trigger_low();

    if (crc != crc_2) {
      simpleserial_put('r',4, win_code);
    } else {
      simpleserial_put('r',4 , (uint8_t*)&crc);
    }
    return 0x00;
}

int main(void) {
    platform_init();
    init_uart();
    trigger_setup();

    /* Device reset detected */
    putch('r');
    putch('R');
    putch('E');
    putch('S');
    putch('E');
    putch('T');
    putch(' ');
    putch(' ');
    putch(' ');
    putch('\n');

    simpleserial_init();

    simpleserial_addcmd('h', 8, hash_loop);

    while(1) {
      simpleserial_get();
    }
}
