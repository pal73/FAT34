/*----------------------------------------------------------------------------
 *      R T L  -  F l a s h   F i l e   S y s t e m
 *----------------------------------------------------------------------------
 *      Name:    SPI_STM32X.C 
 *      Purpose: Serial Peripheral Interface Driver for STM32x
 *      Rev.:    V3.21
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2008 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <File_Config.h>
#include <stm32f10x_lib.h>                  /* STM32F10x Library Definitions */


/* SPI_SR - bit definitions. */
#define RXNE    0x01
#define TXE     0x02
#define BSY     0x80

/*----------------------------------------------------------------------------
 *      SPI Driver Functions
 *----------------------------------------------------------------------------
 *  Required functions for SPI driver module:
 *   - void spi_init ()
 *   - void spi_ss (U32 ss)
 *   - U8   spi_send (U8 outb)
 *   - void spi_hi_speed (BOOL on)
 *---------------------------------------------------------------------------*/

/*--------------------------- spi_init --------------------------------------*/

void spi_init (void) {
   /* Initialize and enable the SSP Interface module. */

   /* Enable clock for SPI, GPIOA and AFIO. */
   RCC->APB2ENR |= 0x00001005;

   /* Reset SPI remap (use PA4..PA7). */
   AFIO->MAPR   &= 0xFFFFFFFE;

   /* SPI1_NSS is GPIO, output set to high. */
   GPIOA->BSRR = 0x00000010;

   /* SPI1_SCK, SPI1_MISO, SPI1_MOSI are SPI pins. */
   GPIOA->CRL &= ~0xFFFF0000;
   GPIOA->CRL |=  0xB8B30000;

   /* Card Sensor PA.8 input */
   /* 1 = NO Card, 0 = Card plugged. */
   GPIOA->CRH &= ~0x0000000F;
   GPIOA->CRH |=  0x00000004;

   /* Enable SPI in Master Mode, CPOL=0, CPHA=0. */
   /* Clock speed = fPCLK1 / 256 = 280 kHz at 72 MHz PCLK1 clk. */
   SPI1->CR1  = 0x037C;
   SPI1->CR2  = 0x0000;
}


/*--------------------------- spi_hi_speed ----------------------------------*/

void spi_hi_speed (BOOL on) {
   /* Set a SPI clock speed to desired value. */

   if (on == __TRUE) {
      /* Max. 18 MBit used for Data Transfer. */
      SPI1->CR1 &= ~0x0030;
      SPI1->CR1 |=  0x0008;
   }
   else {
      /* Max. 400 kBit used in Card Initialization. */
      SPI1->CR1 |= 0x0038;
   }
}


/*--------------------------- spi_ss ----------------------------------------*/

void spi_ss (U32 ss) {
   /* Enable/Disable SPI Chip Select (drive it high or low). */

   GPIOA->BSRR = ss ? 0x00000010 : 0x00100000;
}


/*--------------------------- spi_send --------------------------------------*/

U8 spi_send (U8 outb) {
   /* Write and Read a byte on SPI interface. */

   /* Wait if TXE cleared, Tx FIFO is full. */
   while (!(SPI1->SR & TXE));
   SPI1->DR = outb;

   /* Wait if RNE cleared, Rx FIFO is empty. */
   while (!(SPI1->SR & RXNE));
   return (SPI1->DR);
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
