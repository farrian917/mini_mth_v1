/*
 * link_interface.c
 *
 *  Created on: May 7, 2020
 *      Author: IVSop
 */

#include "link_interface.h"
#include "user_hw_abstraction_layer.h"

static gpio_interface_td _gpio_interface_handle_array[GPIO_INTERFACE_HANDLE_SIZE];
static periph_interface_td _sw_spi_interface_handle_array[SW_SPI_INTERFACE_HANDLE_SIZE];
static periph_interface_td _hw_spi_interface_handle_array[HW_SPI_INTERFACE_HANDLE_SIZE];
static periph_interface_td _sw_i2c_interface_handle_array[SW_I2C_INTERFACE_HANDLE_SIZE];
static periph_interface_td _hw_i2c_interface_handle_array[HW_I2C_INTERFACE_HANDLE_SIZE];
static periph_interface_td _hw_uart_interface_handle_array[HW_UART_INTERFACE_HANDLE_SIZE];

/**
 * \brief
 *
 */
void link_periph_interface(periph_interface_td *p_periph_interface,
							const void * p_interface_events_handle,
							const uint32_t tx_done_event_flag,
							const uint32_t rx_done_event_flag,
							interface_type_td interface_type,
							interface_ic_addr_type_td ic_addr_type,
							void * const p_low_lvl_interface_handle,
							p_interface_write_ftd write_func,
							p_interface_read_ftd read_func,
							p_delay_us_ftd delay_func)
{
	p_periph_interface->console_send = NULL;
	p_periph_interface->delay_us = delay_func;
	p_periph_interface->params.interface_type = interface_type;
	p_periph_interface->params.ic_addr_type = ic_addr_type;
	p_periph_interface->params.p_interface_handle = p_low_lvl_interface_handle;
	p_periph_interface->read = read_func;
	p_periph_interface->write = write_func;

	p_periph_interface->interface_events_handle.p_interface_events_handle = p_interface_events_handle;
	p_periph_interface->interface_events_handle.tx_done_events_flags = tx_done_event_flag;
	p_periph_interface->interface_events_handle.rx_done_events_flags = rx_done_event_flag;
}

/**
 * \brief
 *
 */
void link_gpio_interface(gpio_interface_td *p_gpio_interface, p_gpio_set_ftd set_func, p_gpio_get_ftd get_func)
{
	p_gpio_interface->gpio_get = get_func;
	p_gpio_interface->gpio_set = set_func;
}

#if (GPIO_INTERFACE_HANDLE_SIZE > 0)

/**
 * \brief
 *
 */
gpio_interface_td *get_gpio_interface_handle(const uint8_t handle_number)
{
	gpio_interface_td *p_handle = NULL;

	if(!(handle_number > (GPIO_INTERFACE_HANDLE_SIZE - 1)))
	{
		p_handle = &_gpio_interface_handle_array[handle_number];
	}

	return p_handle;
}

#endif

#if (SW_SPI_INTERFACE_HANDLE_SIZE > 0)

/**
 * \brief
 *
 */
periph_interface_td *get_soft_spi_interface_handle(const uint8_t handle_number)
{
	periph_interface_td *p_handle = NULL;

	if(!(handle_number > (SW_SPI_INTERFACE_HANDLE_SIZE - 1)))
	{
		p_handle = &_sw_spi_interface_handle_array[handle_number];
	}

	return p_handle;
}

#endif

#if (HW_SPI_INTERFACE_HANDLE_SIZE > 0)

/**
 * \brief
 *
 */
periph_interface_td *get_hard_spi_interface_handle(const uint8_t handle_number)
{
	periph_interface_td *p_handle = NULL;

	if(!(handle_number > (HW_SPI_INTERFACE_HANDLE_SIZE - 1)))
	{
		p_handle = &_hw_spi_interface_handle_array[handle_number];
	}

	return p_handle;
}

#endif

#if (SW_I2C_INTERFACE_HANDLE_SIZE > 0)

/**
 * \brief
 *
 */
periph_interface_td *get_soft_i2c_interface_handle(const uint8_t handle_number)
{
	periph_interface_td *p_handle = NULL;

	if(!(handle_number > (SW_I2C_INTERFACE_HANDLE_SIZE - 1)))
	{
		p_handle = &_sw_i2c_interface_handle_array[handle_number];
	}

	return p_handle;
}

#endif

#if (HW_I2C_INTERFACE_HANDLE_SIZE > 0)

/**
 * \brief
 *
 */
periph_interface_td *get_hw_spi_interface_handle(const uint8_t handle_number)
{
	periph_interface_td *p_handle = NULL;

	if(!(handle_number > (HW_I2C_INTERFACE_HANDLE_SIZE - 1)))
	{
		p_handle = &_hw_i2c_interface_handle_array[handle_number];
	}

	return p_handle;
}

#endif

#if (HW_UART_INTERFACE_HANDLE_SIZE > 0)

/**
 * \brief
 *
 */
periph_interface_td *get_hard_uart_interface_handle(const uint8_t handle_number)
{
	periph_interface_td *p_handle = NULL;

	if(!(handle_number > (HW_UART_INTERFACE_HANDLE_SIZE - 1)))
	{
		p_handle = &_hw_uart_interface_handle_array[handle_number];
	}

	return p_handle;
}

#endif

