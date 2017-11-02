#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "xl_320.h"

int main(){
  uint8_t buffer[256];
  uint8_t params[8] = {0xFF, 0xFD, 0xFD, 0xFF, 0xFF, 0xFF, 0xFD, 0x87};
  uint8_t size = build_frame(0x04, 0xFF, params, 8, buffer);
  uint8_t i;
  for(i=0; i < size; i++){
    printf("0x%2.2X ", buffer[i]);
  }
  printf("\n");
  return EXIT_SUCCESS;
}
