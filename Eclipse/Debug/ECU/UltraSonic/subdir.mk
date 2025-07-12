################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECU/UltraSonic/ultrasonic.c 

OBJS += \
./ECU/UltraSonic/ultrasonic.o 

C_DEPS += \
./ECU/UltraSonic/ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
ECU/UltraSonic/%.o: ../ECU/UltraSonic/%.c ECU/UltraSonic/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


