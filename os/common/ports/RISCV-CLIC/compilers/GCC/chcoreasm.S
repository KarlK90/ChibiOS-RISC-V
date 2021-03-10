/*
    ChibiOS - Copyright (C) 2021 Stefan Kerkmann.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    compilers/GCC/chcoreasm.S
 * @brief   RISC-V architecture port low level code.
 *
 * @addtogroup RISCV_GCC_CORE
 * @{
 */

#if !defined(FALSE) || defined(__DOXYGEN__)
#define FALSE   0
#endif

#if !defined(TRUE) || defined(__DOXYGEN__)
#define TRUE    1
#endif

#define _FROM_ASM_
#include "chlicense.h"
#include "chconf.h"
#include "chcore.h"
#include "riscv_encoding.h"

#if !defined(__DOXYGEN__)

/*
 * RTOS-specific context offset.
 */
#if defined(_CHIBIOS_RT_CONF_)
#define CONTEXT_OFFSET  12
#elif defined(_CHIBIOS_NIL_CONF_)
#define CONTEXT_OFFSET  0
#else
#error "invalid chconf.h"
#endif

#define STORE    sw
#define LOAD     lw
#define LOG_REGBYTES 2
#define REGBYTES (1 << LOG_REGBYTES)

.macro DISABLE_MIE
    csrc CSR_MSTATUS, MSTATUS_MIE
.endm

.macro ENABLE_MIE
    csrs CSR_MSTATUS, MSTATUS_MIE
.endm

.macro DISABLE_MPIE
    li a0, MSTATUS_MPIE
    csrc CSR_MSTATUS, a0
.endm

.macro ENABLE_MPIE
    li a0, MSTATUS_MPIE
    csrs CSR_MSTATUS, a0
.endm
/**
 * \brief  Macro for context save
 * \details
 * This macro save ABI defined caller saved registers in the stack.
 * \remarks
 * - This Macro could use to save context when you enter to interrupt
 * or exception
*/
/* Save caller registers */
.macro SAVE_CONTEXT
    /* Allocate stack space for context saving */
#ifndef __riscv_32e
    addi sp, sp, -20*REGBYTES
#else
#error
    addi sp, sp, -14*REGBYTES
#endif /* __riscv_32e */
    /* Store CSR mepc to stack using pushmepc */
    csrrwi  x0, CSR_PUSHMEPC, 12
    /* Store CSR mcause to stack using pushmcause */
    csrrwi  x0, CSR_PUSHMCAUSE, 11
    /* Store CSR msub to stack using pushmsub */
    csrrwi  x0, CSR_PUSHMSUBM, 13

    STORE x1, 0*REGBYTES(sp)
    STORE x4, 1*REGBYTES(sp)
    STORE x5, 2*REGBYTES(sp)
    STORE x6, 3*REGBYTES(sp)
    STORE x7, 4*REGBYTES(sp)
    STORE x10, 5*REGBYTES(sp)
    STORE x11, 6*REGBYTES(sp)
    STORE x12, 7*REGBYTES(sp)
    STORE x13, 8*REGBYTES(sp)
    STORE x14, 9*REGBYTES(sp)
    STORE x15, 10*REGBYTES(sp)
#ifndef __riscv_32e
    STORE x16, 14*REGBYTES(sp)
    STORE x17, 15*REGBYTES(sp)
    STORE x28, 16*REGBYTES(sp)
    STORE x29, 17*REGBYTES(sp)
    STORE x30, 18*REGBYTES(sp)
    STORE x31, 19*REGBYTES(sp)
#endif /* __riscv_32e */
.endm

/**
 * \brief  Macro for restore caller registers
 * \details
 * This macro restore ABI defined caller saved registers from stack.
 * \remarks
 * - You could use this macro to restore context before you want return
 * from interrupt or exeception
 */
/* Restore caller registers */
.macro RESTORE_CONTEXT
    LOAD x1, 0*REGBYTES(sp)
    LOAD x4, 1*REGBYTES(sp)
    LOAD x5, 2*REGBYTES(sp)
    LOAD x6, 3*REGBYTES(sp)
    LOAD x7, 4*REGBYTES(sp)
    LOAD x10, 5*REGBYTES(sp)
    LOAD x11, 6*REGBYTES(sp)
    LOAD x12, 7*REGBYTES(sp)
    LOAD x13, 8*REGBYTES(sp)
    LOAD x14, 9*REGBYTES(sp)
    LOAD x15, 10*REGBYTES(sp)
#ifndef __riscv_32e
    LOAD x16, 14*REGBYTES(sp)
    LOAD x17, 15*REGBYTES(sp)
    LOAD x28, 16*REGBYTES(sp)
    LOAD x29, 17*REGBYTES(sp)
    LOAD x30, 18*REGBYTES(sp)
    LOAD x31, 19*REGBYTES(sp)

    LOAD x5,  13*REGBYTES(sp)
    csrw CSR_MSUBM, x5
    LOAD x5,  12*REGBYTES(sp)
    csrw CSR_MEPC, x5
    LOAD x5,  11*REGBYTES(sp)
    csrw CSR_MCAUSE, x5

    # De-allocate the stack space
    addi sp, sp, 20*REGBYTES
#else
    # De-allocate the stack space
    addi sp, sp, 14*REGBYTES
#endif /* __riscv_32e */

.endm


/*
    Trap entry point (_start_trap)
*/
.section .trap, "ax"
.option push
.option norelax
.align 6
.option pop
.globl _start_trap
    _start_trap:
    # Save the caller saving registers (context)
    SAVE_CONTEXT

    # Set the function argument
    csrr a0, mcause
    mv a1, sp
    csrr a2, CSR_MDCAUSE
    csrr a3, CSR_MSUBM

    # Call the function
    call handle_trap

    # Restore the caller saving registers (context)
    RESTORE_CONTEXT

    # Return to regular code
    mret

