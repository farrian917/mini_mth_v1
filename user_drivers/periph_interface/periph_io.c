
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "periph_io.h"
#include "gpio_interface.h"
#include "gpio_io.h"
#include "events.h"
#include "cmsis_os.h"
#include "main.h"
#include "user_hw_abstraction_layer.h"

///
#define UART_TIMEOUT 	(uint32_t)(5000)
#define SPI_TIMEOUT 	(uint32_t)(5000)
#define I2C_TIMEOUT 	(uint32_t)(5000)
#define TIMEOUT_NONE 	(uint32_t)(0)

/**
 * \brief
 *
 */
static void _i2c_soft_start(soft_i2c_interface_td *p_soft_i2c_interface_handle, p_delay_us_ftd delay_us)
{
	gpio_brd_label_td scl_pin = p_soft_i2c_interface_handle->gpio_i2c_scl;
	gpio_brd_label_td sda_pin = p_soft_i2c_interface_handle->gpio_i2c_sda;
	p_gpio_set_ftd gpio_set_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_set;
	p_gpio_get_ftd gpio_get_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_get;

	gpio_set_func(sda_pin, GPIO_TRUE);
	delay_us(100);
	gpio_set_func(scl_pin, GPIO_TRUE);
	delay_us(100);

	while(!gpio_get_func(sda_pin))
	{
		gpio_set_func(scl_pin, GPIO_FALSE);
		delay_us(100);
		gpio_set_func(scl_pin, GPIO_TRUE);
		delay_us(100);
	}

	gpio_set_func(sda_pin, GPIO_FALSE);
	delay_us(100);
	gpio_set_func(scl_pin, GPIO_FALSE);
	delay_us(100);
}

/**
 * \brief
 *
 */
static void _i2c_soft_stop(soft_i2c_interface_td *p_soft_i2c_interface_handle, p_delay_us_ftd delay_us)
{
	gpio_brd_label_td scl_pin = p_soft_i2c_interface_handle->gpio_i2c_scl;
	gpio_brd_label_td sda_pin = p_soft_i2c_interface_handle->gpio_i2c_sda;
	p_gpio_set_ftd gpio_set_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_set;

	gpio_set_func(sda_pin, GPIO_FALSE);
	delay_us(100);
	gpio_set_func(scl_pin, GPIO_TRUE);
	delay_us(100);
	gpio_set_func(sda_pin, GPIO_TRUE);
	delay_us(100);
}

/**
 * \brief
 *
 */
static uint8_t _i2c_soft_read_byte(soft_i2c_interface_td *p_soft_i2c_interface_handle, p_delay_us_ftd delay_us, uint8_t ack)
{
	uint8_t i = 0;
	uint8_t data = 0;

	gpio_brd_label_td gpio_clk_pin = p_soft_i2c_interface_handle->gpio_i2c_scl;
	gpio_brd_label_td gpio_sda_pin = p_soft_i2c_interface_handle->gpio_i2c_sda;
	p_gpio_set_ftd gpio_set_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_set;
	p_gpio_get_ftd gpio_get_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_get;

	gpio_set_func(gpio_sda_pin, GPIO_TRUE);

	for(i = 0; i < 8; i++)
	{
		delay_us(100);
		gpio_set_func(gpio_clk_pin, GPIO_TRUE);
		delay_us(100);
		data <<= 1;

		if(gpio_get_func(gpio_sda_pin))
		{
			data++;
		}

		gpio_set_func(gpio_clk_pin, GPIO_FALSE);

	}

	if(ack)
	{
		gpio_set_func(gpio_sda_pin, GPIO_FALSE);
	}

	delay_us(100);
	gpio_set_func(gpio_clk_pin, GPIO_TRUE);
	delay_us(100);
	gpio_set_func(gpio_clk_pin, GPIO_FALSE);
	gpio_set_func(gpio_sda_pin, GPIO_TRUE);

	return data;
}

/**
 * \brief
 *
 */
static uint8_t _i2c_soft_write_byte(soft_i2c_interface_td *p_soft_i2c_interface_handle, uint8_t data_write, p_delay_us_ftd delay_us)
{
	uint8_t i = 0;
	uint8_t ack = 0;
	gpio_brd_label_td gpio_scl_pin = p_soft_i2c_interface_handle->gpio_i2c_scl;
	gpio_brd_label_td gpio_sda_pin = p_soft_i2c_interface_handle->gpio_i2c_sda;
	p_gpio_set_ftd gpio_set_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_set;
	p_gpio_get_ftd gpio_get_func = p_soft_i2c_interface_handle->p_gpio_interface->gpio_get;

	for(i = 0; i < 8 ; i++)
	{
	   if(data_write & 0x80)
	   {
		   gpio_set_func(gpio_sda_pin, GPIO_TRUE);
	   }
	   else
	   {
		   gpio_set_func(gpio_sda_pin, GPIO_FALSE);
	   }

	   delay_us(100);
	   gpio_set_func(gpio_scl_pin, GPIO_TRUE);
	   delay_us(100);
	   gpio_set_func(gpio_scl_pin, GPIO_FALSE);
	   data_write = data_write << 1;
	}

	delay_us(100);
	gpio_set_func(gpio_scl_pin, GPIO_TRUE);
	delay_us(100);

	ack = gpio_get_func(gpio_sda_pin);

	gpio_set_func(gpio_scl_pin, GPIO_FALSE);
	gpio_set_func(gpio_sda_pin, GPIO_FALSE);

	return ack;
}

