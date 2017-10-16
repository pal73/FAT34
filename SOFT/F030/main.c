/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
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

//#include <stdio.h>
#include "STM32F0xx.h"
#include "main.h"
#include "lcd_pal_4_2.h"
#include "ruslcd.h"
#include "common_func.h"

//***********************************************
//Время
char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz; 
char time_cnt1,time_cnt2,time_cnt3,time_cnt4,time_cnt5,time_cnt6,time_cnt7;
signed short short_time_cnt,short_time_cnt_;
char bFL5,bFL2,bFL;

//***********************************************
//ɭ婪ᷨ󍊣
char lcd_buffer[LCD_SIZE]="Hello World....@.............. ";//{"Hello World"};
signed char parol[3];
char phase;
//char lcd_bitmap[10];
char dig[5];
char zero_on;
char mnemo_cnt=50;
char simax;
short av_j_si_max;
const char ABCDEF[]={"0123456789ABCDEF"};
//const char sm_mont[13][4]={"   ","󭢢,"𥢢,"𬀢,"ᰰ","𪐢,"鿭","鿫","ᣣ","񥭢,"﫲","","妪"}; //
signed short ptr_ind=0;
stuct_ind a_ind,b_ind[8];
signed short ind_pointer=0;
unsigned char /*f0,fc0,f1,fc1,*/ret_duty;

//-----------------------------------------------
//Звук
//signed short sound_buff[500];
signed short sound_cnt;
char bZV,bEND,bEND_,b1,b2,b1ERR,bZV_ERROR;
signed long File_len;
unsigned long sound_read_adress;
unsigned short current_cluster;
unsigned char current_sector;
signed short sound_buffer[1024],sound_buffer_;
//char sound_control_buffer[40];
//char memo_out[50];
unsigned long pbr_adr;
unsigned char Sectors_per_Cluster;
unsigned short Rezerv;
unsigned char Number_of_Fat; 
unsigned short Root_dir_entry;
unsigned short Sectors_per_FAT;
unsigned long Fat_base;
unsigned long Root_base;
unsigned long Cluster_base;
unsigned short zv_err_cnt;
//char memo_out[256];
unsigned short unsigned_cnt;
unsigned short audio_out_cnt;

//-----------------------------------------------
//ԯ𠢫殨塣𮬪ﲲ𾍊
signed short volume;
signed char volume_vector=0;
signed short volume_koef;
signed short volume_max;
signed short volume_period_cnt;
signed short volume_period_cnt_max=100;
//    FRESULT fr=5;
//    FATFS fs;
//    FIL fil;

//-----------------------------------------------
//ԯ𠢫殨塯𮶥񱮬
//signed short time_wrk;
//signed short demo_per;
//signed short demo_len;
signed short current_sound;
signed short wrk_cnt;
signed short max_file;
signed short current_file;
signed short current_demo_file;
signed short main_demo_cnt=25;

//**********************************************
//ˮ񴴨򨥭򻬠ﳮⱠ硥󙐠駠ƅАό
signed short MAIN_TIME;
signed short DEMO_TIME;
signed short DEMO_PERIOD;
signed short NUM_OF_FILES;
signed short MAIN_VOLUME;
signed short MAIN_CNT;


//-----------------------------------------------
//ԯ𠢫殨塢ﲯ𮨧㦤殨欠񙽪򓐊
signed short main_music_cnt;
signed short max_main_music_cnt;
signed short fade_out_main_music_cnt;

volatile uint32_t msTicks;                /* counts 1ms timeTicks       */


/*//-----------------------------------------------
const char* mems[]={
				{(char)0x20,(char)0x20,(char)0x20,0xa6,0x20,0x20,0x20,0xa6,0x20,0x20,0x20,0xa6,0x20,0x20,0x20,0xa6},
				{(char)0x20,(char)0x20,0x20,0xa6,0x20,0x20,0x20,0xa6,0x20,0x20,0x20,0xa6,0x20,0x20,0x20,0xa6},
				{(char)0x20,(char)0x20,0x20,0xa6,0x20,0x20,0x20,0xa6,0x20,0x20,0x20,0xa6,0x20,0x20,0x20,0xa6}
			};*/

