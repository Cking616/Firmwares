################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
bsp/Bumper.obj: ../bsp/Bumper.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/Bumper.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsp/CO_driver.obj: ../bsp/CO_driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/CO_driver.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsp/MA3encoder.obj: ../bsp/MA3encoder.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/MA3encoder.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsp/delay.obj: ../bsp/delay.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/delay.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsp/driver.obj: ../bsp/driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/driver.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsp/io.obj: ../bsp/io.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/io.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

bsp/sonar.obj: ../bsp/sonar.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="bsp/sonar.d_raw" --obj_directory="bsp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


