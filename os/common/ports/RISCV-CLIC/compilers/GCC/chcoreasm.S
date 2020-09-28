/*
    ChibiOS - Copyright (C) 2020 Patrick Seidel.

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

#define CSR_MSTATUS     0x300
#define CSR_MTVT        0x307
#define CSR_MEPC        0x341
#define CSR_MCAUSE      0x342
#define CSR_MTVT2       0x7EC
#define CSR_JALMNXTI    0x7ED
#define CSR_PUSHMCAUSE  0x7EE
#define CSR_PUSHMEPC    0x7EF
#define CSR_PUSHMSUBM   0x7EB
#define CSR_MMISC_CTL   0x7d0
#define CSR_MSUBM       0x7c4

#define MSTATUS_MIE     0x00000008

.macro DISABLE_MIE
  csrc CSR_MSTATUS, MSTATUS_MIE
.endm

.macro SAVE_CONTEXT
  addi sp, sp, -20*REGBYTES

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
  STORE x16, 11*REGBYTES(sp)
  STORE x17, 12*REGBYTES(sp)
  STORE x28, 13*REGBYTES(sp)
  STORE x29, 14*REGBYTES(sp)
  STORE x30, 15*REGBYTES(sp)
  STORE x31, 16*REGBYTES(sp)
.endm

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
  LOAD x16, 11*REGBYTES(sp)
  LOAD x17, 12*REGBYTES(sp)
  LOAD x28, 13*REGBYTES(sp)
  LOAD x29, 14*REGBYTES(sp)
  LOAD x30, 15*REGBYTES(sp)
  LOAD x31, 16*REGBYTES(sp)
  // De-allocate the stack space
  addi sp, sp, 20*REGBYTES
.endm


###############################################
###############################################
# Save the mepc and mstatus
#
.macro SAVE_EPC_STATUS
  csrr x5, CSR_MEPC  
  STORE x5,  16*REGBYTES(sp)
  csrr x5, CSR_MSTATUS  
  STORE x5,  17*REGBYTES(sp)
  csrr x5, CSR_MSUBM  
  STORE x5,  18*REGBYTES(sp)
.endm

###############################################
###############################################
# Restore the mepc and mstatus
#
.macro RESTORE_EPC_STATUS
  LOAD x5,  16*REGBYTES(sp)
  csrw CSR_MEPC, x5  
  LOAD x5,  17*REGBYTES(sp)
  csrw CSR_MSTATUS, x5  
  LOAD x5,  18*REGBYTES(sp)
  csrw CSR_MSUBM, x5  
.endm

/*
    Trap entry point (_start_trap)
*/
.section .trap, "ax"
.option push
.option norelax
.align 6
.option pop
.global _start_trap
    _start_trap:
    // Save the caller saving registers (context)
    SAVE_CONTEXT
    // Save the MEPC/Mstatus/Msubm reg
    SAVE_EPC_STATUS

        // Set the function argument
    csrr a0, mcause
    mv a1, sp
        // Call the function
    call handle_trap

    // Restore the MEPC/Mstatus/Msubm reg
    RESTORE_EPC_STATUS
    // Restore the caller saving registers (context)
    RESTORE_CONTEXT

    // De-allocate the stack space
    // addi sp, sp, 19*REGBYTES
    // Return to regular code
    mret

/*--------------------------------------------------------------------------*
 * Performs a context switch between two threads.
 * a0 = ntp, a1 = otp
 *--------------------------------------------------------------------------*/
                .globl  _port_switch
_port_switch:
                sw      ra, -52(sp) //port_intctx
                sw      s0, -48(sp)
                sw      s1, -44(sp)
                sw      s2, -40(sp)
                sw      s3, -36(sp)
                sw      s4, -32(sp)
                sw      s5, -28(sp)
                sw      s6, -24(sp)
                sw      s7, -20(sp)
                sw      s8, -16(sp)
                sw      s9, -12(sp)
                sw      s10, -8(sp)
                sw      s11, -4(sp)

                sw      sp, CONTEXT_OFFSET(a1)
                lw      sp, CONTEXT_OFFSET(a0)

                lw      ra, -52(sp)
                lw      s0, -48(sp)
                lw      s1, -44(sp)
                lw      s2, -40(sp)
                lw      s3, -36(sp)
                lw      s4, -32(sp)
                lw      s5, -28(sp)
                lw      s6, -24(sp)
                lw      s7, -20(sp)
                lw      s8, -16(sp)
                lw      s9, -12(sp)
                lw      s10, -8(sp)
                lw      s11, -4(sp)
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

// IRQ entry point
.section .text.irq
.option push
.option norelax
.align 2
.option pop
.global _irq_handler
_irq_handler:
    addi    sp, sp, -80 //port_extctx

    SAVE_EPC_STATUS
    
    // alle caller save register auf dem stack speichern, eqvlt. zu SAVE_CONTEXT exkl. tp register
    sw      a0, 0(sp)
    sw      a1, 4(sp)
    sw      a2, 8(sp)
    sw      a3, 12(sp)
    sw      a4, 16(sp)
    sw      a5, 20(sp)
    sw      a6, 24(sp)
    sw      a7, 28(sp)
    sw      t0, 32(sp)
    sw      t1, 36(sp)
    sw      t2, 40(sp)
    sw      t3, 44(sp)
    sw      t4, 48(sp)
    sw      t5, 52(sp)
    sw      t6, 56(sp)
    sw      ra, 60(sp)

    // The special CSR read/write operation, which is actually Claim the CLIC to
    // find its pending highest ID, if the ID is not 0, then automatically enable
    // the mstatus.MIE, and jump to its vector-entry-label, and update the link register.
    csrrw ra, CSR_JALMNXTI, ra
    
    // Critical Section Disable Interrupts Globaly
    DISABLE_MIE

    beq     a0, zero, _port_exit_from_isr
    j       _port_switch_from_isr

.global handle_trap
.weak handle_trap
handle_trap:
    j handle_trap  # jump to handle_trap

/*--------------------------------------------------------------------------*
 * Post-IRQ switch code.
 *
 * Exception handlers return here for context switching.
 *--------------------------------------------------------------------------*/

// context switch in dem der neue programm counter in mepc geschrieben wird
.global _port_switch_from_isr
_port_switch_from_isr:
#if CH_DBG_STATISTICS
                jal     ra, _stats_start_measure_crit_thd
#endif
#if CH_DBG_SYSTEM_STATE_CHECK
                jal     ra, _dbg_check_lock
#endif
                jal     ra, chSchDoReschedule
#if CH_DBG_SYSTEM_STATE_CHECK
                jal     ra, _dbg_check_unlock
#endif
#if CH_DBG_STATISTICS
                jal     ra, _stats_stop_measure_crit_thd
#endif

.global _port_exit_from_isr
_port_exit_from_isr:
                lw      a0, 0(sp)
                lw      a1, 4(sp)
                lw      a2, 8(sp)
                lw      a3, 12(sp)
                lw      a4, 16(sp)
                lw      a5, 20(sp)
                lw      a6, 24(sp)
                lw      a7, 28(sp)
                lw      t0, 32(sp)
                lw      t1, 36(sp)
                lw      t2, 40(sp)
                lw      t3, 44(sp)
                lw      t4, 48(sp)
                lw      t5, 52(sp)
                lw      t6, 56(sp)
                lw      ra, 60(sp)

                RESTORE_EPC_STATUS

                addi    sp, sp, 80
                mret

#endif /* !defined(__DOXYGEN__) */

/** @} */
