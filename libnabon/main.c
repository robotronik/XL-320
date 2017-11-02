#include <stdint.h>
#include <stdio.h>
#include "xl_320.h"

void fake_send1(char * buff, uint8_t buff_len)
{
	int i;
	printf("fake_send1 :");
	for(i=0;i<buff_len;i++)
	{
			printf("\\x%02hhX", buff[i]);
	}
	printf("\n");
}

void fake_send2(char * buff, uint8_t buff_len)
{
	int i;
	printf("fake_send2 :");
	for(i=0;i<buff_len;i++)
	{
			printf("\\x%02hhX", buff[i]);
	}
	printf("\n");
}

int main(void)
{
	XL_320_socket_t my_socket1;
	init_socket(&my_socket1,&fake_send1);
	XL_320_servo_t my_servo1;
	init_servo(&my_servo1,0x02,&my_socket1);
	XL_320_socket_t my_socket2;
	init_socket(&my_socket2,&fake_send2);
	XL_320_servo_t my_servo2;
	init_servo(&my_servo2,0x02,&my_socket2);
	XL_320_servo_t my_servo3;
	init_servo(&my_servo3,0x02,&my_socket2);
	XL_320_group_t my_group;
	init_group(&my_group);
	add_servo_to_group(&my_servo1,&my_group);
	add_servo_to_group(&my_servo2,&my_group);
	add_servo_to_group(&my_servo3,&my_group);
	send_data_group(&my_group,LED,LED_BLUE,0);
	launch_previous_action(&my_group);
	set_led_color_servo(&my_servo1,LED_OFF,1);

	return 0;
}
