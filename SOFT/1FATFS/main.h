#define PAROL_FISK	753 

#include <RTL.h>

#define MMC_GO_IDLE_STATE 0 ///< initialize card to SPI-type access
#define MMC_SEND_OP_COND 1 ///< set card operational mode
#define MMC_SET_BLOCKLEN 16 ///< Set number of bytes to transfer per block
#define MMC_READ_SINGLE_BLOCK 17 ///< read a block
#define MMC_CRC_ON_OFF 59 ///< Turns CRC check on/off
#define MMC_WRITE_SINGLE_BLOCK 24 ///< read a block


//***********************************************
//Установки для софтового I2C
#define PORT_I2C_SDA	GPIOB
#define PORT_I2C_SCL	GPIOB
#define PIN_SDA		7
#define PIN_SCL		6


//***********************************************
//Таймер
extern char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz; 
extern char time_cnt1,time_cnt2,time_cnt3,time_cnt4,time_cnt5,time_cnt6,time_cnt7;
extern char bFL5,bFL2,bFL;
extern signed short short_time_cnt;

#define LCD_SIZE	40
//extern char lcd_buffer[LCD_SIZE];

//***********************************************
//Индикация
typedef enum {iMn,iSrv_sl,iFisk_prl,iSet,iFisk,iBps,iS2,iSet_prl,iK_prl,iDnd,iK,
	iSpcprl,iSpc,k,Crash_0,Crash_1,iKednd,iAv_view_avt,iAKE,
	iLoad,iSpc_prl_vz,iNotCard,iBadCard,iAVAR,iStr,iVrs,iPrltst,iApv,
	iK_bps,iK_bps_sel,iK_bat,iK_bat_sel,iK_load,iK_net,iTst,iTst_klbr,iTst_BPS1,iTst_BPS2,
	iTst_BPS12,iDebug,iDef,iSet_st_prl,iK_pdp,iSet_T,iDeb,iJ_bat,iK_inv,iK_inv_sel,
	iPrl_bat_in_out,iPdp1,iJAv_sel,iJAv_net_sel,iJAv_net,iJAv_src1,
	iTst_bps,/*iJAv_bat,iJAv_bat_sel,*/iAusw,iAusw_prl,iAusw_set,iK_t_ext,iAv_view,
	iBatLogKe,iJ_bat_ke,iBatLogVz,iJ_bat_vz,iBatLogWrk,iEnerg,iExtern,iK_power_net,
	iExt_set,iExt_dt,iExt_sk,iExt_ddv,iExt_ddi,iExt_dud,iExt_dp,iSM,iLog,iLog_,iBatLog}i_enum;
typedef struct  
{

i_enum i;
signed char s_i;
signed char s_i1;
signed char s_i2;
signed char i_s;
} stuct_ind;

#define ind     a_ind.i
#define sub_ind     a_ind.s_i
#define sub_ind1     a_ind.s_i1
#define sub_ind2     a_ind.s_i2
#define index_set     a_ind.i_s

extern stuct_ind a_ind,b_ind[8];
extern signed short ptr_ind;
extern char lcd_buffer[LCD_SIZE];
extern signed char parol[3];
extern char phase;
//extern char lcd_bitmap[1024];
extern char dig[5];
extern signed short ind_pointer;
extern char zero_on;
extern char mnemo_cnt;
extern char simax;
extern short av_j_si_max;
extern const char ABCDEF[];
extern const char sm_mont[13][4]; 


//**********************************************
//Коэффициенты, отображаемые из ЕЕПРОМ
/*extern signed short MAIN_TIME;
extern signed short DEMO_TIME;
extern signed short DEMO_PERIOD;
extern signed short MAIN_VOLUME;
extern signed short NUM_OF_FILES;*/

//**********************************************
//Присутствие карты в слоте
extern signed short sd_card_insert_drv_cnt;
typedef enum {scisOFF,scisON,scisWAKEUP,scisGOOD}	enum_sd_card_insert_stat;
extern enum_sd_card_insert_stat sd_card_insert_stat,sd_card_insert_stat_old;

//-----------------------------------------------
//Генератор звука
//extern signed short sound_buff[500];
extern signed short sound_cnt;
extern BOOL bZV,bEND,bEND_,b1,b2,b1ERR,bZV_ERROR;
extern signed long File_len;
extern unsigned long sound_read_adress;
extern unsigned short current_cluster;
extern unsigned char current_sector;
//extern signed short sound_buffer[256],sound_buffer_;
//extern char sound_control_buffer[100];
//extern char memo_out[50];
extern unsigned long pbr_adr;
extern unsigned char Sectors_per_Cluster;
extern unsigned short Rezerv;
extern unsigned char Number_of_Fat; 
extern unsigned short Root_dir_entry;
extern unsigned short Sectors_per_FAT;
extern unsigned long Fat_base;
extern unsigned long Root_base;
extern unsigned long Cluster_base;
extern unsigned short zv_err_cnt;
//char memo_out[256];
extern unsigned short unsigned_cnt;
extern unsigned short audio_out_cnt;

//-----------------------------------------------
//Управление воспроизведением музыки
extern signed short main_music_cnt;
extern signed short max_main_music_cnt;
extern signed short fade_out_main_music_cnt;
//-----------------------------------------------
//Управление громкостью
extern signed short volume;
extern signed char volume_vector;
extern signed short volume_koef;
extern signed short volume_max;
extern signed short volume_period_cnt;
extern signed short volume_period_cnt_max;

//-----------------------------------------------
//Управление процессом
//extern signed short time_wrk;
//extern signed short demo_per;
//extern signed short demo_len;
extern signed short current_sound;
extern signed short wrk_cnt,wrk_cnt_up;
extern signed short max_file;
extern signed short current_file;
extern signed short current_demo_file;
extern signed short main_demo_cnt;

//**********************************************
//Карта памяти ЕЕПРОМ
#define EE_MAIN_TIME	10
#define EE_DEMO_TIME	12
#define EE_DEMO_PERIOD 	14
#define EE_NUM_OF_FILES	16
#define EE_MAIN_VOLUME	18
#define EE_MAIN_CNT		20

//-----------------------------------------------
void delay_us(long del);
//-----------------------------------------------
unsigned SD_Reset(void);
//-----------------------------------------------
unsigned char SD_Command(char cmd,unsigned long int arg);
//-----------------------------------------------
unsigned char SD_SendCommand(char cmd,unsigned long int arg);
//-----------------------------------------------
unsigned char SD_Read32Bytes(unsigned long adr, char* ptr);
//-----------------------------------------------
unsigned char SD_FileNameCompare(char* name_readed, char* name_comand);
//-----------------------------------------------
unsigned char SD_Read256Bytes(unsigned long adr, char* ptr);
//-----------------------------------------------
unsigned char SD_Read2Bytes(unsigned long adr, char* ptr);
//-----------------------------------------------
unsigned char SD_Read512Bytes(unsigned long adr, char* ptr);
//-----------------------------------------------
unsigned char SD_Read1024Bytes(unsigned long adr, char* ptr);
//-----------------------------------------------
void ret(char duty);
//-----------------------------------------------
void ret_hndl(void);
//-----------------------------------------------
void music_start(	signed short file_num__,
				signed short time_in_sec__,
				char fade_in__,
				char time_fade_in__,
				char volume__,
				char fade_out__,
				char fade_out_time__);
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
