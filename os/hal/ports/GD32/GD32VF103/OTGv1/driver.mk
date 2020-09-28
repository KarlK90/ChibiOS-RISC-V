ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_USB TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/OTGv1/hal_usb_lld.c
endif
else
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/OTGv1/hal_usb_lld.c
endif

PLATFORMINC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/OTGv1
