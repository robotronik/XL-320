#include <stdint.h>
#include "xl_320.h"

//http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm
static const uint8_t  field_addr[NBR_FIELD]= {
	[MODEL_NUMBER]=0,
	[FIRMWARE_VERSION]=2,
	[ID]=3,
	[BAUDRATE]=4,
	[RETURN_DELAY_TIME]=5,
	[CW_ANGLE_LIMIT]=6,
	[CCW_ANGLE_LIMIT]=8,
	[CONTROL_MODE]=11,
	[LIMIT_TEMPERATURE]=12,
	[LOWER_LIMIT_VOLTAGE]=13,
	[UPPER_LIMIT_VOLTAGE]=14,
	[MAX_TORQUE]=15,
	[RETURN_LEVEL]=17,
	[ALARM_SHUTDOWN]=18,
	[TORQUE_ENABLE]=24,
	[LED]=25,
	[D_GAIN]=27,
	[I_GAIN]=28,
	[P_GAIN]=29,
	[GOAL_POSITION]=30,
	[GOAL_VELOCITY]=32,
	[GOAL_TORQUE]=35,
	[PRESENT_POSITION]=37,
	[PRESENT_SPEED]=39,
	[PRESENT_LOAD]=41,
	[PRESENT_VOLTAGE]=45,
	[PRESENT_TEMPERATURE]=46,
	[REGISTERED_INSTRUCTION]=47,
	[MOVING]=49,
	[HDW_ERROR_STATUS]=50,
	[PUNCH]=51,
};

static const uint8_t  field_len[NBR_FIELD]= {
	[MODEL_NUMBER]=2,
	[FIRMWARE_VERSION]=1,
	[ID]=1,
	[BAUDRATE]=1,
	[RETURN_DELAY_TIME]=1,
	[CW_ANGLE_LIMIT]=2,
	[CCW_ANGLE_LIMIT]=2,
	[CONTROL_MODE]=1,
	[LIMIT_TEMPERATURE]=1,
	[LOWER_LIMIT_VOLTAGE]=1,
	[UPPER_LIMIT_VOLTAGE]=1,
	[MAX_TORQUE]=2,
	[RETURN_LEVEL]=1,
	[ALARM_SHUTDOWN]=1,
	[TORQUE_ENABLE]=1,
	[LED]=1,
	[D_GAIN]=1,
	[I_GAIN]=1,
	[P_GAIN]=1,
	[GOAL_POSITION]=2,
	[GOAL_VELOCITY]=2,
	[GOAL_TORQUE]=2,
	[PRESENT_POSITION]=2,
	[PRESENT_SPEED]=2,
	[PRESENT_LOAD]=2,
	[PRESENT_VOLTAGE]=1,
	[PRESENT_TEMPERATURE]=1,
	[REGISTERED_INSTRUCTION]=1,
	[MOVING]=1,
	[HDW_ERROR_STATUS]=1,
	[PUNCH]=2,
};


void set_led_color_servo(_XL_320 servo, _LED_COLOR color)
{
	uint8_t param[]={LED, 0x00, color};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,3);
}

void set_control_mode_servo(_XL_320 servo, _CONTROL_MODE mode)
{
	uint8_t param[]={CONTROL_MODE, 0x00, mode};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,3);
}

void set_speed_servo(_XL_320 servo, uint16_t speed)
{
	uint8_t param[]={GOAL_VELOCITY,0x00, (uint8_t) speed,(uint8_t) (speed>>8)};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,4);
}

void set_angle_servo(_XL_320 servo, uint16_t angle)
{
	uint8_t param[]={GOAL_POSITION,0x00, (uint8_t) angle,(uint8_t) (angle>>8)};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,4);
}

void set_torque_servo(_XL_320 servo, uint16_t angle)
{
	uint8_t param[]={GOAL_TORQUE,0x00, (uint8_t) angle,(uint8_t) (angle>>8)};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,4);
}

void set_ID_servo(_XL_320 * servo, uint8_t new_ID)
{
	uint8_t param[]={ID, 0x00, new_ID};
	send_instruction_frame(servo->ID,servo->GROUP,WRITE,param,3);
	servo->ID=new_ID;
}

