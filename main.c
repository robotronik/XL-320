#include <stdint.h>
#include <stdio.h>
#include "xl_320.h"

void fake_send(char * buff, uint8_t buff_len)
{
	int i;
	for(i=0;i<buff_len;i++)
	{
			printf("\\x%02hhX", buff[i]);
	}
	//printf("\n");
}

int main(void)
{
	_XL_320_GROUP my_servo_grp;
	init_servo_group(&my_servo_grp,&fake_send);
	_XL_320 my_servo;
	init_servo(&my_servo,0x02,&my_servo_grp);
	set_led_color_servo(&my_servo,LED_OFF,1);

	return 0;
}