/**
 * \brief
 *
 */
static uint8_t _i2c_soft_write_data(soft_i2c_interface_td *p_soft_i2c_interface_handle, interface_data_info_td *p_interface_data_info, p_delay_us_ftd delay_us)
{
    uint8_t i = 0;
	uint8_t addr = p_interface_data_info->p_data[0];
	uint8_t *p_data = &p_interface_data_info->p_data[1];
	uint16_t data_size = p_interface_data_info->data_size - 1; ///< sub from data_size '1' for sending data without addr

    _i2c_soft_start(p_soft_i2c_interface_handle, delay_us);
    _i2c_soft_write_byte(p_soft_i2c_interface_handle, addr, delay_us);

    for(i = 0; i < data_size; i++)
    {
    	_i2c_soft_write_byte(p_soft_i2c_interface_handle, p_data[i], delay_us);
    }

    _i2c_soft_stop(p_soft_i2c_interface_handle, delay_us);
}

/**
 * \brief
 *
 */
static void _i2c_soft_read_data(soft_i2c_interface_td *p_soft_i2c_interface_handle, interface_data_info_td *p_interface_data_info, p_delay_us_ftd delay_us)
{
	uint8_t i = 0;
	uint8_t addr = p_interface_data_info->p_data[0];
	uint8_t *p_data = &p_interface_data_info->p_data[0];
	uint16_t data_size = p_interface_data_info->data_size - 1; ///< sub from data_size '1' for sending data without addr

	_i2c_soft_start(p_soft_i2c_interface_handle, delay_us);
	_i2c_soft_write_byte(p_soft_i2c_interface_handle, addr, delay_us);

	for(i = 0; i < data_size; i++)
	{
		p_data[i]  = _i2c_soft_read_byte(p_soft_i2c_interface_handle, delay_us, i != (data_size - 1));
	}

	_i2c_soft_stop(p_soft_i2c_interface_handle, delay_us);
}

/**
 * \brief SPI write function
 */
periph_io_status_td spi_read_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_spi_rx_polling(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, SPI_TIMEOUT);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->rx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}

/**
 * \brief SPI write function
 */
periph_io_status_td spi_write_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_spi_tx_polling(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, SPI_TIMEOUT);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->tx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}

/**
 * \brief SPI write function
 */
periph_io_status_td i2c_write_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_i2c_tx_polling(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, I2C_TIMEOUT);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->rx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}

/**
 * \brief SPI write function
 */
periph_io_status_td i2c_read_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_i2c_rx_polling(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, I2C_TIMEOUT);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->rx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}


/**
 * \brief I2C read function
 */
periph_io_status_td i2c_soft_write(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	periph_io_status_td periph_io_status = IO_OK;
	p_delay_us_ftd delay_us = ((periph_interface_td *)p_periph_interface)->delay_us;
	soft_i2c_interface_td *p_soft_i2c_interface_handle = (soft_i2c_interface_td *)(((periph_interface_td *) p_periph_interface)->params.p_interface_handle);

	_i2c_soft_write_data(p_soft_i2c_interface_handle, p_interface_data_info, delay_us);

	return periph_io_status;
}

/**
 * \brief I2C read function
 */
periph_io_status_td i2c_soft_read(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	periph_io_status_td periph_io_status = IO_OK;
	p_delay_us_ftd delay_us = ((periph_interface_td *)p_periph_interface)->delay_us;
	soft_i2c_interface_td *p_soft_i2c_interface_handle = (soft_i2c_interface_td *)(((periph_interface_td *) p_periph_interface)->params.p_interface_handle);

	_i2c_soft_read_data(p_soft_i2c_interface_handle, p_interface_data_info, delay_us);

	return periph_io_status;
}

/**
 * \brief SPI write function
 */
periph_io_status_td spi_write_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_spi_tx_dma(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, TIMEOUT_NONE);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->tx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}

/**
 * \brief SPI write function
 */
periph_io_status_td spi_read_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_spi_rx_dma(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, TIMEOUT_NONE);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->rx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}

/**
 * \brief UART write function
 */
periph_io_status_td uart_write_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_uart_tx_dma(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, TIMEOUT_NONE);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->tx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}

/**
 * \brief UART write function
 */
periph_io_status_td uart_read_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info)
{
	void *p_interface_handle = ((periph_interface_td *) p_periph_interface)->params.p_interface_handle;
	interface_events_td *p_interface_events_handle = &((periph_interface_td *) p_periph_interface)->interface_events_handle;
	periph_io_status_td periph_io_status = IO_OK;
	user_hw_abstr_status_td user_status = USER_OK;

	user_uart_rx_dma(p_interface_handle, p_interface_data_info->p_data, p_interface_data_info->data_size, TIMEOUT_NONE);

	/// if we have an event for this interface
	if(p_interface_events_handle != NULL)
	{
		user_status = user_wait_event_flags(p_interface_events_handle->p_interface_events_handle, p_interface_events_handle->rx_done_events_flags);

		if(user_status != USER_OK)
		{
			periph_io_status = IO_ERROR;
		}
	}

	return periph_io_status;
}
