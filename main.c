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
	XL_320_socket_t my_socket;
	init_socket(&my_socket,&fake_send);
	XL_320_servo_t my_servo;
	init_servo(&my_servo,0x02,&my_socket);
	//set_led_color_servo(&my_servo,LED_OFF,1);

	return 0;
}
