#define VERSION 1012

#define OLD_CAN_PROTOKOL

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#define BIN__N(x) (x) | x>>3 | x>>6 | x>>9
#define BIN__B(x) (x) & 0xf | (x)>>12 & 0xf0
#define BIN8(v) (BIN__B(BIN__N(0x##v)))

#define delay_ms(x) {long xx; xx=(unsigned long)x * 20000UL; while(xx)xx--;}
#define delay_us(x) {long xx; xx=(unsigned long)x * 17UL; while(xx)xx--;}

#define OID_ENTERPRISE 	OID0(1,3), 6, 1, 4, 1, 130, 131, 31
#define OID_DEVICE 		10
#define DISPLAY_DEVICE_INFO			1
#define DISPLAY_DEVICE_INFO_CODE			1
#define DISPLAY_DEVICE_INFO_SERIAL			2
#define DISPLAY_DEVICE_INFO_SERIAL_LSB		3
#define DISPLAY_DEVICE_INFO_SERIAL_MSB		4
#define DISPLAY_DEVICE_INFO_LOCATION 		5
#define DISPLAY_DEVICE_INFO_NUMOFBAT 		6
#define DISPLAY_DEVICE_INFO_NUMOFBPS 		7
#define DISPLAY_DEVICE_INFO_NUMOFEVENTS		8

#define DISPLAY_MAINS_POWER			2
#define DISPLAY_MAINS_POWER_VOLTAGE		1
#define DISPLAY_MAINS_POWER_FREQUENCY		2
#define DISPLAY_MAINS_POWER_STATUS			3
#define DISPLAY_MAINS_POWER_ALARM			4

#define DISPLAY_LOAD				3
#define DISPLAY_LOAD_VOLTAGE				1
#define DISPLAY_LOAD_CURRENT				2

#define DISPLAY_PSU					4
#define DISPLAY_PSU_ENTRY_NUMBER			1,1
#define DISPLAY_PSU_ENTRY_VOLTAGE 			1,2
#define DISPLAY_PSU_ENTRY_CURRENT			1,3
#define DISPLAY_PSU_ENTRY_TEMPERATURE		1,4
#define DISPLAY_PSU_ENTRY_STATUS			1,5

#define DISPLAY_BAT					5
#define DISPLAY_BAT_VOLTAGE				1
#define DISPLAY_BAT_CURRENT				2
#define DISPLAY_BAT_TEMPERATURE			3
#define DISPLAY_BAT_CAPACITY			4
#define DISPLAY_BAT_CHARGE				5
#define DISPLAY_BAT_STATUS				6

#define DISPLAY_SPEC				6
#define DISPLAY_SPEC_STAT				1
#define DISPLAY_SPEC_TRAP_MESSAGE			4
#define DISPLAY_SPEC_TRAP_VALUE 			5


#define LCD_SIZE 200

#define SNMP_COMMAND				8
#define COMMAND_ANSWER					1
#define COMMAND_PARAMETR					2

#define SYSPARAMS					10
#define SYSPARAMSMAINPSU					20
#define SYSPARAMSSOUNDALARMEN				40
#define SYSPARAMSALARMAUTODISABLE			41
#define SYSPARAMS_BAT_TEST_TIME			42
#define SYSPARAMS_U_MAX					49
#define SYSPARAMS_U_0_GRAD				50
#define SYSPARAMS_U_20_GRAD				51 
#define SYSPARAMS_U_SIGN					52
#define SYSPARAMS_U_MIN_POWER				53
#define SYSPARAMS_U_WITHOUT_BAT			54
#define SYSPARAMS_IBK					55
#define SYSPARAMS_IZMAX					56
#define SYSPARAMS_IMAX					57
#define SYSPARAMS_KIMAX					58
#define SYSPARAMS_KVZ					59
#define SYSPARAMS_TZAS					60
#define SYSPARAMS_TMAX					61	


#define COMMAND_OK		0x5555
#define COMAND_FAIL		0xaaaa
#define COMMAND_INVALID	0xeeee
#define WRONG_PARAMETER	0xeeef

