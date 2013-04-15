################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/asscache.cpp \
../src/asscacheset.cpp \
../src/cache.cpp \
../src/config.cpp \
../src/dmcache.cpp \
../src/dmcacheblock.cpp \
../src/instruction.cpp \
../src/lrunode.cpp \
../src/main.cpp \
../src/results.cpp \
../src/simulator.cpp \
../src/trace.cpp 

OBJS += \
./src/asscache.o \
./src/asscacheset.o \
./src/cache.o \
./src/config.o \
./src/dmcache.o \
./src/dmcacheblock.o \
./src/instruction.o \
./src/lrunode.o \
./src/main.o \
./src/results.o \
./src/simulator.o \
./src/trace.o 

CPP_DEPS += \
./src/asscache.d \
./src/asscacheset.d \
./src/cache.d \
./src/config.d \
./src/dmcache.d \
./src/dmcacheblock.d \
./src/instruction.d \
./src/lrunode.d \
./src/main.d \
./src/results.d \
./src/simulator.d \
./src/trace.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/user/Dropbox/Project/CacheSimulatorCPP/inc" -I"/home/user/Dropbox/Project/CacheSimulatorCPP/configs" -I"/home/user/Dropbox/Project/CacheSimulatorCPP/src/inih_r27/cpp" -I"/home/user/Dropbox/Project/CacheSimulatorCPP/src/inih_r27" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


