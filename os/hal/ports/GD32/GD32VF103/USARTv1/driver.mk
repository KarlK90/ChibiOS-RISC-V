ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_SERIAL TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/USARTv1/hal_serial_lld.c
endif
ifneq ($(findstring HAL_USE_UART TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/USARTv1/hal_uart_lld.c
endif
else
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/USARTv1/hal_serial_lld.c
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/USARTv1/hal_uart_lld.c
endif

PLATFORMINC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/USARTv1
