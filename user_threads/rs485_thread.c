/*
 * rs485_thread.c
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */
#include "periph_interface.h"
#include "link_interface.h"
#include "gpio_interface.h"
#include "rs485_thread.h"
//#include "cmd_handlers.h"
#include "periph_io.h"
//#include "board_hw.h"
//#include "commands.h"
#include "callback.h"
//#include "messages.h"
#include "gpio_io.h"
//#include "mcu_io.h"
#include "string.h"
#include "api.h"
#include "rs485.h"
#include "user_hw_abstraction_layer.h"

/// Thread name
#define RS485_THREAD_NAME "rs485_th"

/// Thread id
static osThreadId_t _rs485_thread_id;

/// Thread attributes
static const osThreadAttr_t _rs485_thread_attributes = {
  .name = RS485_THREAD_NAME,
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 16
};

/**
 * \brief
 *
 */
void rs485_thread_init(void)
{
	_rs485_thread_id = osThreadNew(rs485_thread, NULL, &_rs485_thread_attributes);

	if(_rs485_thread_id == NULL)
	{
		/// \todo pprintf
	}
}

/**
 * \brief
 *
 */
void rs485_thread (void *argument)
{
	rs485_status_td io_status = RS485_OK;

	uint8_t buffer[16] = {0}; // 16 is only for tests
	//periph_interface_td *p_rs485_interface = get_hard_uart_interface_handle(1);
	uint8_t response_data_buffer[4];
	uint8_t response_data_size = 0;

	rs485_params_td rs485h;

	rs485_init(&rs485h, get_hard_uart_interface_handle(1), get_gpio_interface_handle(0), GPIO_RS485_DIR);

//	rs485h.huart = get_hard_uart_interface_handle(1);
//	rs485h.hgpio = get_gpio_interface_handle(0);
//	rs485h.dir_pin = GPIO_RS485_DIR;

//	set_cb_sr485_thread_id(_rs485_thread_id);

//	print_to_console("RS485 THREAD STARTED!");

	//print_operation_status_to_console(io_status, RS485_THREAD_NAME, "Thread started");

	while(1)
	{
		/// reset command packet header for the next receive operation
		memset(&buffer, 0, sizeof(buffer));

		print_to_console("RS485 WAIT FOR MSG!");
		io_status = rs485_read(&rs485h, buffer);

		if(io_status == RS485_OK)
		{
			print_to_console("MSG FROM RS485 WAS GOT WITH 16 BYTES!");
			rs485_write_str(&rs485h, "^_^");
		}

		osDelay(10);
	}
}

/**
 * \brief
 *
 */
osThreadId_t get_rs485_thread_id(void)
{
	return _rs485_thread_id;
}
