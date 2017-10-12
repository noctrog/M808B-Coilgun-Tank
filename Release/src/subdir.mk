################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Motors.c \
../src/USART.c \
../src/cannon.c \
../src/main.c 

OBJS += \
./src/Motors.o \
./src/USART.o \
./src/cannon.o \
./src/main.o 

C_DEPS += \
./src/Motors.d \
./src/USART.d \
./src/cannon.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/ramon/Documents/Programming/workspace/Tank/includes" -Wall -O3 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=7372800UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


