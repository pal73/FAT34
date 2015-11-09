//Ветка "Железная дорога"

#include "main.h"
#include <stm32f10x_lib.h>
//#include <RTL.h>                      /* RTL kernel functions & defines      */
//#include <stdio.h>                    /* standard I/O .h-file                */
//#include <ctype.h>                    /* character functions                 */
#include <string.h>                   /* string and memory functions         */
#include "STM32_Init.h"               /* stm32 initialisation                */
#include "common_func.h"
#include "lcd_pal_4_2.h"
#include "24c01.h"
#include "i2c.h"
#include "SPI_STM32f103.h"
#include "ruslcd.h"
#include "gran.h"
#include "integer.h"
#include "ffconf.h"
#include "ff.h"
//#include "gran.h"

//***********************************************
//Таймер
char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz; 
char time_cnt1,time_cnt2,time_cnt3,time_cnt4,time_cnt5,time_cnt6,time_cnt7;
signed short short_time_cnt,short_time_cnt_;
char bFL5,bFL2,bFL;

//***********************************************
//Индикация
char lcd_buffer[LCD_SIZE]="*...............@.............. ";//{"Hello World"};
signed char parol[3];
char phase;
//char lcd_bitmap[10];
char dig[5];
char zero_on;
char mnemo_cnt=50;
char simax;
short av_j_si_max;
const char ABCDEF[]={"0123456789ABCDEF"};
//const char sm_mont[13][4]={"   ","янв","фев","мар","апр","май","июн","июл","авг","сен","окт","ноя","дек"}; //
signed short ptr_ind=0;
stuct_ind a_ind,b_ind[8];
signed short ind_pointer=0;
unsigned char /*f0,fc0,f1,fc1,*/ret_duty;

//**********************************************
//Работа с кнопками 
char but;                            
unsigned long but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;
char speed,l_but,n_but;
char in_drv_cnt,in_stop_drv_cnt;
char bIN,bIN_STOP;

//**********************************************
//Коэффициенты, отображаемые из ЕЕПРОМ
signed short MAIN_TIME;
signed short DEMO_TIME;
signed short DEMO_PERIOD;
signed short NUM_OF_FILES;
signed short MAIN_VOLUME;
signed short MAIN_CNT;

//**********************************************
//Присутствие карты в слоте
signed short sd_card_insert_drv_cnt=10;
enum_sd_card_insert_stat sd_card_insert_stat=scisWAKEUP,sd_card_insert_stat_old=scisWAKEUP;

//-----------------------------------------------
//Генератор звука
//signed short sound_buff[500];
signed short sound_cnt;
BOOL bZV,bEND,bEND_,b1,b2,b1ERR,bZV_ERROR;
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
//Управление воспроизведением музыки
signed short main_music_cnt;
signed short max_main_music_cnt;
signed short fade_out_main_music_cnt;

//-----------------------------------------------
//Управление громкостью
signed short volume;
signed char volume_vector=0;
signed short volume_koef;
signed short volume_max;
signed short volume_period_cnt;
signed short volume_period_cnt_max=100;
    FRESULT fr=5;
    FATFS fs;
    FIL fil;
//-----------------------------------------------
//Управление процессом
//signed short time_wrk;
//signed short demo_per;
//signed short demo_len;
signed short current_sound;
signed short wrk_cnt;
signed short max_file;
signed short current_file;
signed short current_demo_file;
signed short main_demo_cnt=25;
//-----------------------------------------------
//Фискальный счетчик
signed short main_cnt;

char plazma,plazma1,plazma2,plazma3=6;
long plazma_long;

unsigned short read_adress;
signed short dac_cnt;


char plazma_cnt;

extern  volatile
UINT Timer1, Timer2;
char bB;
UINT readed_bytes;

/*----------------------------------------------------------------------------
 *        Initialize On Board LCD Module
 *---------------------------------------------------------------------------*/
static void init_display (void) {
   // LCD Module.2x16 init

  lcd_init  ();                               // initialise LCD              
  lcd_clear ();
  //lcd_print ("Антон           ");
  set_cursor (0, 0);
  //lcd_print ("  www.keil.com  ");
} 


//-----------------------------------------------
void delay_us(long del)
{
long temp;
temp=5*del;

while (--temp);
return;
}

//-----------------------------------------------
void dac_init(void)
{
RCC->APB1ENR|=(1<<29);
DAC->CR=0x00000001;
}

