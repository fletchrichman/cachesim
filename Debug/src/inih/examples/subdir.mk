################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/inih/examples/ini_dump.c \
../src/inih/examples/ini_example.c \
../src/inih/examples/ini_xmacros.c 

OBJS += \
./src/inih/examples/ini_dump.o \
./src/inih/examples/ini_example.o \
./src/inih/examples/ini_xmacros.o 

C_DEPS += \
./src/inih/examples/ini_dump.d \
./src/inih/examples/ini_example.d \
./src/inih/examples/ini_xmacros.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih/examples/%.o: ../src/inih/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