char string1[]={0x20,0x20,0xa9,0x63,0xbf,0x61,0xbd,'o',0xb3,0xbb,'e',0xbd,0xbd,'o','e',0x20,0};
char string2[]={0x20,0x20,0xb3,0x70,'e',0xbc,0xc7,0x20,0x20,0x20,'0','!',':','0','@',0x20,0};
char string3[]={0x63,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0};
char string4[]={0x63,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0};
char string5[]={0x63,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0};

//-----------------------------------------------
void ind_hndl(void)
{
const char* ptrs[30];

if(ind==iMn)
	{
	if(!wrk_cnt)
		{
		bgnd_par(
			string1,
			string2
			/*" world  0!:0@ "*/);
			
			//lcd_buffer[1]=0xa7;

		int2lcd(MAIN_TIME/60,'!',0);
		int2lcd(MAIN_TIME%60,'@',0);

		//fr=5;

		/*int2lcdyx(fr,0,2,0);
		int2lcdyx(bZV,0,4,0);
		int2lcdyx(b1,0,6,0);
		int2lcdyx(b2,0,8,0);
		int2lcdyx(audio_out_cnt,0,12,0);
		int2lcdyx(bEND,0,14,0);*/

/*
	=1; 
	b2=1;
	b1=1;
	audio_out_cnt=250;
	bEND=0;*/

		}
	else
		{
		bgnd_par(
			"  Ů 﫮  ",
			" ﲲᬮ񼠰<:0> ");

		int2lcd((wrk_cnt/10)/60,'<',0);
		int2lcd((wrk_cnt/10)%60,'>',0);

		//int2lcdyx(plazma1,0,2,0);
		//int2lcdyx(MAIN_CNT,0,6,0);
		}
/*	int2lcdyx(bZV,0,0,0);

	int2lcdyx(sound_buffer_,0,15,0);
	int2lcdyx(current_demo_file,0,2,0);

	int2lcdyx(main_demo_cnt,0,5,0);

	int2lcdyx(current_file,1,2,0); */
	}
else if (ind==iSet)
	{
	ptrs[0]	=" ū鳥콭ﲲ𠠠";
	ptrs[1]	=" 񥠭񠠠 !챀c ";	
	ptrs[2]	=" Х𨮤鸭ﲲ𠠢";
	ptrs[3]	=" 妬謹𻠣";
	ptrs[4]	=" ū鳥콭ﲲ𠠠";
	ptrs[5]	=" 妬謹𻠥";
	ptrs[6]	=" İﭪﲲ𠠠   ";
	ptrs[7]	=" 裳렠      )  ";
	ptrs[8]	=" ˮ쩷沲㮠    ";
	ptrs[9]	=" 𠩫     (  "; 
	ptrs[10]	=" ҷ泷骠       ";
	ptrs[11]	=" 񥠭񮢠       "; 
	ptrs[12]	=" û񮤠         ";
	ptrs[13]	="                ";

	bgnd_par(ptrs[sub_ind*2],ptrs[sub_ind*2+1]);

	int2lcd(MAIN_TIME/60,'!',0);
	int2lcd(MAIN_TIME%60,'@',0); 
	int2lcd(DEMO_PERIOD/60,'#',0);
	int2lcd(DEMO_PERIOD%60,'$',0);
	int2lcd(DEMO_TIME/60,'%',0);
	int2lcd(DEMO_TIME%60,'^',0);
	int2lcd(NUM_OF_FILES,'(',0);
	int2lcd(MAIN_VOLUME,')',0);
	}
else if(ind==iNotCard)
	{
	bgnd_par(
			"  ϲ񳲱򢳥򠠠",
			"  롰򠠯᭿򨠠");

	}

else if(ind==iBadCard)
	{
	static char cnt__;
	cnt__++;
	if(cnt__>20)
		{
		cnt__=0;
		index_set++;
		if(index_set>2)index_set=0;
		}
	if(!index_set)
		{
		bgnd_par(
				"ˠ𲠠࡬󲨠",
				"鮨򨠫騨");
		}
	else if(index_set==1)
		{
		bgnd_par(
				"  î譮箮 ﮠ  ",
				"   񯰠㮠,  ");
		}
	else if(index_set==2)
		{
		bgnd_par(
				"鬨 ﳴﱬ᳨",
				"𮢠⡆AT16  ");
		}

	}

else if (ind==iFisk_prl)
	{          
     bgnd_par(
			"  â楨򥠠     ",
			"   ࡰלּ       ");
     lcd_buffer[11]=parol[0]+0x30;
     lcd_buffer[12]=parol[1]+0x30;
     lcd_buffer[13]=parol[2]+0x30; 
     lcd_buffer[27+sub_ind]='^';    
	}

else if (ind==iDnd)
	{          
     bgnd_par(
			"     Р𮫼     ",
			"   汭󩡡!  ");
   	
	}
else if (ind==iFisk)
	{
	bgnd_par(
			"         !      ",
			"                ");
	int2lcd(MAIN_CNT,'!',0);
	}
else if (ind==iDeb)
	{
	bgnd_par(
			"                ",
			"                ");
	if(sub_ind==0)
		{
		int2lcdyx(1,0,0,0);

		int2lcdyx(MAIN_VOLUME,1,2,0);
		int2lcdyx(volume,0,15,0);
		int2lcdyx(volume_koef,1,15,0);
		int2lcdyx(fade_out_main_music_cnt,0,12,0);
		int2lcdyx(max_main_music_cnt,1,12,0);
		int2lcdyx(wrk_cnt,0,5,0);
		int2lcdyx(current_file,1,5,0);
		}
	else if(sub_ind==1)
		{
		int2lcdyx(2,0,0,0);
		}
	else if(sub_ind==2)
		{
		int2lcdyx(3,0,0,0);
		}
	}
//int2lcdyx(plazma1,0,6,0);
//ruslcd((unsigned char*)lcd_buffer);
}

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) 
{
if(bEND_==1)
	{
	bZV=0;
	bZV_ERROR=0;		
	bEND_=0;
     }

if(bZV)
	{
	audio_out_cnt++;
	if(audio_out_cnt>=1024)
		{
		audio_out_cnt=0;
		}
     
	if(volume==100)sound_buffer_=sound_buffer[audio_out_cnt]+0x8000;
	else sound_buffer_=((signed short)(((signed)sound_buffer[audio_out_cnt])*((signed)volume_koef)/100))+0x8000;
	
	DAC->DHR12L1=sound_buffer_;
     
     if(audio_out_cnt==3) b2=1;
     if(audio_out_cnt==515) b1=1;
   	}
/*!!!
else if(bZV_ERROR)
	{
	audio_out_cnt++;
	if(audio_out_cnt>=256)
		{
		audio_out_cnt=0;
		}
	     
	sound_buffer_=sound_buffer[audio_out_cnt]+0x200;
	
	//if((audio_out_cnt/16)&0x01) PWMMR6=900;
	//else PWMMR6=100;
	PWMMR6=sound_buffer_;
	PWMMR4=sound_buffer_ ;
	    
     if(audio_out_cnt==1)
     	{
         	b1ERR=1;

     	}
	}*/	
else
	{
	DAC->DHR12L1=0x8000;
	}

if(++short_time_cnt_>=44)
     {
     short_time_cnt_=0;
     b1000Hz=1;
	///disk_timerproc();
	}

if(++short_time_cnt>=441)
     {
     short_time_cnt=0;
     b100Hz=1;

     if(++time_cnt4>=10)
	    	{
	    	time_cnt4=0;
	    	b10Hz=1;
	     }

     if(++time_cnt5>=20)
	    	{
	    	time_cnt5=0;
	    	b5Hz=1;
		if(bFL5)bFL5=0;
		else bFL5=1;     
	    	}

     if(++time_cnt6>=50)
	    	{
	   	time_cnt6=0;
	    	b2Hz=1;
		if(bFL2)bFL2=0;
		else bFL2=1;
	    	}         
	
	if(++time_cnt7>=100)
	    	{
	    	time_cnt7=0;
	    	b1Hz=1;
		if(bFL)bFL=0;
		else bFL=1;
		}
    	}
	
msTicks++;
} 


