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

#include "ch.h"
#include "hal.h"
//#include "oslib_test_root.h"
//#include "rt_test_root.h"

extern thread_reference_t blinkerRef;
thread_reference_t blinkerRef = NULL;

static const ioline_t LINE_LED_GREEN = PAL_LINE(GPIOA, 1);
static const ioline_t LINE_LED_BLUE = PAL_LINE(GPIOA, 2);
static const ioline_t LINE_LED_RED = PAL_LINE(GPIOC, 13);

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * an LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;

  chRegSetThreadName("blinker");
  while (true) {
    palToggleLine(LINE_LED_RED);
    chThdSleepMilliseconds(10000);
  }
}

static virtual_timer_t led_vt;

/*
 * LED timer callback.
 */
static void led_cb(void *arg) {

  palToggleLine(LINE_LED_GREEN);
  chSysLockFromISR();
  chVTSetI(&led_vt, TIME_MS2I(1050), led_cb, NULL);
  chSysUnlockFromISR();
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the serial driver 0 using the driver default configuration.
   * GPIO 16(RX) and 17(TX) are routed to UART0.
   */
  // sdStart(&SD0, NULL);
  // palSetPadMode(GPIO0, 16, PAL_MODE_ALTERNATE(0));
  // palSetPadMode(GPIO0, 17, PAL_MODE_ALTERNATE(0));

  palSetLineMode(LINE_LED_GREEN, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_LED_BLUE, PAL_MODE_OUTPUT_PUSHPULL);
  palSetLineMode(LINE_LED_RED, PAL_MODE_OUTPUT_PUSHPULL);

  // Set up the global timer to generate an interrupt every ms.
  // Figure out how many interrupts are available.
  uint32_t max_irqn =
      *(volatile uint32_t *)(ECLIC_ADDR_BASE + ECLIC_INFO_OFFSET);
  max_irqn &= (0x00001FFF);
  // Initialize the 'ECLIC' interrupt controller.
  eclic_init(max_irqn);
  eclic_global_interrupt_enable();
  eclic_set_irq_lvl_abs(CLIC_INT_TMR, 1);
  eclic_set_irq_priority(CLIC_INT_TMR, 1);
  eclic_set_posedge_trig(CLIC_INT_TMR);
  eclic_enable_interrupt(CLIC_INT_TMR);
  nvicEnableVector(CLIC_INT_TMR, 1);
  // test_execute((BaseSequentialStream *)&SD0, &rt_test_suite);
  // test_execute((BaseSequentialStream *)&SD0, &oslib_test_suite);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop.
   */

  /* LED timer initialization.*/
  chVTObjectInit(&led_vt);

  /* Starting blinker.*/
  chVTSet(&led_vt, TIME_MS2I(250), led_cb, NULL);

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1,
                    NULL);

  while (true) {
    palToggleLine(LINE_LED_BLUE);
    chThdSleepMilliseconds(1000);
  }
}

/*__attribute__((weak))*/ uintptr_t handle_nmi() {
  write(1, "nmi\n", 5);
  //_exit(1);
  return 0;
}

/*__attribute__((weak))*/ uintptr_t handle_trap(uintptr_t mcause,
                                                uintptr_t sp) {
  if (mcause == 0xFFF) {
    handle_nmi();
  }
  // write(1, "trap\n", 5);
  // printf("In trap handler, the mcause is %d\n", mcause);
  // printf("In trap handler, the mepc is 0x%x\n", read_csr(mepc));
  // printf("In trap handler, the mtval is 0x%x\n", read_csr(mbadaddr));
  // _exit(mcause);
  return 0;
}