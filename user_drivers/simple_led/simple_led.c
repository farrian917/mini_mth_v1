
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



	return status;
}

/**
 * \brief simple led driver initialization
 * \p_params[in] p_params ptr to simple led parameter structure
 *
 */
simple_led_status_td simple_led_init(simple_led_params_td *p_params)
{
	simple_led_status_td status = SIMPLE_LED_OK;



//	status = _ina226_reg_write(p_params, INA226_CONFIG, 0x0B27); ///< AVG = 256, BUS conv time = 1.1ms, SHUNT conv time = 1.1ms, MODE = SHUNT & BUS continious
	
	return status;
}

