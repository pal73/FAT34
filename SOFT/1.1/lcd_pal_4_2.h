/*----------------------------------------------------------------------------
 * Name:    lcd_pal_4_2.h
 * Purpose: функции для работы с 2х16 индикатором через порт C  микроконтроллера STM32 
 * Version: V1.0
 *----------------------------------------------------------------------------
 * Copyright (c) PAL.
 *---------------------------------------------------------------------------*/


/* Включение тактирования порта                                */
#define LCD_CLOCK_EN         (RCC->APB2ENR |= (1 << 4)); // enable clock for GPIOC

/*-------------------- LCD interface hardware definitions --------------------*/
/* PINS: 
   - DB4 = PC6
   - DB5 = PC7
   - DB6 = PC8
   - DB7 = PC9
   - E   = PC11
   - RS  = PC10 
*/
   
#define PIN_RS                (   1 << 10)
#define PIN_E                 (   1 << 11)
#define PINS_DATA             (0x0F <<  6)

/* Setting all pins to output mode                                            */
#define LCD_ALL_DIR_OUT       GPIOC->CRL = (GPIOC->CRL & 0xFFFF0000) | 0x33000000; \
                              GPIOC->CRH = (GPIOC->CRH & 0xFFF000FF) | 0x00003333;

/* Подбираемый коэффициент, увеличивает задержку, выдаваемую функцией Delay в степень 2 раз                                   */
#define DELAY_2N     0

/* pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)             GPIOC->ODR = (GPIOC->ODR & ~PIN_RS) | (x ? PIN_RS : 0);
/* pin E  setting to 0 or 1                                                   */
#define LCD_E(x)              GPIOC->ODR = (GPIOC->ODR & ~PIN_E)  | (x ? PIN_E : 0);
/* Writing value to DATA pins                                                 */
#define LCD_DATA_OUT(x)       GPIOC->ODR = (GPIOC->ODR & ~PINS_DATA) | ((x) << 6);

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
