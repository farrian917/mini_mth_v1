################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user_drivers/rs485/rs485.c 

OBJS += \
./user_drivers/rs485/rs485.o 

C_DEPS += \
./user_drivers/rs485/rs485.d 


# Each subdirectory must supply rules for building sources it contributes
user_drivers/rs485/%.o user_drivers/rs485/%.su user_drivers/rs485/%.cyclo: ../user_drivers/rs485/%.c user_drivers/rs485/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../user_messages -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Device/ST/STM32F1xx/Include -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Include -I../user_drivers -I../user_drivers/gpio_interface -I../user_drivers/link_interface -I../user_drivers/periph_interface -I../user_drivers/simple_led -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../user_events -I../user_callbacks -I../user_threads -I../user_api -I../user_drivers/rs485 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-user_drivers-2f-rs485

clean-user_drivers-2f-rs485:
	-$(RM) ./user_drivers/rs485/rs485.cyclo ./user_drivers/rs485/rs485.d ./user_drivers/rs485/rs485.o ./user_drivers/rs485/rs485.su

.PHONY: clean-user_drivers-2f-rs485

