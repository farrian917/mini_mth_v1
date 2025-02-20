/*
 * api.c
 *
 *  Created on: May 12, 2020
 *      Author: User
 */

#include "api.h"
//#include "mutex.h"
#include "periph_interface.h"
#include "link_interface.h"
//#include "printf.h"
#include "events.h"
#include "gpio_io.h"

#define PRINT_BUFFER_SIZE 128
#define PRINT_ADDITIONAL_SYMBOLS 50
#define PRINT_ALLOW_BUFFER_SIZE PRINT_BUFFER_SIZE - PRINT_ADDITIONAL_SYMBOLS

#define CONSOLE_GREEN_YELLOW 	93
#define CONSOLE_YELLOW_COLOR 	33
#define CONSOLE_GREEN_COLOR 	32
#define CONSOLE_RED_COLOR 		31
#define CONSOLE_CYAN_COLOR 		36
#define CONSOLE_DEFAULT_COLOR	39

static printf_handle_td _printf_handle = {{[0] = 0}, .counter = 0};
static interface_data_info_td _interface_console_data_info = {0};
static periph_interface_td *_p_console_interface = NULL;

///**
// * \brief
// *
// */
//void _putchar(char character)
//{
//	_printf_handle._printf_buffer[_printf_handle.counter] = character;
//	_printf_handle.counter++;
//
//	if(character == '\r')
//	{
//		_p_console_interface = get_hard_uart_interface_handle(0);
//
//		// Add last NULL symbol
//		_printf_handle._printf_buffer[_printf_handle.counter] = '\0';
//		_printf_handle.counter++;
//
//		_interface_console_data_info.data_size =_printf_handle.counter;
//		_interface_console_data_info.p_data = _printf_handle._printf_buffer;
//
//		_p_console_interface->write(_p_console_interface, &_interface_console_data_info);
//
//		_printf_handle.counter = 0;
//	}
//}

/**
 * \brief
 *
 */
static osStatus_t _send_message_to_console(uint8_t *p_str)
{
	osStatus_t status = osOK;
	osMessageQueueId_t message_id = get_print_msg_queue_id();

	status = osMessageQueuePut(message_id, p_str, 0U, 0U);

	return status;
}

/**
 * \brief Print some msg to the console.
 * \detaled Print some msg to the console with the next format string - [MSG]
 *
 */
osStatus_t print_to_console(const char *const p_msg)
{
	osStatus_t status = osOK;
	uint8_t print_buffer[PRINT_BUFFER_SIZE];

	/// \todo Check p_thread_name + p_msg size. We have a 64-byte buffer.

	sprintf(print_buffer, "[%s]\n\r", p_msg);
	status = _send_message_to_console(print_buffer);

	return status;
}

/**
 * \brief
 *
 */
void delay_us(uint32_t us)
{
	uint32_t tick = osKernelSysTick();

	while ((osKernelSysTick() - tick) < osKernelSysTickMicroSec(us));
}