#define SNMP_BPS_DISABLE		5
#define SNMP_BPS_UNDISABLE	8
#define SNMP_SPEC_VZ		3
#define SNMP_SPEC_KE		4
#define SNMP_SPEC_DISABLE	7

#define DISPLAY_LOG					9
#define DISPLAY_LOG_ENTRY_EVENTS 			1,1
//#define DISPLAY_LOG_ENTRY_EVENTS 			1,1

#define SPA_OID	130, 131, 31,


#define MASK(lengt) 		(0xffffffff>>(32-lengt))
#define MASK_OFFSET(shift,lengt)	(MASK(lengt)<<shift)

#define GET_REG( reg, shift, lengt) 		( (reg & MASK_OFFSET(shift,lengt)) >> shift)
#define SET_REG( reg, val, shift, lengt)  	reg = ( (reg & ~MASK_OFFSET(shift,lengt)) | ((val&MASK(lengt)) << shift) )
//#define CHK_REG( reg, mask ) ( (reg) & (mask) == (mask) )


#define OFFBP1 GET_REG(LPC_GPIO0->FIOPIN,8,1)
#define OFFBP2 GET_REG(LPC_GPIO0->FIOPIN,9,1)

#define SEC_IN_HOUR	3600L

#define KOEFPOT 100

#define BAUD_RATE0 9600UL
#define BAUD_RATE1 9600UL

//#define HARDVARE_VERSION	 5

#define AVAR_UNET_ON 	5
#define AV_UMAX_ON 		100
#define AV_UMIN_ON 		100 
#define AV_T_ON 		20
#define AV_UBAT_ON 		25
#define AV_IBAT_ON 		15 

//#define PAROL_ALL_ZERO


#ifndef PAROL_ALL_ZERO
#define PAROL_KALIBR 873
#define PAROL_SET 184
#define PAROL_MODE 0 
#define PAROL_ALLER 815 
#define PAROL_BAT_IN 722 
#define PAROL_BAT_OUT 722
#define PAROL_KE 125
#define PAROL_VZ 126
#define PAROL_TST 999 
#define PAROL_DEFAULT 295
#define PAROL_AUSW 949
#define PAROL_LOG_RESET	691
#endif                

#ifdef PAROL_ALL_ZERO
#define PAROL_KALIBR 0
#define PAROL_SET 0
#define PAROL_MODE 0 
#define PAROL_ALLER 0 
#define PAROL_BAT_IN 0 
#define PAROL_BAT_OUT 0
#define PAROL_KE 0
#define PAROL_VZ 0
#define PAROL_TST 0
#define PAROL_DEFAULT 0
#define PAROL_AUSW 0
#endif

#define BUT0	0
#define BUT1	1
#define BUT2	2
#define BUT3	3
#define BUT4	4   
#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)|(1UL<<BUT3)|(1UL<<BUT4)

//-----------------------------------------------
//������
extern char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz,b33Hz,bADC, bADC1;
extern short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7,t0_cnt8,t0_cnt_adc;
extern char bFL5,bFL2,bFL,bFL_;

//-----------------------------------------------
//���
extern signed short adc_buff[12][16],adc_buff_[12]/*,unet_buff[18],unet_buff_*/,adc_buff_max[12],adc_buff_min[12],unet_buff_max,unet_buff_min;
extern char adc_cnt,adc_cnt1,adc_ch,adc_self_ch_cnt;
extern signed short adc_buff_old[12];
extern signed short adc_self_ch_buff[3],adc_self_ch_disp[3];
extern signed short adc_buff_9[64],adc_buff_9_cnt,adc_buff_9_;

//-----------------------------------------------
//��������� ����
extern short Hz_cnt,fnet,Hz_out;
extern char bFF,bFF_;
extern signed short Unet,Unet_;
extern char unet_drv_cnt, unet_max_drv_cnt;
extern signed short unet_store;

