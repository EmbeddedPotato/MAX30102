/** @file
 * @defgroup MAX30102.c
 * @{
 * @brief MAX30102 I2C basic driver
 *
 * 
 *
 */

#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "MAX30102.h"


int main(void)
{
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool detected_device = false;
		
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();


    twi_init();

	//uint32_t red_led[100];
	//uint32_t ir_led[100];

	MAX30102_init();
	MAX30102_reset();
 	MAX30102_setup ();

	while(1){
	
	read_fifo();
		nrf_delay_ms(50);
	
	}
}