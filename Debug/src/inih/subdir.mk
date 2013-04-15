################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/inih/ini.o 

C_SRCS += \
../src/inih/ini.c 

OBJS += \
./src/inih/ini.o 

C_DEPS += \
./src/inih/ini.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih/%.o: ../src/inih/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


