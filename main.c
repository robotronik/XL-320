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
	_XL_320_GROUP servoGroup;
	init_servo_grp(&servoGroup, &fake_send);

	_XL_320 servo;
	init_servo(&servo,0x02, &servoGroup);
	
	set_led_color_servo(servo,LED_BLUE);
	//set_control_mode_servo(my_servo,WHEEL);
	//set_speed_servo(my_servo,512);
	//set_angle_servo(my_servo,422);
	//disable_power_servo(my_servo);
	//set_ID_servo(&my_servo, 0x02);
	//set_torque_servo(my_servo,422);
	//send_instruction_frame(my_servo,WRITE,param,4);
	//send_instruction_frame(my_servo,PING,NULL,0);
	return 0;
}
