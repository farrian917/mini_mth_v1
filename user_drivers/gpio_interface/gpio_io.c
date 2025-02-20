
#include "gpio_io.h"
//#include "gpio_user.h"
//#include "stm32f1xx_hal.h"

#include "user_hw_abstraction_layer.h"

const static uint32_t _gpio_port_array[MAX_GPIO_NUM] =
{
	LED_ORANGE_PORT,
	RS485_DIR_PORT,
	CAN_SHDN_PORT,
	USER_BTN_0_PORT,
	USER_BTN_1_PORT,
	SOFT_I2C_2_CLK_PORT,
	SOFT_I2C_2_SDA_PORT
};

const static uint32_t _gpio_pin_array[MAX_GPIO_NUM] =
{
	LED_ORANGE_PIN,
	RS485_DIR_PIN,
	CAN_SHDN_PIN,
	USER_BTN_0_PIN,
	USER_BTN_1_PIN,
	SOFT_I2C_2_CLK_PIN,
	SOFT_I2C_2_SDA_PIN
};

uint32_t *get_gpio_port_array_ptr(void)
{
	return (uint32_t *)_gpio_port_array;
}

uint32_t *get_gpio_pin_array_ptr(void)
{
	return (uint32_t *)_gpio_pin_array;
}

/**
 * \brief
 *
 */
void gpio_set(/*gpio_brd_label_td gpio_brd_label*/ const uint32_t pin_label, gpio_value_td gpio_value)
{
	if (/*(uint32_t)gpio_brd_label*/ pin_label <  MAX_GPIO_NUM)
	{
		switch(gpio_value)
		{
			case GPIO_TRUE:
				HAL_GPIO_WritePin((GPIO_TypeDef *)_gpio_port_array[/*gpio_brd_label*/pin_label], _gpio_pin_array[/*gpio_brd_label*/pin_label], GPIO_PIN_SET);
				break;

			case GPIO_FALSE:
				HAL_GPIO_WritePin((GPIO_TypeDef *)_gpio_port_array[/*gpio_brd_label*/pin_label], _gpio_pin_array[/*gpio_brd_label*/pin_label], GPIO_PIN_RESET);
				break;
		}
	}
	else
	{
		/// \\todo PRINTF
	}
}

/**
 * \brief
 *
 */
gpio_value_td gpio_get(/*gpio_brd_label_td gpio_brd_label*/ const uint32_t pin_label)
{
	gpio_value_td gpio_pin_state = GPIO_FALSE;

	if (/*(uint32_t)gpio_brd_label*/pin_label < MAX_GPIO_NUM)
	{
		if(HAL_GPIO_ReadPin((GPIO_TypeDef *)_gpio_port_array[/*gpio_brd_label*/pin_label], _gpio_pin_array[/*gpio_brd_label*/pin_label]) == (uint8_t)GPIO_PIN_SET)
		{
			gpio_pin_state = GPIO_TRUE;
		}
		else
		{
			gpio_pin_state = GPIO_FALSE;
		}
	}
	else
	{
		/// \todo PRINTF
	}

	return gpio_pin_state;
}

/**
 * \brief
 *
 */
void setup_soft_spi_interface(soft_spi_interface_td *p_soft_spi_interface_handle, gpio_interface_td *p_gpio_interface_handle, const /*gpio_brd_label_td*/ uint32_t clk_pin, const /*gpio_brd_label_td*/ uint32_t mosi_pin, const /*gpio_brd_label_td*/ uint32_t miso_pin)
//void setup_soft_spi_interface(soft_spi_interface_td *p_soft_spi_interface_handle, gpio_interface_td *p_gpio_interface_handle, const /*gpio_brd_label_td*/ uint32_t clk_pin, const /*gpio_brd_label_td*/ uint32_t mosi_pin, const /*gpio_brd_label_td*/  miso_pin)
{
	p_soft_spi_interface_handle->p_gpio_interface = p_gpio_interface_handle;
	p_soft_spi_interface_handle->gpio_spi_clk = clk_pin;
	p_soft_spi_interface_handle->gpio_spi_miso = miso_pin;
	p_soft_spi_interface_handle->gpio_spi_mosi = mosi_pin;
}

/**
 * \brief
 *
 */
void setup_soft_i2c_interface(soft_i2c_interface_td *p_soft_i2c_interface_handle, gpio_interface_td *p_gpio_interface_handle, const /*gpio_brd_label_td*/ uint32_t scl_pin, const /*gpio_brd_label_td*/ uint32_t sda_pin)
//void setup_soft_i2c_interface(soft_i2c_interface_td *p_soft_i2c_interface_handle, gpio_interface_td *p_gpio_interface_handle, const /*gpio_brd_label_td*/ uint32_t scl_pin, const /*gpio_brd_label_td*/ uint32_t sda_pin)
{
	p_soft_i2c_interface_handle->p_gpio_interface = p_gpio_interface_handle;
	p_soft_i2c_interface_handle->gpio_i2c_scl = scl_pin;
	p_soft_i2c_interface_handle->gpio_i2c_sda = sda_pin;
}

