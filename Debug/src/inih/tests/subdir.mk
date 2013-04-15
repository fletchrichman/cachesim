################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/inih/tests/unittest.c 

OBJS += \
./src/inih/tests/unittest.o 

C_DEPS += \
./src/inih/tests/unittest.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih/tests/%.o: ../src/inih/tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


