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
 * @file    GPIOv2/stm32_gpio.h
 * @brief   STM32 GPIO units common header.
 * @note    This file requires definitions from the ST STM32 header file.
 *
 * @addtogroup STM32_GPIOv2
 * @{
 */

#ifndef STM32_GPIO_H
#define STM32_GPIO_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/


/**
 * @name    GPIO ports definitions
 * @{
 */
#define GPIOA                           ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB                           ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC                           ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD                           ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE                           ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF                           ((GPIO_TypeDef *)GPIOF_BASE)
#define GPIOG                           ((GPIO_TypeDef *)GPIOG_BASE)
#define GPIOH                           ((GPIO_TypeDef *)GPIOH_BASE)
#define GPIOI                           ((GPIO_TypeDef *)GPIOI_BASE)
#define GPIOJ                           ((GPIO_TypeDef *)GPIOJ_BASE)
#define GPIOK                           ((GPIO_TypeDef *)GPIOK_BASE)
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   STM32 GPIO registers block.
 */
/*typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#endif /* STM32_GPIO_H */

/** @} */

