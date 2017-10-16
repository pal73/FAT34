/*----------------------------------------------------------------------------
 * Name:    LED.c
 * Purpose: Low level LED functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2012 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stm32f0xx.h>                  /* STM32F0xx Definitions              */
#include "LED.h"

const unsigned long led_mask[] = {1UL << 8, 1UL << 9};

/*-----------------------------------------------------------------------------
 *      LED_Init:  Initialize LEDs
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Init (void) {

  /* Enable clock for GPIOC                                                   */
  RCC->AHBENR |= (1UL << 17);

  /* Configure LED (PC.8..9) pins as push-pull outputs */
  GPIOA->MODER  &= ~((3UL << 2 * 3) | (3UL << 2 * 4));
  GPIOA->MODER  |=  ((1UL << 2 * 3) | (1UL << 2 * 4));
  GPIOA->OTYPER &= ~((1UL <<     3) | (1UL <<     4));

}


/*-----------------------------------------------------------------------------
 *      LED_On: Turns on requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_On (uint32_t num) {

  //if (num < LED_NUM) {
    GPIOA->ODR |= (1<<3);
		GPIOA->ODR &= (1<<4);
  //}
}

/*-----------------------------------------------------------------------------
 *       LED_Off: Turns off requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Off (uint32_t num) {

    GPIOA->ODR |= (1<<3);
		GPIOA->ODR |= (1<<4);
  //}

}

/*-----------------------------------------------------------------------------
 *       LED_Val: Write value to LEDs
 *
 * Parameters:  val - value to be displayed on LEDs
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void LED_Out (uint32_t val) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (val & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}

void LED_reverse (void) 
{
GPIOA->ODR |= (1<<3);
GPIOA->ODR ^= (1<<4);
}

