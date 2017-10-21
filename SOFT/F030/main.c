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
#include "gran.h"
#include "eeprom.h"

//***********************************************
//–í—Ä–µ–º—è
char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz; 
char time_cnt1,time_cnt2,time_cnt3,time_cnt4,time_cnt5,time_cnt6,time_cnt7;
signed short short_time_cnt,short_time_cnt_;
char bFL5,bFL2,bFL;

//***********************************************
//…≠Â©™·∑®Ûçä£
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
//const char sm_mont[13][4]={"   ","Û≠¢¢,"•¢¢,"¨Ä¢,"·∞∞","™ê¢,"Èø≠","Èø´","·££","Ò•≠¢,"Ô´≤","ÓØø","Â¶™"}; //
signed short ptr_ind=0;
stuct_ind a_ind,b_ind[8];
signed short ind_pointer=0;
unsigned char /*f0,fc0,f1,fc1,*/ret_duty;

//-----------------------------------------------
//–ó–≤—É–∫
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
//‘Ø†¢´ÊÆ®Â°£Æ¨™Ô≤≤æçä
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
//‘Ø†¢´ÊÆ®Â°ØÆ∂•Ò±Æ¨
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
//ÀÆÒ¥¥®Ú®•≠Úª¨†Ô≥Æ‚±†Á°•Ûôê†Èß†∆Ö–êœå
signed short MAIN_TIME;
signed short DEMO_TIME;
signed short DEMO_PERIOD;
signed short NUM_OF_FILES;
signed short MAIN_VOLUME;
signed short MAIN_CNT;

//**********************************************
//–‡·ÓÚ‡ Ò ÍÌÓÔÍ‡ÏË 
char but;                            
unsigned short but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;
char speed,l_but,n_but;
char in_drv_cnt,in_stop_drv_cnt;
char bIN,bIN_STOP;

//-----------------------------------------------
//‘Ø†¢´ÊÆ®Â°¢Ô≤ØÆ®ß„¶§ÊÆ®Ê¨†ÒôΩ™Úìêä
signed short main_music_cnt;
signed short max_main_music_cnt;
signed short fade_out_main_music_cnt;

//**********************************************
// ‡Ú‡ Ô‡ÏˇÚË ≈≈œ–ŒÃ
const short EE_MAIN_TIME =	0x1111;
const short EE_DEMO_TIME	=	0x2222;
const short EE_DEMO_PERIOD =	0x3333;
const short EE_NUM_OF_FILES =	0x4444;
const short EE_MAIN_VOLUME =	0x5555;
const short EE_MAIN_CNT =	0x6666;

uint16_t VirtAddVarTab[NB_OF_VAR] = {0x5555, 0x6666, 0x7777};




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
void ret(char duty)
{
ret_duty=duty;
}

//-----------------------------------------------
void ret_hndl(void)
{
if(ret_duty)
     {
     ret_duty--;
     if(!ret_duty)
          {
          tree_down(0,0);
          }
     }
}



//-----------------------------------------------
void memo_read(void)
{
EE_ReadVariable((uint16_t)EE_MAIN_TIME, (uint16_t*)&MAIN_TIME);
EE_ReadVariable((uint16_t)EE_DEMO_TIME, (uint16_t*)&DEMO_TIME);
EE_ReadVariable((uint16_t)EE_DEMO_PERIOD, (uint16_t*)&DEMO_PERIOD);
EE_ReadVariable((uint16_t)EE_NUM_OF_FILES, (uint16_t*)&NUM_OF_FILES);
EE_ReadVariable((uint16_t)EE_MAIN_VOLUME, (uint16_t*)&MAIN_VOLUME);
EE_ReadVariable((uint16_t)EE_MAIN_CNT, (uint16_t*)&MAIN_CNT);
}

