/*
 * messages.h
 *
 *  Created on: Apr 30, 2020
 *      Author: IVSop
 */

#ifndef USER_MESSAGES_MESSAGES_H_
#define USER_MESSAGES_MESSAGES_H_

#include "cmsis_os.h"

/// Command message structure
typedef struct
{
	uint8_t thread_from;
	uint8_t thread_to;
	uint8_t cmd;
	uint8_t reserved;
	uint32_t data[4];
} cmd_msg_td;

/// Out thread message structure
typedef struct
{
	uint8_t thread_from;
	uint8_t thread_to;
	uint8_t cmd;
	uint8_t reserved;
	uint32_t data[4];
} out_msg_td;

/// Cmd msg for GPIO THREAD
#define CMD_1	(uint8_t)(1)
#define CMD_2 	(uint8_t)(2)
#define CMD_3 	(uint8_t)(3)
#define CMD_4	(uint8_t)(4)
#define CMD_5 	(uint8_t)(5)
#define CMD_6 	(uint8_t)(6)
#define CMD_7	(uint8_t)(7)

void gpio_cmd_msg_queue_init(void);
void gpio_out_msg_queue_init(void);
void print_msg_queue_init(void);

osMessageQueueId_t get_gpio_cmd_msg_queue_id(void);
osMessageQueueId_t get_print_msg_queue_id(void);

#endif /* USER_MESSAGES_MESSAGES_H_ */
