/*
 * messages.c
 *
 *  Created on: Apr 30, 2020
 *      Author: IVSop
 */

#include "messages.h"

static osMessageQueueId_t _gpio_cmd_msg_queue_id = 0;
#define GPIO_CMD_MSGQUEUE_OBJECTS				(uint8_t)(2)
#define GPIO_CMD_MSGQUEUE_OBJECT_SIZE			sizeof(cmd_msg_td)//sizeof(uint8_t)

static osMessageQueueId_t _gpio_out_msg_queue_id = 0;
#define GPIO_OUT_MSGQUEUE_OBJECTS				(uint8_t)(2)
#define GPIO_OUT_MSGQUEUE_OBJECT_SIZE			sizeof(out_msg_td)//sizeof(uint8_t)

static osMessageQueueId_t _print_msg_queue_id = 0;
#define PRINT_MSGQUEUE_OBJECTS					(uint8_t)(16)
#define PRINT_MSGQUEUE_OBJECT_SIZE 					128

/**
 * \brief
 *
 */
void gpio_cmd_msg_queue_init(void)
{
	_gpio_cmd_msg_queue_id = osMessageQueueNew(GPIO_CMD_MSGQUEUE_OBJECTS, GPIO_CMD_MSGQUEUE_OBJECT_SIZE, NULL);

	if (_gpio_cmd_msg_queue_id == NULL)
	{
	 // Message Queue object not created, handle failure
	  /// \todo printf
		while(1){}
	}
}

/**
 * \brief
 *
 */
void gpio_out_msg_queue_init(void)
{
	_gpio_out_msg_queue_id = osMessageQueueNew(GPIO_OUT_MSGQUEUE_OBJECTS, GPIO_OUT_MSGQUEUE_OBJECT_SIZE, NULL);

	if (_gpio_out_msg_queue_id == NULL)
	{
	 // Message Queue object not created, handle failure
	  /// \todo printf
		while(1){}
	}
}

/**
 * \brief
 *
 */
void print_msg_queue_init(void)
{
	_print_msg_queue_id = osMessageQueueNew(PRINT_MSGQUEUE_OBJECTS, PRINT_MSGQUEUE_OBJECT_SIZE, NULL);

	if (_print_msg_queue_id == NULL)
	{
	 // Message Queue object not created, handle failure
	  /// \todo printf
		while(1){}
	}
}

/**
 * \brief
 *
 */
osMessageQueueId_t get_gpio_cmd_msg_queue_id(void)
{
	return _gpio_cmd_msg_queue_id;
}

/**
 * \brief
 *
 */
osMessageQueueId_t get_gpio_out_msg_queue_id(void)
{
	return _gpio_out_msg_queue_id;
}

/**
 * \brief
 *
 */
osMessageQueueId_t get_print_msg_queue_id(void)
{
	return _print_msg_queue_id;
}
