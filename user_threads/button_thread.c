/*
 * button_thread.c
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */

#include "button_thread.h"
#include "api.h"
#include "user_hw_abstraction_layer.h"

/// Thread name
#define BUTTON_THREAD_NAME "button_th"

/// Thread id
static osThreadId_t _button_thread_id;

/// Thread attributes
static const osThreadAttr_t _button_thread_attributes = {
  .name = BUTTON_THREAD_NAME,
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};

/**
 * \brief
 *
 */
void button_thread_init(void)
{
	_button_thread_id = osThreadNew(button_thread, NULL, &_button_thread_attributes);

	if(_button_thread_id == NULL)
	{
		/// \todo pprintf
	}
}

/**
 * \brief
 *
 */
void button_thread (void *argument)
{
	print_to_console("Buttons thread was started!");

	while(1)
	{
		if(!(GPIOB->IDR & GPIO_IDR_IDR1))
		{
			print_to_console("User button 0 was pushed!");
		}

		if(!(GPIOA->IDR & GPIO_IDR_IDR15))
		{
			print_to_console("User button 1 was pushed!");
		}

		osDelay(10);
	}
}

/**
 * \brief
 *
 */
osThreadId_t get_mcu_io_thread_id(void)
{
	return _button_thread_id;
}
