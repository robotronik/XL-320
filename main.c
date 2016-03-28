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
	send_instruction_frame(my_servo,WRITE,param,4);
	send_instruction_frame(my_servo,PING,NULL,0);
	return 0;
}
