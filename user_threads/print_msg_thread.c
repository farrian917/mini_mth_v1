/*
 * print_msg_thread.c
 *
 *  Created on: May 14, 2020
 *      Author: User
 */

#include "print_msg_thread.h"
#include "messages.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "link_interface.h"

extern UART_HandleTypeDef huart1;

/// Thread id
static osThreadId_t _print_msg_thread_id;

/// Thread attributes
static const osThreadAttr_t _print_msg_thread_attributes = {
  .name = "print_msg_thread",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 8
};

/**
 * \brief
 */
void print_msg_thread_init(void)
{
	_print_msg_thread_id = osThreadNew(print_msg_thread, NULL, &_print_msg_thread_attributes);

	if(_print_msg_thread_id == NULL)
	{
		/// \todo pprintf
		while(1){}
	}
}

/**
 * \brief
 *
 */
void print_msg_thread(void)
{
	osStatus_t status = osOK;
	osMessageQueueId_t print_msg_message_id = get_print_msg_queue_id();
	uint8_t print_buffer[128] = {[0] = 0};

	while(1)
	{
	    while(osMessageQueueGetCount(print_msg_message_id) > 0)
	    {
			status = osMessageQueueGet(print_msg_message_id, print_buffer, NULL, osWaitForever);   // wait for message
		    if (status == osOK)
		    {
		    	//printf(&print_buffer);
		        HAL_UART_Transmit(&huart1, print_buffer, strlen(print_buffer), 0xFFFF);
		    }
	    }

		osDelay(100);
	}
}
