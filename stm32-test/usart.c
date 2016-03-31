#include <stdint.h>
/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include <libopencmsis/core_cm3.h>

#include "xl_320.h"

 static void clock_setup(void)
 {
   /* Enable GPIOD clock for LED & USARTs. */
   rcc_periph_clock_enable(RCC_GPIOD);
   rcc_periph_clock_enable(RCC_GPIOA);

   /* Enable clocks for USART2. */
   rcc_periph_clock_enable(RCC_USART2);
 }

static void usart_setup(void)
{
  /* Setup USART2 parameters. */
  usart_set_baudrate(USART2, 1000000);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

  /* half duplex cuz wooo */
  USART_CR3(USART2) |= USART_CR3_HDSEL;
  USART_CR2(USART2) &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
  USART_CR3(USART2) &= ~(USART_CR3_SCEN | USART_CR3_IREN);

  /* Finally enable the USART. */
  usart_enable(USART2);
}

static void gpio_setup(void)
{
  /* Setup GPIO pin GPIO12 on GPIO port D for LED. */
  gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);

  /* Setup GPIO pins for USART2 transmit. */
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);

  /* Setup USART2 TX pin as alternate function. */
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

static void send(char* buff, uint8_t size) {
  for(int i=0; i<size; i++)
    usart_send_blocking(USART2, buff[i]);
}

void delay() {
  static volatile int i;
  for (i = 0; i < 300000; i++) {        //* Wait a bit. *\/ */
    __asm__("NOP");
  }
}

const struct rcc_clock_scale rcc_hse_8mhz_3v3_perf =
  { /* 120MHz */
    .pllm = 8,
    .plln = 240,
    .pllp = 2,
    .pllq = 5,
    .hpre = RCC_CFGR_HPRE_DIV_NONE,
    .ppre1 = RCC_CFGR_PPRE_DIV_4,
    .ppre2 = RCC_CFGR_PPRE_DIV_2,
    //.power_save = 1,
    .flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
    FLASH_ACR_LATENCY_3WS,
    .apb1_frequency = 30000000,
    .apb2_frequency = 60000000,
  };

int main(void)
{
  volatile int i;

  /* main clock */
  rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3_perf);

  clock_setup();
  gpio_setup();
  usart_setup();

  _XL_320_GROUP group = create_servo_grp(&send);
  _XL_320 servo = create_servo(1, &group);

  delay();
  set_control_mode_servo(servo, JOIN, 1);
  set_torque_servo(servo, 1050, 1);
  delay();

  while (1) {
    gpio_toggle(GPIOD, GPIO12);
    set_led_color_servo(servo, LED_BLUE, 1);
    set_angle_servo(servo, 0, 1);
    delay();
    set_led_color_servo(servo, LED_WHITE, 1);
    set_angle_servo(servo, 512, 1);
    delay();
    set_led_color_servo(servo, LED_RED, 1);
    set_angle_servo(servo, 1023, 1);
    delay();

  }
  return 0;
}
