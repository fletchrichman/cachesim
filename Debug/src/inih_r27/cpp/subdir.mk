################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/inih_r27/cpp/INIReader.cpp 

OBJS += \
./src/inih_r27/cpp/INIReader.o 

CPP_DEPS += \
./src/inih_r27/cpp/INIReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih_r27/cpp/%.o: ../src/inih_r27/cpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/user/Dropbox/Project/CacheSimulatorCPP/inc" -I"/home/user/Dropbox/Project/CacheSimulatorCPP/configs" -I"/home/user/Dropbox/Project/CacheSimulatorCPP/src/inih_r27/cpp" -I"/home/user/Dropbox/Project/CacheSimulatorCPP/src/inih_r27" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


