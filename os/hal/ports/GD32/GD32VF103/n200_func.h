// See LICENSE file for licence details

#ifndef N200_FUNC_H
#define N200_FUNC_H

#include "n200_eclic.h"
#include "n200_timer.h"
#include <stddef.h>

#define ECLIC_GROUP_LEVEL0_PRIO4 0
#define ECLIC_GROUP_LEVEL1_PRIO3 1
#define ECLIC_GROUP_LEVEL2_PRIO2 2
#define ECLIC_GROUP_LEVEL3_PRIO1 3
#define ECLIC_GROUP_LEVEL4_PRIO0 4

void pmp_open_all_space(void);

void switch_m2u_mode(void);

uint32_t get_mtime_freq(void);

__attribute__((always_inline)) static inline uint32_t mtime_lo(void) {
  return *(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME);
}

__attribute__((always_inline)) static inline uint32_t mtime_hi(void) {
  return *(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME + 4);
}

__attribute__((always_inline)) static inline uint64_t get_timer_value(void) {
  return *(volatile uint64_t *)(TIMER_CTRL_ADDR + TIMER_MTIME);
  while (1) {
    uint32_t hi = mtime_hi();
    uint32_t lo = mtime_lo();
    if (hi == mtime_hi())
      return ((uint64_t)hi << 32) | lo;
  }
}

__attribute__((always_inline)) static inline void clear_timer(void) {
  *(volatile uint64_t *)(TIMER_CTRL_ADDR + TIMER_MTIME) = 0;
}

uint64_t get_mtime_value(void);

uint64_t get_instret_value(void);

uint64_t get_cycle_value(void);

///////////////////////////////////////////////////////////////////
/////// ECLIC relevant functions
///////
void eclic_init(uint32_t num_irq);

__attribute__((always_inline)) static inline void eclic_enable_interrupt(uint32_t source) {
  *(volatile uint8_t *)(ECLIC_ADDR_BASE + ECLIC_INT_IE_OFFSET + source * 4) = 1;
}

__attribute__((always_inline)) static inline void eclic_disable_interrupt(uint32_t source) {
  *(volatile uint8_t *)(ECLIC_ADDR_BASE + ECLIC_INT_IE_OFFSET + source * 4) = 0;
}

__attribute__((always_inline)) static inline uint32_t eclic_interrupt_is_enabled(uint32_t source){
  return *(volatile uint8_t *)(ECLIC_ADDR_BASE + ECLIC_INT_IE_OFFSET + source * 4) == 1;
}

void eclic_set_pending(uint32_t source);
void eclic_clear_pending(uint32_t source);

static inline uint32_t eclic_is_pending(uint32_t source) {
  return *(volatile uint8_t *)(ECLIC_ADDR_BASE + ECLIC_INT_IP_OFFSET +
                               source * 4) == 1;
}

__attribute__((always_inline)) static inline void eclic_set_intctrl (uint32_t source, uint8_t intctrl){
  *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTRL_OFFSET+source*4) = intctrl;
}
__attribute__((always_inline)) static inline uint8_t eclic_get_intctrl  (uint32_t source){
  return *(volatile uint8_t*)(ECLIC_ADDR_BASE+ECLIC_INT_CTRL_OFFSET+source*4);
}

void eclic_set_intattr(uint32_t source, uint8_t intattr);
uint8_t eclic_get_intattr(uint32_t source);

void eclic_set_cliccfg(uint8_t cliccfg);
uint8_t eclic_get_cliccfg(void);

void eclic_set_mth(uint8_t mth);
uint8_t eclic_get_mth(void);

// sets nlbits
void eclic_set_nlbits(uint8_t nlbits);

// get nlbits
uint8_t eclic_get_nlbits(void);

//sets an interrupt level based encoding of nlbits and ECLICINTCTLBITS
__attribute__((always_inline)) static inline void eclic_set_irq_lvl(uint32_t source, uint8_t lvl) {
  //extract nlbits
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  //shift lvl right to mask off unused bits
  lvl = lvl >> (8-nlbits);
  //shift lvl into correct bit position
  lvl = lvl << (8-nlbits);
 
  //write to clicintctrl
  uint8_t current_intctrl = eclic_get_intctrl(source);
  //shift intctrl left to mask off unused bits
  current_intctrl = current_intctrl << nlbits;
  //shift intctrl into correct bit position
  current_intctrl = current_intctrl >> nlbits;

  eclic_set_intctrl(source, (current_intctrl | lvl));
}
uint8_t eclic_get_irq_lvl(uint32_t source);


__attribute__((always_inline)) static inline void eclic_set_irq_lvl_abs(uint32_t source, uint8_t lvl_abs) {
  //extract nlbits
  uint8_t nlbits = eclic_get_nlbits();
  if (nlbits > ECLICINTCTLBITS) {
    nlbits = ECLICINTCTLBITS;
  }

  //shift lvl_abs into correct bit position
  uint8_t lvl = lvl_abs << (8-nlbits);
 
  //write to clicintctrl
  uint8_t current_intctrl = eclic_get_intctrl(source);
  //shift intctrl left to mask off unused bits
  current_intctrl = current_intctrl << nlbits;
  //shift intctrl into correct bit position
  current_intctrl = current_intctrl >> nlbits;

  eclic_set_intctrl(source, (current_intctrl | lvl));
}

uint8_t eclic_get_irq_lvl_abs(uint32_t source);

uint8_t eclic_set_irq_priority(uint32_t source, uint8_t priority);
uint8_t eclic_get_irq_priority(uint32_t source);

void eclic_mode_enable(void);

void eclic_set_vmode(uint32_t source);
void eclic_set_nonvmode(uint32_t source);

void eclic_set_level_trig(uint32_t source);
void eclic_set_posedge_trig(uint32_t source);
void eclic_set_negedge_trig(uint32_t source);

///** \brief  Wait For Interrupt
//
//    Wait For Interrupt is a hint instruction that suspends execution
//    until one of a number of events occurs.
// */
__attribute__((always_inline)) static inline void __WFI(void) {
  __asm volatile("wfi");
}
//
//
/** \brief  Wait For Event

    Wait For Event is a hint instruction that permits the processor to enter
    a low-power state until one of a number of events occurs.
 */
__attribute__((always_inline)) static inline void __WFE(void) {
  __asm volatile("csrs 0x810, 0x1");
  __asm volatile("wfi");
  __asm volatile("csrc 0x810, 0x1");
}

#endif
