/*
 * user_hw_abstraction_layer.c
 *
 *  Created on: 22 сент. 2020 г.
 *      Author: User
 */

#include "user_hw_abstraction_layer.h"

#ifdef HAL_SPI_MODULE_ENABLED

user_hw_abstr_status_td user_spi_tx_dma(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout)
{
	user_hw_abstr_status_td user_status = USER_OK;

	HAL_SPI_Transmit_DMA((SPI_HandleTypeDef *)p_interface_handle, p_data, data_size);

	return user_status;
}

user_hw_abstr_status_td user_spi_rx_dma(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout)
{
	user_hw_abstr_status_td user_status = USER_OK;

	HAL_SPI_Receive_DMA((SPI_HandleTypeDef *)p_interface_handle, p_data, data_size);

	return user_status;
}

user_hw_abstr_status_td user_spi_tx_polling(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout)
{
	user_hw_abstr_status_td user_status = USER_OK;

	HAL_SPI_Transmit((SPI_HandleTypeDef *)p_interface_handle, p_data, data_size, timeout);

	return user_status;
}

user_hw_abstr_status_td user_spi_rx_polling(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout)
{
	user_hw_abstr_status_td user_status = USER_OK;

	HAL_SPI_Receive((SPI_HandleTypeDef *)p_interface_handle, p_data, data_size, timeout);

	return user_status;
}

#endif

#ifdef HAL_UART_MODULE_ENABLED

user_hw_abstr_status_td user_uart_tx_dma(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout)
{
	user_hw_abstr_status_td user_status = USER_OK;

	HAL_UART_Transmit_DMA((UART_HandleTypeDef *)p_interface_handle, p_data, data_size);

	return user_status;
}

user_hw_abstr_status_td user_uart_rx_dma(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout)
{
	user_hw_abstr_status_td user_status = USER_OK;

	HAL_UART_Receive_DMA((UART_HandleTypeDef *)p_interface_handle, p_data, data_size);

	return user_status;
}

#endif

user_hw_abstr_status_td user_wait_event_flags(void *const p_interface_events_handle, const uint32_t tx_done_event_flag)
{
	user_hw_abstr_status_td user_status = USER_OK;
	uint32_t event_status = 0;
	osEventFlagsId_t evt_id = p_interface_events_handle;

	event_status = osEventFlagsWait(evt_id, tx_done_event_flag, osFlagsWaitAny, osWaitForever); // wait for complete sending data
	if((event_status & tx_done_event_flag) == 0)
	{
		user_status = USER_ERROR;
	}

	return user_status;
}

//user_hw_abstr_status_td user_gpio_set(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
//user_hw_abstr_status_td user_gpio_get(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);


