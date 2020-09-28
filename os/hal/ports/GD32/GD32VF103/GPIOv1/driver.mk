ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_PAL TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/GPIOv1/hal_pal_lld.c
endif
else
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/GPIOv1/hal_pal_lld.c
endif

PLATFORMINC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/GPIOv1
