/*
 * periph_io.h
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */
#include "periph_interface.h"
//#include "Driver_USART.h"

#ifndef DRIVERS_PERIPH_INTERFACE_PERIPH_IO_H_
#define DRIVERS_PERIPH_INTERFACE_PERIPH_IO_H_

periph_io_status_td i2c_write_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
periph_io_status_td i2c_read_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info);

periph_io_status_td spi_write_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
periph_io_status_td spi_read_polling(void *p_periph_interface, interface_data_info_td *p_interface_data_info);

periph_io_status_td spi_write_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
periph_io_status_td spi_read_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info);

periph_io_status_td uart_write_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
periph_io_status_td uart_read_dma(void *p_periph_interface, interface_data_info_td *p_interface_data_info);

// periph_io_status_td ad9826_soft_spi_write(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
// periph_io_status_td ad9826_soft_spi_read(void *p_periph_interface, interface_data_info_td *p_interface_data_info);

periph_io_status_td i2c_soft_write(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
periph_io_status_td i2c_soft_read(void *p_periph_interface, interface_data_info_td *p_interface_data_info);

void console_send(char *p_str, uint32_t str_size);
//void delay_us(uint32_t us);

#endif /* DRIVERS_PERIPH_INTERFACE_PERIPH_IO_H_ */
