################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/inih/cpp/INIReader.cpp \
../src/inih/cpp/INIReaderTest.cpp 

OBJS += \
./src/inih/cpp/INIReader.o \
./src/inih/cpp/INIReaderTest.o 

CPP_DEPS += \
./src/inih/cpp/INIReader.d \
./src/inih/cpp/INIReaderTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih/cpp/%.o: ../src/inih/cpp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/inc" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/extra" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih/extra" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih/cpp" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


