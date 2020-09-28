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
 * @file    hal_st_lld.h
 * @brief   RISC-V ST subsystem low level driver header.
 * @details This header is designed to be include-able without having to
 *          include other files from the HAL.
 *
 * @addtogroup ST
 * @{
 */

#ifndef HAL_ST_LLD_H
#define HAL_ST_LLD_H
// TODO(pseidel): Assumes only 1 hart

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define RISCV_MTIMECMP0 TIMER_REG64(TIMER_MTIMECMP)
#define RISCV_MTIMECMPH0 TIMER_REG(TIMER_MTIMECMP + 4)

#define RISCV_MTIME TIMER_REG64(TIMER_MTIME)
#define RISCV_MTIMEL TIMER_REG(TIMER_MTIME)
#define RISCV_MTIMEH TIMER_REG(TIMER_MTIME + 4)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#ifndef RISCV_HAS_CLIC
#error "clint/hal_st_lld.h requires the device to have a CLIC"
#endif

#if CH_CFG_ST_RESOLUTION != 64
#error "RISC-V requires CH_CFG_ST_RESOLUTION == 64"
#endif

#if CH_CFG_ST_FREQUENCY != 32768
//#error "RISC-V requires CH_CFG_ST_FREQUENCY == 32768"
#endif

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
void st_lld_init(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Driver inline functions.                                                  */
/*===========================================================================*/

/**
 * @brief   Returns the time counter value.
 *
 * @return              The counter value.
 *
 * @notapi
 */
__attribute__((always_inline)) static inline systime_t
st_lld_get_counter(void) {
  uint32_t high, low, temp;
  do {
    high = RISCV_MTIMEH;
    low = RISCV_MTIMEL;
    temp = RISCV_MTIMEH;
  } while (high != temp);

  return (((systime_t)high) << 32) | (systime_t)low;
  // while (true) {
  //   uint32_t mtime_h = RISCV_MTIMEH;
  //   /* Check if timer wrapping occured while we read the higher bits. */
  //   if (mtime_h == RISCV_MTIMEH) {
  //     return ((systime_t)mtime_h << 32) | RISCV_MTIMEL;
  //   }
  // }
}

/**
 * @brief   Starts the alarm.
 * @note    Makes sure that no spurious alarms are triggered after
 *          this call.
 *
 * @param[in] abstime   the time to be set for the first alarm
 *
 * @notapi
 */
__attribute__((always_inline)) static inline void
st_lld_start_alarm(systime_t abstime) {
  eclic_enable_interrupt(CLIC_INT_TMR);
  eclic_set_level_trig(CLIC_INT_TMR);
  //eclic_set_irq_lvl_abs(CLIC_INT_TMR, 1);
  eclic_set_irq_priority(CLIC_INT_TMR, STM32_ST_IRQ_PRIORITY);
  RISCV_MTIMECMP0 = abstime;
}

/**
 * @brief   Stops the alarm interrupt.
 *
 * @notapi
 */
__attribute__((always_inline)) static inline void st_lld_stop_alarm(void) {
  eclic_disable_interrupt(CLIC_INT_TMR);
  RISCV_MTIMECMP0 = (uint32_t)(~0);
}

/**
 * @brief   Sets the alarm time.
 *
 * @param[in] abstime   the time to be set for the next alarm
 *
 * @notapi
 */
__attribute__((always_inline)) static inline void
st_lld_set_alarm(systime_t abstime) {
  RISCV_MTIMECMP0 = abstime;
}

/**
 * @brief   Returns the current alarm time.
 *
 * @return              The currently set alarm time.
 *
 * @notapi
 */
__attribute__((always_inline)) static inline systime_t st_lld_get_alarm(void) {
  return (systime_t)RISCV_MTIMECMP0;
}

/**
 * @brief   Determines if the alarm is active.
 *
 * @return              The alarm status.
 * @retval false        if the alarm is not active.
 * @retval true         is the alarm is active
 *
 * @notapi
 */
__attribute__((always_inline)) static inline bool st_lld_is_alarm_active(void) {
  // return (bool)(1);
  // return false;//todo fix me
  return eclic_is_pending(CLIC_INT_TMR);
}

#endif /* HAL_ST_LLD_H */

/** @} */