//-----------------------------------------------
void dac_drv(void)
{
dac_cnt++;
if(dac_cnt>4000)dac_cnt=0;
DAC->DHR12R1=dac_cnt;
DAC->DHR12R2=(4000-dac_cnt);
}


//-----------------------------------------------
void music_start(	signed short file_num__,
				signed short time_in_sec__,
				char fade_in__,
				char time_fade_in__,
				char volume__,
				char fade_out__,
				char fade_out_time__)
{


char n,r1; 
char str[15];
short file_num;
//unsigned i;
//unsigned long sector;

max_main_music_cnt=time_in_sec__*10;
main_music_cnt=0;

if(!fade_out__)fade_out_main_music_cnt=0;
else
	{
	fade_out_main_music_cnt=max_main_music_cnt-(fade_out_time__*10);
	}

volume_max=volume__;

if(!fade_in__) 
	{
	volume=volume__;
	volume_vector=0;
	}
else
	{
	volume=20;
	volume_vector=1;
	volume_period_cnt_max=(time_fade_in__*100) / (volume_max-20);
	}

file_num=file_num__; 
         
str[0]='0';
str[1]='0';
str[2]='0';
str[3]='0';
str[4]='0';
str[5]='0';
str[6]='0';
str[7]='0';
str[8]='.';
str[9]='w';
str[10]='a';
str[11]='v';
str[12]=0;
          
str[7]=(file_num%10)+'0';
file_num/=10;
str[6]=(file_num%10)+'0';
file_num/=10;
str[5]=(file_num%10)+'0';
file_num/=10;
str[4]=(file_num%10)+'0';


//fr =f_open(&fil, "00000011.wav", FA_READ);
    //fr =f_mount(&fs, "", 1);
fr =f_open(&fil, str, FA_READ);

 
/*           
			
n=strlen(str);
         
r1=SD_SendCommand(MMC_SET_BLOCKLEN,32);
if(r1) return;
 			
r1=SD_Read32Bytes(0x000001BEUL,&memo_out[3]);
if(r1)return;
    		
*((char*)&pbr_adr)=memo_out[11];
*(((char*)&pbr_adr)+1)=memo_out[12];
*(((char*)&pbr_adr)+2)=memo_out[13];
*(((char*)&pbr_adr)+3)=memo_out[14];

pbr_adr<<=9;
r1=SD_Read32Bytes(pbr_adr,&memo_out[3]);

Sectors_per_Cluster=memo_out[3+0x0d];
	
*((char*)&Rezerv)=memo_out[3+0x0e];
*(((char*)&Rezerv)+1)=memo_out[3+0x0f];	 

Number_of_Fat=memo_out[3+0x10];
	
Root_dir_entry=*((short*)&memo_out[3+0x11]);
	
Sectors_per_FAT=*((short*)&memo_out[3+0x16]);

Fat_base = pbr_adr+(((long)Rezerv)<<9);
Root_base = Fat_base+(((long)Number_of_Fat)*(((long)Sectors_per_FAT)<<9));  		//	plazma= Root_base/1000;
Cluster_base = Root_base+(((long)Root_dir_entry)<<5)-(((long)(Sectors_per_Cluster))<<10); 

for(unsigned_cnt=0;((unsigned_cnt<Root_dir_entry)&&(n));unsigned_cnt++)
     {
     SD_Read32Bytes(Root_base+(((long)unsigned_cnt)<<5),sound_control_buffer);

	n=SD_FileNameCompare(sound_control_buffer,str);
	}

if((unsigned_cnt>=256)&&(n))
     {                      
     ///error_sound_init(3);
     }	
else	
	{
	*((char*)&File_len)=sound_control_buffer[0x1c];
	*(((char*)&File_len)+1)=sound_control_buffer[0x1d];
	*(((char*)&File_len)+2)=sound_control_buffer[0x1e];
	*(((char*)&File_len)+3)=sound_control_buffer[0x1f];

	current_cluster=*((unsigned short*)&sound_control_buffer[0x1a]); 

	current_sector=0; 

	sound_read_adress=(unsigned long)current_cluster;
	sound_read_adress*=(unsigned long)Sectors_per_Cluster;
	sound_read_adress+=(unsigned long)current_sector;
	sound_read_adress<<=9;
	sound_read_adress+=(unsigned long)Cluster_base;
*/
	bZV=1; 
	b2=1;
	b1=1;
	audio_out_cnt=250;
	bEND=0;

}

