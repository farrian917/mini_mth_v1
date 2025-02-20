/*
 * gpio_io.h
 *
 *  Created on: 24 апр. 2020 г.
 *      Author: IVSop
 */

#ifndef DRIVERS_GPIO_INTERFACE_GPIO_IO_H_
#define DRIVERS_GPIO_INTERFACE_GPIO_IO_H_

#include "gpio_interface.h"

uint32_t *get_gpio_port_array_ptr(void);
uint32_t *get_gpio_pin_array_ptr(void);

void gpio_set(const uint32_t pin_label, const gpio_value_td gpio_value);
gpio_value_td gpio_get(const uint32_t pin_label);

void setup_soft_spi_interface(soft_spi_interface_td *p_soft_spi_interface_handle, gpio_interface_td *p_gpio_interface_handle, const /*gpio_brd_label_td*/ uint32_t clk_pin, const /*gpio_brd_label_td*/ uint32_t mosi_pin, const /*gpio_brd_label_td*/ uint32_t miso_pin);
void setup_soft_i2c_interface(soft_i2c_interface_td *p_soft_i2c_interface_handle, gpio_interface_td *p_gpio_interface_handle, const /*gpio_brd_label_td*/ uint32_t scl_pin, const /*gpio_brd_label_td*/ uint32_t sda_pin);

#endif /* DRIVERS_GPIO_INTERFACE_GPIO_IO_H_ */