void enable_power_servo(_XL_320 servo)
{
	uint8_t param[]={TORQUE_ENABLE, 0x00, 1};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,3);
}

void disable_power_servo(_XL_320 servo)
{
	uint8_t param[]={TORQUE_ENABLE, 0x00, 0};
	send_instruction_frame(servo.ID,servo.GROUP,WRITE,param,3);
}

void add_servo_to_group(_XL_320 servo, _XL_320_GROUP * group)
{
	group->ID_LIST[group->LEN]=servo.ID;
	group->LEN+=1;
}

_XL_320_GROUP create_servo_grp(void (*send_function)(char *,uint8_t))
{
	_XL_320_GROUP group;
	group.SEND_FUNC=send_function;
	group.LEN=0;
	return group;
}

_XL_320 create_servo(uint8_t ID, _XL_320_GROUP * root_group)
{
	_XL_320 servo;
	servo.ID=ID;
	servo.GROUP=root_group;
	add_servo_to_group(servo,root_group);
	return servo;
}

void get_instruction_string(_INSTR_FRAME instruction, char * instr_buff, int max_len, uint8_t * instr_buff_len)
{
	if (max_len<7+instruction.LEN)
	{
		return;
	}
	instr_buff[0]=(char) instruction.H_BYTE3;
	instr_buff[1]=(char) instruction.H_BYTE2;
	instr_buff[2]=(char) instruction.H_BYTE1;
	instr_buff[3]=(char) instruction.RES;
	instr_buff[4]=(char) instruction.ID;
	instr_buff[5]=(char) instruction.LEN_L;
	instr_buff[6]=(char) instruction.LEN_H;
	instr_buff[7]=(char) instruction.INSTR;
	int i;
	for(i=0;i<instruction.LEN-3;i++)
	{
		instr_buff[8+i]=instruction.PARAM[i];
	}
	//TODO : add byte stuffing
	uint16_t crc=update_crc(0,(unsigned char*) instr_buff,5+instruction.LEN);
	instruction.CRC=crc;
	instr_buff[5+instruction.LEN]=instruction.CRC_L;
	instr_buff[5+instruction.LEN+1]=instruction.CRC_H;

	*instr_buff_len=7+instruction.LEN;
	
	return;
}

_INSTR_FRAME build_instruction_frame(_XL_320_INSTRUCTION instruction, uint8_t device_id, uint8_t * parameters, uint8_t parameters_length)
{
	_INSTR_FRAME frame;
	frame.HEADER=XL_320_HEADER;
	frame.ID=device_id;
	frame.INSTR= (uint8_t) instruction;
	frame.LEN=parameters_length+3;
	frame.PARAM=parameters;
	return frame;
}

void send_instruction_frame(uint8_t target_ID, _XL_320_GROUP * group, _XL_320_INSTRUCTION instr, uint8_t * param, uint8_t param_len)
{
	_INSTR_FRAME frame=build_instruction_frame(instr, target_ID, param, param_len);
	uint8_t max_len=param_len+10+(param_len+2)/3;
	char buff[max_len];
	uint8_t final_len;
	get_instruction_string(frame,buff,max_len,&final_len);
	group->SEND_FUNC(buff,final_len);
}

//code from : http://support.robotis.com/en/product/dynamixel_pro/communication/crc.htm
unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size)
{
	unsigned short i, j;
	unsigned short crc_table[256] = {
		0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
		0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
		0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
		0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
		0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
		0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
		0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
		0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
		0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
		0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
		0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
		0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
		0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
		0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
		0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
		0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
		0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
		0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
		0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
		0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
		0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
		0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
		0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
		0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
		0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
		0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
		0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
		0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
		0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
		0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
		0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
		0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202};

	for(j = 0; j < data_blk_size; j++)
	{
		i = ((unsigned short)(crc_accum >> 8) ^ data_blk_ptr[j]) & 0xFF;
		crc_accum = (crc_accum << 8) ^ crc_table[i];
	} 

	return crc_accum;
}
