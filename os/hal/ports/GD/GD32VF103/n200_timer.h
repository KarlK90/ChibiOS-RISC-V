// See LICENSE file for licence details

#ifndef N200_TIMER_H
#define N200_TIMER_H

#define TIMER_MSIP 0xFFC
#define TIMER_MSIP_size   0x4
#define TIMER_MTIMECMP 0x8
#define TIMER_MTIMECMP_size 0x8
#define TIMER_MTIME 0x0
#define TIMER_MTIME_size 0x8

#define TIMER_CTRL_ADDR           0xD1000000
#define _REG32(addr, offset) (*(volatile uint32_t *)(uint32_t)(addr + offset))
#define _REG64(addr, offset) (*(volatile uint64_t *)(uint64_t)(addr + offset))
#define TIMER_REG(offset)         _REG32(TIMER_CTRL_ADDR, offset)
#define TIMER_REG64(offset)         _REG64(TIMER_CTRL_ADDR, offset)

#define RISCV_MTIMECMP TIMER_REG64(TIMER_MTIMECMP)
#define RISCV_MTIMECMPL TIMER_REG(TIMER_MTIMECMP)
#define RISCV_MTIMECMPH TIMER_REG(TIMER_MTIMECMP + 4)

#define RISCV_MTIME TIMER_REG64(TIMER_MTIME)
#define RISCV_MTIMEL TIMER_REG(TIMER_MTIME)
#define RISCV_MTIMEH TIMER_REG(TIMER_MTIME + 4)

#endif

