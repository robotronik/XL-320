#include <stdint.h>
#include <stdio.h>
#include "xl_320.h"

void fake_send(char * buff, uint8_t buff_len)
{
	int i;
	for(i=0;i<buff_len;i++)
	{
			printf("\\x%08x", buff[i]);
	}
	printf("\n");
}

int main(void)
{
	_XL_320_GROUP my_servo_grp = create_servo_grp(&fake_send);
	_XL_320 my_servo=create_servo(0x01,&my_servo_grp);
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
