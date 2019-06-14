/*
  _____  ______ _____ _____  _____ _______ ______ _____        __  __          _____  
 |  __ \|  ____/ ____|_   _|/ ____|__   __|  ____|  __ \      |  \/  |   /\   |  __ \ 
 | |__) | |__ | |  __  | | | (___    | |  | |__  | |__) |     | \  / |  /  \  | |__) |
 |  _  /|  __|| | |_ | | |  \___ \   | |  |  __| |  _  /      | |\/| | / /\ \ |  ___/ 
 | | \ \| |___| |__| |_| |_ ____) |  | |  | |____| | \ \      | |  | |/ ____ \| |     
 |_|  \_\______\_____|_____|_____/   |_|  |______|_|  \_\     |_|  |_/_/    \_\_|  

*/



#include <stdint.h>

#define MAX30102_ADDRESS	0x57

#define 	REV_ID			 ((uint8_t)0xFE)
#define 	PART_ID 		 ((uint8_t)0xFF)


#define		INT_STATUS_1	 ((uint8_t)0x00)
#define 	INT_STATUS_2	 ((uint8_t)0x01)
#define 	INT_ENABLE_1	 ((uint8_t)0x02)
#define 	INT_ENABLE_2	 ((uint8_t)0x03)
#define		FIFO_WR_PTR		 ((uint8_t)0x04)
#define		OVERFLOW_CTR	 ((uint8_t)0x05)
#define		FIFO_RD_PTR		 ((uint8_t)0x06)
#define		FIFO_DATA			 ((uint8_t)0x07)
#define		FIFO_CONF		 ((uint8_t)0x08)
#define		MODE_CONF		 ((uint8_t)0x09)
#define 	SPO2_CONF		 ((uint8_t)0X0A)
#define 	LED1_PA			 ((uint8_t)0x0C)
#define 	LED2_PA			 ((uint8_t)0x0D)
#define 	PILOT_PA		 ((uint8_t)0x10)
#define		MULTILED_1	 ((uint8_t)0x11)
#define 	MULTILED_2	 ((uint8_t)0x12)

#define 	TEMP_INTR		 0x1F
#define		TEMP_FRAC		 0x20
#define		TEMP_CONF		 0x21
#define		PROX_INT_TH	 0x30

