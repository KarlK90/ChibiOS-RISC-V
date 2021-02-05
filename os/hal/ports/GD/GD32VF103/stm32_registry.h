/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    STM32F1xx/stm32_registry.h
 * @brief   STM32F1xx capabilities registry.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef STM32_REGISTRY_H
#define STM32_REGISTRY_H

#if defined(STM32F100xB)
#define STM32F10X_MD_VL

#elif defined(STM32F100xE)
#define STM32F10X_HD_VL

#elif defined(STM32F101x6) || defined(STM32F102x6) || defined(STM32F103x6)
#define STM32F10X_LD

#elif defined(STM32F101xB) || defined(GD32VF103x8) || defined(GD32VF103xB)
#define STM32F10X_MD

#elif defined(STM32F101xE) || defined(STM32F103xE)
#define STM32F10X_HD

#elif defined(STM32F101xG) || defined(STM32F103xG)
#define STM32F10X_XL

#elif defined(STM32F105xC) || defined(STM32F107xC)
#define STM32F10X_CL

#else
//TODO
#define STM32F10X_MD
//#error "unsupported or unrecognized STM32F1xx member"
#endif

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/

#if defined(STM32F10X_MD) || defined(__DOXYGEN__)
/**
 * @name    STM32F103 MD capabilities
 * @{
 */
/* ADC attributes.*/
#define STM32_HAS_ADC1                      TRUE
#define STM32_HAS_ADC2                      TRUE
#define STM32_HAS_ADC3                      FALSE
#define STM32_HAS_ADC4                      FALSE

#define STM32_HAS_SDADC1                    FALSE
#define STM32_HAS_SDADC2                    FALSE
#define STM32_HAS_SDADC3                    FALSE

/* CAN attributes.*/
#define STM32_HAS_CAN1                      TRUE
#define STM32_HAS_CAN2                      FALSE
#define STM32_HAS_CAN3                      FALSE
#define STM32_CAN_MAX_FILTERS               14

/* DAC attributes.*/
#define STM32_HAS_DAC1_CH1                  FALSE
#define STM32_HAS_DAC1_CH2                  FALSE
#define STM32_HAS_DAC2_CH1                  FALSE
#define STM32_HAS_DAC2_CH2                  FALSE

/* DMA attributes.*/
#define STM32_ADVANCED_DMA                  FALSE
#define STM32_DMA_SUPPORTS_DMAMUX           FALSE
#define STM32_DMA_SUPPORTS_CSELR            FALSE

#define STM32_DMA1_NUM_CHANNELS             7
#define STM32_DMA1_CH1_HANDLER              DMA0_CHANNEL0
#define STM32_DMA1_CH2_HANDLER              DMA0_CHANNEL1
#define STM32_DMA1_CH3_HANDLER              DMA0_CHANNEL2
#define STM32_DMA1_CH4_HANDLER              DMA0_CHANNEL3
#define STM32_DMA1_CH5_HANDLER              DMA0_CHANNEL4
#define STM32_DMA1_CH6_HANDLER              DMA0_CHANNEL5
#define STM32_DMA1_CH7_HANDLER              DMA0_CHANNEL6
#define STM32_DMA1_CH1_NUMBER               30
#define STM32_DMA1_CH2_NUMBER               31
#define STM32_DMA1_CH3_NUMBER               32
#define STM32_DMA1_CH4_NUMBER               33
#define STM32_DMA1_CH5_NUMBER               34
#define STM32_DMA1_CH6_NUMBER               35
#define STM32_DMA1_CH7_NUMBER               36

#define STM32_DMA2_NUM_CHANNELS             0

/* ETH attributes.*/
#define STM32_HAS_ETH                       FALSE

/* EXTI attributes.*/
#define STM32_EXTI_NUM_LINES                19
#define STM32_EXTI_IMR_MASK                 0x00000000U

/* Flash attributes.*/
#define STM32_FLASH_NUMBER_OF_BANKS         1
#define STM32_FLASH_SECTOR_SIZE             1024U
#if !defined(STM32_FLASH_SECTORS_PER_BANK) || defined(__DOXYGEN__)
#define STM32_FLASH_SECTORS_PER_BANK        128 /* Maximum, can be redefined.*/
#endif

/* GPIO attributes.*/
#define STM32_HAS_GPIOA                     TRUE
#define STM32_HAS_GPIOB                     TRUE
#define STM32_HAS_GPIOC                     TRUE
#define STM32_HAS_GPIOD                     TRUE
#define STM32_HAS_GPIOE                     TRUE
#define STM32_HAS_GPIOF                     FALSE
#define STM32_HAS_GPIOG                     FALSE
#define STM32_HAS_GPIOH                     FALSE
#define STM32_HAS_GPIOI                     FALSE
#define STM32_HAS_GPIOJ                     FALSE
#define STM32_HAS_GPIOK                     FALSE

/* I2C attributes.*/
#define STM32_HAS_I2C1                      TRUE
#define STM32_I2C_I2C1_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 7)
#define STM32_I2C_I2C1_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 6)