//-----------------------------------------------
//���������
typedef enum {iMn,iSrv_sl,iNet,iSet,iBat,iSrc,iS2,iSet_prl,iK_prl,iDnd,iK,
	iSpcprl,iSpc,k,Crash_0,Crash_1,iKednd,
	iLoad,iSpc_prl_vz,iSpc_prl_ke,iKe,iVz,iAVAR,iStr,iVrs,iPrltst,iApv,
	iK_src,iK_bat,iK_load,iK_net,iTst,iTst_klbr,iTst_BPS1,iTst_BPS2,
	iTst_BPS12,iDebug,iDef,iSet_st_prl,iK_pdp,iSet_T,iSet_T_avt,iDeb,iJ_bat,
	iPrl_bat_in_out,iPdp1,iJAv_sel,iJAv_net_sel,iJAv_net,iJAv_src1,
	iJAv_src2,iJAv_bat,iJAv_bat_sel,iAusw,iAusw_prl,iAusw_set,iK_t_out,
	iJ_bat_ke_sel,iJ_bat_ke,iJ_bat_vz_sel,iJ_bat_vz,iJ_bat_wrk_sel,iJ_bat_wrk,
	iExt_set,iExt_dt,iExt_sk,iAvz,iJAv_src1_sel,iJAv_src2_sel,iLog,iLog_,iLan_set,iLan,iSM,
	iFWabout, iLog_reset_prl}ind_enum;


typedef struct  
{
ind_enum i;

signed char s_i;
signed char s_i1;
signed char s_i2;
signed char i_s;
} stuct_ind;

extern stuct_ind a,b[10];

#define ind     a.i
#define sub_ind     a.s_i
#define sub_ind1     a.s_i1
#define sub_ind2     a.s_i2
#define index_set     a.i_s

extern char dig[5];
extern char zero_on;
extern char lcd_buffer[LCD_SIZE];
extern char lcd_bitmap[1024];
extern const char ABCDEF[];
extern signed char ptr_ind;
extern char mnemo_cnt;
extern signed char parol[3];
extern char fl_simv_num,fl_simv_len;
extern char default_temp;
extern signed short av_j_si_max,av_j_si_max_;
extern char simax;
extern char phase;
extern const char sm_[]; //
extern const char sm_exit[]; //
extern const char smon[]; 
extern const char smoff[];
extern const char sm_mont[13][4]; //
extern char content[63]; 

//-----------------------------------------------
//������������, ������������ �� EEPROM
extern signed short Ktsrc[2];
extern signed short Kusrc[2];
extern signed short Kisrc[2];
extern signed short Ki0src[2];
extern signed short Kubat;
extern signed short Kibat0;
extern signed short Kibat1;
extern signed short Ktbat;
extern signed short Kunet;
extern signed short Ktout[3];

extern signed short MAIN_IST;
extern signed short UMAX;
extern signed short UB0;
extern signed short UB20;
extern signed short TMAX;
extern signed short AV_OFF_AVT;
extern signed short USIGN;
extern signed short UMN;
extern signed short UMAXN;
extern signed short ZV_ON;
extern signed short IKB;
extern signed short KVZ;
extern signed short IMAX;
extern signed short KIMAX;
extern signed short IMIN;
extern signed short APV_ON;
extern signed short IZMAX;
extern signed short U0B;
extern signed short TZAS;
extern signed short VZ_HR;
extern signed short TBAT;

extern signed short NUMBAT;
extern signed short NUMIST;
extern signed short NUMDT;
extern signed short NUMSK;
extern signed short BAT_C_REAL;
extern signed short BAT_C_NOM;
extern signed short BAT_RESURS;
extern signed short KINDSRC;

//signed short ZAR_CNT,ZAR_CNT_KE;
//signed short BAT_RESURS;

