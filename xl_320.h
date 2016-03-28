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
	_XL_320_GROUP GROUP;
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
	MODEL_NUMBER=0,
	FIRMWARE_VERSION=2,
	ID=3,
	BAUDRATE=4,
	RETURN_DELAY_TIME=5,
	CW_ANGLE_LIMIT=6,
	CCW_ANGLE_LIMIT=8,
	CONTROL_MODE=11,
	LIMIT_TEMPERATURE=12,
	LOWER_LIMIT_VOLTAGE=13,
	UPPER_LIMIT_VOLTAGE=14,
	MAX_TORQUE=15,
	RETURN_LEVEL=17,
	ALARM_SHUTDOWN=18,
	TORQUE_ENABLE=24,
	LED=25,
	D_GAIN=27,
	I_GAIN=28,
	P_GAIN=29,
	GOAL_POSITION=30,
	GOAL_VELOCITY=32,
	GOAL_TORQUE=35,
	PRESENT_POSITION=37,
	PRESENT_SPEED=39,
	PRESENT_LOAD=41,
	PRESENT_VOLTAGE=45,
	PRESENT_TEMPERATURE=46,
	REGISTERED_INSTRUCTION=47,
	MOVING=49,
	HDW_ERROR_STATUS=50,
	PUNCH=51,
} _XL_320_ADRR;

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

void set_led_color_servo(_XL_320 servo, _LED_COLOR color);
void set_control_mode_servo(_XL_320 servo, _CONTROL_MODE mode);
void set_speed_servo(_XL_320 servo, uint16_t speed);
_XL_320_GROUP create_servo_grp(void (*send_function)(char *,uint8_t));
_XL_320 create_servo(uint8_t ID, _XL_320_GROUP * group);
void send_instruction_frame(_XL_320 servo, _XL_320_INSTRUCTION instr, uint8_t * param, uint8_t param_len);
unsigned short update_crc(unsigned short crc_accum, unsigned char *data_blk_ptr, unsigned short data_blk_size);

#endif	/* XL_320 */