#define STM32_HAS_I2C2                      TRUE
#define STM32_I2C_I2C2_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 5)
#define STM32_I2C_I2C2_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 4)

#define STM32_HAS_I2C3                      FALSE
#define STM32_HAS_I2C4                      FALSE

/* QUADSPI attributes.*/
#define STM32_HAS_QUADSPI1                  FALSE

/* RTC attributes.*/
#define STM32_HAS_RTC                       TRUE
#define STM32_RTC_HAS_SUBSECONDS            TRUE
#define STM32_RTC_IS_CALENDAR               FALSE

/* SDIO attributes.*/
#define STM32_HAS_SDIO                      FALSE

/* SPI attributes.*/
#define STM32_HAS_SPI1                      TRUE
#define STM32_SPI1_SUPPORTS_I2S             FALSE
#define STM32_SPI_SPI1_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 2)
#define STM32_SPI_SPI1_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 3)

#define STM32_HAS_SPI2                      TRUE
#define STM32_SPI2_SUPPORTS_I2S             FALSE
#define STM32_SPI_SPI2_RX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 4)
#define STM32_SPI_SPI2_TX_DMA_STREAM        STM32_DMA_STREAM_ID(1, 5)

#define STM32_HAS_SPI3                      FALSE
#define STM32_HAS_SPI4                      FALSE
#define STM32_HAS_SPI5                      FALSE
#define STM32_HAS_SPI6                      FALSE

/* TIM attributes.*/
#define STM32_TIM_MAX_CHANNELS              4

#define STM32_HAS_TIM1                      TRUE
#define STM32_TIM1_IS_32BITS                FALSE
#define STM32_TIM1_CHANNELS                 4

#define STM32_HAS_TIM2                      TRUE
#define STM32_TIM2_IS_32BITS                FALSE
#define STM32_TIM2_CHANNELS                 4

#define STM32_HAS_TIM3                      TRUE
#define STM32_TIM3_IS_32BITS                FALSE
#define STM32_TIM3_CHANNELS                 4

#define STM32_HAS_TIM4                      TRUE
#define STM32_TIM4_IS_32BITS                FALSE
#define STM32_TIM4_CHANNELS                 4

#define STM32_HAS_TIM5                      FALSE
#define STM32_HAS_TIM6                      FALSE
#define STM32_HAS_TIM7                      FALSE
#define STM32_HAS_TIM8                      FALSE
#define STM32_HAS_TIM9                      FALSE
#define STM32_HAS_TIM10                     FALSE
#define STM32_HAS_TIM11                     FALSE
#define STM32_HAS_TIM12                     FALSE
#define STM32_HAS_TIM13                     FALSE
#define STM32_HAS_TIM14                     FALSE
#define STM32_HAS_TIM15                     FALSE
#define STM32_HAS_TIM16                     FALSE
#define STM32_HAS_TIM17                     FALSE
#define STM32_HAS_TIM18                     FALSE
#define STM32_HAS_TIM19                     FALSE
#define STM32_HAS_TIM20                     FALSE
#define STM32_HAS_TIM21                     FALSE
#define STM32_HAS_TIM22                     FALSE

/* USART attributes.*/
#define STM32_HAS_USART1                    TRUE
#define STM32_UART_USART1_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 5)
#define STM32_UART_USART1_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 4)

#define STM32_HAS_USART2                    TRUE
#define STM32_UART_USART2_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 6)
#define STM32_UART_USART2_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 7)

#define STM32_HAS_USART3                    TRUE
#define STM32_UART_USART3_RX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 3)
#define STM32_UART_USART3_TX_DMA_STREAM     STM32_DMA_STREAM_ID(1, 2)

#define STM32_HAS_UART4                     FALSE
#define STM32_HAS_UART5                     FALSE
#define STM32_HAS_USART6                    FALSE
#define STM32_HAS_UART7                     FALSE
#define STM32_HAS_UART8                     FALSE
#define STM32_HAS_LPUART1                   FALSE

/* USB attributes.*/
#define STM32_OTG_STEPPING                  1
#define STM32_HAS_OTG1                      TRUE
#define STM32_OTG1_ENDPOINTS                3

#define STM32_HAS_OTG2                      FALSE
#define STM32_HAS_USB                       TRUE

/* IWDG attributes.*/
#define STM32_HAS_IWDG                      TRUE
#define STM32_IWDG_IS_WINDOWED              FALSE

/* LTDC attributes.*/
#define STM32_HAS_LTDC                      FALSE

/* DMA2D attributes.*/
#define STM32_HAS_DMA2D                     FALSE

/* FSMC attributes.*/
#define STM32_HAS_FSMC                      FALSE

/* CRC attributes.*/
#define STM32_HAS_CRC                       TRUE
#define STM32_CRC_PROGRAMMABLE              FALSE
/** @} */
#endif /* defined(STM32F10X_MD) */


#endif /* STM32_REGISTRY_H */

/** @} */