//-----------------------------------------------
void ind_hndl(void)
{
const char* ptrs[30];

if(ind==iMn)
	{
	if(!wrk_cnt)
		{
		bgnd_par(
			" ”ÒÚ‡ÌÓ‚ÎÂÌÌÓÂ  ",//string1,
			" ‚ÂÏˇ   0!:0@  "//string2
			);
			
			

		int2lcd(MAIN_TIME/60,'!',0);
		int2lcd(MAIN_TIME%60,'@',0);
		//int2lcd(MAIN_TIME,'!',0);
		//int2lcd(but,'@',0);
		//fr=5;

		/*int2lcdyx(fr,0,2,0);
		int2lcdyx(bZV,0,4,0);
		int2lcdyx(b1,0,6,0);
		int2lcdyx(b2,0,8,0);
		int2lcdyx(audio_out_cnt,0,12,0);
		*/
	//int2lcdyx(but_n,0,14,0);
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
			"  ƒÓ ÓÍÓÌ˜‡ÌËˇ  ",
			" ÓÒÚ‡ÎÓÒ¸ 0<:0> ");

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
	ptrs[0]	=" ƒÎËÚÂÎ¸ÌÓÒÚ¸   ";
	ptrs[1]	=" ÒÂ‡ÌÒ‡   !Ï0@c ";	
	ptrs[2]	=" œÂËÓ‰Ë˜ÌÓÒÚ¸  ";
	ptrs[3]	=" ‰ÂÏÓË„˚ #Ï0$Ò ";
	ptrs[4]	=" ƒÎËÚÂÎ¸ÌÓÒÚ¸   ";
	ptrs[5]	=" ‰ÂÏÓË„˚ %Ï0^Ò ";
	ptrs[6]	=" √ÓÏÍÓÒÚ¸      ";
	ptrs[7]	=" Á‚ÛÍ‡       )  ";
	ptrs[8]	="  ÓÎË˜ÂÒÚ‚Ó     ";
	ptrs[9]	=" Ù‡ÈÎÓ‚      (  "; 
	ptrs[10]	=" —˜ÂÚ˜ËÍ        ";
	ptrs[11]	=" ÒÂ‡ÌÒÓ‚        "; 
	ptrs[12]	=" ¬˚ıÓ‰          ";
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
			"  œ≤Ò≥≤±Ú¢≥•Ú†††",
			"  Î°∞Ú††Ø·≠øÚ®††");

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
				"À†≤††‡°¨Û≤®†Ó•†",
				"ÈÆ®Ú®†´È®®");
		}
	else if(index_set==1)
		{
		bgnd_par(
				"  √ÆË≠ÆÁÆÆ ÔÆ†  ",
				"   Ó¶®ÒØ∞†„Æ†,  ");
		}
	else if(index_set==2)
		{
		bgnd_par(
				"È¨® Ó•†Ô≥¥Ô±¨·≥®",
				"Æ¢†Ó††‚°ÜAT16  ");
		}

	}

else if (ind==iFisk_prl)
	{          
     bgnd_par(
			"  √¢Ê•®Ú•††     ",
			"   ‡°∞Ô¨º       ");
     lcd_buffer[11]=parol[0]+0x30;
     lcd_buffer[12]=parol[1]+0x30;
     lcd_buffer[13]=parol[2]+0x30; 
     lcd_buffer[27+sub_ind]='^';    
	}

else if (ind==iDnd)
	{          
     bgnd_par(
			"     –†Æ´º     ",
			"   Ó¶¢Ê±≠Û©°°!  ");
   	
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
ruslcd((unsigned char*)lcd_buffer);
}

#define BUT_ON 4
#define BUT_ONL 20 

#define butU   253
#define butU_  125
#define butD   251
#define butD_  123
#define butL   254
#define butL_  126
#define butR   239
#define butR_  111
#define butE   247
#define butE_  119
#define butEL_ 118
#define butUD  249
#define butUD_ 121
#define butLR  238
#define butLR_ 110