//-----------------------------------------------
void music_hndl(void)
{
if((max_main_music_cnt)&&(max_main_music_cnt>main_music_cnt))
	{
	main_music_cnt++;
	if(main_music_cnt>=max_main_music_cnt)
		{
		max_main_music_cnt=0;
		main_music_cnt=0;
		volume=0;
		bEND=1;
		} 
	}

if((fade_out_main_music_cnt) && (fade_out_main_music_cnt==main_music_cnt))
	{
	volume_vector=-1;
	volume_period_cnt_max=((max_main_music_cnt-fade_out_main_music_cnt)*10) / (volume_max-10);
	}

}


//-----------------------------------------------
void music_stop(void)
{
bEND=1;
main_music_cnt=0;
}

//-----------------------------------------------
void wrk_drv(void)
{
GPIOA->CRL&=~0x0000f000;
GPIOA->CRL|=0x00002000;
if(wrk_cnt)
	{
	wrk_cnt--;
	GPIOA->ODR|=1<<3;
	main_demo_cnt=0;
	}
else
	{
	GPIOA->ODR&=~(1<<3);
	}


if(wrk_cnt==((MAIN_TIME-5)*10))
	{
	MAIN_CNT++;
	gran_ring(&MAIN_CNT,0,9999);
	_24c01_write_2byte(EE_MAIN_CNT,MAIN_CNT);
	}
}

//-----------------------------------------------
void volume_drv(void)
{
volume_period_cnt++;
if(volume_period_cnt>=volume_period_cnt_max)
	{
	volume_period_cnt=0;
	
	if(volume_vector==1)volume++;
	else if(volume_vector==-1)volume--;

	gran(&volume,0,volume_max);

	} 
volume_koef=(volume*volume)/100;


}

//-----------------------------------------------
void demo_hndl(void)
{
if((DEMO_TIME) && (DEMO_PERIOD))
	{
	main_demo_cnt++;
	if(main_demo_cnt>=DEMO_PERIOD)
		{
		main_demo_cnt=0;
		current_demo_file++;
		gran_ring(&current_demo_file,1,NUM_OF_FILES);
		music_start(current_demo_file,DEMO_TIME,1,DEMO_TIME/5,50,1,DEMO_TIME/5);
		}

	}
else main_demo_cnt=0;
}


//-----------------------------------------------
void in_drv(void)
{
GPIOB->CRH&=~0x000ff000;
GPIOB->CRH|=0x00088000;
GPIOB->ODR|=(1<<11)|(1<<12);

if(!(GPIOB->IDR&(1<<11)))
	{
	if(in_drv_cnt<10)
		{
		in_drv_cnt++;
		if(in_drv_cnt>=10)
			{
			bIN=1;
			}
		}
	}
else 
	{
	in_drv_cnt=0;
	}

if(!(GPIOB->IDR&(1<<12)))
	{
	if(in_stop_drv_cnt<10)
		{
		in_stop_drv_cnt++;
		if(in_stop_drv_cnt>=10)
			{
			bIN_STOP=1;
			}
		}
	}
else 
	{
	in_stop_drv_cnt=0;
	}

}


//-----------------------------------------------
void in_an(void)
{
if(bIN)
	{
	bIN=0;

	wrk_cnt= MAIN_TIME*10;
	current_file++;
	gran_ring(&current_file,1,NUM_OF_FILES);
	music_start(current_file,MAIN_TIME+10,1,5,MAIN_VOLUME,1,10);
	//ind=iMn;
	

	}

if(bIN_STOP)
	{
	bIN_STOP=0;

	wrk_cnt=0;
	music_stop();
	}
}

//-----------------------------------------------
void sd_card_insert_drv(void)
{
GPIOA->CRL&=~0x0000000F;
GPIOA->CRL|=0x00000008;
GPIOA->ODR|=0x00000001;

if(GPIOA->IDR&0x00000001)
	{
	if(sd_card_insert_drv_cnt)
		{
		sd_card_insert_drv_cnt--;
		if(sd_card_insert_drv_cnt<=0)
			{
			sd_card_insert_stat=scisOFF;
			}
		}
	}
else 
	{
	if(sd_card_insert_drv_cnt<20)
		{
		sd_card_insert_drv_cnt++;
		if(sd_card_insert_drv_cnt>=20)
			{
			sd_card_insert_stat=scisON;
			}
		}
	}

if((sd_card_insert_stat==scisOFF)&&(sd_card_insert_stat_old!=scisOFF))
	{
	tree_up(iNotCard,0,0,0);
	}
else if((sd_card_insert_stat==scisON)&&(sd_card_insert_stat_old!=scisON))
	{
	if(SD_Reset())
		{
		tree_up(iBadCard,0,0,0);
		}
	else 
		{
		sd_card_insert_stat=scisGOOD;
		tree_down(0,0);
		}
	}
sd_card_insert_stat_old=sd_card_insert_stat;
}

