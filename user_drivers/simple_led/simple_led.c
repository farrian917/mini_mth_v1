
#include <stdint.h>
#include "simple_led.h"

/**
 * \brief
 * \p_params[in] p_params ptr to simple_led parameter structure
 * \value[in] value for set
 */
uint16_t simple_led_set (simple_led_params_td *p_params, simple_led_states_td led_state)
{
	simple_led_status_td status = SIMPLE_LED_OK;

	p_params->interface->gpio_set(p_params->pin, led_state);

	return status;
}

/**
 * \brief simple led driver initialization
 * \p_params[in] p_params ptr to simple led parameter structure
 *
 */
simple_led_status_td simple_led_init(simple_led_params_td *p_params, gpio_interface_td *hgpio, uint32_t led_pin_number)
{
	simple_led_status_td status = SIMPLE_LED_OK;
	
	p_params->interface = hgpio;
	p_params->pin = led_pin_number;

	return status;
}

