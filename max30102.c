#include "MAX30102.h"
#include "nrf_drv_twi.h"


/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif

static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/**
 * @brief TWI initialization.
 */
void twi_init (void)
{
    ret_code_t err_code;
    const nrf_drv_twi_config_t twi_config = {
       .scl                = 24,
       .sda                = 22,
       .frequency          = NRF_DRV_TWI_FREQ_400K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi);
}


uint32_t read_register(uint8_t reg, uint8_t * p_data, uint32_t length)
{
    uint32_t err_code;
    err_code = nrf_drv_twi_tx(&m_twi, MAX30102_ADDRESS, &reg, 1, false);
    if(err_code != NRF_SUCCESS) return err_code;

    
    err_code = nrf_drv_twi_rx(&m_twi, MAX30102_ADDRESS, p_data, length);
    if(err_code != NRF_SUCCESS) return err_code;
    return err_code;
}

uint32_t write_register(uint8_t reg_address, uint8_t data)
{
    ret_code_t err_code; 
    uint8_t buffer_send[2] = {reg_address, data};
		
    err_code = nrf_drv_twi_tx(&m_twi, MAX30102_ADDRESS, buffer_send, sizeof(buffer_send), true);
    APP_ERROR_CHECK(err_code);
	
}

void MAX30102_reset (void)
{	
	
    write_register(MODE_CONF, 0x40);	
	
}


void MAX30102_setup (void)
{
	write_register(INT_ENABLE_1, 0xC0);
	write_register(INT_ENABLE_2, 0x00);
	
	
	write_register(FIFO_WR_PTR, 0x00);	// Reset FIFO Write pointer
	write_register(OVERFLOW_CTR, 0x00); // Reset OVERFLOW_CTR pointer
	write_register(FIFO_RD_PTR, 0x00); 	// Reset FIFO READ pointer
	
	write_register(FIFO_CONF, 0x4F); //average sampling  = 4
	write_register(MODE_CONF, 0x03); // ADC range = 4096nA | Sampling Rate = 100 Hz | LED pulseWidth = 411uS
	
	write_register(SPO2_CONF, 0x27); // 400 samples per second
	write_register(LED1_PA, 0x5F); // LED1 current = 19 mA 
	write_register(LED2_PA, 0x5F); // LED2 current = 19 mA 
	write_register(PILOT_PA, 0x7F); // Pilot LED ~ 25mA
	
	
}


void MAX30102_init (void)
{

    uint8_t revID; 
    uint8_t partID;
		ret_code_t err_code;
    err_code  = read_register (PART_ID, &partID,sizeof(partID));
		APP_ERROR_CHECK(err_code);
	
    NRF_LOG_INFO("MAX30102 PART ID: 0x%02x \r\n", partID);
    
	
    err_code = read_register (REV_ID, &revID,sizeof(revID));
		APP_ERROR_CHECK(err_code);
	
    NRF_LOG_INFO("MAX30102 REV ID: 0x%02x \r\n", revID);
}


void read_fifo()
{

    uint8_t clearINT1;
		uint8_t clearINT2;
    uint32_t LEDdata=0;
    uint8_t dataArray[6];
    ret_code_t err_code;
    uint8_t FIFO_data;
    
		//Clear Interrupts
    err_code = read_register(INT_STATUS_1, &clearINT1,sizeof(clearINT1));
		err_code = read_register(INT_STATUS_1, &clearINT2,sizeof(clearINT2));
  
		
		err_code =read_register(FIFO_DATA,dataArray,sizeof(dataArray));
    APP_ERROR_CHECK(err_code);	
		
		//Extract 3 bytes for IR LED
    LEDdata=dataArray[0]<<16|dataArray[1]<<8 |dataArray[2];
  
		NRF_LOG_RAW_INFO("%d,",LEDdata) ;	   // RED LED data		

    LEDdata=0;

		//Extract 3 bytes for RED LED
    LEDdata=dataArray[3]<<16|dataArray[4]<<8 |dataArray[5];
  	NRF_LOG_RAW_INFO("%d\r\n", LEDdata);	// IR LED data
		
}