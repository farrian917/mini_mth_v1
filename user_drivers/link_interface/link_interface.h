/*
 * link_interface.h
 *
 *  Created on: May 7, 2020
 *      Author: IVSop
 */

#ifndef LINK_INTERFACE_LINK_INTERFACE_H_
#define LINK_INTERFACE_LINK_INTERFACE_H_

#include "periph_interface.h"
#include "gpio_interface.h"

void link_gpio_interface(gpio_interface_td *p_gpio_interface,
							p_gpio_set_ftd set_func,
							p_gpio_get_ftd get_func);

void link_soft_spi_interface(periph_interface_td *p_periph_interface,
								interface_ic_addr_type_td ic_addr_type,
								soft_spi_interface_td * const p_gpio_spi_interface_handle,
								p_interface_write_ftd write_func,
								p_interface_read_ftd read_func,
								p_delay_us_ftd delay_func);

void link_soft_i2c_interface(periph_interface_td *p_periph_interface,
								interface_ic_addr_type_td ic_addr_type,
								soft_spi_interface_td * const p_gpio_spi_interface_handle,
								p_interface_write_ftd write_func, p_interface_read_ftd read_func,
								p_delay_us_ftd delay_func);

void link_spi_interface(periph_interface_td *p_periph_interface,
							interface_ic_addr_type_td ic_addr_type,
							/*SPI_HandleTypeDef*/ void * const p_spi_handle,
							p_interface_write_ftd write_func,
							p_interface_read_ftd read_func,
							p_delay_us_ftd delay_func);

void link_i2c_interface(periph_interface_td *p_periph_interface,
							interface_ic_addr_type_td ic_addr_type,
							/*I2C_HandleTypeDef*/ void * const p_i2c_handle,
							p_interface_write_ftd write_func, p_interface_read_ftd read_func,
							p_delay_us_ftd delay_func);

void link_uart_interface(periph_interface_td *p_periph_interface,
							interface_ic_addr_type_td ic_addr_type,
								/*UART_HandleTypeDef*/ void * const p_uart_handle,
								p_interface_write_ftd write_func,
								p_interface_read_ftd read_func,
								p_delay_us_ftd delay_func);

void link_periph_interface(periph_interface_td *p_periph_interface,
							const void * p_interface_events_handle,
							const uint32_t tx_done_event_flag,
							const uint32_t rx_done_event_flag,
							interface_type_td interface_type,
							interface_ic_addr_type_td ic_addr_type,
							void * const p_low_lvl_interface_handle,
							p_interface_write_ftd write_func,
							p_interface_read_ftd read_func,
							p_delay_us_ftd delay_func);

gpio_interface_td *get_gpio_interface_handle(const uint8_t handle_number);
periph_interface_td *get_soft_spi_interface_handle(const uint8_t handle_number);
periph_interface_td *get_hard_spi_interface_handle(const uint8_t handle_number);
periph_interface_td *get_soft_i2c_interface_handle(const uint8_t handle_number);
periph_interface_td *get_hard_i2c_interface_handle(const uint8_t handle_number);
periph_interface_td *get_soft_uart_interface_handle(const uint8_t handle_number);
periph_interface_td *get_hard_uart_interface_handle(const uint8_t handle_number);

#endif /* LINK_INTERFACE_LINK_INTERFACE_H_ */
