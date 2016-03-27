#include <stdint.h>
#include <stdio.h>
#include "xl_320.h"

int main(void)
{
	uint8_t param[]={LED,0x00,LED_RED};
	_INSTR_FRAME test=build_instruction_frame(WRITE,0x01 /*BROADCAST_ID*/,param,3);
	_INSTR_FRAME ping=build_instruction_frame(PING,0x01 /*BROADCAST_ID*/,NULL,0);
	char instr_buff[255];
	uint8_t instr_buff_len; 
	get_instruction_string(test, instr_buff,255, &instr_buff_len);
	int i;
	for(i=0;i<instr_buff_len;i++)
	{
			printf("\\x%08x",instr_buff[i]);
	}
	printf("\n");
	printf("0x%08x\n",test.LEN_H);
	uint8_t data_blk[11]={0xFF,0xFF,0xFD,0x00,0xFE,0x06,0x00,0x03,0x25,0x00,0x03};
	printf("0x%08x\n",update_crc(0,data_blk,11));
	return 0;
}
