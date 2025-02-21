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
#define UART1_PRINTF_TX_DONE 	(uint32_t)(1 << 0)
#define UART2_RS485_TX_DONE 	(uint32_t)(1 << 1)
#define UART2_RS485_RX_DONE 	(uint32_t)(1 << 2)

#define THREAD_OK_RESPONSE 		(uint32_t)(1 << 0)
#define THREAD_ERROR_RESPONSE 	(uint32_t)(1 << 1)

void init_periph_events(void);
osEventFlagsId_t get_periph_event_id(void);

#endif /* EVENTS_H_ */