extern signed short AUSW_MAIN;
extern signed long 	AUSW_MAIN_NUMBER;
extern signed short AUSW_DAY;
extern signed short AUSW_MONTH;
extern signed short AUSW_YEAR;
extern signed short AUSW_UKU;
extern signed short AUSW_UKU_SUB;
extern signed long AUSW_UKU_NUMBER;
extern signed long	AUSW_BPS1_NUMBER;
extern signed long  AUSW_BPS2_NUMBER;
extern signed short AUSW_RS232;
extern signed short AUSW_PDH;
extern signed short AUSW_SDH;
extern signed short AUSW_ETH;

extern signed short TMAX_EXT_EN[3];
extern signed short TMAX_EXT[3];
extern signed short TMIN_EXT_EN[3];
extern signed short TMIN_EXT[3];
extern signed short T_EXT_REL_EN[3];
extern signed short T_EXT_ZVUK_EN[3];
extern signed short T_EXT_LCD_EN[3];
extern signed short T_EXT_RS_EN[3];

extern signed short SK_SIGN[4];
extern signed short SK_REL_EN[4];
extern signed short SK_ZVUK_EN[4];
extern signed short SK_LCD_EN[4];
extern signed short SK_RS_EN[4];

typedef enum {AVZ_1=1,AVZ_2=2,AVZ_3=3,AVZ_6=6,AVZ_12=12,AVZ_OFF=0}enum_AVZ;
extern enum_AVZ AVZ;

extern unsigned short HOUR_AVZ;
extern unsigned short MIN_AVZ;
extern unsigned short SEC_AVZ;
extern unsigned short DATE_AVZ;
extern unsigned short MONTH_AVZ;
extern unsigned short YEAR_AVZ;
extern signed short AVZ_TIME;

extern signed short ETH_IS_ON;
extern signed short ETH_DHCP_ON;
extern signed short ETH_IP_1;
extern signed short ETH_IP_2;
extern signed short ETH_IP_3;
extern signed short ETH_IP_4;
extern signed short ETH_MASK_1;
extern signed short ETH_MASK_2;
extern signed short ETH_MASK_3;
extern signed short ETH_MASK_4;
extern signed short ETH_TRAP1_IP_1;
extern signed short ETH_TRAP1_IP_2;
extern signed short ETH_TRAP1_IP_3;
extern signed short ETH_TRAP1_IP_4;
extern signed short ETH_TRAP2_IP_1;
extern signed short ETH_TRAP2_IP_2;
extern signed short ETH_TRAP2_IP_3;
extern signed short ETH_TRAP2_IP_4;
extern signed short ETH_TRAP3_IP_1;
extern signed short ETH_TRAP3_IP_2;
extern signed short ETH_TRAP3_IP_3;
extern signed short ETH_TRAP3_IP_4;
extern signed short ETH_TRAP4_IP_1;
extern signed short ETH_TRAP4_IP_2;
extern signed short ETH_TRAP4_IP_3;
extern signed short ETH_TRAP4_IP_4;
extern signed short ETH_TRAP5_IP_1;
extern signed short ETH_TRAP5_IP_2;
extern signed short ETH_TRAP5_IP_3;
extern signed short ETH_TRAP5_IP_4;
extern signed short ETH_SNMP_PORT_READ;
extern signed short ETH_SNMP_PORT_WRITE;
extern signed short ETH_GW_1;
extern signed short ETH_GW_2;
extern signed short ETH_GW_3;
extern signed short ETH_GW_4;

extern signed short dumm[8];

typedef enum  {bisON=0x0055,bisOFF=0x00aa}enum_BAT_IS_ON;
extern enum_BAT_IS_ON BAT_IS_ON;
typedef enum  {apvON=0x0055,apvOFF=0x00aa}enum_apv_on;
extern enum_apv_on apv_on1,apv_on2;

extern signed short BAT_DAY_OF_ON,BAT_MONTH_OF_ON,BAT_YEAR_OF_ON;
extern signed short apv_on2_time;

typedef enum {mnON=0x55,mnOFF=0xAA}enum_MNEMO_ON;
extern enum_MNEMO_ON MNEMO_ON;
extern signed short MNEMO_TIME;

