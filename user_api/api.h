/*
 * api.h
 *
 *  Created on: May 12, 2020
 *      Author: User
 */

#ifndef API_H_
#define API_H_

#include <stdint.h>
#include "cmsis_os.h"

typedef struct
{
	uint8_t _printf_buffer[128];
	uint8_t counter;
} printf_handle_td;

osStatus_t print_to_console(const char *const p_msg);
void delay_us(uint32_t us);

#endif /* API_H_ */
