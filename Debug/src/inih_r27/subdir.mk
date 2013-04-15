################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/inih_r27/ini.c 

OBJS += \
./src/inih_r27/ini.o 

C_DEPS += \
./src/inih_r27/ini.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih_r27/%.o: ../src/inih_r27/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


