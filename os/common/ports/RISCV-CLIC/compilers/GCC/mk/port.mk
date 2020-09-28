# List of the ChibiOS/RT RISCV generic port files.
PORTSRC = $(CHIBIOS_RV)/os/common/ports/RISCV-CLIC/chcore.c

PORTASM = $(CHIBIOS_RV)/os/common/ports/RISCV-CLIC/compilers/GCC/chcoreasm.S

PORTINC = $(CHIBIOS_RV)/os/common/ports/RISCV-CLIC \
          $(CHIBIOS)/os/common/ports/RISCV-CLIC/compilers/GCC

# Shared variables
ALLXASMSRC += $(PORTASM)
ALLCSRC    += $(PORTSRC)
ALLINC     += $(PORTINC)
