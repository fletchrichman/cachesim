################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/inih-master/lib/INIReader.cpp 

C_SRCS += \
../src/inih-master/lib/ini.c 

OBJS += \
./src/inih-master/lib/INIReader.o \
./src/inih-master/lib/ini.o 

C_DEPS += \
./src/inih-master/lib/ini.d 

CPP_DEPS += \
./src/inih-master/lib/INIReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih-master/lib/%.o: ../src/inih-master/lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/inc" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih-master" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih-master/lib" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih-master/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/inih-master/lib/%.o: ../src/inih-master/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


