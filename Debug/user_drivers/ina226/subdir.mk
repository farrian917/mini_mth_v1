################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user_drivers/ina226/ina226.c 

OBJS += \
./user_drivers/ina226/ina226.o 

C_DEPS += \
./user_drivers/ina226/ina226.d 


# Each subdirectory must supply rules for building sources it contributes
user_drivers/ina226/%.o user_drivers/ina226/%.su user_drivers/ina226/%.cyclo: ../user_drivers/ina226/%.c user_drivers/ina226/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/Third_Party/FreeRTOS/Source/include -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Device/ST/STM32F1xx/Include -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Drivers/CMSIS/Include -IC:/Users/User/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.6/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../user_drivers -I../user_drivers/gpio_interface -I../user_drivers/link_interface -I../user_drivers/periph_interface -I../user_drivers/simple_led -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-user_drivers-2f-ina226

clean-user_drivers-2f-ina226:
	-$(RM) ./user_drivers/ina226/ina226.cyclo ./user_drivers/ina226/ina226.d ./user_drivers/ina226/ina226.o ./user_drivers/ina226/ina226.su

.PHONY: clean-user_drivers-2f-ina226

