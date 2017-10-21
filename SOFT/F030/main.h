#define LCD_SIZE	40

#define PAROL_FISK	753 

//***********************************************
//
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

//-----------------------------------------------
//ФЇр ў«ж®ЁеЎЇр®¶Ґс±®¬
//extern signed short time_wrk;
//extern signed short demo_per;
//extern signed short demo_len;
extern signed short current_sound;
extern signed short wrk_cnt;
extern signed short max_file;
extern signed short current_file;
extern signed short current_demo_file;
extern signed short main_demo_cnt;


//-----------------------------------------------
//Управление воспроизведением музыки
extern signed short main_music_cnt;
extern signed short max_main_music_cnt;
extern signed short fade_out_main_music_cnt;

