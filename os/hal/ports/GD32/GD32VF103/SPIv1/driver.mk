ifeq ($(USE_SMART_BUILD),yes)
ifneq ($(findstring HAL_USE_I2S TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SPIv1/hal_i2s_lld.c
endif
ifneq ($(findstring HAL_USE_SPI TRUE,$(HALCONF)),)
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SPIv1/hal_spi_lld.c
endif
else
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SPIv1/hal_i2s_lld.c
PLATFORMSRC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SPIv1/hal_spi_lld.c
endif

PLATFORMINC += ${CHIBIOS_RV}/os/hal/ports/GD32/GD32VF103/SPIv1
