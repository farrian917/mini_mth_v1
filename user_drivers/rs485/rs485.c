
#include "rs485.h"
#include <stdint.h>

/**
 * \brief
 * \p_params[in]
 *
 */
void static _rs_485_dir_set(rs485_params_td *p_params, rs485_dir_td dir)
{
	uint32_t pin = p_params->dir_pin;

	switch(dir)
	{
		case RS485_RX:
			p_params->hgpio->gpio_set(pin, GPIO_FALSE);
			break;

		case RS485_TX:
			p_params->hgpio->gpio_set(pin, GPIO_TRUE);
			break;
	}
}

/**
 * \brief
 * \p_params[in]
 *
 */
uint32_t rs485_read(rs485_params_td *p_params, uint8_t * p_data)
{
	rs485_status_td status = RS485_OK;
	//uint8_t print_buffer[128];
	interface_data_info_td interface_data_read_write;

	//sprintf(print_buffer, "[%s]\n\r", p_msg);

	interface_data_read_write.p_data = p_data;
	interface_data_read_write.data_size = 16; // 16 is only for tests

	_rs_485_dir_set(p_params, RS485_RX);

	p_params->huart->read(p_params->huart, &interface_data_read_write);

	return status;
}


/**
 * \brief
 * \p_params[in]
 *
 */
rs485_status_td rs485_write_str(rs485_params_td *p_params, const char *const p_msg)
{
	rs485_status_td status = RS485_OK;
	uint8_t print_buffer[128];
	interface_data_info_td interface_data_read_write;
	
	sprintf(print_buffer, "[%s]\n\r", p_msg);

	interface_data_read_write.p_data = print_buffer;
	interface_data_read_write.data_size = strlen(print_buffer);

	_rs_485_dir_set(p_params, RS485_TX);

	p_params->huart->write(p_params->huart, &interface_data_read_write);

	return status;
}

/**
 * \brief
 * \p_params[in]
 *
 */
rs485_status_td rs485_init(rs485_params_td *p_params,
							periph_interface_td  * const p_interface,
							gpio_interface_td * const hgpio,
							uint32_t dir_pin_number)
{
	rs485_status_td status = RS485_OK;

	p_params->huart = p_interface;
	p_params->hgpio = hgpio;
	p_params->dir_pin = dir_pin_number;

	return status;
}

