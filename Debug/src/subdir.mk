################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ASet.cpp \
../src/Associative.cpp \
../src/Cache.cpp \
../src/DMBlock.cpp \
../src/DirectMap.cpp \
../src/LRU.cpp \
../src/config.cpp \
../src/instruction.cpp \
../src/main.cpp \
../src/results.cpp \
../src/simulator.cpp \
../src/trace.cpp 

OBJS += \
./src/ASet.o \
./src/Associative.o \
./src/Cache.o \
./src/DMBlock.o \
./src/DirectMap.o \
./src/LRU.o \
./src/config.o \
./src/instruction.o \
./src/main.o \
./src/results.o \
./src/simulator.o \
./src/trace.o 

CPP_DEPS += \
./src/ASet.d \
./src/Associative.d \
./src/Cache.d \
./src/DMBlock.d \
./src/DirectMap.d \
./src/LRU.d \
./src/config.d \
./src/instruction.d \
./src/main.d \
./src/results.d \
./src/simulator.d \
./src/trace.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/user/Dropbox/Project/CacheSim/inc" -I"/home/user/Dropbox/Project/CacheSim/src/inih_r27/cpp" -I"/home/user/Dropbox/Project/CacheSim/src/inih_r27" -I"/home/user/Dropbox/Project/CacheSim/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


