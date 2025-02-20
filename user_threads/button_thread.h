/*
 * button_thread.h
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */

#ifndef BUTTON_THREAD_H_
#define BUTTON__THREAD_H_

#include "cmsis_os.h"

void button_thread_init(void);
void button_thread(void *argument);
osThreadId_t get_button_thread_id(void);

#endif /* BUTTON_THREAD_H_ */

