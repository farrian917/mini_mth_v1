
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include <stdint.h>

typedef enum
{
	IN_GPIO,	///< Use this for I2C software addressing
	OUT_GPIO	///< Use this for SPI (or some another interface) with true hardware addressing
} gpio_type_td;

typedef enum
{
	GPIO_FALSE = 0,
	GPIO_TRUE
} gpio_value_td;

typedef void (*p_gpio_set_ftd)(/*gpio_brd_label_td gpio_brd_label*/ const uint32_t pin_number, const gpio_value_td gpio_value);
typedef gpio_value_td (*p_gpio_get_ftd)(/*gpio_brd_label_td gpio_brd_label*/ const uint32_t pin_number);

/// Struct for used gpio interface
typedef struct
{
	p_gpio_set_ftd gpio_set;
	p_gpio_get_ftd gpio_get;
} gpio_interface_td;

/// Struct for advanced gpio interface
typedef struct
{
	gpio_interface_td *p_gpio_interface;
	/*gpio_brd_label_td*/uint32_t gpio_spi_clk;
	/*gpio_brd_label_td*/uint32_t gpio_spi_mosi;
	/*gpio_brd_label_td*/uint32_t gpio_spi_miso;
} soft_spi_interface_td;

/// Struct for advanced gpio interface
typedef struct
{
	gpio_interface_td  *p_gpio_interface;
	/*gpio_brd_label_td*/ uint32_t gpio_i2c_scl;
	/*gpio_brd_label_td*/ uint32_t gpio_i2c_sda;
} soft_i2c_interface_td;

#endif
