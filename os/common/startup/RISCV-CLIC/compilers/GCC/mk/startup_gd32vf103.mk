# List of the ChibiOS generic FE310 startup files.
STARTUPSRC = $(CHIBIOS_RV)/os/common/startup/RISCV-CLIC/compilers/GCC/crt1.c
          
STARTUPASM = $(CHIBIOS_RV)/os/common/startup/RISCV-CLIC/compilers/GCC/crt0.S \
             $(CHIBIOS_RV)/os/common/startup/RISCV-CLIC/compilers/GCC/vectors.S

STARTUPINC = $(CHIBIOS)/os/common/portability/GCC \
             $(CHIBIOS_RV)/os/common/startup/RISCV-CLIC/compilers/GCC \
             $(CHIBIOS_RV)/os/common/startup/RISCV-CLIC/devices/GD32VF103 \

STARTUPLD  = $(CHIBIOS_RV)/os/common/startup/RISCV-CLIC/compilers/GCC/ld

# Shared variables
ALLXASMSRC += $(STARTUPASM)
ALLCSRC    += $(STARTUPSRC)
ALLINC     += $(STARTUPINC)

