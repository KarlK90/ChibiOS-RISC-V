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

#endif

