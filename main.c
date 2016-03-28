#include <stdint.h>
#include <stdio.h>
#include "xl_320.h"

int main(void)
{
	uint8_t param[]={GOAL_VELOCITY,0x00,0xFF,0x00};
	_INSTR_FRAME test=build_instruction_frame(WRITE,0x01 /*BROADCAST_ID*/,param,4);
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
	return 0;
}
