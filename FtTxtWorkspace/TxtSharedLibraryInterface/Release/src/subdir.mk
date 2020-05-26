################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LibExampleSLI.cpp 

OBJS += \
./src/LibExampleSLI.o 

CPP_DEPS += \
./src/LibExampleSLI.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"H:\WorkspaceGitHub\fischertechnik\txt_demo_ROBOPro_SLI\FtTxtWorkspace\TxtDeps\Txt_Includes" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