/*----------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *----------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {                                              
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}


/*----------------------------------------------------------------------------
  Function that initializes Button pins
 *----------------------------------------------------------------------------*/
void BTN_Init(void) {

  RCC->AHBENR  |= ((1UL << 17) );               /* Enable GPIOA clock         */

  GPIOA->MODER    &= ~((3UL << 2*0)  );         /* PA.0 is input              */
  GPIOA->OSPEEDR  &= ~((3UL << 2*0)  );         /* PA.0 is Low Speed          */
  GPIOA->PUPDR    &= ~((3UL << 2*0)  );         /* PA.0 is no Pull up         */
}

/*----------------------------------------------------------------------------
  Function that read Button pins
 *----------------------------------------------------------------------------*/
uint32_t BTN_Get(void) {

 return (GPIOA->IDR & (1UL << 0));
}


/*----------------------------------------------------------------------------
  set HSI as SystemCoreClock (HSE is not populated on STM32L-Discovery board)
 *----------------------------------------------------------------------------*/
void SystemCoreClockSetHSI(void) {

  RCC->CR |= ((uint32_t)RCC_CR_HSION);                      /* Enable HSI                        */ 
  while ((RCC->CR & RCC_CR_HSIRDY) == 0);                   /* Wait for HSI Ready                */

  RCC->CFGR = RCC_CFGR_SW_HSI;                              /* HSI is system clock               */
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);   /* Wait for HSI used as system clock */

  FLASH->ACR  = FLASH_ACR_PRFTBE;                           /* Enable Prefetch Buffer            */
  FLASH->ACR |= FLASH_ACR_LATENCY;                          /* Flash 1 wait state                */
 
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                          /* HCLK = SYSCLK                     */
  RCC->CFGR |= RCC_CFGR_PPRE_DIV1;                          /* PCLK = HCLK                       */

  RCC->CR &= ~RCC_CR_PLLON;                                 /* Disable PLL */

  /*  PLL configuration:  = HSI * 12 = 48 MHz */
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
  RCC->CFGR |=  (RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL12);
            
  RCC->CR |= RCC_CR_PLLON;                                  /* Enable PLL                        */
  while((RCC->CR & RCC_CR_PLLRDY) == 0) __NOP();            /* Wait till PLL is ready            */

  RCC->CFGR &= ~RCC_CFGR_SW;                                /* Select PLL as system clock source */
  RCC->CFGR |=  RCC_CFGR_SW_PLL;    

 //
 while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);   /* Wait till PLL is system clock src */
}


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) 
{
SystemCoreClockSetHSI();

SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  
if (SysTick_Config(SystemCoreClock / 44100)) /* SysTick 1 msec interrupts  */
	{ 
	while (1);                                  /* Capture error              */
	}

//LED_Init();
lcd_init  ();                               // initialise LCD              
lcd_clear (); 
//lcd_print ("  www.keil.com  ");
	
while(1) 
	{   		/* Loop forever               */
		
if(b10Hz)
	{
	b10Hz=0;
	ind_hndl();
		
	lcd_out(lcd_buffer);
	}
if(b100Hz)
	{
	b100Hz=0;
	//LED_reverse();
	//
	}
if(b1Hz)
	{
	b1Hz=0;
	//LED_reverse();
	//
	}
      //LED_On (0);
      //Delay( 500);                               /* Delay 50ms                 */
      //LED_Off(0);
      //Delay(50);                               /* Delay 450ms                */
	}

  
}

