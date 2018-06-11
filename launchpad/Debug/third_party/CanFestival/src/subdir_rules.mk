################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
third_party/CanFestival/src/dcf.obj: ../third_party/CanFestival/src/dcf.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/dcf.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/emcy.obj: ../third_party/CanFestival/src/emcy.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/emcy.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/lifegrd.obj: ../third_party/CanFestival/src/lifegrd.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/lifegrd.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/lss.obj: ../third_party/CanFestival/src/lss.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/lss.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/nmtMaster.obj: ../third_party/CanFestival/src/nmtMaster.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/nmtMaster.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/nmtSlave.obj: ../third_party/CanFestival/src/nmtSlave.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/nmtSlave.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/objacces.obj: ../third_party/CanFestival/src/objacces.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/objacces.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/pdo.obj: ../third_party/CanFestival/src/pdo.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/pdo.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/sdo.obj: ../third_party/CanFestival/src/sdo.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/sdo.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/states.obj: ../third_party/CanFestival/src/states.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/states.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/sync.obj: ../third_party/CanFestival/src/sync.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/sync.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

third_party/CanFestival/src/timer.obj: ../third_party/CanFestival/src/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc" --include_path="C:/Users/cking/Source/Repos/Firmwares/launchpad/third_party/CanFestival/inc/tm4c" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="third_party/CanFestival/src/timer.d_raw" --obj_directory="third_party/CanFestival/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


