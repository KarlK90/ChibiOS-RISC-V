# List of all the template platform files.
ifeq ($(USE_SMART_BUILD),yes)

# Configuration files directory
ifeq ($(CONFDIR),)
  CONFDIR = .
endif

HALCONF := $(strip $(shell cat $(CONFDIR)/halconf.h | egrep -e "\#define"))

PLATFORMSRC := ${CHIBIOS_RV}/os/hal/ports/common/RISCV/clic/hal_st_lld.c \
               ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/hal_lld.c \
               ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/n200_func.c \
               ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/gd32vf103_eclic.c \
               ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/nvic.c \
               ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/gd32_isr.c

else
PLATFORMSRC = ${CHIBIOS_RV}/os/hal/ports/common/RISCV/clic/hal_st_lld.c \
              ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/hal_lld.c \
              ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/n200_func.c \
              ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/gd32vf103_eclic.c \
              ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/nvic.c \
              ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/gd32_isr.c

endif

# Required include directories
PLATFORMINC = ${CHIBIOS_RV}/os/hal/ports/common/RISCV/clic \
              ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103

# Drivers compatible with the platform.
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/CANv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/DACv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/DMAv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/GPIOv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/I2Cv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/RTCv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SDIOv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SPIv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/TIMv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/USARTv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/OTGv1/driver.mk
include ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/xWDGv1/driver.mk

# Shared variables
ALLCSRC += $(PLATFORMSRC)
ALLINC  += $(PLATFORMINC)