//-----------------------------------------------
void but_drv(void)
{
/* ËÌËˆË‡ÎËÁ‡ˆËˇ ÍÌÓÔÓÍ */
RCC->AHBENR  |= ((1UL << 17) );
GPIOA->MODER 	&= 	~((3UL << 2*0) | (3UL << 2*1) | (3UL << 2*2) | (3UL << 2*3)/* | (3UL << 2*9)*/ | (3UL << 2*10));      
GPIOA->OSPEEDR &= 	~((3UL << 2*0) | (3UL << 2*1) | (3UL << 2*2) | (3UL << 2*3)/* | (3UL << 2*9)*/ | (3UL << 2*10));
GPIOA->PUPDR   &= 	~((3UL << 2*0) | (3UL << 2*1) | (3UL << 2*2) | (3UL << 2*3)/* | (3UL << 2*9)*/ | (3UL << 2*10));
GPIOA->PUPDR   |= 	 ((1UL << 2*0) | (1UL << 2*1) | (1UL << 2*2) | (1UL << 2*3)/* | (1UL << 2*9)*/ | (1UL << 2*10));	

	
but_n=(((GPIOA->IDR)|0xfff0)/*&0xffffffcf*/)&(((GPIOA->IDR)>>6)|0xffef); 	
//but_n=(GPIOA->IDR);
	
if((but_n==0xffff)||(but_n!=but_s))
 	{
 	speed=0;
 
   	if (((but0_cnt>=BUT_ON)||(but1_cnt!=0))&&(!l_but))
  		{
   	     n_but=1;
          but=(char)but_s;

          }
   	if (but1_cnt>=but_onL_temp)
  		{
   	     n_but=1;
 
          but=((char)but_s)&0x7f;
          }
    	l_but=0;
   	but_onL_temp=BUT_ONL;
    	but0_cnt=0;
  	but1_cnt=0;          
     goto but_drv_out;
  	}
else if(but_n==but_s)
 	{
  	but0_cnt++;
  	if(but0_cnt>=BUT_ON)
  		{
   		but0_cnt=0;
   		but1_cnt++;
   		if(but1_cnt>=but_onL_temp)
   			{              
    			but=(char)(but_s&0x7f);
    			but1_cnt=0;
    			n_but=1;
    			     
    			l_but=1;
			if(speed)
				{
    				but_onL_temp=but_onL_temp>>1;
        			if(but_onL_temp<=2) but_onL_temp=2;
				}    
   			}
  		}
 	}
but_drv_out: 
but_s=but_n;
	   
}

//-----------------------------------------------
void but_an(void)
{
//signed short temp_SS;
//signed short deep,i,cap,ptr;
if(!n_but)goto but_an_end;

if(but==butUD)
	{
	if(ind!=iDeb)ind=iDeb;
	else ind=iMn;
	}

if(ind==iMn)
	{
	if(but==butE_)
		{
		tree_up(iSet,0,0,0);
		}

	if(but==butE)
		{
		//ee_24c01_write_2byte(30,read_adress);
		}
	if(but==butU)
		{
		}
	if(but==butR)
		{
		MAIN_TIME++;
		EE_WriteVariable(VirtAddVarTab[0], MAIN_TIME);
		}
	if(but==butD)
		{
		///fr=10;
		}
	if(but==butL)
		{
		///music_start(1,MAIN_TIME+10,1,5,MAIN_VOLUME,1,10);
	   //bB=1;
		}

	}
else if(ind==iSet)
	{ 
     if(but==butU)
     	{
    		sub_ind--;
     	gran_char(&sub_ind,0,6);
     	}
 	else if(but==butD)
     	{
     	sub_ind++;
     	gran_char(&sub_ind,0,6);
     	} 
     else if(but==butD_)
     	{
     	sub_ind=5;
     	}
	else if(sub_ind==0)
		{
		if(but==butR)
			{
			MAIN_TIME=(((MAIN_TIME/10)+1)*10);//MAIN_TIME++;
			gran(&MAIN_TIME,30,300);
			EE_WriteVariable(EE_MAIN_TIME, MAIN_TIME);
			}
		else if(but==butR_)
			{
			MAIN_TIME=(((MAIN_TIME/10)+1)*10);
			gran(&MAIN_TIME,30,300);
			EE_WriteVariable(EE_MAIN_TIME, MAIN_TIME);
			}
		else if(but==butL)
			{
			MAIN_TIME=(((MAIN_TIME/10)-1)*10);//MAIN_TIME--;
			gran(&MAIN_TIME,30,300);
			EE_WriteVariable(EE_MAIN_TIME, MAIN_TIME);
			}
		else if(but==butL_)
			{
			MAIN_TIME=(((MAIN_TIME/10)-1)*10);
			gran(&MAIN_TIME,30,300);
			EE_WriteVariable(EE_MAIN_TIME, MAIN_TIME);
			}
		//speed=1;

		}

	else if(sub_ind==1)
		{
		if(but==butR)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)+1)*10);//DEMO_PERIOD++;
			gran(&DEMO_PERIOD,0,300);
			EE_WriteVariable(EE_DEMO_PERIOD, DEMO_PERIOD);
			}
		else if(but==butR_)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)+1)*10);
			gran(&DEMO_PERIOD,0,300);
			EE_WriteVariable(EE_DEMO_PERIOD, DEMO_PERIOD);
			}
		else if(but==butL)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)-1)*10);//DEMO_PERIOD--;
			gran(&DEMO_PERIOD,0,300);
			EE_WriteVariable(EE_DEMO_PERIOD, DEMO_PERIOD);
			}
		else if(but==butL_)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)-1)*10);
			gran(&DEMO_PERIOD,0,300);
			EE_WriteVariable(EE_DEMO_PERIOD, DEMO_PERIOD);
			}
		//speed=1;

		}
	else if(sub_ind==2)
		{
		if((but==butR)||(but==butR_))
			{
			DEMO_TIME++;
			gran(&DEMO_TIME,0,60);
			EE_WriteVariable(EE_DEMO_TIME, DEMO_TIME);
			}
	/*	else if(but==butR_)
			{
			MAIN_TIME=(((MAIN_TIME/10)+1)*10);
			gran(&MAIN_TIME,30,300);
			//ee_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			}*/
		else if((but==butL)||(but==butL_))
			{
			DEMO_TIME--;
			gran(&DEMO_TIME,0,60);
			EE_WriteVariable(EE_DEMO_TIME, DEMO_TIME);
			}
/*		else if(but==butL_)
			{
			MAIN_TIME=(((MAIN_TIME/10)-1)*10);
			gran(&MAIN_TIME,30,300);
			//ee_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			} */
		//speed=1;

		}

	else if(sub_ind==3)
		{
		if((but==butR)||(but==butR_))
			{
			MAIN_VOLUME++;
			gran(&MAIN_VOLUME,10,100);
			EE_WriteVariable(EE_MAIN_VOLUME, MAIN_VOLUME);
			}
		else if((but==butL)||(but==butL_))
			{
			MAIN_VOLUME--;
			gran(&MAIN_VOLUME,10,100);
			EE_WriteVariable(EE_MAIN_VOLUME, MAIN_VOLUME);
			}
		speed=1;
		}
	else if(sub_ind==4)
		{
		if((but==butR)||(but==butR_))
			{
			NUM_OF_FILES++;
			gran(&NUM_OF_FILES,1,20);
			EE_WriteVariable(EE_NUM_OF_FILES, NUM_OF_FILES);
			}
		else if((but==butL)||(but==butL_))
			{
			NUM_OF_FILES--;
			gran(&NUM_OF_FILES,1,20);
			EE_WriteVariable(EE_NUM_OF_FILES, NUM_OF_FILES);
			}
		}
	else if(sub_ind==5)
		{
		if(but==butE_)tree_up(iFisk_prl,0,0,0);
		}
	else if(sub_ind==6)
		{
		if(but==butE_)tree_down(0,0);
		}														
	}
