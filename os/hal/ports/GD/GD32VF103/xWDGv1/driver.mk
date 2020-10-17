ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_WDG TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD/GD32VF103/xWDGv1/hal_wdg_lld.c
endif
else
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD/GD32VF103/xWDGv1/hal_wdg_lld.c
endif

PLATFORMINC += ${CHIBIOS_RV}/os/hal/ports/GD/GD32VF103/xWDGv1
