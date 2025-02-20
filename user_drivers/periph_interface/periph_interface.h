
#ifndef PERIPH_INTERFACE_H
#define PERIPH_INTERFACE_H

#include <stdint.h>

typedef enum
{
	IO_ERROR = -2,
	IO_TIMEOUT = -1,
	IO_OK
} periph_io_status_td;

typedef enum
{
	SOFTWARE_ADDR,	///< Use this for I2C software addressing
	HARDWARE_ADDR,	///< Use this for SPI (or some another interface) with true hardware addressing
	HARD_SOFT_ADDR	///< Use this for interface (SPI for example) with hardware addressing controlling by the software (manually toggle nCS pin)
} interface_ic_addr_type_td;

/// Enumeration
typedef enum
{
	I2C = 0,
	SPI,
	UART,
	USART,
	SOFT_SPI,
	SOFT_I2C
} interface_type_td;

///
typedef struct
{
	uint8_t *p_data;
	uint32_t data_size;
} interface_data_info_td;

typedef periph_io_status_td (*p_interface_write_ftd)(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
typedef periph_io_status_td (*p_interface_read_ftd)(void *p_periph_interface, interface_data_info_td *p_interface_data_info);
typedef void (*p_console_send_ftd)(char *p_str);
typedef void (*p_delay_us_ftd)(uint32_t us);

/// \todo make one interface
typedef struct
{
	interface_type_td interface_type;
	interface_ic_addr_type_td ic_addr_type; ///< \todo move addr to another place, to IC driver structure maybe
	void *p_interface_handle; ///< Handle for interface control struct (ARM_DRIVER_USART for example)
} interface_params_td;

/// Structure for use with RTOS.
/// Consist RTOS events handle and needed event flag for current interface
typedef struct
{
	void *p_interface_events_handle;	///< events interface handle
	uint32_t tx_done_events_flags;		///< transmit done event flag
	uint32_t rx_done_events_flags;		///< receive done event flag
} interface_events_td;

/// Struct for used interface
typedef struct
{
	interface_params_td params;
	interface_events_td interface_events_handle;
	p_interface_write_ftd write;
	p_interface_read_ftd read;
	p_delay_us_ftd delay_us;
	p_console_send_ftd console_send;
} periph_interface_td;

#endif
