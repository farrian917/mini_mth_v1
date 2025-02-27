/*
 * callback.c
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */

//#include "mcu_io.h"
#include "cmsis_os.h"
#include "stm32f1xx_hal.h"
#include "link_interface.h"
#include "main.h"
#include "gpio_interface.h"
#include "events.h"

static osThreadId_t _rs485_thread_id;
static osEventFlagsId_t _periph_event_id;

#ifdef HAL_SPI_MODULE_ENABLED
/**
 * \brief
 *
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	SPI_HandleTypeDef *p_hal_spi_handle = NULL;

	p_hal_spi_handle = (SPI_HandleTypeDef *) get_hard_spi_interface_handle(0);

	if(p_hal_spi_handle == hspi)
	{
		osEventFlagsSet(_periph_event_id, SPI1_TX_DONE);
	}
}

/**
 * \brief
 *
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	SPI_HandleTypeDef *p_hal_spi_handle = NULL;

	p_hal_spi_handle = (SPI_HandleTypeDef *) get_hard_spi_interface_handle(0);

	if(p_hal_spi_handle == hspi)
	{
		osEventFlagsSet(_periph_event_id, SPI1_RX_DONE);
	}
}
#endif

#ifdef HAL_UART_MODULE_ENABLED
/**
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UART_HandleTypeDef *p_hal_uart_handle = NULL;
	periph_interface_td *p_user_interface_h = get_hard_uart_interface_handle(1);

	p_hal_uart_handle = (UART_HandleTypeDef *)p_user_interface_h->params.p_interface_handle;

	if(huart == p_hal_uart_handle)
	{
		osEventFlagsSet(_periph_event_id, UART2_RS485_RX_DONE);
	}
	else
	{
		///callback for printf uart
	}
}

/**
 *
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UART_HandleTypeDef *p_hal_uart_handle = NULL;
	periph_interface_td *p_user_interface_h = get_hard_uart_interface_handle(1);

	p_hal_uart_handle = (UART_HandleTypeDef *)p_user_interface_h->params.p_interface_handle;

	if(huart == p_hal_uart_handle)
	{
		osEventFlagsSet(_periph_event_id, UART2_RS485_TX_DONE);
	}
	else
	{
		osEventFlagsSet(_periph_event_id, UART1_PRINTF_TX_DONE);
	}
}
#endif

/**
 *
 */
void set_cb_sr485_thread_id(osThreadId_t thread_id)
{
	_rs485_thread_id = thread_id;
}

/**
 *
 */
void set_cb_periph_event_id(osEventFlagsId_t event_id)
{
	_periph_event_id = event_id;
}