//-----------------------------------------------
unsigned char SD_FileNameCompare(char* name_readed, char* name_comand)
{
char r1/*,n*/;
unsigned i;
/*
__disable_irq();
if(strlen(name_comand)<8)strlcpy(name_comand,"        ", 8-strlen(name_comand));

__enable_irq();*/
//strlcpy(name_comand+strlen(name_comand),"WAV",4);
//				uart_out_adr0(name_readed,13); /**/
//				for(i=0;i<1000000;i++)  __nop();


//				uart_out_adr0(name_comand,13); /**/
//				for(i=0;i<10000000;i++)  __nop();


r1=0;

for(i=0;i<8;i++)
	{
	if(name_readed[i]!=name_comand[i])	r1=1;
	}

return r1;//strncmp(name_readed, name_comand, 8);
}

//-----------------------------------------------
unsigned char SD_Command(char cmd,unsigned long int arg)
{
char r1,retry;
retry=0;

spi_send(cmd|0x40);//Комманда 
spi_send(arg>>24);//Аргумент
spi_send(arg>>16);
spi_send(arg>>8);
spi_send(arg); 
spi_send(0x95);//Имеет значение только при передачи режима обмена
do
	{
	r1=spi_send(0xff);
	retry++;
	}
while((r1==0xFF)&&(retry<252));

//Вернуть ответ
return r1;
}

//-----------------------------------------------
unsigned char SD_Read2Bytes(unsigned long adr, char* ptr)
{
//unsigned short i_;
char r1,n;

spi_init();
spi_hi_speed(1);
spi_ss(0);

r1=SD_Command(MMC_READ_SINGLE_BLOCK, adr);

if(!r1)
	{
	do
		{
		//__disable_irq();
		n=spi_send(0xff);
		//__enable_irq();
		}	
	while(n!=0xfe);

	//__disable_irq();
	ptr[0]=spi_send(0xff);
	//__enable_irq();
	//__disable_irq();
	ptr[1]=spi_send(0xff);
	//__enable_irq();
	//__disable_irq();
	spi_send(0xff);
	spi_send(0xff);
	//__enable_irq();
	}
spi_ss(1);
//__disable_irq();
spi_send(0xff);
//__enable_irq();
return r1;	
}

//-----------------------------------------------
unsigned char SD_Read32Bytes(unsigned long adr, char* ptr)
{
unsigned short i_;
char r1,n;

spi_init();
spi_ss (0);

r1=SD_Command(MMC_READ_SINGLE_BLOCK, adr);

if(!r1)
	{
	do
		{
		//__disable_irq();
		n=spi_send(0xff);
		//__enable_irq();
		}	
	while(n!=0xfe);
	
	for(i_=0;i_<32;i_++)
		{
		//__disable_irq();
		ptr[i_]=spi_send(0xff);
		//__enable_irq();
		}
	//__disable_irq();
	spi_send(0xff);
	spi_send(0xff); 
	//__enable_irq(); 
	}
spi_ss (1);
//__disable_irq();
spi_send(0xff); 
//__enable_irq();
return r1;	
}

//-----------------------------------------------
unsigned char SD_Read256Bytes(unsigned long adr, char* ptr)
{
unsigned i_;
char r1,n;

spi_init();
spi_hi_speed(1);

spi_ss (0);
r1=SD_Command(MMC_READ_SINGLE_BLOCK, adr);

if(!r1)
	{ 
	do
		{
		//__disable_irq();
		n=spi_send(0xff);
		//__enable_irq();
		}	
	while(n!=0xfe);
	
	for(i_=0;i_<256;i_++)
		{
		//__disable_irq();
		ptr[i_]=spi_send(0xff);
		//__enable_irq();
		}
	//__disable_irq();
	spi_send(0xff);
	spi_send(0xff);
	//__enable_irq();
	}
spi_ss (1);
//__disable_irq();
spi_send(0xff);
//__enable_irq();
return r1;	
}

