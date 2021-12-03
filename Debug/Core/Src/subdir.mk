################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ace_gir.c \
../Core/Src/can_bus.c \
../Core/Src/dina.c \
../Core/Src/fatfs_sd.c \
../Core/Src/forceGauge.c \
../Core/Src/indutivo.c \
../Core/Src/main.c \
../Core/Src/rot.c \
../Core/Src/sdCard.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/vel.c 

OBJS += \
./Core/Src/ace_gir.o \
./Core/Src/can_bus.o \
./Core/Src/dina.o \
./Core/Src/fatfs_sd.o \
./Core/Src/forceGauge.o \
./Core/Src/indutivo.o \
./Core/Src/main.o \
./Core/Src/rot.o \
./Core/Src/sdCard.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/vel.o 

C_DEPS += \
./Core/Src/ace_gir.d \
./Core/Src/can_bus.d \
./Core/Src/dina.d \
./Core/Src/fatfs_sd.d \
./Core/Src/forceGauge.d \
./Core/Src/indutivo.d \
./Core/Src/main.d \
./Core/Src/rot.d \
./Core/Src/sdCard.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/vel.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ace_gir.d ./Core/Src/ace_gir.o ./Core/Src/can_bus.d ./Core/Src/can_bus.o ./Core/Src/dina.d ./Core/Src/dina.o ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/forceGauge.d ./Core/Src/forceGauge.o ./Core/Src/indutivo.d ./Core/Src/indutivo.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/rot.d ./Core/Src/rot.o ./Core/Src/sdCard.d ./Core/Src/sdCard.o ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/vel.d ./Core/Src/vel.o

.PHONY: clean-Core-2f-Src

