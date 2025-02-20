/**
 * \file
 * \brief Header for simple led driver.
 * \author Ilya Sopkin
 */

#include "gpio_interface.h"

#ifndef SIMPLE_LED_H_
#define SIMPLE_LED_H_


/// Simple led states
typedef enum
{
	LED_ON = 0,
	LED_OFF
} simple_led_states_td;

/// Simple led status codes enumeration
typedef enum
{
	SIMPLE_LED_ERROR = -1,
	SIMPLE_LED_OK
} simple_led_status_td;

/// Struct for simple led parameters
typedef struct
{
	gpio_interface_td interface;
} simple_led_params_td;

uint16_t simple_led_set (simple_led_params_td *p_params, simple_led_states_td led_state);
simple_led_status_td simple_led_init(simple_led_params_td *p_params);

#endif /* SIMPLE_LED_H_ */
