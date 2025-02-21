/*
 * user_hw_abstraction_layer.h
 *
 *  Created on: 21 сент. 2020 г.
 *      Author: User
 */

#ifndef USER_HW_ABSTRACTION_LAYER_H_
#define USER_HW_ABSTRACTION_LAYER_H_

#define STM32_HAL_HEADER "stm32f1xx_hal.h"

#include <stdint.h>
#include STM32_HAL_HEADER

#ifdef USE_RTOS
#undef USE_RTOS
#endif

#define USE_RTOS

#ifdef USE_RTOS
#include "cmsis_os.h"
#endif
//#include "build_config.h"

typedef enum
{
	USER_ERROR = -1,
	USER_OK
} user_hw_abstr_status_td;

/// Interfaces number that will be used
#define GPIO_INTERFACE_HANDLE_SIZE 		(1)	///<
#define SW_SPI_INTERFACE_HANDLE_SIZE 	(1)	///<
#define HW_SPI_INTERFACE_HANDLE_SIZE 	(3)	///<
#define SW_I2C_INTERFACE_HANDLE_SIZE 	(1)	///<
#define HW_I2C_INTERFACE_HANDLE_SIZE 	(0)	///<
#define HW_UART_INTERFACE_HANDLE_SIZE 	(2)	///<

typedef enum
{
	GPIO_LED_ORANGE = 0,
	GPIO_RS485_DIR,
	GPIO_CAN_SHDN,
	GPIO_USER_BTN_0,
	GPIO_USER_BTN_1,
	GPIO_SOFT_I2C_2_CLK,
	GPIO_SOFT_I2C_2_SDA,
	GPIO_END_VALUE
} gpio_brd_label_td;

#define MAX_GPIO_NUM	(uint8_t) (GPIO_END_VALUE) ///< Must be equal to gpio_brd_label_td members number

/// PIN led_orange
#define LED_ORANGE_PORT		GPIOC
#define LED_ORANGE_PIN		GPIO_PIN_13

/// PIN usb_connect in motherboard
#define RS485_DIR_PORT		GPIOB
#define RS485_DIR_PIN		GPIO_PIN_2

/// PIN usb_connect in motherboard
#define CAN_SHDN_PORT		GPIOA
#define CAN_SHDN_PIN		GPIO_PIN_1

/// PIN usb_connect in motherboard
#define USER_BTN_0_PORT		GPIOB
#define USER_BTN_0_PIN		GPIO_PIN_1

/// PIN usb_connect in motherboard
#define USER_BTN_1_PORT		GPIOA
#define USER_BTN_1_PIN		GPIO_PIN_15

///
#define SOFT_I2C_2_CLK_PORT		GPIOB
#define SOFT_I2C_2_CLK_PIN		GPIO_PIN_10

///
#define SOFT_I2C_2_SDA_PORT		GPIOB
#define SOFT_I2C_2_SDA_PIN		GPIO_PIN_11


/// Function prototypes

#ifdef HAL_SPI_MODULE_ENABLED
user_hw_abstr_status_td user_spi_tx_dma(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
user_hw_abstr_status_td user_spi_rx_dma(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
user_hw_abstr_status_td user_spi_tx_polling(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
user_hw_abstr_status_td user_spi_rx_polling(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
#endif

#ifdef HAL_UART_MODULE_ENABLED
user_hw_abstr_status_td user_uart_tx_it(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
user_hw_abstr_status_td user_uart_rx_it(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
#endif

#ifdef HAL_I2C_MODULE_ENABLED
user_hw_abstr_status_td user_i2c_tx_polling(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
user_hw_abstr_status_td user_i2c_rx_polling(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
#endif

user_hw_abstr_status_td user_wait_event_flags(void *const p_interface_events_handle, const uint32_t tx_done_events_flag);

//user_hw_abstr_status_td user_gpio_set(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);
//user_hw_abstr_status_td user_gpio_get(void *const p_interface_handle, const uint8_t *const p_data, const uint16_t data_size, uint32_t timeout);


#endif /* USER_HW_ABSTRACTION_LAYER_H_ */
