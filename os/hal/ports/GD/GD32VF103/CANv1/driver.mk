ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_CAN TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD/GD32VF103/CANv1/hal_can_lld.c
endif
else
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD/GD32VF103/CANv1/hal_can_lld.c
endif

PLATFORMINC += ${CHIBIOS_RV}/os/hal/ports/GD/GD32VF103/CANv1
