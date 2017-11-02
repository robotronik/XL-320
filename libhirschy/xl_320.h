/*
 * Librairie XL-320 @Robotronik
 * xl_320.h
 * Ecrit pour un µC en little-endian
 * Il est autorisé de rager librement avec ce fichier.
 */
#ifndef XL_320_HEADER
#define XL_320_HEADER

#include <stdint.h>

#define XL_320_BUFFER_SIZE 256

typedef enum XL_320_Instruction_E{
  PING = 0x01,
  READ = 0x02,
  WRITE = 0x03,
  REG_WRITE = 0x04,
  ACTION = 0x05,
  FACTORY_RESET = 0x06,
  REBOOT = 0x08,
  STATUS = 0x55,
  SYNC_READ = 0x82,
  SYNC_WRITE = 0x83,
  BULK_READ = 0x92,
  BULK_WRITE = 0x93
}XL_320_Instruction;

uint8_t build_frame(uint8_t id, uint8_t instruction, uint8_t *params, uint8_t nb_params, uint8_t buffer[256]);
//Contrôle de redondance cyclique
uint16_t update_crc(uint16_t crc_accum, uint8_t *data_blk_ptr, uint16_t data_blk_size);

#endif
