/*
 * mcu_io.h
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */

#ifndef RS485_THREAD_H_
#define RS485_THREAD_H_

#include "cmsis_os.h"

void rs485_thread_init(void);
void rs485_thread(void *argument);
osThreadId_t get_rs485_thread_id(void);

#endif /* RS485_THREAD_H_ */

