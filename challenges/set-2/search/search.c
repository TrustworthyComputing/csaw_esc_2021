#include "hal.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "../simpleserial/simpleserial.h"

#define DELAY 10

uint8_t arr[257] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
  18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
  35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68,
  69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
  86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
  103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
  117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130,
  131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144,
  145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158,
  159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
  173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186,
  187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200,
  201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214,
  215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228,
  229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
  243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 0
};

#if SS_VER == SS_VER_2_1
uint8_t verify(uint8_t cmd, uint8_t scmd, uint8_t dlen, uint8_t* data)
#else
uint8_t verify(uint8_t* data, uint8_t dlen)
#endif
{
  uint8_t zero = 0, one = 1;
  bool allmatch = true;
  for (int i = 0; i < 6; i++) {
    bool onematch = false;
    for (int j = 0; j < 6; j++) {
      if (arr[250+j] == data[i]) {
        onematch = true;
      }
    }
    if (!onematch) {
      allmatch = false;
    }
  }
  if (allmatch) {
    simpleserial_put('r', 1, &one); // GOAL
  } else {
    simpleserial_put('r', 1, &zero);
  }
  return allmatch ? 0x01 : 0x00;
}

uint8_t binarySearch(uint8_t l, uint8_t r, uint8_t x) {
  volatile uint8_t mid = l + (r - l) / 2;
  if (r >= l) {
    // If the element is present at the middle itself
    if (arr[mid] == x) return mid;

    // If element is smaller than mid, then
    // it can only be present in left subarray
    if (arr[mid] > x) return binarySearch(l, mid - 1, x);

    // Else the element can only be present in right subarray
    return binarySearch(mid + 1, r, x);
  }
  // We reach here when element is not present in array
  return -1;
}

void remove_six(void) {
  for (uint8_t i = 1 ; i <= 6; i++) {
    uint8_t rep = rand();
    arr[256] = arr[rep];
    memmove(&arr[rep], &arr[rep+1], (256-rep)*sizeof(arr[0]));
  }
}

#if SS_VER == SS_VER_2_1
uint8_t search(uint8_t cmd, uint8_t scmd, uint8_t dlen, uint8_t* data)
#else
uint8_t search(uint8_t* data, uint8_t dlen)
#endif
{
  trigger_high();
  binarySearch(0, 249, data[0]);
  trigger_low();
  return 0;
}

int main(void) {
  platform_init();
  init_uart();
  trigger_setup();
  simpleserial_init();

  int key = 0xdeadbeef; // DUMMY VAL

  srand(key);
  remove_six();

  simpleserial_addcmd('a', 6, verify);
  simpleserial_addcmd('s', 1, search);

  while(1) simpleserial_get();
  return 0;
}
