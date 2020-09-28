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
 * @file    FE310/riscv_registry.h
 * @brief   FE310 capabilities registry.
 *
 * @addtogroup HAL
 * @{
 */

#ifndef RISCV_REGISTRY_H
#define RISCV_REGISTRY_H

/*===========================================================================*/
/* Platform capabilities.                                                    */
/*===========================================================================*/

/**
 * @name    FE310-G002 capabilities
 * @{
 */
/* CLIC parameters */
#define RISCV_HAS_CLIC
#define CLIC_BASE              0xd2000000

/** @} */

#endif /* RISCV_REGISTRY_H */

/** @} */