//-----------------------------------------------
unsigned char SD_Read512Bytes(unsigned long adr, char* ptr)
{
unsigned i_;
char r1,n;

spi_init();
spi_hi_speed(1);

spi_ss (0);
r1=SD_Command(MMC_READ_SINGLE_BLOCK, adr);

if(!r1)
	{ 
	do
		{
		//__disable_irq();
		n=spi_send(0xff);
		//__enable_irq();
		}	
	while(n!=0xfe);
	
	for(i_=0;i_<512;i_++)
		{
		//__disable_irq();
		ptr[i_]=spi_send(0xff);
		//__enable_irq();
		}
	//__disable_irq();
	spi_send(0xff);
	spi_send(0xff);
	//__enable_irq();
	}
spi_ss (1);
//__disable_irq();
spi_send(0xff);
//__enable_irq();
return r1;	
}

//-----------------------------------------------
unsigned char SD_Read1024Bytes(unsigned long adr, char* ptr)
{
unsigned short i_;
char r1,n;

spi_init();
spi_hi_speed(1);

spi_ss (0);
r1=SD_Command(MMC_READ_SINGLE_BLOCK, adr);

if(!r1)
	{ 
	do
		{
		//__disable_irq();
		n=spi_send(0xff);
		//__enable_irq();
		}	
	while(n!=0xfe);
	
	for(i_=0;i_<1024;i_++)
		{
		//__disable_irq();
		ptr[i_]=spi_send(0xff);
		//__enable_irq();
		}
	//__disable_irq();
	spi_send(0xff);
	spi_send(0xff);
	//__enable_irq();
	}
spi_ss (1);
//__disable_irq();
spi_send(0xff);
//__enable_irq();
return r1;	
}

//-----------------------------------------------
unsigned char SD_SendCommand(char cmd,unsigned long int arg)
{
char r1;
spi_init();
//spi_hi_speed(1);
//CS_ON
spi_ss (0);
r1=SD_Command(cmd,arg);
//CS_OFF
spi_ss (1);
//#asm("cli")
//__disable_irq();
spi_send(0xFF);
//#asm("sei")
//__enable_irq();

return r1; 

}

//-----------------------------------------------
unsigned SD_Reset(void)
{
unsigned char r1;
unsigned retry;
r1=retry=0;

spi_init();

//Устанавливаем карту в режим SPI
do
	{
//	CS_OFF
	spi_ss (1);
//	#asm("cli")
__disable_irq();
	spi_send(0xFF); 
	spi_send(0xFF); 
	spi_send(0xFF); 
	spi_send(0xFF);
//	#asm("sei")
__enable_irq();
//	#asm("cli") 
__disable_irq();
	spi_send(0xFF);
	spi_send(0xFF);
	spi_send(0xFF);
	spi_send(0xFF);
//	#asm("sei")
__enable_irq();
//	#asm("cli")
__disable_irq();
	spi_send(0xFF);
	spi_send(0xFF);
	spi_send(0xFF);
	spi_send(0xFF);
//	#asm("sei")
__enable_irq();

	r1=SD_SendCommand(MMC_GO_IDLE_STATE,0);

	retry++;
	if(retry>10)return 10;
	}
while(r1!=0x01);

//определение типа карты

r1=SD_SendCommand(55,0);
r1=SD_SendCommand(41,0);

if(r1<=1)
	{
	//Инициализировать SD-карту

	retry=0;
	do
		{ 
		//r1=SD_SendCommand(MMC_SEND_OP_COND,0);
     	r1=SD_SendCommand(55,0);
		r1=SD_SendCommand(41,0);

		retry++;
		if(retry>1000)return retry;
          }
	while(r1);
	}
	
else
	{
	//Инициализировать MMC-карту

	retry=0;
	do
		{ 
		r1=SD_SendCommand(MMC_SEND_OP_COND,0);
     	//r1=SD_SendCommand(55,0);
		//r1=SD_SendCommand(41,0);

		retry++;
		if(retry>1000)return retry;
          }
	while(r1);
	}
;

//Отключить CRC проверку


r1=SD_SendCommand(MMC_CRC_ON_OFF, 0);

//Установить длину блока 


r1=SD_SendCommand(MMC_SET_BLOCKLEN,512);//Сдесь задаётся размер сектора


//spi_init_fast();
spi_hi_speed(1);


return r1;
}    

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
void ind_hndl(void)
{
const char* ptrs[30];

if(ind==iMn)
	{
	if(!wrk_cnt)
		{
		bgnd_par(
			" Установленное  ",
			" время    0!:0@ ");

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
			"  До окончания  ",
			" осталось 0<:0> ");

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
	ptrs[0]	=" Длительность   ";
	ptrs[1]	=" сеанса   !м0@c ";	
	ptrs[2]	=" Периодичность  ";
	ptrs[3]	=" демоигры #м0$с ";
	ptrs[4]	=" Длительность   ";
	ptrs[5]	=" демоигры %м0^с ";
	ptrs[6]	=" Громкость      ";
	ptrs[7]	=" звука       )  ";
	ptrs[8]	=" Количество     ";
	ptrs[9]	=" файлов      (  "; 
	ptrs[10]	=" Счетчик        ";
	ptrs[11]	=" сеансов        "; 
	ptrs[12]	=" Выход          ";
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
			"  Отсутствует   ",
			"  карта памяти  ");

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
				"Карта памяти не ",
				"инициализируется");
		}
	else if(index_set==1)
		{
		bgnd_par(
				"  Возможно она  ",
				"   неисправна,  ");
		}
	else if(index_set==2)
		{
		bgnd_par(
				"или не отформати",
				"рована в FAT16  ");
		}

	}