else if(ind==iFisk_prl)
	{
	short tempU;
	speed=1;
	if ((but==butU)||(but==butU_))parol[sub_ind]++;
	else if ((but==butD)||(but==butD_))parol[sub_ind]--;
	gran_ring_char(&parol[sub_ind],0x00,0x09);
	if (but==butR)
		{
		sub_ind++;
		gran_ring_char(&sub_ind,0,2);
		} 
	else if (but==butL)
		{ 
		sub_ind--;
		gran_ring_char(&sub_ind,0,2); 
		}
	else if(but==butE)
		{
		tempU=parol[2]+(parol[1]*10U)+(parol[0]*100U);
		if(ind==iFisk_prl)
			{
	     	if(tempU==PAROL_FISK) 
				{
				tree_down(0,0);
				tree_up(iFisk,0,0,0);
				ret(15);
				parol[0]=0;
				parol[1]=0;
				parol[2]=0;
				}
			else 
				{
				ind=iDnd;
				ret(15);
				}
			}
		}
	}
else if(ind==iDeb)
	{ 
     if(but==butL)
     	{
    		sub_ind--;
     	gran_ring_char(&sub_ind,0,2);
     	}
 	else if(but==butR)
     	{
     	sub_ind++;
     	gran_ring_char(&sub_ind,0,2);
     	}
	}		 			
but_an_end:
n_but=0;
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

FLASH_Unlock();

EE_Init();
	
while(1) 
	{   		/* Loop forever               */
if(b100Hz)
	{
	b100Hz=0;
	but_drv();
	but_an();
	
	}
	
if(b10Hz)
	{
	b10Hz=0;
	ind_hndl();	
	lcd_out(lcd_buffer);
	ret_hndl();
	memo_read();
	}

if(b1Hz)
	{
	b1Hz=0;
		
	//MAIN_TIME++;
	//LED_reverse();
	//
	}
      //LED_On (0);
      //Delay( 500);                               /* Delay 50ms                 */
      //LED_Off(0);
      //Delay(50);                               /* Delay 450ms                */
	}

  
}

