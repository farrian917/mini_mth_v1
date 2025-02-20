/*
 * callback.h
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */

#ifndef CALLBACK_H_
#define CALLBACK_H_

#include "cmsis_os.h"

void set_cb_mcu_io_thread_id(osThreadId_t thread_id);
void set_cb_periph_event_id(osEventFlagsId_t event_id);

#endif /* CALLBACK_H_ */
