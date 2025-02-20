/*
 * events.h
 *
 *  Created on: 8 мая 2020 г.
 *      Author: IVSop
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include "cmsis_os.h"

/// Global event flags
#define SPI1_TX_DONE 			(uint32_t)(1 << 0)
#define SPI1_RX_DONE 			(uint32_t)(1 << 1)
#define UART1_PRINTF_TX_DONE 	(uint32_t)(1 << 2)
#define UART2_MCU_IO_TX_DONE 	(uint32_t)(1 << 3)
#define UART2_MCU_IO_RX_DONE 	(uint32_t)(1 << 4)

/// Event flags for I2C1 THREAD
#define I2C1_AD5272_GET_FH_VOLTAGE (uint32_t)(1 << 0)

#define THREAD_OK_RESPONSE 		(uint32_t)(1 << 0)
#define THREAD_ERROR_RESPONSE 	(uint32_t)(1 << 1)

void init_periph_events(void);
osEventFlagsId_t get_periph_event_id(void);

#endif /* EVENTS_H_ */