extern signed short SNTP_ENABLE;
extern signed short SNTP_GMT;

//-----------------------------------------------
//��������� �������
extern char St;
extern short main_cnt;

//-----------------------------------------------
//��������� �������
extern signed short t_b,Ubat,Ibat;
extern signed long zar_cnt,zar_cnt_ke;
extern signed char zar_percent;
extern char cnt_wrk;
typedef enum {wrkON=0x55,wrkOFF=0xAA}enum_wrk;
extern enum_wrk wrk;
extern unsigned long wrk_date[2];
extern signed long ibat_integr_;
extern signed short ibat_integr;
extern signed short cnt_resurs;
extern char cnt_ibat,cnt_ubat;
extern char cnt_irazr;
extern char bUrazr;
extern char bUOFF,bIOFF;
extern char cnt_irazr;
extern char bIrazr;
extern char bI;
extern char NDB;
extern signed short ubat_old[8];
extern signed short ubat_old_cnt;

//-----------------------------------------------
//��������� ����������
extern char St_[2];
extern signed short t_i[2],Us[2],Is[2];
extern char ND[2];

//-----------------------------------------------
//��������� ��������
extern signed short iload,Uload;

//-----------------------------------------------
//��������� ������� ��������
extern signed short tout[3];
extern signed char tout_max_cnt[3],tout_min_cnt[3];
typedef enum {tNORM,tMAX,tMIN}enum_tout_stat;
extern enum_tout_stat tout_stat[3];
extern char in_stat_out_old[4];
typedef enum {skON=0x55,skOFF=0xaa}enum_sk_stat;
extern enum_sk_stat sk_stat[4];
extern char ND_out[3];
extern char in_stat_out[4];

//-----------------------------------------------
//������
extern char speed,l_but,n_but;
extern char but;                            
extern unsigned long but_n,but_s;
extern char but0_cnt;
extern char but1_cnt;
extern char but_onL_temp;

 //-----------------------------------------------
//���������
extern char MSG_IND2OUT_DIS_SRC1,MSG_IND2OUT_DIS_SRC1_OLD;
extern char MSG_IND2OUT_DIS_SRC2,MSG_IND2OUT_DIS_SRC2_OLD;
extern char MSG_IND2OUT_EN_SRC1,MSG_IND2OUT_EN_SRC1_OLD;
extern char MSG_IND2OUT_EN_SRC2,MSG_IND2OUT_EN_SRC2_OLD;
extern char MSG_IND2OUT_EN_RELSAM,MSG_IND2OUT_EN_RELSAM_OLD;
extern short MSG_IND2PWM_SRC1,MSG_IND2PWM_SRC2;


//-----------------------------------------------
//����
typedef enum {tstOFF,tstON,tstU} enum_tst_state;
extern enum_tst_state tst_state[10];

//-----------------------------------------------
//��������������
extern unsigned short skb_cnt;

//-----------------------------------------------
//�����
extern unsigned short hour_cnt_5hz,hour_cnt_1hz;
extern char cnt_ind;

//-----------------------------------------------
//WEB-���������
extern char uku_set_autorized;
extern long web_param_input;
extern char place_holder[70];
extern short web_cnt_main;
extern short web_cnt_2hz;

//-----------------------------------------------
//�������
extern unsigned short rotor_can[6];
extern unsigned short cnt_sec;
extern char plazma_suzun;
extern short plazma_mib,plazma_mib1;
extern short snmp_plazma;
extern char plazma_can,plazma_can1,plazma_can2,plazma_can3,plazma_can4;
extern char web_plazma[5];
extern short plazma_uart_ee[8];

extern char bRESET_RESET;
//-----------------------------------------------
//���������� ��� �������� �� SNMP
extern  char str_of_device_name;

extern const char* DEVICE_NAME[20];

//-----------------------------------------------
void Delay (unsigned long tick); 
void bitmap_hndl(void);
void SysTick_Handler (void);
/******************************************************************************
**                            End Of File
******************************************************************************/
