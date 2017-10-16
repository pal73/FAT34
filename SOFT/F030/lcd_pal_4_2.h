/*----------------------------------------------------------------------------
 * Name:    lcd_pal_4_2.h
 * Purpose: функции для работы с 2х16 индикатором через порт C  микроконтроллера STM32 
 * Version: V1.0
 *----------------------------------------------------------------------------
 * Copyright (c) PAL.
 *---------------------------------------------------------------------------*/


/* Включение тактирования порта                                */
#define LCD_CLOCK_EN         RCC->AHBENR |= (1UL << 17); // enable clock for GPIOA

/*-------------------- LCD interface hardware definitions --------------------*/
/* PINS: 
   - DB4 = PA0
   - DB5 = PA1
   - DB6 = PA2
   - DB7 = PA3
   - E   = PA9
   - RS  = PA10 
*/
   
#define PIN_RS                (1 << 10)
#define PIN_E                 (1 << 9)
#define PINS_DATA             (0x0F)

/* Setting all pins to output mode                                            */
#define LCD_ALL_DIR_OUT   	GPIOA->MODER  &= ~((3UL << 2 * 0) | (3UL << 2 * 1) | (3UL << 2 * 2) | (3UL << 2 * 3) | (3UL << 2 * 9) | (3UL << 2 * 10)); \
						GPIOA->MODER  |=  ((1UL << 2 * 0) | (1UL << 2 * 1) | (1UL << 2 * 2) | (1UL << 2 * 3) | (1UL << 2 * 9) | (1UL << 2 * 10)); \
						GPIOA->OTYPER &= ~((1UL <<     0) | (1UL <<     1) | (1UL <<     2) | (1UL <<     3) | (1UL <<     9) | (1UL <<     10));

/* Подбираемый коэффициент, увеличивает задержку, выдаваемую функцией Delay в степень 2 раз                                   */
#define DELAY_2N     2

/* pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)             GPIOA->ODR = (GPIOA->ODR & ~PIN_RS) | (x ? PIN_RS : 0);	//GPIOC->ODR = (GPIOC->ODR & ~PIN_RS) | (x ? PIN_RS : 0);
/* pin E  setting to 0 or 1                                                   */
#define LCD_E(x)              GPIOA->ODR = (GPIOA->ODR & ~PIN_E)  | (x ? PIN_E : 0);		//GPIOC->ODR = (GPIOC->ODR & ~PIN_E)  | (x ? PIN_E : 0);
/* Writing value to DATA pins                                                 */
#define LCD_DATA_OUT(x)       GPIOA->ODR = (GPIOA->ODR & ~PINS_DATA) | (x);			//GPIOC->ODR = (GPIOC->ODR & ~PINS_DATA) | ((x) << 6);

//-----------------------------------------------
static void delay (int cnt);
//-----------------------------------------------
void lcd_write_4bit (unsigned char c);
//-----------------------------------------------
static void lcd_write_data (unsigned char c);
//-----------------------------------------------
void lcd_putchar (char c);
//-----------------------------------------------
void lcd_write_cmd (unsigned char c);
//-----------------------------------------------
void set_cursor (int column, int line);
//-----------------------------------------------
void lcd_clear (void);
//-----------------------------------------------
void lcd_out (char* adress);
//-----------------------------------------------
void lcd_init (void);
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
