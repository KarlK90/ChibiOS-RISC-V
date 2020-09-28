/*
    ChibiOS - Copyright (C) 2020 Patrick Seidel

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
 * @file    RISCV/GCC/vectors.S
 * @brief   Interrupt vectors for RISC-V devices.
 *
 * @defgroup RISCV_GCC_VECTORS RISC-V Interrupt Vectors
 * @{
 */

#define _FROM_ASM_

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Code section.                                                             */
/*===========================================================================*/

#if !defined(__DOXYGEN__)

.section .text.vectors, "ax"
.global      vectors
.type vectors, %object
.option push 
.option norelax
.align 9
vectors:
    // j _start
    .word     0
    .word     0
    .word     0
    .word     INT_SFT
    .word     0
    .word     0
    .word     0
    .word     INT_TMR
    .word     0
    .word     0
    .word     0
    .word     0
    .word     0
    .word     0
    .word     0
    .word     0
    .word     0
    .word     INT_BWEI
    .word     INT_PMOVI
    .word     WWDGT
    .word     EXTI_LVD
    .word     TAMPER
    .word     RTC
    .word     FMC
    .word     RCU
    .word     EXTI_LINE0
    .word     EXTI_LINE1
    .word     EXTI_LINE2
    .word     EXTI_LINE3
    .word     EXTI_LINE4
    .word     DMA0_CHANNEL0
    .word     DMA0_CHANNEL1
    .word     DMA0_CHANNEL2
    .word     DMA0_CHANNEL3
    .word     DMA0_CHANNEL4
    .word     DMA0_CHANNEL5
    .word     DMA0_CHANNEL6
    .word     ADC0_1
    .word     CAN0_TX
    .word     CAN0_RX0
    .word     CAN0_RX1
    .word     CAN0_EWMC
    .word     EXTI_LINE9_5
    .word     TIMER0_BRK
    .word     TIMER0_UP
    .word     TIMER0_TRG_CMT
    .word     TIMER0_CHANNEL
    .word     TIMER1
    .word     TIMER2
    .word     TIMER3
    .word     I2C1_EV
    .word     I2C1_ER
    .word     I2C2_EV
    .word     I2C2_ER
    .word     SPI0
    .word     SPI1
    .word     USART0
    .word     USART1
    .word     USART2
    .word     EXTI_LINE15_10
    .word     RTC_ALARM
    .word     USBFS_WKUP
    .word     0
    .word     0
    .word     0
    .word     0
    .word     0
    .word     EXMC // not present in Reference Manual but present in vendor HAL
    .word     0
    .word     TIMER4
    .word     SPI2
    .word     UART3
    .word     UART4
    .word     TIMER5
    .word     TIMER6
    .word     DMA1_CHANNEL0
    .word     DMA1_CHANNEL1
    .word     DMA1_CHANNEL2
    .word     DMA1_CHANNEL3
    .word     DMA1_CHANNEL4
    .word     0
    .word     0
    .word     CAN1_TX
    .word     CAN1_RX0
    .word     CAN1_RX1
    .word     CAN1_EWMC
    .word     USBFS
    .size vectors, . - vectors

.weak INT_SFT
.weak INT_TMR
.weak INT_BWEI
.weak INT_PMOVI
.weak WWDGT
.weak EXTI_LVD
.weak TAMPER
.weak RTC
.weak FMC
.weak RCU
.weak EXTI_LINE0
.weak EXTI_LINE1
.weak EXTI_LINE2
.weak EXTI_LINE3
.weak EXTI_LINE4
.weak DMA0_CHANNEL0
.weak DMA0_CHANNEL1
.weak DMA0_CHANNEL2
.weak DMA0_CHANNEL3
.weak DMA0_CHANNEL4
.weak DMA0_CHANNEL5
.weak DMA0_CHANNEL6
.weak ADC0_1
.weak CAN0_TX
.weak CAN0_RX0
.weak CAN0_RX1
.weak CAN0_EWMC
.weak EXTI_LINE9_5
.weak TIMER0_BRK
.weak TIMER0_UP
.weak TIMER0_TRG_CMT
.weak TIMER0_CHANNEL
.weak TIMER1
.weak TIMER2
.weak TIMER3
.weak I2C1_EV
.weak I2C1_ER
.weak I2C2_EV
.weak I2C2_ER
.weak SPI0
.weak SPI1
.weak USART0
.weak USART1
.weak USART2
.weak EXTI_LINE15_10
.weak RTC_ALARM
.weak USBFS_WKUP
.weak EXMC
.weak TIMER4
.weak SPI2
.weak UART3
.weak UART4
.weak TIMER5
.weak TIMER6
.weak DMA1_CHANNEL0
.weak DMA1_CHANNEL1
.weak DMA1_CHANNEL2
.weak DMA1_CHANNEL3
.weak DMA1_CHANNEL4
.weak CAN1_TX
.weak CAN1_RX0
.weak CAN1_RX1
.weak CAN1_EWMC
.weak USBFS

#endif /* !defined(__DOXYGEN__) */

/** @} */
