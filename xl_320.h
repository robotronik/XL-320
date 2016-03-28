#ifndef XL_320_H
#define	XL_320_H

#define XL_320_HEADER 0xFFFFFD00
#define BROADCAST_ID 0xFE

typedef struct {
	void (*SEND_FUNC)(char *,uint8_t);
	uint8_t ID_LIST[253];
	uint8_t LEN;
} _XL_320_GROUP;

typedef struct {
	_XL_320_GROUP * GROUP;
	uint8_t ID;
} _XL_320;

typedef struct{
	union {
		struct {
			uint32_t HEADER;
		};
		struct {
			uint8_t RES;
			uint8_t H_BYTE1;
			uint8_t H_BYTE2;
			uint8_t H_BYTE3;
		};
	};
	uint8_t ID;
	union {
		struct {
			uint16_t LEN;
		};
		struct {
			uint8_t LEN_L;
			uint8_t LEN_H;
		};
	};
	uint8_t INSTR;
	uint8_t * PARAM;
	//uint8_t PARAM_LEN; usefull ?
	union {
		struct {
			uint16_t CRC;
		};
		struct {
			uint8_t CRC_L;
			uint8_t CRC_H;
		};
	};
} _INSTR_FRAME;

//http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm
typedef enum {
	MODEL_NUMBER,
	FIRMWARE_VERSION,
	ID,
	BAUDRATE,
	RETURN_DELAY_TIME,
	CW_ANGLE_LIMIT,
	CCW_ANGLE_LIMIT,
	CONTROL_MODE,
	LIMIT_TEMPERATURE,
	LOWER_LIMIT_VOLTAGE,
	UPPER_LIMIT_VOLTAGE,
	MAX_TORQUE,
	RETURN_LEVEL,
	ALARM_SHUTDOWN,
	TORQUE_ENABLE,
	LED,
	D_GAIN,
	I_GAIN,
	P_GAIN,
	GOAL_POSITION,
	GOAL_VELOCITY,
	GOAL_TORQUE,
	PRESENT_POSITION,
	PRESENT_SPEED,
	PRESENT_LOAD,
	PRESENT_VOLTAGE,
	PRESENT_TEMPERATURE,
	REGISTERED_INSTRUCTION,
	MOVING,
	HDW_ERROR_STATUS,
	PUNCH,
	NBR_FIELD, //just to know the total number
} _XL_320_FIELD;

//http://support.robotis.com/en/product/dynamixel/xl-320/xl-320.htm#Actuator_Address_19
typedef enum {
	LED_RED=0b001,
	LED_GREEN=0b010,
	LED_YELLOW=0b011,
	LED_BLUE=0b100,
	LED_PINK=0b101,
	LED_BLUE_GREEN=0b110,
	LED_WHITE=0b111,
} _LED_COLOR;

typedef enum {
	WHEEL=1,
	JOIN=2,
} _CONTROL_MODE;

//http://support.robotis.com/en/product/dynamixel_pro/communication/instruction_status_packet.htm
typedef enum {
	PING=0x01,
	READ=0x02,
	WRITE=0x03,
	REG_WRITE=0x04,
	ACTION=0x05,
	FACTORY_RESET=0x06,
	REBOOT=0x08,
	STATUS=0x55,
	SYNC_READ=0x82,
	SYNC_WRITE=0x83,
	BULK_READ=0x92,
	BULK_WRITE=0x93,
} _XL_320_INSTRUCTION;

void set_data_group(_XL_320_GROUP group, _XL_320_FIELD data, uint16_t value, uint8_t now);
void set_data_servo(_XL_320 servo, _XL_320_FIELD data, uint16_t value, uint8_t now);
void launch_previous_action(_XL_320_GROUP * group);
void set_led_color_servo(_XL_320 servo, _LED_COLOR color);
void set_control_mode_servo(_XL_320 servo, _CONTROL_MODE mode);
void set_speed_servo(_XL_320 servo, uint16_t speed);
void set_angle_servo(_XL_320 servo, uint16_t angle);
void set_torque_servo(_XL_320 servo, uint16_t angle);
void set_ID_servo(_XL_320 * servo, uint8_t new_ID);
void enable_power_servo(_XL_320 servo);
void disable_power_servo(_XL_320 servo);
_XL_320_GROUP create_servo_grp(void (*send_function)(char *,uint8_t));
_XL_320 create_servo(uint8_t ID, _XL_320_GROUP * root_group);
void send_instruction_frame(uint8_t target_ID, _XL_320_GROUP * group, _XL_320_INSTRUCTION instr, uint8_t * param, uint8_t param_len);
unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);

#endif	/* XL_320 */