/*--------------------------------------------------------------------------*
 * Performs a context switch between two threads.
 * a0 = ntp, a1 = otp
 *--------------------------------------------------------------------------*/
.option push
.option norelax
.align 4
.option pop
.globl  _port_switch
.type _port_switch,@function
_port_switch:
    # OLD THREAD CONTEXT SAVE BEGIN
    # Allocate space for port_intctx structure on the threading stack
    addi sp, sp, -13*REGBYTES

    # Store callee save registers
    STORE      ra, 0*REGBYTES(sp)
    STORE      s0, 1*REGBYTES(sp)
    STORE      s1, 2*REGBYTES(sp)
    STORE      s2, 3*REGBYTES(sp)
    STORE      s3,  4*REGBYTES(sp)
    STORE      s4,  5*REGBYTES(sp)
    STORE      s5,  6*REGBYTES(sp)
    STORE      s6,  7*REGBYTES(sp)
    STORE      s7,  8*REGBYTES(sp)
    STORE      s8,  9*REGBYTES(sp)
    STORE      s9,  10*REGBYTES(sp)
    STORE      s10, 11*REGBYTES(sp)
    STORE      s11, 12*REGBYTES(sp)

    # Store stackpointer in otp->ctx
    STORE      sp, CONTEXT_OFFSET(a1)
    # OLD THREAD CONTEXT SAVE END

    # NEW THREAD CONTEXT RESTORE BEGIN
    # Load stackpointer from ntp->ctx
    LOAD       sp, CONTEXT_OFFSET(a0)

    LOAD      ra, 0*REGBYTES(sp)
    LOAD      s0, 1*REGBYTES(sp)
    LOAD      s1, 2*REGBYTES(sp)
    LOAD      s2, 3*REGBYTES(sp)
    LOAD      s3,  4*REGBYTES(sp)
    LOAD      s4,  5*REGBYTES(sp)
    LOAD      s5,  6*REGBYTES(sp)
    LOAD      s6,  7*REGBYTES(sp)
    LOAD      s7,  8*REGBYTES(sp)
    LOAD      s8,  9*REGBYTES(sp)
    LOAD      s9,  10*REGBYTES(sp)
    LOAD      s10, 11*REGBYTES(sp)
    LOAD      s11, 12*REGBYTES(sp)

    # De-allocate space on the threading stack
    addi sp, sp, 13*REGBYTES
    # NEW THREAD CONTEXT RESTORE END

    # Jump to return address loaded into ra
    ret

/*--------------------------------------------------------------------------*
 * Start a thread by invoking its work function.
 *
 * Threads execution starts here, the code leaves the system critical zone
 * and then jumps into the thread function passed in register S0. The
 * register S1 contains the thread parameter. The function chThdExit() is
 * called on thread function return.
 *--------------------------------------------------------------------------*/
.globl  _port_thread_start
_port_thread_start:
#if CH_DBG_SYSTEM_STATE_CHECK
    jal     ra, _dbg_check_unlock
#endif
#if CH_DBG_STATISTICS
    jal     ra, _stats_stop_measure_crit_thd
#endif

    csrsi   mstatus, 0x8
    mv      a0, s1
    jalr    ra, s0
    li      a0, 0              /* MSG_OK */
    jal     ra, chThdExit
_zombies:       j       _zombies


# IRQ entry point
.section .text.irq
.option push
.option norelax
.align 4
.option pop
.globl _irq_handler
_irq_handler:
    # Save all caller registers and csr registers on the thread stack
    SAVE_CONTEXT

    # The special CSR read/write operation, which is actually Claim the CLIC to
    # find its pending highest ID, if the ID is not 0, then automatically enable
    # the mstatus.MIE, and jump to its vector-entry-label, and update the link register.
    csrrw   ra, CSR_JALMNXTI, ra

    # Critical Section Disable Interrupts Globaly
    DISABLE_MIE

    # No reschedule is necessary, just restore irq context and exit machine mode.
    beq     a0, zero, _port_exit_from_isr

    # Context switch is necessary, load switching routine into mepc
    la      a0, _port_switch_from_isr
    csrw    mepc, a0

    # Context switch is a critical section, so disable interrupts on return.
    DISABLE_MPIE

    mret



.globl handle_trap
.weak handle_trap
handle_trap:
    j       handle_trap  # jump to handle_trap

/*--------------------------------------------------------------------------*
 * Post-IRQ switch code.
 *
 * Exception handlers return here for context switching.
 *--------------------------------------------------------------------------*/
.globl _port_switch_from_isr
_port_switch_from_isr:
#if CH_DBG_STATISTICS
    jal     ra, _stats_start_measure_crit_thd
#endif
#if CH_DBG_SYSTEM_STATE_CHECK
    jal     ra, _dbg_check_lock
#endif
    # Calls _port_switch at the end of the function
    jal     ra, chSchDoReschedule
#if CH_DBG_SYSTEM_STATE_CHECK
    jal     ra, _dbg_check_unlock
#endif
#if CH_DBG_STATISTICS
    jal     ra, _stats_stop_measure_crit_thd
#endif

    # Enable interrupts after leaving the interrupt handler
    ENABLE_MPIE

.globl _port_exit_from_isr
_port_exit_from_isr:
    # Restore caller registers and csr registers from the thread stack
    RESTORE_CONTEXT

    # Leave machine mode and return to address stored in mepc
    mret

#endif /* !defined(__DOXYGEN__) */

/** @} */
