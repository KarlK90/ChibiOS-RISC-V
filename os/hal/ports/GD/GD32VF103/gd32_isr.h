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
 * @file    GD32F1xx/stm32_isr.h
 * @brief   GD32F3xx ISR handler header.
 *
 * @addtogroup GD32F1xx_ISR
 * @{
 */

#ifndef STM32_ISR_H
#define STM32_ISR_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    ISR names and numbers remapping
 * @{
 */
/*
 * CAN units.
 */
#define STM32_CAN1_TX_HANDLER       CAN0_TX
#define STM32_CAN1_RX0_HANDLER      CAN0_RX0
#define STM32_CAN1_RX1_HANDLER      CAN0_RX1
#define STM32_CAN1_SCE_HANDLER      CAN0_EWMC
#define STM32_CAN2_TX_HANDLER       CAN1_TX
#define STM32_CAN2_RX0_HANDLER      CAN1_RX0
#define STM32_CAN2_RX1_HANDLER      CAN1_RX1
#define STM32_CAN2_SCE_HANDLER      CAN1_EWMC

#define STM32_CAN1_TX_NUMBER        38
#define STM32_CAN1_RX0_NUMBER       39
#define STM32_CAN1_RX1_NUMBER       40
#define STM32_CAN1_SCE_NUMBER       41
#define STM32_CAN2_TX_NUMBER        82
#define STM32_CAN2_RX0_NUMBER       83
#define STM32_CAN2_RX1_NUMBER       84
#define STM32_CAN2_SCE_NUMBER       85

/*
 * I2C units.
 */
#define STM32_I2C1_EVENT_HANDLER    I2C1_EV
#define STM32_I2C1_ERROR_HANDLER    I2C1_ER
#define STM32_I2C1_EVENT_NUMBER     50
#define STM32_I2C1_ERROR_NUMBER     51

#define STM32_I2C2_EVENT_HANDLER    I2C2_EV
#define STM32_I2C2_ERROR_HANDLER    I2C2_ER
#define STM32_I2C2_EVENT_NUMBER     52
#define STM32_I2C2_ERROR_NUMBER     53


//TODO possibly not available
/*
 * SDIO unit.
 */
#define STM32_SDIO_HANDLER          Vector104

#define STM32_SDIO_NUMBER           49

/*
 * TIM units.
 */
#define STM32_TIM1_UP_HANDLER       TIMER0_UP
#define STM32_TIM1_CC_HANDLER       TIMER0_CHANNEL
#define STM32_TIM2_HANDLER          TIMER1
#define STM32_TIM3_HANDLER          TIMER2
#define STM32_TIM4_HANDLER          TIMER3
#define STM32_TIM5_HANDLER          TIMER4
#define STM32_TIM6_HANDLER          TIMER5
#define STM32_TIM7_HANDLER          TIMER6
// TODO NA 
// #define STM32_TIM8_UP_HANDLER       VectorF0
// #define STM32_TIM8_CC_HANDLER       VectorF8
// #define STM32_TIM9_HANDLER          VectorA0 /* Note: same as STM32_TIM1_BRK */
// #define STM32_TIM10_HANDLER         VectorA4 /* Note: same as STM32_TIM1_UP */
// #define STM32_TIM11_HANDLER         VectorA8 /* Note: same as STM32_TIM1_TRG_COM */
// #define STM32_TIM12_HANDLER         VectorEC /* Note: same as STM32_TIM8_BRK */
// #define STM32_TIM13_HANDLER         VectorF0 /* Note: same as STM32_TIM8_UP */
// #define STM32_TIM14_HANDLER         VectorF4 /* Note: same as STM32_TIM8_TRG_COM */

#define STM32_TIM1_UP_NUMBER        44
#define STM32_TIM1_CC_NUMBER        46
#define STM32_TIM2_NUMBER           47
#define STM32_TIM3_NUMBER           48
#define STM32_TIM4_NUMBER           49
#define STM32_TIM5_NUMBER           69
#define STM32_TIM6_NUMBER           73
#define STM32_TIM7_NUMBER           74
// #define STM32_TIM8_UP_NUMBER        44
// #define STM32_TIM8_CC_NUMBER        46
// #define STM32_TIM9_NUMBER           24 /* Note: same as STM32_TIM1_BRK */
// #define STM32_TIM10_NUMBER          25 /* Note: same as STM32_TIM1_UP */
// #define STM32_TIM11_NUMBER          26 /* Note: same as STM32_TIM1_TRG_COM */
// #define STM32_TIM12_NUMBER          43 /* Note: same as STM32_TIM8_BRK */
// #define STM32_TIM13_NUMBER          44 /* Note: same as STM32_TIM8_UP */
// #define STM32_TIM14_NUMBER          45 /* Note: same as STM32_TIM8_TRG_COM */

/*
 * USART units.
 */
#define STM32_USART1_HANDLER        USART0
#define STM32_USART2_HANDLER        USART1
#define STM32_USART3_HANDLER        USART2
#define STM32_UART4_HANDLER         UART3
#define STM32_UART5_HANDLER         UART4

#define STM32_USART1_NUMBER         56
#define STM32_USART2_NUMBER         57
#define STM32_USART3_NUMBER         58
#define STM32_UART4_NUMBER          71
#define STM32_UART5_NUMBER          72

/*
 * OTG units.
 */
#define STM32_OTG1_HANDLER          USBFS
#define STM32_OTG1_NUMBER           86

/*
 * RTC unit
 */
#define STM32_RTC1_HANDLER          RTC
#define STM32_RTC1_NUMBER           22
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   EXTI0 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI0_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI0_PRIORITY            6
#endif

/**
 * @brief   EXTI1 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI1_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI1_PRIORITY            6
#endif

/**
 * @brief   EXTI2 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI2_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI2_PRIORITY            6
#endif

/**
 * @brief   EXTI3 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI3_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI3_PRIORITY            6
#endif

/**
 * @brief   EXTI4 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI4_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI4_PRIORITY            6
#endif

/**
 * @brief   EXTI9..5 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI5_9_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI5_9_PRIORITY          6
#endif

/**
 * @brief   EXTI15..10 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI10_15_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI10_15_PRIORITY        6
#endif

/**
 * @brief   EXTI16 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI16_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI16_PRIORITY           6
#endif

/**
 * @brief   EXTI17 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI17_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI17_PRIORITY           6
#endif

/**
 * @brief   EXTI18 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI18_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI18_PRIORITY           6
#endif

/**
 * @brief   EXTI19 interrupt priority level setting.
 */
#if !defined(STM32_IRQ_EXTI19_PRIORITY) || defined(__DOXYGEN__)
#define STM32_IRQ_EXTI19_PRIORITY           6
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void irqInit(void);
  void irqDeinit(void);
#ifdef __cplusplus
}
#endif

#endif /* STM32_ISR_H */

/** @} */
