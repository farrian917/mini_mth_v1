/**
 * \file
 * \brief Header for RS485 driver.
 * \author ivs
 */

#include "periph_interface.h"
#include "gpio_interface.h"

#ifndef RS485_H_
#define RS485_H_

/// RS485 dir enum
typedef enum
{
	RS485_RX = 0,
	RS485_TX
} rs485_dir_td;

/// RS485 status codes enumeration
typedef enum
{
	RS485_ERROR = -1,
	RS485_OK
} rs485_status_td;

/// Struct for INA226 parameters
typedef struct
{
	periph_interface_td *huart;
	gpio_interface_td *hgpio;
	uint32_t dir_pin;
} rs485_params_td;

uint32_t rs485_read(rs485_params_td *p_params, uint8_t * p_data);
rs485_status_td rs485_write_str(rs485_params_td *p_params, const char *const p_msg);
rs485_status_td rs485_init(rs485_params_td *p_params,
							periph_interface_td  * const p_interface,
							gpio_interface_td *hgpio,
							uint32_t dir_pin_number);

#endif /* RS485_H_ */
