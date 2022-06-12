################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/introInter.cpp \
../src/introRepository.cpp \
../src/main.cpp \
../src/mainInter.cpp \
../src/mainRepository.cpp \
../src/mconnector.cpp \
../src/request.cpp \
../src/user.cpp 

CPP_DEPS += \
./src/introInter.d \
./src/introRepository.d \
./src/main.d \
./src/mainInter.d \
./src/mainRepository.d \
./src/mconnector.d \
./src/request.d \
./src/user.d 

OBJS += \
./src/introInter.o \
./src/introRepository.o \
./src/main.o \
./src/mainInter.o \
./src/mainRepository.o \
./src/mconnector.o \
./src/request.o \
./src/user.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I~/Ruslan/mysql-connector-c++-8.0.29-linux-glibc2.12-x86-64bit/include -I/home/user/Ruslan/json/include/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/introInter.d ./src/introInter.o ./src/introRepository.d ./src/introRepository.o ./src/main.d ./src/main.o ./src/mainInter.d ./src/mainInter.o ./src/mainRepository.d ./src/mainRepository.o ./src/mconnector.d ./src/mconnector.o ./src/request.d ./src/request.o ./src/user.d ./src/user.o

.PHONY: clean-src

