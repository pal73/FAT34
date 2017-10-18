/*----------------------------------------------------------------------------
 * Name:    lcd_pal_4_2.c
 * Purpose: функции для работы с 2х16 индикатором через порт C  микроконтроллера STM32 
 * Version: V1.0
 *----------------------------------------------------------------------------
 * Copyright (c) PAL.
 *---------------------------------------------------------------------------*/

#include <stm32f0xx.h>                  /* STM32F0xx Definitions              */
#include "lcd_pal_4_2.h"

//-----------------------------------------------
static void delay (int cnt)
{
cnt <<= DELAY_2N;
while (cnt--);
}

//-----------------------------------------------
void lcd_write_4bit (unsigned char c)
{
LCD_E(1)
LCD_DATA_OUT(c&0x0F)
delay(2);
LCD_E(0)
delay(2);
}

//-----------------------------------------------

static void lcd_write_data (unsigned char c)
{
delay (200);//wait_while_busy();

LCD_RS(1)
lcd_write_4bit (c>>4);
lcd_write_4bit (c);
}

//-----------------------------------------------
void lcd_putchar (char c)
{ 
lcd_write_data (c);
}


//-----------------------------------------------
void lcd_write_cmd (unsigned char c)
{
delay (1500);//wait_while_busy();

LCD_RS(0)
lcd_write_4bit (c>>4);
lcd_write_4bit (c);
}

//-----------------------------------------------
void set_cursor (int column, int line)
{
unsigned char address;

address = (line * 40) + column;
address = 0x80 + (address & 0x7F);
lcd_write_cmd(address);               /* Set DDRAM address counter to 0     */
}

//-----------------------------------------------
void lcd_clear (void)
{
lcd_write_cmd(0x01);                  /* Display clear                      */
set_cursor (0, 0);
}

//-----------------------------------------------
void lcd_out (char* adress)
{
/*
char i;
for(i=0;i<16;i++)
	{
	lcd_putchar(*adress++);
  	}
set_cursor (0, 1);
for(i=16;i<32;i++)
	{
	lcd_putchar(*adress++);
  	}
	*/



char temp,i;
LCD_ALL_DIR_OUT
i=0;

set_cursor (0, 0);
lbl_lp_000:
temp=adress[i];
if(!temp)goto lbl_lp_001;
else
	{
	lcd_putchar(temp);
	i++;

	if(i==16)
		{
		//lcd_gotoyx(1,0);
		set_cursor (0, 1);
		}
	goto lbl_lp_000;
	}
lbl_lp_001:
return;


}

//-----------------------------------------------
void lcd_init (void)
{ 

LCD_CLOCK_EN                          /* Enable clock for peripheral        */

  /* Set all pins for LCD as outputs                                          */
LCD_ALL_DIR_OUT

delay (1500);
LCD_RS(0)
lcd_write_4bit (0x3);                 /* Select 4-bit interface             */
delay (4100);
lcd_write_4bit (0x3);
delay (100);
lcd_write_4bit (0x3);
lcd_write_4bit (0x2);

lcd_write_cmd (0x28);                 /* 2 lines, 5x8 character matrix      */
lcd_write_cmd (0x0C);                 /* Display ctrl:Disp=ON,Curs/Blnk=OFF */
lcd_write_cmd (0x06);                 /* Entry mode: Move right, no shift   */

  /* Load user-specific characters into CGRAM                                 */
lcd_write_cmd(0x40);                  /* Set CGRAM address counter to 0     */

lcd_write_cmd(0x80);                  /* Set DDRAM address counter to 0     */
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