else if (ind==iFisk_prl)
	{          
     bgnd_par(
			"  Введите       ",
			"   пароль       ");
     lcd_buffer[11]=parol[0]+0x30;
     lcd_buffer[12]=parol[1]+0x30;
     lcd_buffer[13]=parol[2]+0x30; 
     lcd_buffer[27+sub_ind]='^';    
	}

else if (ind==iDnd)
	{          
     bgnd_par(
			"     Пароль     ",
			"   неверный!!!  ");
   	
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

#define BUT0	16
#define BUT1	17
#define BUT2	18
#define BUT3	19
#define BUT4	20   
#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)|(1UL<<BUT3)|(1UL<<BUT4)

#define BUT_ON 4
#define BUT_ONL 20 

#define butU   254
#define butU_  126
#define butD   251
#define butD_  123
#define butL   239
#define butL_  111
#define butR   223
#define butR_  95
#define butE   253
#define butE_  125
#define butEL_  107
#define butUD  250
#define butUD_  122
#define butLR   207
#define butLR_   79

//-----------------------------------------------
void but_drv(void)
{

but_n=(GPIOB->IDR)|0xfffffff8; 	//	FAT34
//but_n=(GPIOB->IDR)|0xfffffffc;	//	STM32VLDISVOVERY
but_n&=(GPIOC->IDR)|0xffffffCf;
if((but_n==0xffffffffUL)||(but_n!=but_s))
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
if(but_n==but_s)
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


/*
PINSEL2&=~(1UL<<((BUT0-16)*2))&~(1UL<<(((BUT0-16)*2)+1))
	   &~(1UL<<((BUT1-16)*2))&~(1UL<<(((BUT1-16)*2)+1))
	   &~(1UL<<((BUT2-16)*2))&~(1UL<<(((BUT2-16)*2)+1))
	   &~(1UL<<((BUT3-16)*2))&~(1UL<<(((BUT3-16)*2)+1))
	   &~(1UL<<((BUT4-16)*2))&~(1UL<<(((BUT4-16)*2)+1));
IO1DIR&=~(1UL<<BUT0)&~(1UL<<BUT1)&~(1UL<<BUT2)&~(1UL<<BUT3)&~(1UL<<BUT4);*/

/* инициализация кнопок для платы FAT34*/
RCC->APB2ENR|=(1<<3)|(1<<4);
GPIOB->CRL &= ~0x00000FFF;
GPIOB->CRL |=  0x00000888;
GPIOB->ODR |=  0x00000007;
plazma_long=GPIOB->ODR;
GPIOC->CRL &= ~0x00FF0000;
GPIOC->CRL |=  0x00880000;
GPIOC->ODR |=  0x00000030;

	   
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
		_24c01_write_2byte(30,read_adress);
		}
	if(but==butU)
		{
		}
	if(but==butR)
		{
		}
	if(but==butD)
		{
		fr=10;
		}
	if(but==butL)
		{
		music_start(1,MAIN_TIME+10,1,5,MAIN_VOLUME,1,10);
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
			_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			}
		else if(but==butR_)
			{
			MAIN_TIME=(((MAIN_TIME/10)+1)*10);
			gran(&MAIN_TIME,30,300);
			_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			}
		else if(but==butL)
			{
			MAIN_TIME=(((MAIN_TIME/10)-1)*10);//MAIN_TIME--;
			gran(&MAIN_TIME,30,300);
			_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			}
		else if(but==butL_)
			{
			MAIN_TIME=(((MAIN_TIME/10)-1)*10);
			gran(&MAIN_TIME,30,300);
			_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			}
		//speed=1;

		}

	else if(sub_ind==1)
		{
		if(but==butR)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)+1)*10);//DEMO_PERIOD++;
			gran(&DEMO_PERIOD,0,300);
			_24c01_write_2byte(EE_DEMO_PERIOD,DEMO_PERIOD);
			}
		else if(but==butR_)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)+1)*10);
			gran(&DEMO_PERIOD,0,300);
			_24c01_write_2byte(EE_DEMO_PERIOD,DEMO_PERIOD);
			}
		else if(but==butL)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)-1)*10);//DEMO_PERIOD--;
			gran(&DEMO_PERIOD,0,300);
			_24c01_write_2byte(EE_DEMO_PERIOD,DEMO_PERIOD);
			}
		else if(but==butL_)
			{
			DEMO_PERIOD=(((DEMO_PERIOD/10)-1)*10);
			gran(&DEMO_PERIOD,0,300);
			_24c01_write_2byte(EE_DEMO_PERIOD,DEMO_PERIOD);
			}
		//speed=1;

		}
	else if(sub_ind==2)
		{
		if((but==butR)||(but==butR_))
			{
			DEMO_TIME++;
			gran(&DEMO_TIME,0,60);
			_24c01_write_2byte(EE_DEMO_TIME,DEMO_TIME);
			}
	/*	else if(but==butR_)
			{
			MAIN_TIME=(((MAIN_TIME/10)+1)*10);
			gran(&MAIN_TIME,30,300);
			_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			}*/
		else if((but==butL)||(but==butL_))
			{
			DEMO_TIME--;
			gran(&DEMO_TIME,0,60);
			_24c01_write_2byte(EE_DEMO_TIME,DEMO_TIME);
			}
/*		else if(but==butL_)
			{
			MAIN_TIME=(((MAIN_TIME/10)-1)*10);
			gran(&MAIN_TIME,30,300);
			_24c01_write_2byte(EE_MAIN_TIME,MAIN_TIME);
			} */
		//speed=1;

		}

	else if(sub_ind==3)
		{
		if((but==butR)||(but==butR_))
			{
			MAIN_VOLUME++;
			gran(&MAIN_VOLUME,10,100);
			_24c01_write_2byte(EE_MAIN_VOLUME,MAIN_VOLUME);
			}
		else if((but==butL)||(but==butL_))
			{
			MAIN_VOLUME--;
			gran(&MAIN_VOLUME,10,100);
			_24c01_write_2byte(EE_MAIN_VOLUME,MAIN_VOLUME);
			}
		speed=1;
		}
	else if(sub_ind==4)
		{
		if((but==butR)||(but==butR_))
			{
			NUM_OF_FILES++;
			gran(&NUM_OF_FILES,1,20);
			_24c01_write_2byte(EE_NUM_OF_FILES,NUM_OF_FILES);
			}
		else if((but==butL)||(but==butL_))
			{
			NUM_OF_FILES--;
			gran(&NUM_OF_FILES,1,20);
			_24c01_write_2byte(EE_NUM_OF_FILES,NUM_OF_FILES);
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



//***********************************************
//***********************************************
//***********************************************
//***********************************************
//***********************************************
void SysTick_Handler (void) 
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
	disk_timerproc();
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
} 




/*----------------------------------------------------------------------------
 *        Main: 
 *---------------------------------------------------------------------------*/
int main (void) {



stm32_Init();
SysTick->LOAD  = 544;  
delay_us(100000);                             
dac_init();
init_display ();
//plazma1=SD_Reset();
ind=iMn;
i2c_init();
_24c01_read_nbyte(EE_MAIN_TIME,(char*)&MAIN_TIME,12);


/* Open or create a log file and ready to append */
    fr =f_mount(&fs, "", 1);
    //fr =f_open(&fil, "00000001.wav", FA_READ);

//fr=3;

//Timer1=10000;
//Timer2=1000;
while (1) 
	{
//#ifdef OLDSDCARD
	if(b1)
     	{
		GPIOB->ODR|=(1<<10);

     	//File_len-=512;
         	//if(File_len<0) bEND=1;

		f_read(&fil,&sound_buffer[0],1024,&readed_bytes);
       	
		/*current_sector+=2;
       	
     	if((current_sector>=(Sectors_per_Cluster<<1))||(current_sector>=128))
     		{
     		current_sector=0;
     		SD_SendCommand(MMC_SET_BLOCKLEN,2);
     		sound_read_adress=(unsigned long)current_cluster;
     		sound_read_adress<<=1;
     		sound_read_adress+=Fat_base;
     		SD_Read2Bytes(sound_read_adress,(char*)&current_cluster);	
		
			if((current_cluster>=0xfff8)&&(current_cluster<=0xffff))
				{
				//bEND=1;
				//usart_out(6,CMND,11,11,current_sector,*((char*)&current_cluster),*(((char*)&current_cluster)+1));
				}
				
		     else if((current_cluster<=0xffef)&&(current_cluster>=0x0002))
				{
			    
				}
 
			}
		if(!bEND)	
			{
			sound_read_adress=(unsigned long)current_cluster;
			sound_read_adress*=(unsigned long)Sectors_per_Cluster;
	     	sound_read_adress*=2UL;
			sound_read_adress+=(unsigned long)current_sector;
			sound_read_adress<<=8;
			sound_read_adress+=(unsigned long)Cluster_base;
			
			SD_SendCommand(MMC_SET_BLOCKLEN,512);
			SD_Read512Bytes(sound_read_adress,(char*)sound_buffer); 
								
		     }*/
		b1=0;
		} 
	if(bEND==1)
		{
		bEND_=1;		
		bEND=0;
		}
				
	if(b2)
     	{
		GPIOB->ODR&=~(1<<10);

     	//File_len-=512;
         	//if(File_len<0) bEND=1;  	
       	//current_sector+=2;

     	//File_len-=512;
         	//if(File_len<0) bEND=1;

		f_read(&fil,&sound_buffer[512],1024,&readed_bytes);
       	
 /*    	if((current_sector>=(Sectors_per_Cluster<<1))||(current_sector>=128))
     		{
     		current_sector=0;
     		SD_SendCommand(MMC_SET_BLOCKLEN,2);
     		     	
     		sound_read_adress=(unsigned long)current_cluster;
     		sound_read_adress<<=1;
     		sound_read_adress+=Fat_base;
     		SD_Read2Bytes(sound_read_adress,(char*)&current_cluster);	
		
			if((current_cluster>=0xfff8)&&(current_cluster<=0xffff))
				{
				//bEND=1;
			    //	usart_out(6,CMND,11,11,current_sector,*((char*)&current_cluster),*(((char*)&current_cluster)+1)); 
				} 
		   	else if((current_cluster<=0xffef)&&(current_cluster>=0x0002))
				{

				} 
			}
		if(!bEND)	
			{			
			sound_read_adress=(unsigned long)current_cluster;
			sound_read_adress*=(unsigned long)Sectors_per_Cluster;
	     	sound_read_adress*=2UL;
			sound_read_adress+=(unsigned long)current_sector;
			sound_read_adress<<=8;
			sound_read_adress+=(unsigned long)Cluster_base;
			
			SD_SendCommand(MMC_SET_BLOCKLEN,512);
			SD_Read512Bytes(sound_read_adress,(char*)(&sound_buffer[256])); 
		
			}*/		
		b2=0;
		} 
	if(bEND==1)
		{
		bEND_=1;		
		bEND=0;
		ind=iMn;
		}
//#endif	                                     
	if (b1000Hz) 
		{
		b1000Hz=0;
		
		
		}
	if (b100Hz) 
		{
		b100Hz=0;
		but_drv();
		but_an();
		/////sd_card_insert_drv();
		in_drv();
		in_an();
		volume_drv();
		}
	if (b10Hz) 
		{
		b10Hz=0; 
		/*plazma++;
		int2lcdyx(plazma,0,2,0);
		int2lcdyx(plazma1,0,6,0);
		int2lcdyx((char)but_n,1,6,0);
		int2lcdyx(but,1,10,0);
		*/		
		ind_hndl();
		lcd_out(lcd_buffer);
		ret_hndl();
					//SD_SendCommand(MMC_SET_BLOCKLEN,256);
			//SD_Read256Bytes(sound_read_adress,(char*)(&sound_buffer[128]));

		wrk_drv();
		music_hndl();
		}   
	if (b5Hz) 
		{
		b5Hz=0; 
		/////read_adress++;		
		
		//SD_SendCommand(MMC_SET_BLOCKLEN,32);
		//SD_Read32Bytes(0x000001beUL,&memo_out[3]);
		
		}
	if (b1Hz) 
		{
		b1Hz=0;
 		/**/_24c01_read_nbyte(EE_MAIN_TIME,(char*)&MAIN_TIME,12);
		//

		/**/demo_hndl();
		/////plazma_cnt++;


		}
		
	if(bB)
			{
			bB=0;
			//fr =f_mount(&fs, "", 1);
		//fr =f_open(&fil, "00000001.wav", FA_READ);
			}
	}
}


/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
