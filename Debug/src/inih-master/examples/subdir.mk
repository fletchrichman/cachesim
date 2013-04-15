################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/inih-master/examples/INIReaderTest.cpp 

C_SRCS += \
../src/inih-master/examples/ini_dump.c \
../src/inih-master/examples/ini_example.c \
../src/inih-master/examples/ini_xmacros.c 

OBJS += \
./src/inih-master/examples/INIReaderTest.o \
./src/inih-master/examples/ini_dump.o \
./src/inih-master/examples/ini_example.o \
./src/inih-master/examples/ini_xmacros.o 

C_DEPS += \
./src/inih-master/examples/ini_dump.d \
./src/inih-master/examples/ini_example.d \
./src/inih-master/examples/ini_xmacros.d 

CPP_DEPS += \
./src/inih-master/examples/INIReaderTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/inih-master/examples/%.o: ../src/inih-master/examples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/inc" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih-master" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih-master/lib" -I"/Users/invert111/Dropbox/Project/CacheSimulatorCPP/src/inih-master/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/inih-master/examples/%.o: ../src/inih-master/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


