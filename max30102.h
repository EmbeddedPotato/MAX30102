#include "stdint.h"
#include "nrf_drv_twi.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "register_map.h"

void twi_init ();

void MAX30102_reset ();
void MAX30102_init ();
void MAX30102_setup ();
void read_fifo ();
