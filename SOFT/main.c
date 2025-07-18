
#include "LPC17xx.H"
#include "system_LPC17xx.h"
#include "net_config.h"
#include "timer.h"
#include "control.h"
#include "common_func.h"
#include "simbols.h"
#include "graphic.h"
#include "gran.h"
#include "eeprom_map.h"
#include "25lc640.h"
#include "avar.h"
#include "ret.h"
#include "memo.h"
#include "beep.h"
#include "lcd_agm1232_UKU203.h" 
#include "rtl.h"
#include "main.h"
#include "beep.h"
#include "snmp_data_file.h" 
#include "uart0.h"
#include "full_can.h"
#include "http_data.h"
#include "sntp.h"
#include "curr_version.h"

extern U8 own_hw_adr[];
extern U8  snmp_Community[];


BOOL tick;
extern LOCALM localm[];
#define MY_IP localm[NETIF_ETH].IpAdr
#define DHCP_TOUT   50


//-----------------------------------------------
//������
char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz,b33Hz, bADC, bADC1;
short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7,t0_cnt8,t0_cnt_adc;
char bFL5,bFL2,bFL,bFL_;





//-----------------------------------------------
//��������� ����
short Hz_cnt,fnet,Hz_out;
char bFF,bFF_;
signed short Unet,Unet_;
char unet_drv_cnt, unet_max_drv_cnt;
signed short unet_store;

//-----------------------------------------------
//���������
stuct_ind a,b[10];
char dig[5];
char zero_on;
char lcd_buffer[LCD_SIZE];
char lcd_bitmap[1024];
const char ABCDEF[]={"0123456789ABCDEF"};
signed char ptr_ind=0;
char mnemo_cnt=10;
signed char parol[3];
char fl_simv_num,fl_simv_len;
char default_temp;
signed short av_j_si_max,av_j_si_max_;
char simax;
char phase;
const char sm_[]		={"                    "}; //
const char sm_exit[]	={" �����              "}; //
const char smon[]	={"���."}; 
const char smoff[]	={"���."};
const char sm_mont[13][4]={"���","���","���","���","���","���","���","���","���","���","���","���","���"}; //
char content[63]; 

//-----------------------------------------------
//������������, ������������ �� EEPROM
signed short Ktsrc[2];
signed short Kusrc[2];
signed short Kisrc[2];
signed short Ki0src[2];
signed short Kubat;
signed short Kibat0;
signed short Kibat1;
signed short Ktbat;
signed short Kunet;
signed short Ktout[3];

signed short MAIN_IST;
signed short UMAX;
signed short UB0;
signed short UB20;
signed short TMAX;
signed short AV_OFF_AVT;
signed short USIGN;
signed short UMN;
signed short UMAXN;
signed short ZV_ON;
signed short IKB;
signed short KVZ;
signed short IMAX;
signed short KIMAX;
signed short IMIN;
signed short APV_ON;
signed short IZMAX;
signed short U0B;
signed short TZAS;
signed short VZ_HR;
signed short TBAT;

signed short NUMBAT;
signed short NUMIST;
signed short NUMDT;
signed short NUMSK;
signed short BAT_C_REAL;
signed short BAT_C_NOM;
signed short BAT_RESURS;
signed short KINDSRC;

//signed short ZAR_CNT,ZAR_CNT_KE;
//signed short BAT_RESURS;

signed short AUSW_MAIN;
signed long AUSW_MAIN_NUMBER;
signed short AUSW_DAY;
signed short AUSW_MONTH;
signed short AUSW_YEAR;
signed short AUSW_UKU;
signed short AUSW_UKU_SUB;
signed long AUSW_UKU_NUMBER;
signed long	AUSW_BPS1_NUMBER;
signed long  AUSW_BPS2_NUMBER;
signed short AUSW_RS232;
signed short AUSW_PDH;
signed short AUSW_SDH;
signed short AUSW_ETH;

signed short TMAX_EXT_EN[3];
signed short TMAX_EXT[3];
signed short TMIN_EXT_EN[3];
signed short TMIN_EXT[3];
signed short T_EXT_REL_EN[3];
signed short T_EXT_ZVUK_EN[3];
signed short T_EXT_LCD_EN[3];
signed short T_EXT_RS_EN[3];

signed short SK_SIGN[4];
signed short SK_REL_EN[4];
signed short SK_ZVUK_EN[4];
signed short SK_LCD_EN[4];
signed short SK_RS_EN[4];

enum_AVZ AVZ;
unsigned short HOUR_AVZ;
unsigned short MIN_AVZ;
unsigned short SEC_AVZ;
unsigned short DATE_AVZ;
unsigned short MONTH_AVZ;
unsigned short YEAR_AVZ;
signed short AVZ_TIME;

signed short ETH_IS_ON;
signed short ETH_DHCP_ON;
signed short ETH_IP_1;
signed short ETH_IP_2;
signed short ETH_IP_3;
signed short ETH_IP_4;
signed short ETH_MASK_1;
signed short ETH_MASK_2;
signed short ETH_MASK_3;
signed short ETH_MASK_4;
signed short ETH_TRAP1_IP_1;
signed short ETH_TRAP1_IP_2;
signed short ETH_TRAP1_IP_3;
signed short ETH_TRAP1_IP_4;
signed short ETH_TRAP2_IP_1;
signed short ETH_TRAP2_IP_2;
signed short ETH_TRAP2_IP_3;
signed short ETH_TRAP2_IP_4;
signed short ETH_TRAP3_IP_1;
signed short ETH_TRAP3_IP_2;
signed short ETH_TRAP3_IP_3;
signed short ETH_TRAP3_IP_4;
signed short ETH_TRAP4_IP_1;
signed short ETH_TRAP4_IP_2;
signed short ETH_TRAP4_IP_3;
signed short ETH_TRAP4_IP_4;
signed short ETH_TRAP5_IP_1;
signed short ETH_TRAP5_IP_2;
signed short ETH_TRAP5_IP_3;
signed short ETH_TRAP5_IP_4;

signed short ETH_SNMP_PORT_READ;
signed short ETH_SNMP_PORT_WRITE;

signed short ETH_GW_1;
signed short ETH_GW_2;
signed short ETH_GW_3;
signed short ETH_GW_4;

signed short dumm[8];

enum_BAT_IS_ON BAT_IS_ON;
enum_apv_on apv_on1,apv_on2;

signed short BAT_DAY_OF_ON,BAT_MONTH_OF_ON,BAT_YEAR_OF_ON;
signed short apv_on2_time;

enum_MNEMO_ON MNEMO_ON;
signed short MNEMO_TIME;

signed short SNTP_ENABLE;
signed short SNTP_GMT;

//-----------------------------------------------
//���
signed short adc_buff[12][16],adc_buff_[12]/*,unet_buff[18],unet_buff_*/,adc_buff_max[12],adc_buff_min[12]={5000,5000,5000,5000,5000,5000,5000,5000,5000,5000},unet_buff_max,unet_buff_min=5000;
signed short adc_buff_old[12];
char adc_cnt,adc_cnt1,adc_ch,adc_self_ch_cnt;
signed short adc_self_ch_buff[3],adc_self_ch_disp[3];
signed short adc_buff_9[64],adc_buff_9_cnt,adc_buff_9_;

//-----------------------------------------------
//��������� �������
char St;
short main_cnt;

//-----------------------------------------------
//��������� �������
signed short t_b,Ubat,Ibat;
signed long zar_cnt,zar_cnt_ke;
signed char zar_percent;
char cnt_wrk;
enum_wrk wrk;
unsigned long wrk_date[2];
signed long ibat_integr_;
signed short ibat_integr;
signed short cnt_resurs;
char cnt_ibat,cnt_ubat;
char cnt_irazr;
char bUrazr;
char bUOFF,bIOFF;
char cnt_irazr;
char bIrazr; 
char bI;
char NDB;
signed short ubat_old[8];
signed short ubat_old_cnt;

//-----------------------------------------------
//����
enum_tst_state tst_state[10];

//-----------------------------------------------
//��������� ����������
char St_[2];
signed short t_i[2],Us[2],Is[2];
char ND[2];

//-----------------------------------------------
//��������� ��������
signed short iload,Uload;

//-----------------------------------------------
//��������� ������� ��������
signed short tout[3];
signed char tout_max_cnt[3],tout_min_cnt[3];
enum_tout_stat tout_stat[3];
char in_stat_out_old[4];
enum_sk_stat sk_stat[4]={skOFF,skOFF};
char ND_out[3];
char in_stat_out[4];

//-----------------------------------------------
//������
char speed,l_but,n_but;
char but;                            
unsigned long but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;


//-----------------------------------------------
//���������
char MSG_IND2OUT_DIS_SRC1,MSG_IND2OUT_DIS_SRC1_OLD;
char MSG_IND2OUT_DIS_SRC2,MSG_IND2OUT_DIS_SRC2_OLD;
char MSG_IND2OUT_EN_SRC1,MSG_IND2OUT_EN_SRC1_OLD;
char MSG_IND2OUT_EN_SRC2,MSG_IND2OUT_EN_SRC2_OLD;
char MSG_IND2OUT_EN_RELSAM,MSG_IND2OUT_EN_RELSAM_OLD;
short MSG_IND2PWM_SRC1,MSG_IND2PWM_SRC2;




//-----------------------------------------------
//��������������
unsigned short skb_cnt;

//-----------------------------------------------
//�����
unsigned short hour_cnt_5hz,hour_cnt_1hz;
char cnt_ind;

//-----------------------------------------------
//WEB-���������
char uku_set_autorized=0;
long web_param_input;
char place_holder[70]="�����������.�����������";
short web_cnt_main;
short web_cnt_2hz;

//-----------------------------------------------
//�������
unsigned short rotor_can[6];
unsigned short cnt_sec;
char plazma_suzun;
char rele_temp;
short snmp_plazma;
char plazma_can,plazma_can1,plazma_can2,plazma_can3,plazma_can4;
char web_plazma[5];
short plazma_uart_ee[8];


BOOL tick;
U32  dhcp_tout;

#define MY_IP localm[NETIF_ETH].IpAdr
#define DHCP_TOUT   50


volatile unsigned long SysTickCnt;

short plazma_mib,plazma_mib1;


const char* DEVICE_NAME[20]={
                              "����220/60-24A",
                              "����220/60-12A",
                              "����220/48-24A",
                              "����220/48-12A",
                              "����220/60-10A",
                              "����220/60-5A ",
                              "����220/48-10A",
                              "����220/48-5A ",
                              "����220/24-24A",
                              "����220/24-12A",
                              "����220/48-40A",
                              "����220/60-40A"
                              "����220/48-20A",
                              "����220/60-20A",
                              "����220/24-50A",
                              "����220/24-25A",
                              "����220/24-24A",
                              "����220/24-12A"
                              };


short adc_plazma;
short AD_last;
char bwd_stop;
char bRESET=0;
char bRESET_RESET=0;

U8 socket_tcp;

//-----------------------------------------------
signed short abs_pal(signed short in)
{
if(in<0)return -in;
else return in;
}



//-----------------------------------------------
void ADC_IRQHandler(void) {
LPC_ADC->ADCR &=  ~(7<<24);
AD_last = (LPC_ADC->ADGDR>>4) & 0xFFF;/* Read Conversion Result             */
adc_plazma++;

adc_self_ch_buff[adc_self_ch_cnt]=AD_last;
adc_self_ch_cnt++;
if(adc_self_ch_cnt<3)
	{
	LPC_ADC->ADCR |=  (1<<24);
	}
else
	{

 
	//SET_REG(LPC_ADC->ADCR,1,24,3);
	}

/*			adc_buff_[0]=AD_last;
			if(AD_last<adc_buff_min[adc_ch])adc_buff_min[adc_ch]=AD_last;
			if(AD_last>adc_buff_max[adc_ch])adc_buff_max[adc_ch]=AD_last;*/
}

//-----------------------------------------------
//���������� ��� �������� �� SNMP
char str_of_device_name;


LOCALM const ip_config = {
  { 192,168,0,150 },             // IP address
  { 192,168,0,1 },               // Default Gateway
  { 255,255,255,0 },             // Net mask
  { 194,25,2,129 },              // Primary DNS server
  { 194,25,2,130 }               // Secondary DNS server
};



//-----------------------------------------------
void init_ETH(void)
{
localm[NETIF_ETH].IpAdr[0]=lc640_read_int(EE_ETH_IP_1);
localm[NETIF_ETH].IpAdr[1]=lc640_read_int(EE_ETH_IP_2);
localm[NETIF_ETH].IpAdr[2]=lc640_read_int(EE_ETH_IP_3);
localm[NETIF_ETH].IpAdr[3]=lc640_read_int(EE_ETH_IP_4);

localm[NETIF_ETH].NetMask[0]=lc640_read_int(EE_ETH_MASK_1);
localm[NETIF_ETH].NetMask[1]=lc640_read_int(EE_ETH_MASK_2);
localm[NETIF_ETH].NetMask[2]=lc640_read_int(EE_ETH_MASK_3);
localm[NETIF_ETH].NetMask[3]=lc640_read_int(EE_ETH_MASK_4);

localm[NETIF_ETH].DefGW[0]=lc640_read_int(EE_ETH_GW_1);
localm[NETIF_ETH].DefGW[1]=lc640_read_int(EE_ETH_GW_2);
localm[NETIF_ETH].DefGW[2]=lc640_read_int(EE_ETH_GW_3);
localm[NETIF_ETH].DefGW[3]=lc640_read_int(EE_ETH_GW_4);

}

//-----------------------------------------------
void Delay (unsigned long tick) 
{       
unsigned long systickcnt;

systickcnt = SysTickCnt;
while ((SysTickCnt - systickcnt) < tick);
}

//-----------------------------------------------
void rtc_init (void) 
{
LPC_RTC->CCR=0x11;
}
//-----------------------------------------------
void pwm_init(void)
{
SET_REG(LPC_PINCON->PINSEL7,3,(25-16)*2,2);
SET_REG(LPC_PINCON->PINSEL7,3,(26-16)*2,2);
LPC_PWM1->PR=0;
LPC_PWM1->PCR=0x00000c00;
LPC_PWM1->MCR=2;
LPC_PWM1->MR0=1000;
LPC_PWM1->MR2=800;
LPC_PWM1->MR3=300;
LPC_PWM1->LER=1;
LPC_PWM1->TCR=2;
LPC_PWM1->TCR=9;
}

//-----------------------------------------------
void info_for_snmp(void)
{
/*if(AUSW_MAIN==6024)		str_of_device_name=	"   ����220/60-24A   ";
else if(AUSW_MAIN==6012)	str_of_device_name=	"   ����220/60-12A   ";
else if(AUSW_MAIN==4824)	str_of_device_name=	"   ����220/48-24A   ";
else if(AUSW_MAIN==4812)	str_of_device_name=	"   ����220/48-12A   ";
else if(AUSW_MAIN==6010)	str_of_device_name=	"   ����220/60-10A   ";
else if(AUSW_MAIN==6005)	str_of_device_name=	"   ����220/60-5A    ";
else if(AUSW_MAIN==4810)	str_of_device_name=	"   ����220/48-10A   ";
else if(AUSW_MAIN==4805)	str_of_device_name=	"   ����220/48-5A    ";
else if(AUSW_MAIN==2424)	str_of_device_name=	"   ����220/24-24A   ";
else if(AUSW_MAIN==2412)	str_of_device_name=	"   ����220/24-12A   ";
else if(AUSW_MAIN==4840)	str_of_device_name=	"   ����220/48-40A   ";
else if(AUSW_MAIN==6030)	str_of_device_name=	"   ����220/60-30A   ";
else if(AUSW_MAIN==4820)	str_of_device_name=	"   ����220/48-20A   ";
else if(AUSW_MAIN==6015)	str_of_device_name=	"   ����220/60-15A   ";
else if(AUSW_MAIN==2450)	str_of_device_name=	"   ����220/24-50A   ";
else if(AUSW_MAIN==2425)	str_of_device_name=	"   ����220/24-25A   ";	
else if(AUSW_MAIN==2424)	str_of_device_name=	"   ����220/24-24A   ";
else if(AUSW_MAIN==2412)	str_of_device_name=	"   ����220/24-12A   ";*/
str_of_device_name=1;
}

//-----------------------------------------------
void bitmap_hndl(void)
{
short x,ii,i;
unsigned int ptr_bitmap;
static char ptr_cnt,ptr_cnt1,ptr_cnt2,ptr_cnt3,ptr_cnt4;

for(ii=0;ii<488;ii++)
	{
	lcd_bitmap[ii]=0x00;
	}

if(!mnemo_cnt)
	{
	if(St&0x01)
		{
		if(bFL2)
			{
			graphic_print(3,3,50,24,50,3,sAVNET,0);
			graphic_print(3,3,50,24,50,3,sAVNET1,0);
			}
		}
	else
		{

		if(NUMIST>=1)
			{
			draw_rectangle(0,0,20,20,0,0);
			draw_rectangle(1,1,18,18,0,0);
			if(!(St_[0]&0x3c))
				{
				graphic_print(3,2,15,15,15,2,sBPS1,0);
				}
			else if(St_[0]&(1<<4))
				{
				if(bFL2)graphic_print(3,2,15,15,15,2,sAVT,0);
				}
			else if((St_[0]&(1<<3))||(St_[0]&(1<<2)))
				{
				if(bFL2)graphic_print(2,2,15,15,15,2,sAVU,0);
				}	
			
			if((!OFFBP1))
				{
				draw(9,20,0,11,0);
				draw(9,31,91,0,0);
				draw_ptr(9,19+ptr_cnt1,0,4);
				}				
			}
		if(NUMIST>=2)
			{
			draw_rectangle(23,0,20,20,0,0);
			draw_rectangle(24,1,18,18,0,0);
			if(!(St_[1]&0x3c))
				{
				graphic_print(25,2,15,15,15,2,sBPS2,0);
				}
			else if(St_[1]&(1<<4))
				{
				if(bFL2)graphic_print(25,2,15,15,15,2,sAVT,0);
				}
			else if((St_[1]&(1<<3))||(St_[1]&(1<<2)))
				{
				if(bFL2)graphic_print(25,2,15,15,15,2,sAVU,0);
				}	
			
			if((!OFFBP2))
				{
				draw(32,20,0,11,0);
				draw(32,31,68,0,0);
				draw_ptr(32,19+ptr_cnt1,0,4);
				}				
			}			
		}
	if(NUMBAT)
		{
		draw_rectangle(50,0,35,20,0,0);
		draw_rectangle(53,20,3,2,0,0);
		draw_rectangle(79,20,3,2,0,0);
		if(St&0x02)
			{
			if(bFL2)graphic_print(43,0,50,24,50,3,sAVNET1,0);
			}
		else 
			{
			draw(66,20,0,11,0);
			draw(66,31,34,0,0);
			if(Ibat<0)draw_ptr(66,19+ptr_cnt1,0,4);
			else if(Ibat>=0)draw_ptr(66,34-ptr_cnt1,2,4);
			
			if(ptr_cnt4<10)
				{
			if(BAT_C_REAL!=0x5555)
				{
				signed short u;
				u=(((signed short)zar_percent/5));
				gran(&u,0,20);
				draw_rectangle(51,0,32,u,1,0);
				//zar_percent=100;
				if(zar_percent<10)
					{
					draw_rectangle(61,5,12,9,1,2);
					graphic_print_text(61,5," %",2,zar_percent,0,1,1);
					}
				else if(zar_percent<100)
					{
					draw_rectangle(58,5,18,9,1,2);
					graphic_print_text(58,5,"  %",3,zar_percent,0,2,1);
					}		
				else 
					{
					draw_rectangle(55,5,24,9,1,2);
					graphic_print_text(55,5,"   %",4,zar_percent,0,3,1);
					}									
				//draw_rectangle(59,3,18,9,1,2);
				//graphic_print_text(53,3,"   %",4,zar_percent,0,3,1);
				}

				}				
			else
				{
				if((Ibat>=1000)||(Ibat<=-1000))graphic_print_text(58,5,"   A",4,Ibat/100,0,3,1);
				else graphic_print_text(58,5,"   A",4,Ibat/10,1,3,1);
				}
			}

		}	
		

	draw_rectangle(92,2,27,14,0,0);
	draw(92,8,-4,0,0);
	draw(118,8,4,0,0);
	draw(67,31,39,0,0);
	draw(105,31,0,-16,0);	
	draw_ptr(105,34-ptr_cnt3,2,4);
	
	graphic_print_text(70,22,"    B",5,Uload,1,4,1);
	if(iload<100)graphic_print_text(93,5,"   A",4,iload,1,3,1);
	else graphic_print_text(90,5,"   A",4,iload/10,0,3,1);
			
	ptr_cnt++;
	if(ptr_cnt>=3)
		{
		ptr_cnt=0;
		ptr_cnt1++;
		if(ptr_cnt1>=13)
			{
			ptr_cnt1=0;
			}
	
		ptr_cnt2++;
		if(ptr_cnt2>=32)
			{
			ptr_cnt2=0;
			}
				
		ptr_cnt3++;
		if(ptr_cnt3>=17)
			{
			ptr_cnt3=0;
			}

		ptr_cnt4++;
		if(ptr_cnt4>=20)
			{
			ptr_cnt4=0;
			}					
		}		
		
	}
else
	{
	for(i=0;i<4;i++)
		{
		ptr_bitmap=122*(unsigned)i;
		for(x=(20*i);x<((20*i)+20);x++)
	 		{
			lcd_bitmap[ptr_bitmap++]=caracter[(unsigned)lcd_buffer[x]*6];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+1];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+2];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+3];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+4];
			lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+5];
			} 
		}
	}	
}
 /*
//-----------------------------------------------
static void dhcp_check () 
{
if (tick == __FALSE || dhcp_tout == 0) 
	{
     return;
   	}

if (mem_test (&MY_IP, 0, IP_ADRLEN) == __FALSE && !(dhcp_tout & 0x80000000)) 
	{
     dhcp_tout = 0;
     return;
   	}
if (--dhcp_tout == 0) 
	{
     dhcp_disable ();
	dhcp_tout = 30 | 0x80000000;
     return;
   	}
if (dhcp_tout == 0x80000000) 
	{
     dhcp_tout = 0;

   	}
}*/

//-----------------------------------------------
void ind_hndl(void)
{
#ifndef MINISIZE
//const char* ptr;
const char* ptrs[35];
const char* sub_ptrs[30];
static char sub_cnt,sub_cnt1;
char i,sub_cnt_max;

sub_cnt_max=5;
i=0;

if(spc_stat==spc_VZ)
	{
	sub_ptrs[i++]=" ������.�����  z:0Z ";
	sub_cnt_max++;
	}
else if((spc_stat==spc_KE))
	{
	sub_ptrs[i++]="  �������� �������  ";
	sub_cnt_max++;
	}	
if(St&0x01)
	{
	sub_ptrs[i++]="   ������ ����!!!   ";
	sub_cnt_max++;	
	}
if(St&0x02)
	{
	sub_ptrs[i++]=" ������ �������!!!  ";
	sub_cnt_max++;	
	}	
if(St_[0]&0x1c)
	{
	sub_ptrs[i++]=" ������ ��������� N1";
	sub_cnt_max++;	
	}	

if(St_[1]&0x1c)
	{
	sub_ptrs[i++]=" ������ ��������� N2";
	sub_cnt_max++;	
	}	
		
if((tout_stat[0]==tMAX)&&(!T_EXT_LCD_EN[0]))
	{
	sub_ptrs[i++]="����.����.N1��������";
	sub_cnt_max++;	
	}	
else if((tout_stat[0]==tMIN)&&(!T_EXT_LCD_EN[0]))
	{
	sub_ptrs[i++]="����.����.N1��������";
	sub_cnt_max++;	
	}	
if((sk_stat[0]==skON)&&(!SK_LCD_EN[0]))
	{
	sub_ptrs[i++]=" �������� ����� N1  ";
	sub_cnt_max++;	
	}

if((sk_stat[1]==skON)&&(!SK_LCD_EN[1]))
	{
	sub_ptrs[i++]=" �������� ����� N2  ";
	sub_cnt_max++;	
	}
	
	/*b_ptrs[i]="   ������� 1        ";
	sub_cnt_max++;	
	sub_ptrs[i]="     ������� 2      ";
	sub_cnt_max++;	*/

	
sub_cnt1++;	
if(sub_cnt1>=20)
	{
	sub_cnt1=0;
	sub_cnt++;
	if(sub_cnt>=sub_cnt_max)
		{
		sub_cnt=0;
		}
	}





if(ind==iDeb)
     {
	if(sub_ind==0)
		{
		ptrs[0]="                    ";
     	ptrs[1]="                    ";
     	ptrs[2]="                    ";
     	ptrs[3]="                    ";

     	
     	
     	bgnd_par(ptrs[0],
     	         ptrs[1],
     	         ptrs[2],
     	         ptrs[3]);

		int2lcdyx(plazma_uart_ee[0],0,4,0);
		int2lcdyx(plazma_uart_ee[1],0,9,0);
		int2lcdyx(plazma_uart_ee[2],0,14,0);
		int2lcdyx(plazma_uart_ee[3],0,19,0);
		int2lcdyx(plazma_uart_ee[4],1,4,0);
		int2lcdyx(plazma_uart_ee[5],1,9,0);
		int2lcdyx(plazma_uart_ee[6],1,14,0);
		int2lcdyx(plazma_uart_ee[7],1,19,0);

		}

	else 	if(sub_ind==0)
		{
ptrs[0]="  --------   !      ";

#ifdef MS48L
		ptrs[0]="  MS48LAN    !      ";
#elif MK48L
		ptrs[0]="  MK48LAN    !      ";
#elif MS24L
		ptrs[0]="  MS24LAN    !      ";
#elif MK24L
		ptrs[0]="  MK24LAN    !      ";
#elif MS48
		ptrs[0]="  MS48       !      ";
#elif MK48
		ptrs[0]="  MK48       !      ";
#elif MS24
		ptrs[0]="  MS24       !      ";
#elif MK24
		ptrs[0]="  MK24       !      ";
#endif




     	ptrs[1]="                    ";
     	ptrs[2]="                    ";
     	ptrs[3]="                    ";

     	
     	
     	bgnd_par(ptrs[0],
     	         ptrs[1],
     	         ptrs[2],
     	         ptrs[3]);

		int2lcd(VERSION,'!',0);
		}

	else if(sub_ind==0) 
     	{
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");


     	int2lcdyx(adc_buff_[0],0,3,0);
     	int2lcdyx(adc_buff_[1],1,3,0);
     	int2lcdyx(adc_buff_[2],2,3,0);
     	int2lcdyx(adc_buff_[3],3,3,0);
     	int2lcdyx(adc_buff_[4],0,9,0);
     	int2lcdyx(adc_buff_[5],1,9,0);
     	int2lcdyx(adc_buff_[6],2,9,0);
     	int2lcdyx(adc_buff_[7],3,9,0);
		int2lcdyx(adc_buff_[8],1,19,0);
		int2lcdyx(adc_buff_[9],3,19,0);

		int2lcdyx(adc_self_ch_buff[0],0,15,0);
		int2lcdyx(adc_self_ch_buff[0],1,15,0);
		int2lcdyx(adc_self_ch_buff[0],2,15,0);
		//adc_self_ch_buff

		}
	else if(sub_ind==1) 
     	{
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");

		int2lcdyx(sub_ind1,0,0,0);

     	int2lcdyx(adc_buff[sub_ind1][0],0,4,0);
     	int2lcdyx(adc_buff[sub_ind1][1],1,4,0);
     	int2lcdyx(adc_buff[sub_ind1][2],2,4,0);
     	int2lcdyx(adc_buff[sub_ind1][3],3,4,0);
     	int2lcdyx(adc_buff[sub_ind1][4],0,9,0);
     	int2lcdyx(adc_buff[sub_ind1][5],1,9,0);
     	int2lcdyx(adc_buff[sub_ind1][6],2,9,0);
     	int2lcdyx(adc_buff[sub_ind1][7],3,9,0);
     	int2lcdyx(adc_buff[sub_ind1][8],0,14,0);
     	int2lcdyx(adc_buff[sub_ind1][9],1,14,0);
     	int2lcdyx(adc_buff[sub_ind1][10],2,14,0);
     	int2lcdyx(adc_buff[sub_ind1][11],3,14,0);
     	int2lcdyx(adc_buff[sub_ind1][12],0,19,0);
     	int2lcdyx(adc_buff[sub_ind1][13],1,19,0);
     	int2lcdyx(adc_buff[sub_ind1][14],2,19,0);
     	int2lcdyx(adc_buff[sub_ind1][15],3,19,0);


		}

    else if(sub_ind==2)
     	{
     	bgnd_par("                    ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    
     	int2lcdyx(adc_buff_[0],0,4,0);
     	int2lcdyx(adc_buff_[1],1,4,0);
     	int2lcdyx(adc_buff_[2],2,4,0);
     	int2lcdyx(adc_buff_[3],3,4,0);
     	int2lcdyx(adc_buff_[4],0,9,0);
     	int2lcdyx(adc_buff_[5],1,9,0);
     	int2lcdyx(adc_buff_[6],2,9,0);
     	int2lcdyx(adc_buff_[7],3,9,0);
     	int2lcdyx(adc_buff_[8],0,14,0);
     	int2lcdyx(adc_buff_[9],1,14,0);
     	int2lcdyx(adc_buff_[10],2,14,0);
     	int2lcdyx(adc_buff_[11],3,14,0);
     	int2lcdyx(adc_buff_[12],0,19,0);
     	int2lcdyx(adc_buff_[13],1,19,0);
     	int2lcdyx(adc_buff_[14],2,19,0);
     	int2lcdyx(adc_buff_[15],3,19,0);

		
//		int2lcdyx(tlv_buff_[1],1,17,0);
//		int2lcdyx(unet_buff_,3,19,0); 
		
     	    
	    }

	else if(sub_ind==2) 
     	{
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");


		int2lcdyx(skb_cnt,0,4,0);

		int2lcdyx(Kibat0,1,4,0);

		int2lcdyx(adc_buff_[4],2,4,0);

		//int2lcdyx(adc_buff_[sub_ind1],1,4,0);
		//int2lcdyx(adc_buff_max[sub_ind1],2,4,0);
		//int2lcdyx(adc_buff_min[sub_ind1],3,4,0);




		}
	else if(sub_ind==3) 
     	{
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");

		int2lcdyx(9,0,0,0);

//		int2lcdyx(unet_buff_,1,4,0);
//		int2lcdyx(unet_buff_max,2,4,0);
//		int2lcdyx(unet_buff_min,3,4,0);


		}
	else if(sub_ind==4) 
     	{
		unsigned int event_ptr,lc640_adr;
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");
		event_ptr=lc640_read_int(PTR_EVENT_LOG);
		lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);

		char2lcdhyx(lc640_read(lc640_adr),0,3);
		char2lcdhyx(lc640_read(lc640_adr+1),0,6);
		char2lcdhyx(lc640_read(lc640_adr+2),0,9);
		char2lcdhyx(lc640_read(lc640_adr+3),0,12);
		char2lcdhyx(lc640_read(lc640_adr+4),0,15);
		char2lcdhyx(lc640_read(lc640_adr+5),0,18);

		char2lcdhyx(lc640_read(lc640_adr+6),1,3);
		char2lcdhyx(lc640_read(lc640_adr+7),1,6);
		char2lcdhyx(lc640_read(lc640_adr+8),1,9);
		char2lcdhyx(lc640_read(lc640_adr+9),1,12);
		char2lcdhyx(lc640_read(lc640_adr+10),1,15);
		char2lcdhyx(lc640_read(lc640_adr+11),1,18);

		char2lcdhyx(lc640_read(lc640_adr+12),2,3);
		char2lcdhyx(lc640_read(lc640_adr+13),2,6);
		char2lcdhyx(lc640_read(lc640_adr+14),2,9);
		char2lcdhyx(lc640_read(lc640_adr+15),2,12);
/*		char2lcdhyx(lc640_read(EVENT_LOG+16),2,15);
		char2lcdhyx(lc640_read(EVENT_LOG+17),2,18);

		char2lcdhyx(lc640_read(EVENT_LOG+18),3,3);
		char2lcdhyx(lc640_read(EVENT_LOG+19),3,6);
		char2lcdhyx(lc640_read(EVENT_LOG+20),3,9);
		char2lcdhyx(lc640_read(EVENT_LOG+21),3,12);
		char2lcdhyx(lc640_read(EVENT_LOG+22),3,15);
		char2lcdhyx(lc640_read(EVENT_LOG+23),3,18);	*/
		int2lcdyx(event_ptr,3,10,0);
		int2lcdyx(lc640_adr,3,18,0);


//		int2lcdyx(unet_buff_,1,4,0);
//		int2lcdyx(unet_buff_max,2,4,0);
//		int2lcdyx(unet_buff_min,3,4,0);


		}

	else if(sub_ind==5) 
     	{
		unsigned int event_ptr,lc640_adr;
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");
		event_ptr=lc640_read_int(PTR_EVENT_LOG);
		lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);

		char2lcdhyx(lc640_read(lc640_adr+16),0,3);
		char2lcdhyx(lc640_read(lc640_adr+17),0,6);
		char2lcdhyx(lc640_read(lc640_adr+18),0,9);
		char2lcdhyx(lc640_read(lc640_adr+19),0,12);
		char2lcdhyx(lc640_read(lc640_adr+20),0,15);
		char2lcdhyx(lc640_read(lc640_adr+21),0,18);

		char2lcdhyx(lc640_read(lc640_adr+22),1,3);
		char2lcdhyx(lc640_read(lc640_adr+23),1,6);
		char2lcdhyx(lc640_read(lc640_adr+24),1,9);
		char2lcdhyx(lc640_read(lc640_adr+25),1,12);
		char2lcdhyx(lc640_read(lc640_adr+26),1,15);
		char2lcdhyx(lc640_read(lc640_adr+27),1,18);

		char2lcdhyx(lc640_read(lc640_adr+28),2,3);
		char2lcdhyx(lc640_read(lc640_adr+29),2,6);
		char2lcdhyx(lc640_read(lc640_adr+30),2,9);
		char2lcdhyx(lc640_read(lc640_adr+31),2,12);
/*		char2lcdhyx(lc640_read(EVENT_LOG+16),2,15);
		char2lcdhyx(lc640_read(EVENT_LOG+17),2,18);

		char2lcdhyx(lc640_read(EVENT_LOG+18),3,3);
		char2lcdhyx(lc640_read(EVENT_LOG+19),3,6);
		char2lcdhyx(lc640_read(EVENT_LOG+20),3,9);
		char2lcdhyx(lc640_read(EVENT_LOG+21),3,12);
		char2lcdhyx(lc640_read(EVENT_LOG+22),3,15);
		char2lcdhyx(lc640_read(EVENT_LOG+23),3,18);	*/
		int2lcdyx(event_ptr,3,10,0);
		int2lcdyx(lc640_adr,3,18,0);
		}
		     
	else if(sub_ind==0) 
     	{
     	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");


		int2lcdyx(bat_ver_cnt,0,3,0);
		int2lcdyx(cntrl_stat,1,3,0);
   		
		
		int2lcdyx(u_necc_up,0,7,0);
		int2lcdyx(u_necc,1,7,0);
		int2lcdyx(u_necc_dn,2,7,0);
		int2lcdyx(Ubat,3,7,0);

		int2lcdyx(sign_U,0,10,0);
		int2lcdyx(sign_I,1,10,0);
		int2lcdyx(superviser_cnt,2,10,0);	


		int2lcdyx(zar_percent,0,19,0);
		int2lcdyx(BAT_C_REAL,1,19,0);
		int2lcdyx(BAT_C_NOM,2,19,0);
		//int2lcdyx(lc640_read_int(EE_ZAR_CNT),3,19,0);

		  //bat_ver_cnt



	/*	int2lcdyx(tlv_buff[1][1],0,9,0);
		int2lcdyx(tlv_buff[1][2],0,14,0);
		int2lcdyx(tlv_buff[1][3],0,19,0);

   		int2lcdyx(tlv_buff[1][4],1,4,0);
		int2lcdyx(tlv_buff[1][5],1,9,0);
		int2lcdyx(tlv_buff[1][6],1,14,0);
		int2lcdyx(tlv_buff[1][7],1,19,0);

   		int2lcdyx(tlv_buff[1][8],2,4,0);
		int2lcdyx(tlv_buff[1][9],2,9,0);
		int2lcdyx(tlv_buff[1][10],2,14,0);
		int2lcdyx(tlv_buff[1][11],2,19,0);

   		int2lcdyx(tlv_buff[1][12],3,4,0);
		int2lcdyx(tlv_buff[1][13],3,9,0);
		int2lcdyx(tlv_buff[1][14],3,14,0);
		int2lcdyx(tlv_buff[1][15],3,19,0);	*/
     	} 

	else if(sub_ind==4) 
     	{

     	bgnd_par(	" ��� - �������      ",
     			"      >             "
     			,sm_,sm_);

	int2lcdyx(rotor_can[0],1,7,0);
	int2lcdyx(rotor_can[1],2,7,0);
	int2lcdyx(rotor_can[2],3,7,0);
	int2lcdyx(rotor_can[3],1,17,0);
	int2lcdyx(rotor_can[4],2,17,0);
	int2lcdyx(rotor_can[5],3,17,0);


  /*   	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "                    ");

   		int2lcdyx(tlv[0],0,4,0);
		int2lcdyx(tlv[1],0,9,0);
		int2lcdyx(tlv_buff_[0],0,14,0);
		int2lcdyx(tlv_buff_[1],0,19,0); */

      	}
    

     else if(sub_ind==1)
     	{
     	bgnd_par("Un    ( �1   !�2   @",
     	         "U�    < U1   #U2   $",
     	         "I�    > I1   %I2   ^",
     	         "St      St1   St2   ");
 //    	lcd_buffer[4]='a';            
 //    	int2lcd_mmm(Ibat,'a',1);   int2lcdyx(cntrl_stat,0,9,0);          int2lcdyx(hour_apv_cnt,0,13,0);                             char2lcdhyx(St_[0],0,19);  
 //    	int2lcdyx(Ubat,1,4,0);     int2lcdyx(main_apv_cnt,1,9,0);        int2lcdyx(lc640_read_int(SRC1_AVAR_PTR),1,13,0);            char2lcdhyx(St_[1],1,19);
 //    	int2lcdyx(Us[0],2,4,0);  int2lcdyx(apv_cnt_1,2,9,0);           int2lcdyx(lc640_read_int(SRC1_AVAR_CNT),2,13,0);                                     int2lcdhyx(av_stat,2,19);
 //    	int2lcdyx(Us[1],3,4,0);  int2lcdyx(reset_apv_cnt,3,9,0);                                            int2lcdyx(plazma,3,19,0);
     	int2lcd(u_necc,'(',1);
     	int2lcd(cntrl_stat1,'!',0);
     	int2lcd(cntrl_stat2,'@',0);
     	int2lcd(Us[0],'#',1);
     	int2lcd(Us[1],'$',1);
     	int2lcd(Is[0],'%',1);
     	int2lcd(Is[1],'^',1);
     	int2lcd(Ubat,'<',1);
     	int2lcd_mmm(Ibat,'>',2);
     	char2lcdhyx(St_[0],3,13);
     	char2lcdhyx(St_[1],3,19);
     	char2lcdhyx(St,3,5);
     	}
 
     else if(sub_ind==2)
     	{

     	
     	/*int2lcd_mmm((signed)(zar_cnt/10),'<',0);
     	int2lcd_mmm((signed)(zar_cnt_ke/10),'>',0);
     	int2lcdyx(lc640_read_int(EE_ZAR_CNT),0,16,0); 
     	int2lcdyx(lc640_read_int(EE_ZAR_CNT_KE),1,16,0);*/
		   
     	/*
     	int2lcdyx(ND[0],0,7,0);
     	int2lcdyx(cnt_av_t[0],1,7,0);
     	int2lcdyx(adc_buff_[6],0,15,0);
     	
     	int2lcdyx(t_i[1],2,3,0);
     	int2lcdyx(ND[1],2,7,0);
     	int2lcdyx(cnt_av_t[1],3,7,0);
     	int2lcdyx(adc_buff_[4],1,15,0);*/
     	
     	
     	//int2lcdyx(plazma_uart1,0,2,0);
     	/*int2lcdyx(rx_wr_index1,1,2,0);
     	int2lcdyx(rx_rd_index1,2,2,0);
     	int2lcdyx(rx_counter1,3,2,0);
//     	char2lcdbyx(U1LCR,0,19);
 //    	char2lcdbyx(U1IER,1,19);
 //    	char2lcdbyx(U1IIR,2,19);
 //    	char2lcdbyx(U1LSR,3,19);
     	int2lcdyx(adc_buff_out_[0],0,19,0);
     	int2lcdyx(adc_buff_out_[1],1,19,0);
     	int2lcdyx(adc_buff_out_[2],2,19,0);
     	int2lcdyx(in_stat_out[0],0,14,0);
     	int2lcdyx(in_stat_out[1],1,14,0);*/
     	//int2lcdyx(can_cnt,1,15,0);
     	//int2lcdyx(can_tx_cnt,2,15,0);
     	//long2lcdyx(C1ICR,0,8);
     	//int2lcdyx(bOUT_FREE,1,2,0);
     	/*int2lcdyx(ptr_can1_tx_wr,2,2,0);
     	int2lcdyx(ptr_can1_tx_rd,3,2,0);
     	long2lcdyx(can1_data[0],0,19);
     	long2lcdyx(can1_datb[0],0,11);
     	long2lcdyx(can1_data[1],1,19);
     	long2lcdyx(can1_datb[1],1,11);
     	long2lcdyx(can1_data[2],2,19);
     	long2lcdyx(can1_datb[2],2,11);
     	long2lcdyx(can1_data[3],3,19);
     	long2lcdyx(can1_datb[3],3,11);
     	char2lcdhyx(bd[0],0,3);*/
     	}

	else if(sub_ind==2)
     	{
     	bgnd_par("pl    ( �1   !�2   @",
     	         "U�    < U1   #U2   $",
     	         "I�    > I1   %I2   ^",
     	         "St      St1   St2   ");
 //    	lcd_buffer[4]='a';            
 //    	int2lcd_mmm(Ibat,'a',1);   int2lcdyx(cntrl_stat,0,9,0);          int2lcdyx(hour_apv_cnt,0,13,0);                             char2lcdhyx(St_[0],0,19);  
 //    	int2lcdyx(Ubat,1,4,0);     int2lcdyx(main_apv_cnt,1,9,0);        int2lcdyx(lc640_read_int(SRC1_AVAR_PTR),1,13,0);            char2lcdhyx(St_[1],1,19);
 //    	int2lcdyx(Us[0],2,4,0);  int2lcdyx(apv_cnt_1,2,9,0);           int2lcdyx(lc640_read_int(SRC1_AVAR_CNT),2,13,0);                                     int2lcdhyx(av_stat,2,19);
 //    	int2lcdyx(Us[1],3,4,0);  int2lcdyx(reset_apv_cnt,3,9,0);                                            int2lcdyx(plazma,3,19,0);
     	//int2lcd(plazma,'(',0);
     	int2lcd(cntrl_stat1,'!',0);
     	int2lcd(cntrl_stat2,'@',0);
     	int2lcd(Us[0],'#',1);
     	int2lcd(Us[1],'$',1);
     	int2lcd(Is[0],'%',1);
     	int2lcd(Is[1],'^',1);
     	int2lcd(Ubat,'<',1);
     	int2lcd_mmm(Ibat,'>',2);
     	char2lcdhyx(St_[0],3,13);
     	char2lcdhyx(St_[1],3,19);
     	char2lcdhyx(St,3,5);
		}
     	
     else if(sub_ind==3)
     	{
     	bgnd_par(sm_,sm_,sm_,sm_);
 		//long2lcdyx(0x1fffffffUL,0,19);
 		//long2lcdyx(cnt_vz_sec,1,19);
 		//long2lcdyx(cnt_vz_sec_,2,19);
 		int2lcdyx(adc_buff_[5],0,19,0);
 		
 		char2lcdhyx(wrk,0,3);
 		int2lcdyx(cnt_wrk,1,3,0);
 		int2lcdyx(ibat_integr,2,8,0);
 		//long2lcdyx(ibat_integr_,3,8);
 		
// 		int2lcdyx(lc640_read_int(WRK_PTR),0,6,0);
//		int2lcdyx(lc640_read_int(WRK_CNT),0,9,0);
		int2lcdyx(but,3,18,0);
 		}
 
 	
     	
    else if(sub_ind==5)
     	{
     	bgnd_par("                    ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     	int2lcdyx(tout_max_cnt[0],0,1,0);	
     	int2lcdyx(tout_min_cnt[0],1,1,0); 
     	int2lcdyx(tout_stat[0],2,1,0);   
     	
     	int2lcdyx(TMAX_EXT[0],0,5,0);	
     	int2lcdyx(tout[0],1,5,0); 
     	int2lcdyx(TMIN_EXT[0],2,5,0);        	
     		
/*     		char tout_max_cnt[3],tout_min_cnt[3];
enum {tNORM,tMAX,tMIN}tout_stat[3];
char in_stat_out_old[4];
enum {skON,skOFF}sk_stat[3];*/
     		    
     /*	int2lcdyx(spc_stat,0,1,0);
     	int2lcdyx(lc640_read_int(EE_BAT_C_NOM),1,4,0);	
     	int2lcdyx(lc640_read_int(EE_BAT_C_REAL),2,4,0);
     	long2lcdyx(zar_cnt_ke,0,19); 
     	long2lcdyx(zar_cnt,1,19);
      	int2lcdyx(lc640_read_int(EE_ZAR_CNT_KE),0,10,0);	
     	int2lcdyx(lc640_read_int(EE_ZAR_CNT),1,10,0);
     	int2lcdyx(zar_percent,3,3,0);    
  		int2lcdyx(lc640_read_int(KE_PTR),3,6,0);
		int2lcdyx(lc640_read_int(KE_CNT),3,9,0);*/
     	}  
	else if(sub_ind==6)
     	{
     	ptrs[0]="    ?        $ # @ !";
     	ptrs[1]="               J   j";
     	ptrs[2]="               Y   y";
     	ptrs[3]="   h   m     Q q Z z";
     	ptrs[4]="   s   S       C   D";
     	ptrs[5]="   f   F       c   d";
     	ptrs[6]="             A a B b";
     	
     	
     	bgnd_par(ptrs[index_set],
     	         ptrs[index_set+1],
     	         ptrs[index_set+2],
     	         ptrs[index_set+3]);
     	
     	int2lcd_mmm(Ibat,'?',2); 
     	int2lcd(OFFBP1,'$',0);
     	char2lcdh(St_[0],'#');
     	int2lcd(OFFBP2,'@',0);
     	char2lcdh(St_[1],'!');
     	int2lcd(Us[0],'J',0);
     	int2lcd(Us[1],'j',0);
      	int2lcd(cnt_src[0],'Y',0);
     	int2lcd(cnt_src[1],'y',0); 
     	int2lcd(hour_apv_cnt[0],'h',0);
     	int2lcd(main_apv_cnt,'m',0); 
//     	int2lcd(lc640_read_int(SRC1_AVAR_PTR),'s',0); 
//     	int2lcd(lc640_read_int(SRC1_AVAR_CNT),'S',0);
//     	int2lcd(lc640_read((lc640_read_int(SRC1_AVAR_PTR)*4)+SRC1_AVAR_DAT),'e',0); 	
//     	int2lcd(lc640_read_int(SRC2_AVAR_PTR),'f',0); 
 //    	int2lcd(lc640_read_int(SRC2_AVAR_CNT),'F',0);     	
     	int2lcd(apv_cnt[0],'Q',0);
     	int2lcd(apv_cnt_sec[0],'q',0);
		int2lcd(apv_cnt[1],'Z',0);
     	int2lcd(apv_cnt_sec[1],'z',0);
     	int2lcd(cnt_av_umax[0],'A',0);
     	int2lcd(cnt_av_umin[0],'a',0);   
     	int2lcd(cnt_av_umax[1],'B',0);
     	int2lcd(cnt_av_umin[1],'b',0); 
     	int2lcd(hour_apv_cnt[0],'C',0); 
     	int2lcd(hour_apv_cnt[1],'D',0);
     	int2lcd(reset_apv_cnt[0],'c',0); 
     	int2lcd(reset_apv_cnt[1],'d',0);     	    	  	
 //    	lcd_buffer[4]='a';            
 //    	  int2lcdyx(cntrl_stat,0,9,0);          int2lcdyx(hour_apv_cnt,0,13,0);                             char2lcdhyx(St_[0],0,19);  
 //    	int2lcdyx(Ubat,1,4,0);     int2lcdyx(main_apv_cnt,1,9,0);                    char2lcdhyx(St_[1],1,19);
 //    	int2lcdyx(Us[0],2,4,0);  int2lcdyx(apv_cnt_1,2,9,0);                                                int2lcdhyx(av_stat,2,19);
 //    	int2lcdyx(Us[1],3,4,0);  int2lcdyx(reset_apv_cnt,3,9,0);                                            int2lcdyx(plazma,3,19,0);
 /*    	int2lcd(plazma,'(',0);
     	int2lcd(cntrl_stat1,'!',0);
     	int2lcd(cntrl_stat2,'@',0);
     	int2lcd(Us[0],'#',1);
     	int2lcd(Us[1],'$',1);
     	int2lcd(Is[0],'%',1);
     	int2lcd(Is[1],'^',1);
     	int2lcd(Ubat,'<',1);
     	int2lcd_mmm(Ibat,'>',2);
     	char2lcdhyx(St_[0],3,13);
     	char2lcdhyx(St_[1],3,19);
     	char2lcdhyx(St,3,5);*/
		}     	       	
		
	else if(sub_ind==7)
     	{
     	bgnd_par(sm_,sm_,sm_,sm_);
     	//long2lcdyx(C1IER,0,10);
  		//long2lcdyx(C1GSR,1,10);
  		int2lcdyx(LPC_RTC->MONTH,0,6,0);
  		int2lcdyx(AVZ,1,6,0);
  		int2lcdyx(lc640_read_int(EE_MONTH_AVZ),2,6,0);
  		int2lcdyx(LPC_RTC->YEAR,0,16,0);
  		
  		int2lcdyx(lc640_read_int(EE_YEAR_AVZ),2,16,0);
  		//long2lcdyx(C1RFS,0,19);
  		//long2lcdyx(C1RID,1,19);
  		//long2lcdyx(C1RDA,2,19);
  		//long2lcdyx(C1RDB,3,19);
  		//long2lcdyx(plazma_can_long,3,10);
		} 
		
	//int2lcdyx(sub_ind,3,1,0);	    	       			
     }

/*
const char sm7[]	={" �������� N2        "}; //
const char sm8[]	={" ��������           "}; //
const char sm9[]	={" ����               "}; //
const char sm10[]	={" �����������        "}; // 
const char sm11[]	={" ������ ������      "}; //
const char sm12[]	={" ���������� ������  "}; //
const char sm14[]	={" �������            "}; //
*/
else if(ind==iMn)
	{
	ptrs[0]="  ����������������  ";
	if((Us[0]>200)&&(Us[1]>200))ptrs[0]=" � ������ ���1,���2 ";
	else if(Us[0]>200)ptrs[0]="    � ������ ���1   ";
	else if(Us[1]>200)ptrs[0]="    � ������ ���2   ";
	else if(Ubat>200)ptrs[0]="  ������ �� ������� ";
	ptrs[1]=		" U�=   l� I�=    @� ";
     ptrs[2]=		" U�=   #� I�=    $� ";
     ptrs[3]=		" 0%:0^:0& 0</>  /0{ ";
     ptrs[4]=		" �������            ";
     ptrs[5]=		" ���1               "; 
	ptrs[6]=		" ���2               ";
     ptrs[7]=		" ��������           ";
     ptrs[8]=		" ����               ";
	/*ptrs[9]=		" LAN                ";
     ptrs[10]=		" �����������        ";
     ptrs[11]=		" ������ �������     ";
	ptrs[12]=		" ���������� ������  ";
     ptrs[13]=		" �������            ";
     ptrs[14]=		" ���������          ";
     ptrs[15]=		" ����� ������       ";
     ptrs[16]=		sm_exit;*/
 
     ptrs[9]=		" �����������        ";
     ptrs[10]=		" ������ �������     ";
	ptrs[11]=		" ���������� ������  ";
     ptrs[12]=		" ������ ��          ";
     ptrs[13]=		" ���������          ";
     ptrs[14]=		" ����� ������       ";
     ptrs[15]=		sm_exit;
     
    
     if(sub_ind==0)index_set=0;
	else if((index_set-sub_ind)>2)index_set=sub_ind+2;
	else if(sub_ind>index_set)index_set=sub_ind;
	if(sub_cnt<5)bgnd_par(ptrs[0],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);
	else bgnd_par(sub_ptrs[sub_cnt-5],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);

	if((index_set)&&(sub_ind))
	     {
	     if(index_set==sub_ind)lcd_buffer[60]=1;
	     else if((index_set-sub_ind)==1)lcd_buffer[40]=1;
	     else if((index_set-sub_ind)==2)lcd_buffer[20]=1;
	     }	
	
 	int2lcd(Ubat,'l',1);
 	int2lcd_mmm(Ibat,'@',2);
 	int2lcd(Uload,'#',1);
 	int2lcd(iload,'$',1); 	
 	
 	int2lcd(LPC_RTC->SEC,'&',0);
 	int2lcd(LPC_RTC->MIN,'^',0);
 	int2lcd(LPC_RTC->HOUR,'%',0);
 	
 	int2lcd(LPC_RTC->DOM,'<',0);
 	sub_bgnd(sm_mont[LPC_RTC->MONTH],'>',0);
 	int2lcd(LPC_RTC->YEAR,'{',0);
 	if(bFL2)
 	     {
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     }
 	//int2lcdyx(sub_ind,0,19,0);
 	//int2lcdyx(index_set,0,15,0);
//    	int2lcd(a,'^',0);
  //   int2lcd(55,'#',0);
  //   int2lcd(897,'@',0);
     //int2lcdyx(plazma,0,19,0);
     //int2lcdyx((int)(CTIME0&0x0000003fUL),0,19,0);
     /*int2lcdyx(adc_ch,0,19,0);*/
     /*int2lcdyx(tlv[0],0,19,0);
     int2lcdyx(tlv_buff_[0],1,19,0);
     int2lcdyx(tlv[1],2,19,0);
     int2lcdyx(tlv_buff_[1],3,19,0);*/
    /* int2lcdyx(adc_cnt1,2,19,0);*/
    /* int2lcdyx(unet_buff_,1,14,0);
     
     int2lcdyx(adc_buff_[1],1,3,0);
     int2lcdyx(adc_buff_[2],2,3,0);
     int2lcdyx(adc_buff_[3],3,3,0);
     
     int2lcdyx(adc_buff_[5],1,8,0);
     int2lcdyx(adc_buff_[6],2,8,0);
     int2lcdyx(adc_buff_[7],3,8,0);*/
     //int2lcdyx(PWM1,0,6,0);
     //int2lcd_m(-200,'#',2);
     
        //  int2lcdyx(phase2,1,14,0);
     /*long2lcdyx(S1SPSR,0,7); 

     long2lcdyx(temp_short[3],3,7); 
     long2lcdyx(temp_short[4],0,16); 
     long2lcdyx(temp_short[5],1,16);
     long2lcdyx(temp_short[6],2,16);
     long2lcdyx(temp_short[7],3,16);*/ 
     
     //long2lcdyx(IO0DIR,0,7);
     //int2lcdyx(adc_ch,0,5,0);   
	//int2lcdyx(tlv_buff_[1],0,19,0); 
	//int2lcdyx((char)(but),0,5,0);

     //int2lcdyx(RTC_SEC,0,19,0);
   /*   long2lcdyx(lc640_read_long(28),2,8);
     int2lcdyx((CTIME0_bit.SEC),3,19,0); 
     char2lcdbyx(0xbe,0,19);*/ 
     
     //char2lcdbyx(I2STAT,0,7); 
     //char2lcdbyx(plazma_char[1],1,7);
     //char2lcdbyx(plazma_char[2],2,7);
     //char2lcdbyx(plazma_char[3],3,7);
     //char2lcdbyx(plazma_char[4],0,16);
     //char2lcdbyx(plazma_char[5],1,16);
     //char2lcdbyx(plazma_char[6],2,16);
     //long2lcdyx(T0EMR,2,16);
     //long2lcdyx(T0TC,3,16);
     //int2lcdyx(U0DLL,0,19,0);
     //int2lcdyx(U0DLM,1,19,0);
/*int2lcdyx(sub_ind,0,0,0);
int2lcdyx(index_set,0,1,0);*/  
  
//     char2lcdhyx(pdh_state,1,2);  
//     char2lcdhyx(sdh_state,2,2);
//int2lcdyx(sub_cnt,0,3,0);
//int2lcdyx(in_stat_out[1],0,6,0);
	int2lcd(cnt_vz_sec/SEC_IN_HOUR,'z',0);
	int2lcd((cnt_vz_sec/60)%60,'Z',0);
	
	//int2lcdyx(tlv_buff_[0],0,4,0);
	//int2lcdyx(tlv_buff_[1],1,4,0);
	//int2lcdyx(hour_apv_cnt[0],0,4,0);
     
     //char2lcdhyx(rotor_rotor_rotor[0],0,2); 
     //char2lcdhyx(rotor_rotor_rotor[1],1,2); 
     
     //char2lcdhyx(uart1_mess[0],0,2); 
     //char2lcdhyx(uart1_mess[1],0,6); 
     
    
     //int2lcdyx(lc640_read_int(PTR_EVENT_LOG),0,3,0);
     //int2lcdyx(lc640_read_int(CNT_EVENT_LOG),0,7,0);
     //int2lcdyx(cnt_vz_sec_,0,11,0);
	//int2lcdyx(spc_stat,0,15,0);
    /* */
    /* int2lcdyx(plazma,0,2,0);
     int2lcdyx(usart1_router_stat,0,6,0);
     int2lcdyx(usart1_router_cnt,0,10,0);
     int2lcdyx(usart1_router_wrk,0,14,0);*/
     //int2lcdyx(plazma,0,3,0);
    /* int2lcdyx(adc_buff_out_[0],1,3,0);*/
    /* int2lcdyx(suzz[0],0,2,0);
     int2lcdyx(suzz[1],0,6,0);
  	int2lcdyx(suzz[2],0,10,0);
     int2lcdyx(suzz[3],0,14,0); */
    // int2lcdyx(suzz[4],0,18,0);   
     //int2lcdyx(lc640_read_int(RESET_CNT),0,14,0);

/*	int2lcdyx(bat_ver_cnt,0,8,0);
	int2lcdyx(kb_cnt[0],0,14,0);
	*/





	//int2lcdyx(GET_REG(FIO1PIN,27,1),0,19,0);
     //int2lcdyx(snmp_plazma,0,2,0);
     //int2lcdyx(MY_IP[1],0,6,0);
	//int2lcdyx(MY_IP[2],0,10,0);
	//int2lcdyx(MY_IP[3],0,14,0);

//	int2lcdyx(plazma,1,2,0);
		//int2lcdyx(udp_callback_cnt,0,2,0);
		//int2lcdyx(time_sinc_hndl_main_cnt,0,9,0);
		//int2lcdyx(time_sinc_hndl_req_cnt,0,19,0);

		//int2lcdyx(adc_buff_[4],0,6,0);
    	} 
     

else if (ind==iBat)
	{
	if(!NUMBAT)
		{
		bgnd_par(" ������� �� ������� ",
		         " ���  ������������� ",
		         "     ������� �     ",
		         "� ���������� �������");
		} 	
	else if(St&0x02)
		{
		if(bFL2)bgnd_par("       ������!!       ",
		                 "       �������        ",
		                 "    �� ����������     ",sm_);
		else bgnd_par(sm_,sm_,sm_,sm_);
		}               
	else
		{
		ptrs[0]="      �������       ";
		if(!bit_minus)
		     {
		     ptrs[1]="    ����������      ";
		     ptrs[3]="   I���=     !�     ";
		     }
		else
		     {
		     ptrs[1]="   �����������      ";
		     ptrs[3]="   I����=    !�     ";
		     }	
		ptrs[2]="   U���=     @�     ";
		
		if(NDB)ptrs[4]="    ��. ����������  ";
		else ptrs[4]="   t��� =   $�C     ";
		ptrs[5]="   �����=    w%     ";
		ptrs[6]="   C���=     Q�*�   ";
		ptrs[7]=sm_exit;
 
		bgnd_par("      �������       ",
		          ptrs[sub_ind+1],ptrs[sub_ind+2],ptrs[sub_ind+3]);
	     
	     
	     int2lcd(Ubat,'@',1);
	     int2lcd_mmm(Ibat,'!',2);
	     int2lcd(t_b,'$',0);
	     int2lcd(zar_percent,'w',0);
	     if(BAT_C_REAL==0x5555)sub_bgnd("------",'Q',-1);
	     else int2lcd(BAT_C_REAL,'Q',1);
	     if(sub_ind==4)lcd_buffer[60]=1;
		}
		
	} 

else if(ind==iSrc)
	{
	char src_off;
	const char* ptr;
	if(sub_ind1==0)src_off=OFFBP1;
	else src_off=OFFBP2;
	
	if((sub_ind1==1)&&(NUMIST==1))
		{
		ptr=    "        ���2        ";
		ptrs[0]="    �����������     ";
		ptrs[1]="  � ��������� ����  ";
		ptrs[2]=sm_;
		}
	else
		{
		if(src_off) ptr=	"    ���! ��������   ";
		else ptr=			"    ���! �������    ";
	
		if(St&0x01)ptrs[0]=" ������ ����        ";
		else if(St_[sub_ind1]&(1<<4))ptrs[0]=" ������ ��������    ";
		else if(St_[sub_ind1]&(1<<3))ptrs[0]=" ������ U���<U���   ";
		else if(St_[sub_ind1]&(1<<2))ptrs[0]=" ������ U���>U����  ";
		else if(!(St_[sub_ind1]&0x3c))ptrs[0]=" ��������� - �����  "; 
		else                          ptrs[0]=" ������������ ����� ";
		ptrs[1]=" U��� =    @�       "; 
		ptrs[2]=" I��� =    #�       ";
		if(ND[sub_ind1])ptrs[3]=" �� ����������      ";
		else ptrs[3]=" t��� =   $�C       ";
	
		ptrs[4]=sm_exit;
		}
		
	if((sub_ind-index_set)>0)index_set=sub_ind;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(ptr,ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);	
	
	int2lcd(sub_ind1+1,'!',0);
	int2lcd(Us[sub_ind1],'@',1);
	int2lcd(Is[sub_ind1],'#',1);
	int2lcd(t_i[sub_ind1],'$',0); 
	if(sub_ind==2)lcd_buffer[60]=1;
	//char2lcdbyx(St_[sub_ind1],0,7);
	}
	
else if(ind==iLoad)
	{
     bgnd_par("      ��������      "
             ," U����=       !�    "
             ," I����=       @A    "
             ," �����              ");	
	lcd_buffer[60]=1;
     int2lcd(Uload,'!',1);
     int2lcd(iload,'@',1);
       
	}
		
else if(ind==iNet)
	{
	if(St&0x01)
	     {
	     if(bFL2)ptrs[0]="   ������ ����!!!  ";
	     else ptrs[0]=sm_;
	     }
	else ptrs[0]="       ����         ";
#if(UKU_VERSION==900)
     bgnd_par(ptrs[0]
             ," U����=       #�    "
             ," F����=       @��   "
             ," �����              ");	
	lcd_buffer[60]=1;
     int2lcd(Unet_,'#',0);
     int2lcd(fnet,'@',1);
#else
     bgnd_par(ptrs[0]
             ," U����=       #�    "
             ," �����              "
             ,"                    ");	
	lcd_buffer[40]=1;
     int2lcd(Unet,'#',0);
#endif          
	}

else if(ind==iSpc)
	{
	ptrs[0]=" �������� �������   ";
	ptrs[1]=" ������������� �����";
	ptrs[2]=" ���.��������. �����";
	ptrs[3]=sm_exit;
	ptrs[4]="                    ";
	
     if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
		
     bgnd_par("    �����������     ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);	
	pointer_set(1);
	
	}

else if(ind==iKe)
	{
	if((spc_stat==spc_KE/*p1)||(spc_stat==spc_KEp2*/))ptrs[0]=" �������            ";
	else ptrs[0]=" ��������           ";
	bgnd_par("  �������� �������  ",
	         ptrs[0],
	         sm_exit,
	         sm_);	
	pointer_set(1);
	} 
else if (ind==iKednd)
	{
	ptrs[0]="  �������� �������  ";
	ptrs[1]="   ����������!!!    ";
	if(sub_ind==0)
		{
		ptrs[0]="    �����������     ";
		ptrs[1]="      �������       ";
		}  
	else if(sub_ind==1)
		{
		ptrs[0]="       ������       ";
		ptrs[1]="        ����        ";
		}	
	else if(sub_ind==2)
		{
		ptrs[0]="      �������       ";
		ptrs[1]="    �����������     ";
		}	
	else if(sub_ind==3)
		{
		ptrs[0]="      �������       ";
		ptrs[1]="     ����������     ";
		}	
						
	bgnd_par("  �������� �������  ",
	         "   ����������!!!    ",
	         ptrs[0],
	         ptrs[1]);	
	}	
else if(ind==iVz)
	{
	if(spc_stat==spc_VZ)ptrs[0]=" �������            ";
	else ptrs[0]=" ��������           ";
	bgnd_par(" ������������� �����",
	         " ������������ -  !�.",
	         ptrs[0],
	         sm_exit);	
	pointer_set(1);
	int2lcd(VZ_HR,'!',0);
	} 

else if(ind==iAvz)
	{
		bgnd_par(" ������������� �����",
		" ������������� �����",
		" ������������� �����",
		" ������������� �����");
	simax=4;
	if(AVZ==AVZ_1) ptrs[0]=" ��� � �����        ";
	else if(AVZ==AVZ_2) ptrs[0]=" ��� � 2 ������     ";
	else if(AVZ==AVZ_3) ptrs[0]=" ��� � 3 ������     "; 
	else if(AVZ==AVZ_6) ptrs[0]=" ��� � �������      "; 
	else if(AVZ==AVZ_12) ptrs[0]=" ��� � ���          ";
	else
		{
		ptrs[0]=" ��������           ";
		simax=1;
		}
	if(simax==4)
		{
		ptrs[1]=" ������������   (�. ";
		ptrs[2]=" ��������� ���������";
	 	ptrs[3]=" 0%:0^:0& 0</>  /0{ ";
	 	ptrs[4]=sm_exit;
	 	}
	else ptrs[1]=sm_exit;
	 
	bgnd_par("   ��������������   ",
						 "������������� ����� ",
						 ptrs[index_set],ptrs[index_set+1]);	
						 
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>1) index_set=sub_ind-1;
	if(sub_ind==2) index_set=2;
	
	pointer_set(2);
	
	int2lcd(HOUR_AVZ,'%',0);
	int2lcd(MIN_AVZ,'^',0);	
	int2lcd(SEC_AVZ,'&',0);
	int2lcd(DATE_AVZ,'<',0);
	
	
	sub_bgnd(sm_mont[MONTH_AVZ],'>',0);
	int2lcd(YEAR_AVZ,'{',0);
    
	int2lcd(AVZ_TIME,'(',0);
 	}
	
else if(ind==iLog)
	{
	av_j_si_max=lc640_read_int(CNT_EVENT_LOG);
	if(av_j_si_max>64)av_j_si_max=0;

	if(av_j_si_max==0)
		{
		bgnd_par("   ������ �������   "," ������ ����        ",sm_exit,sm_);
		//lcd_buffer[33]=1;
		//sub_ind=0;
		index_set=0;
		}       
		
	else if(av_j_si_max==1)
		{
		bgnd_par("   ������ �������   "," (                  ",sm_exit," �������� ������    ");
		//if(sub_ind==0)lcd_buffer[16]=1;
		//else if(sub_ind==1)lcd_buffer[33]=1;
		//else if(sub_ind==2)lcd_buffer[50]=1;		
		index_set=0;
		}

	else if(av_j_si_max==2)
		{
		if(sub_ind<index_set) index_set=sub_ind;
		else if((sub_ind-index_set)>2) index_set=sub_ind-2;		
		if(index_set==0) bgnd_par("   ������ �������   "," (                  "," [                  ",sm_exit);
		else if(index_set==1) bgnd_par("   ������ �������   "," (                  ",sm_exit," �������� ������    ");
		
		//if((sub_ind-index_set)==0) lcd_buffer[16]=1; 
		//else if((sub_ind-index_set)==1) lcd_buffer[33]=1;
		//else if((sub_ind-index_set)==2) lcd_buffer[50]=1;
		}
		
	else if(av_j_si_max>2)
		{
		if(sub_ind<index_set) index_set=sub_ind;
		else if((sub_ind-index_set)>2) index_set=sub_ind-2;  
		if(index_set==(av_j_si_max-1)) bgnd_par("   ������ �������   "," (                  ",sm_exit," �������� ������    ");
		else if(index_set==(av_j_si_max-2)) bgnd_par("   ������ �������   "," (                  "," [                  ",sm_exit);
		else bgnd_par("   ������ �������   "," (                  "," [                  "," {                  ");
		
		//if((sub_ind-index_set)==0) lcd_buffer[16]=1; 
		//else if((sub_ind-index_set)==1) lcd_buffer[33]=1;
		//else if((sub_ind-index_set)==2) lcd_buffer[50]=1;

		}
	pointer_set(1);
     event2ind(index_set,'(');
     event2ind(index_set+1,'[');	
     event2ind(index_set+2,'{');	  
     
	}



else if(ind==iLog_)
	{	
	unsigned short tempUI;
//	unsigned long tempUL;
	char av_head[4],av_data_on[8],av_data_off[8],av_data[4];
	short av_head_int[2];
	
	bgnd_par(sm_,sm_,sm_,sm_);
	tempUI=lc640_read_int(PTR_EVENT_LOG);
	tempUI=ptr_carry(tempUI,64,-1*((signed)sub_ind1));
	tempUI*=32;
	tempUI+=EVENT_LOG;
     
     lc640_read_long_ptr(tempUI,av_head);
     lc640_read_long_ptr(tempUI+4,(char*)av_head_int);
     lc640_read_long_ptr(tempUI+8,av_data_on);
     lc640_read_long_ptr(tempUI+12,&(av_data_on[4])); 
     lc640_read_long_ptr(tempUI+16,av_data_off);
     lc640_read_long_ptr(tempUI+20,&(av_data_off[4]));      
	lc640_read_long_ptr(tempUI+24,av_data);  
	
	if((av_head[0]=='U')&&(av_head[2]=='R'))
		{
		bgnd_par(	"    ������������    ",
				"   ��� ���������    ",
				"        ����        ",
				"  0%(  0^ 0@:0#:0$  ");
				
				  	
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
		av_j_si_max=0;
		
		}

/*	else if((av_head[0]=='P')&&(av_head[2]=='A'))
		{  
		ptrs[0]="   ������ ����!!!   ";
		ptrs[1]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[2]="    �� ���������    ";
			ptrs[3]="     U����=  +�     ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			int2lcd(Unet,'+',0);
			}
		else 
			{
			gran_char(&index_set,0,1);
			ptrs[2]="      ���������     ";
			ptrs[3]="  0[]  0< 0>:0=:0)  ";
			ptrs[4]="     U���=  +�      ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);
			
			int2lcd(av_data[0]+(av_data[1]*256),'+',0);			
			}	
		
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
		av_j_si_max=1;
		} */
	else if((av_head[0]=='P')&&(av_head[2]=='A'))
		{  
		ptrs[0]="������ ����!(�����.)";
		ptrs[1]="  0%f  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[2]="    �� ���������    ";
			ptrs[3]="     U����=  +�     ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			int2lcd(Unet,'+',0);
			}
		else 
			{
			gran_char(&index_set,0,1);
			ptrs[2]="      ���������     ";
			ptrs[3]="  0[]  0< 0>:0=:0F  ";
			ptrs[4]="     U���=  +�      ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],'F',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);
			
			int2lcd(av_data[0]+(av_data[1]*256),'+',0);			
			}	
		
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'f',0);
		
		av_j_si_max=1;
		}
	else if((av_head[0]=='P')&&(av_head[2]=='B'))
		{  
		ptrs[0]="������ ����!(�����.)";
		ptrs[1]="  0%f  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[2]="    �� ���������    ";
			ptrs[3]="     U����=  +�     ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			int2lcd(Unet,'+',0);	 //o_10
			}
		else 
			{
			gran_char(&index_set,0,1);
			ptrs[2]="      ���������     ";
			ptrs[3]="  0[]  0< 0>:0=:0F  ";
			ptrs[4]="     U����=  +�     ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],'F',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);
			
			int2lcd(av_data[0]+(av_data[1]*256),'+',0);			
			}	
		
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'f',0);
		
		av_j_si_max=1;
		}


	else if((av_head[0]=='B')&&(av_head[2]=='C'))
		{  
		ptrs[0]="       ������       ";
		ptrs[1]="      �������       ";
		ptrs[2]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[3]="    �� ���������    ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			}
		else 
			{
			gran_char(&index_set,0,1);
			ptrs[3]="      ���������     ";
			ptrs[4]="  0[]  0< 0>:0=:0)  ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
		av_j_si_max=1;
		}

	else if((av_head[0]=='B')&&(av_head[2]=='Z'))
		{  
		ptrs[0]="   �������������    ";
		ptrs[1]="       �����        ";
		ptrs[2]=" 0%/(  /0^ 0@:0#:0$ ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[3]="    �� ��������     ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			}
		else 
			{
			gran_char(&index_set,0,1);
			ptrs[3]="      ��������      ";
			ptrs[4]=" 0[/]  /0< 0>:0=:0) ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
		av_j_si_max=1;
		}



	else if((av_head[0]=='B')&&(av_head[2]=='W'))
		{  
		ptrs[0]="       ������       ";
		ptrs[1]="       �������      ";
		ptrs[2]=" ������             ";
		ptrs[3]=" 0%/(  /0^ 0@:0#:0$ ";
		ptrs[4]="          U���=  <� ";
		ptrs[5]=" �����              ";
		ptrs[6]=" 0q/w  /0r 0i:0l:0s ";
		ptrs[7]="          U���=  >� ";
		ptrs[8]="    ������    z�*�. ";
		
		bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
		
		int2lcd(av_head[1]+1,'!',0);

		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
				
		int2lcd(av_data_off[4],'i',0);
		int2lcd(av_data_off[5],'l',0);
		int2lcd(av_data_off[6],'s',0);
		int2lcd(av_data_off[2],'q',0);
		int2lcd(av_data_off[0],'r',0); 
		if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
		sub_bgnd(sm_mont[av_data_off[1]],'w',0);
		
		
		int2lcd(av_head_int[0],'z',1);
		int2lcd(av_data_on[3]+(av_data_on[7]*256),'<',1);
		int2lcd(av_head_int[1],'>',1);	
		av_j_si_max=5;				

		
		}

	else if((av_head[0]=='B')&&(av_head[2]=='K'))
		{  
		ptrs[0]="  �������� �������  ";
		ptrs[1]="       �������      ";
		ptrs[2]=" ������             ";
		ptrs[3]=" 0%/(  /0^ 0@:0#:0$ ";
		ptrs[4]="         U���=  <�  ";
		ptrs[5]=" �����              ";
		ptrs[6]=" 0q/w  /0r 0i:0l:0s ";
		ptrs[7]="         U���=  >�  ";
		ptrs[8]=" �������     z�*�.  ";
		
		bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
		
		int2lcd(av_head[1]+1,'!',0);

		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
				
		int2lcd(av_data_off[4],'i',0);
		int2lcd(av_data_off[5],'l',0);
		int2lcd(av_data_off[6],'s',0);
		int2lcd(av_data_off[2],'q',0);
		int2lcd(av_data_off[0],'r',0); 
		if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
		sub_bgnd(sm_mont[av_data_off[1]],'w',0);
		
		
		int2lcd(av_head_int[0],'z',1);
		int2lcd(av_data_on[3]+(av_data_on[7]*256),'<',1);
		int2lcd(av_head_int[1],'>',1);	
		av_j_si_max=5;				

		
		}



	else if(av_head[0]=='S')
		{  
		ptrs[0]="   ������ ��� N+    ";
		
		if(av_head[2]=='L')
			{
			ptrs[1]="     ����������     ";
			}
		else if(av_head[2]=='T')
			{
			ptrs[1]="      ��������      ";
			}		
		else if(av_head[2]=='U')
			{
			ptrs[1]="   �������� U���.   ";
			}		
		else if(av_head[2]=='u')
			{
			ptrs[1]="   �������� U���.   ";
			}								
		
		
		ptrs[2]="  0%(  0^ 0@:0#:0$  ";
		if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[3]="    �� ���������    ";
			bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
			}
		else 
			{
			gran_char(&index_set,0,1);
			ptrs[3]="      ���������     ";
			ptrs[4]="  0[]  0< 0>:0=:0)  ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
		}

	
	}
	
	


else if(ind==iAusw)
	{
	if(AUSW_MAIN==6024)		ptrs[0]="   ����220/60-24A   ";
	else if(AUSW_MAIN==6012)	ptrs[0]="   ����220/60-12A   ";
	else if(AUSW_MAIN==4824)	ptrs[0]="   ����220/48-24A   ";
	else if(AUSW_MAIN==4812)	ptrs[0]="   ����220/48-12A   ";
	else if(AUSW_MAIN==6010)	ptrs[0]="   ����220/60-10A   ";
	else if(AUSW_MAIN==6005)	ptrs[0]="   ����220/60-5A    ";
	else if(AUSW_MAIN==4810)	ptrs[0]="   ����220/48-10A   ";
	else if(AUSW_MAIN==4805)	ptrs[0]="   ����220/48-5A    ";
	else if(AUSW_MAIN==2424)	ptrs[0]="   ����220/24-24A   ";
	else if(AUSW_MAIN==2412)	ptrs[0]="   ����220/24-12A   ";
	else if(AUSW_MAIN==4840)	ptrs[0]="   ����220/48-40A   ";
	else if(AUSW_MAIN==6030)	ptrs[0]="   ����220/60-30A   ";
	else if(AUSW_MAIN==4820)	ptrs[0]="   ����220/48-20A   ";
	else if(AUSW_MAIN==6015)	ptrs[0]="   ����220/60-15A   ";
	else if(AUSW_MAIN==2450)	ptrs[0]="   ����220/24-50A   ";
	else if(AUSW_MAIN==2425)	ptrs[0]="   ����220/24-25A   ";	
	else if(AUSW_MAIN==2424)	ptrs[0]="   ����220/24-24A   ";
	else if(AUSW_MAIN==2412)	ptrs[0]="   ����220/24-12A   ";

	else ptrs[0]="   ��� ����������   ";
	
	ptrs[1]="���� �����. 0!/0@/0#";
	
	ptrs[2]="�����     S/N00000? ";
	
	ptrs[3]="���202.+( S/N00000) ";
	
	ptrs[4]="��        v    [    ";
	
	ptrs[5]="���1 -    S/N00000< ";
	
	ptrs[6]="���2 -    S/N00000> ";
	
	ptrs[7]="RS232      v   $    ";

	ptrs[8]="CAN PDH -  v   %    ";
	
	ptrs[9]="CAN SDH -  v   ^    ";
	
	ptrs[10]="Ethernet-  v   &    ";

	ptrs[11]=" �����              ";		
	
	
	bgnd_par(ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);	
	if(index_set==8)lcd_buffer[60]=1;
	/*long2lcdyx_mmm(AUSW_BPS2_NUMBER,3,9,0);
	long2lcdyx_mmm(lc640_read_long(EE_AUSW_BPS2_NUMBER),3,19,0);*/
	
	if(AUSW_DAY<32)int2lcd(AUSW_DAY,'!',0);
	else sub_bgnd("**",'!',-1);
	if(AUSW_MONTH<13)int2lcd(AUSW_MONTH,'@',0);
	else sub_bgnd("**",'@',-1);
	if(AUSW_YEAR<100)int2lcd(AUSW_YEAR,'#',0);
	else sub_bgnd("**",'#',-1);	

	if(AUSW_MAIN_NUMBER>=1000000)sub_bgnd("******",'?',-5);
	else long2lcd_mmm(AUSW_MAIN_NUMBER,'?',0);

	/*if(AUSW_UKU>=1000) sub_bgnd("***",'+',-2);
	else int2lcd(AUSW_UKU,'+',0);

	if(AUSW_UKU_SUB>=100) sub_bgnd("**",'(',-1);
	else int2lcd(AUSW_UKU_SUB,'(',0);*/
	int2lcd(UKU_VERSION/100,'+',0);
	int2lcd(HARDVARE_VERSION,'(',0);
	
	if(AUSW_UKU_NUMBER>=1000000)sub_bgnd("******",')',-5);
	else long2lcd_mmm(AUSW_UKU_NUMBER,')',0);

	if(AUSW_UKU_NUMBER>=1000000)sub_bgnd("******",')',-5);
	else long2lcd_mmm(AUSW_UKU_NUMBER,')',0);
	
	if(AUSW_BPS1_NUMBER>=1000000)sub_bgnd("******",'<',-5);
	else long2lcd_mmm(AUSW_BPS1_NUMBER,'<',0);	
	
	if(AUSW_BPS2_NUMBER>=1000000)sub_bgnd("******",'>',-5);
	else long2lcd_mmm(AUSW_BPS2_NUMBER,'>',0);	

	#ifdef SOFT 
	int2lcd(SOFT,'[',2);
	#else 
	sub_bgnd("---------",'[',-4);
	#endif

	#ifdef RS232_VERSION 
	int2lcd(RS232_VERSION,'$',2);
	#else 
	sub_bgnd("---------",'$',-4);
	#endif
	
	#ifdef CAN_PDH_VERSION 
	int2lcd(CAN_PDH_VERSION,'%',2);
	#else 
	sub_bgnd("---------",'%',-4);
	#endif	
	//else if((AUSW_RS232<0)||(AUSW_RS232>=1000))sub_bgnd("�� ����������",'$',-5);
	//else 

	//if(AUSW_PDH==0)sub_bgnd("�����������",'%',-5);
//	else if((AUSW_PDH<0)||(AUSW_PDH>=1000))sub_bgnd("�� ����������",'%',-5);
	//else int2lcd(AUSW_PDH,'%',2);

	#ifdef CAN_SDH_VERSION 
	int2lcd(CAN_SDH_VERSION,'^',2);
	#else 
	sub_bgnd("---------",'^',-4);
	#endif	
	
	//if(AUSW_SDH==0)sub_bgnd("�����������",'%',-5);
	//else if((AUSW_SDH<0)||(AUSW_SDH>=1000))sub_bgnd("�� ����������",'%',-5);
	//else int2lcd(AUSW_SDH,'%',2);

	#ifdef ETH_VERSION 
	int2lcd(ETH_VERSION,'&',2);
	#else 
	sub_bgnd("---------",'&',-4);
	#endif	
	
	fl_simv(0,0,0);
	
	}

else if(ind==iAusw_set)
	{
	if(AUSW_MAIN==6024)		ptrs[0]="   ����220/60-24A   ";
	else if(AUSW_MAIN==6012)	ptrs[0]="   ����220/60-12A   ";
	else if(AUSW_MAIN==4824)	ptrs[0]="   ����220/48-24A   ";
	else if(AUSW_MAIN==4812)	ptrs[0]="   ����220/48-12A   ";
	else if(AUSW_MAIN==6010)	ptrs[0]="   ����220/60-10A   ";
	else if(AUSW_MAIN==6005)	ptrs[0]="   ����220/60-5A    ";
	else if(AUSW_MAIN==4810)	ptrs[0]="   ����220/48-10A   ";
	else if(AUSW_MAIN==4805)	ptrs[0]="   ����220/48-5A    ";
	else if(AUSW_MAIN==2424)	ptrs[0]="   ����220/24-24A   ";
	else if(AUSW_MAIN==2412)	ptrs[0]="   ����220/24-12A   ";
	else if(AUSW_MAIN==4840)	ptrs[0]="   ����220/48-40A   ";
	else if(AUSW_MAIN==6030)	ptrs[0]="   ����220/60-30A   ";
	else if(AUSW_MAIN==4820)	ptrs[0]="   ����220/48-20A   ";
	else if(AUSW_MAIN==6015)	ptrs[0]="   ����220/60-15A   ";
	else if(AUSW_MAIN==2450)	ptrs[0]="   ����220/24-50A   ";
	else if(AUSW_MAIN==2425)	ptrs[0]="   ����220/24-25A   ";
		
	else ptrs[0]="   ��� ����������   ";
	
	ptrs[1]="���� �����. 0!/0@/0#";
	
	ptrs[2]="�����     S/N00000? ";
	
	ptrs[3]="���00+.0( S/N00000) ";
	
	ptrs[4]="���1 -    S/N00000< ";
	
	ptrs[5]="���2 -    S/N00000> ";
	
	ptrs[6]=" �����              ";		
	
	
	bgnd_par(ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);	
	
	/*long2lcdyx_mmm(AUSW_BPS2_NUMBER,3,9,0);
	long2lcdyx_mmm(lc640_read_long(EE_AUSW_BPS2_NUMBER),3,19,0);*/

	if(AUSW_DAY<32)int2lcd(AUSW_DAY,'!',0);
	else sub_bgnd("**",'!',-1);
	if(AUSW_MONTH<13)int2lcd(AUSW_MONTH,'@',0);
	else sub_bgnd("**",'@',-1);
	if(AUSW_YEAR<100)int2lcd(AUSW_YEAR,'#',0);
	else sub_bgnd("**",'#',-1);	
	
	if(AUSW_MAIN_NUMBER>=1000000)sub_bgnd("******",'?',-5);
	else long2lcd_mmm(AUSW_MAIN_NUMBER,'?',0);
	
	/*if(AUSW_UKU>=1000) sub_bgnd("***",'+',-2);
	else int2lcd(AUSW_UKU,'+',0);

	if(AUSW_UKU_SUB>=100) sub_bgnd("**",'(',-1);
	else int2lcd(AUSW_UKU_SUB,'(',0);*/
	
	int2lcd(UKU_VERSION,'+',0);
	int2lcd(HARDVARE_VERSION,'(',0);	

	if(AUSW_UKU_NUMBER>=1000000)sub_bgnd("******",')',-5);
	else long2lcd_mmm(AUSW_UKU_NUMBER,')',0);

	if(AUSW_BPS1_NUMBER>=1000000)sub_bgnd("******",'<',-5);
	else long2lcd_mmm(AUSW_BPS1_NUMBER,'<',0);	

	if(AUSW_BPS2_NUMBER>=1000000)sub_bgnd("******",'>',-5);
	else long2lcd_mmm(AUSW_BPS2_NUMBER,'>',0);
	
				
	if((index_set==3)&&(sub_ind==9))lcd_buffer[60]=1;

	
	if((sub_ind==0)&&(!index_set)) fl_simv(0,0,20);	
	else if((sub_ind==1)&&(index_set<2))fl_simv(1-index_set,12,2);
	else if((sub_ind==2)&&(index_set<2))fl_simv(1-index_set,15,2);
	else if((sub_ind==3)&&(index_set<2))fl_simv(1-index_set,18,2);
	
	else if((sub_ind==4)&&(index_set<3)) fl_simv(2-index_set,10,10);	
	else if((sub_ind==5)&&(index_set<4)) fl_simv(3-index_set,3,6);	
	else if((sub_ind==6)&&(index_set<4)) fl_simv(3-index_set,10,10);	

	else if((sub_ind==7)/*&&(index_set<4)*/) fl_simv(4-index_set,10,10);	
	else if((sub_ind==8)/*&&(index_set<4)*/) fl_simv(5-index_set,10,10);	
	else fl_simv(0,0,0);	
	/*
	
	
	ptrs[1]="���� �����. - �����.";
	if((AUSW_YEAR<=99)||(AUSW_MONTH<=12)||(AUSW_DAY<=31))
		{
		

		}	
	
	
	ptrs[2]="����� S/N - �����.  ";
	ptrs[2]="����� S/N - �����.  ";
	if(AUSW_MAIN_NUMBER<60000)
		{
		ptrs[2]="����� S/N - 00000?  ";
		
		}	

	ptrs[3]="���--+.-( S/N �����)";
	if(AUSW_UKU>1000) sub_bgnd("-.--",'(',-3);
	else 
		{
	
		}
	if(AUSW_UKU_SUB>99) sub_bgnd("-",'(',0);
	else 
		{
	
		}		
	if(AUSW_UKU_NUMBER>30000)sub_bgnd("��.",')',-2);
	else
		{
		sub_bgnd("00000)",')',-5);
		//int2lcd((signed short)AUSW_UKU_NUMBER,')',0);
		}

	ptrs[4]="���1 - �� ����������";
	if(AUSW_BPS1<60000)
		{
		ptrs[4]="���1 - S/N0000<     ";
		
		}
		
	ptrs[5]="���2 - �� ����������";	
	if(AUSW_BPS2<60000)
		{
		ptrs[5]="���2 - S/N0000>     ";
		
		}	

	if((AUSW_RS232==0)||(AUSW_RS232>=1000))
		{
		ptrs[6]="RS232   ����������� ";
		}
	else ptrs[6]="RS232 - ������     [";
	
	if((AUSW_PDH==0)||(AUSW_PDH>=1000))
		{
		ptrs[7]="CAN PDH ����������� ";
		}
	else ptrs[7]="CAN PDH - ������   ]";
	
	if((AUSW_SDH==0)||(AUSW_SDH>=1000))
		{
		ptrs[8]="CAN SDH ����������� ";
		}
	else ptrs[8]="CAN SDH - ������   )";		
	
	
	int2lcd((unsigned short)AUSW_MAIN_NUMBER,'?',0);
	if(AUSW_DAY<32)int2lcd(AUSW_DAY,'!',0);
	else sub_bgnd("**",'!',-1);
	if(AUSW_MONTH<13)int2lcd(AUSW_MONTH,'@',0);
	else sub_bgnd("**",'@',-1);
	if(AUSW_YEAR<100)int2lcd(AUSW_YEAR,'#',0);
	else sub_bgnd("**",'#',-1);
	int2lcd((unsigned short)AUSW_BPS1,'<',0);
	int2lcd((unsigned short)AUSW_BPS2,'>',0);
	int2lcd(AUSW_UKU,'+',0);
	int2lcd(AUSW_UKU_SUB,'(',0);
	if(AUSW_UKU_NUMBER==0xffff)
		{
		sub_bgnd(" ",')',0);
		}
	else
		{
		sub_bgnd("     )",')',-5);
		int2lcd((unsigned short)AUSW_UKU_NUMBER,')',0);
		}
	
	//int2lcdyx(AUSW_UKU,0,19,0);
	
	if(ind==iAusw_set)
		{
		if((sub_ind==0)&&(!index_set)) fl_simv(0,0,20);
		
		else if((sub_ind==1)&&(index_set<2))
			{
			if((AUSW_YEAR>99)&&(AUSW_MONTH>12)&&(AUSW_DAY>31)) fl_simv(1-index_set,14,6);
			else fl_simv(1,12,2);
			}
		else if((sub_ind==2)&&(index_set<2))
			{
			if((AUSW_YEAR>99)&&(AUSW_MONTH>12)&&(AUSW_DAY>31)) fl_simv(1-index_set,14,6);
			else fl_simv(1,15,2);
			}	
		else if((sub_ind==3)&&(index_set<2))
			{
			if((AUSW_YEAR>99)&&(AUSW_MONTH>12)&&(AUSW_DAY>31)) fl_simv(1-index_set,14,6);
			else fl_simv(1,18,2);
			}	
		else if((sub_ind==4)&&(index_set<3)) fl_simv(2-index_set,10,10);	
		else if((sub_ind==5)&&(index_set<4)) fl_simv(3-index_set,3,6);	
		else if((sub_ind==6)&&(index_set<4)) fl_simv(3-index_set,14,6);				
		}*/
	}


	
else if(ind==iSet)
	{
	/*
const char sm301[]	={" �����������        "};
const char sm302[]	={" �������� ������. N<"};
const char sm303[]	={" Umax=       !�     "}; 
const char sm304[]	={" U�0=        @�     "};
const char sm305[]	={" U�20=       #�     "};	
const char sm306[]	={" tmax=       $�C    "}; 
const char sm307[]	={" C���=       %�*�   "}; 
const char sm308[]	={" U����=      ^�     "};
const char sm309[]	={" Umin.����=  &�     "}; 
const char sm310[]	={" ��.����.   (       "}; 
const char sm311[]	={" I��.=       )�     "};
const char sm312[]	={" K���.���.=    [    "}; 
const char sm313[]	={" Imax=       ]A     "};
const char sm314[]	={" Kimax=      {      "};
const char sm315[]	={" ��� ����������     "};
const char sm316[]	={" I�.���.=    <�     "};
const char sm317[]	={" U0�=        >�     "};
const char sm318[]	={" T�.���.�.�. !�     "};
const char sm319[]	={" �����              "};
const char sm320[]	={" ���������          "};	*/

	ptrs[0]=	" �����������        ";
	ptrs[1]=	" ����� � ����       ";
	ptrs[2]=	" �������������      ";
	ptrs[3]=	"   ������� � ����   ";
	ptrs[4]=	" ���������          ";
	ptrs[5]=	" ���������         y";
	ptrs[6]=	" �������� ������. N<";
	ptrs[7]=	" ��.����.   (       ";
	ptrs[8]=	" ���������� ������� ";
	ptrs[9]=	"  ������    )       ";
	ptrs[10]=	" ��� ����������     ";
	ptrs[11]=	" T ��������   ����  ";
	ptrs[12]=	" �������     q���.  ";
	ptrs[13]=	" Umax=       !�     ";
	ptrs[14]=	" U�0�=       @�     ";
	ptrs[15]=	" U�20�=      #�     ";
	ptrs[16]=	" U����=      ^�     ";
	ptrs[17]=	" Umin.����=  &�     ";
	ptrs[18]=	" Umax.����=  F�     ";
	ptrs[19]=	" U0�=        >�     ";
	ptrs[20]=	" I��.=       j�     ";
	ptrs[21]=	" I�.���.=    J�     ";
	ptrs[22]=	" Imax=       ]A     ";
	ptrs[23]=	" Imin=       {�     ";
	ptrs[24]=	" K���.���.=    [    ";
	ptrs[25]=	" T�.���.�.�. !�     ";
	ptrs[26]=	" t���.max. =  $�C    ";
	ptrs[27]=	" Ethernet           ";
	ptrs[28]=	" ������� �������    ";
	ptrs[29]=   " �������� N        w";
	ptrs[30]=	sm_exit; 
	ptrs[31]=	" ����������         "; 
	ptrs[32]=	" ����               ";        
	
	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("     ���������      ",
			ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	
	if(index_set<19)
	     {
	     int2lcd(MAIN_IST+1,'<',0);
	     if(ZV_ON)sub_bgnd(smon,'(',0);
	     else sub_bgnd(smoff,'(',0);
	     if(AV_OFF_AVT)sub_bgnd("�����.",')',0);
	     else sub_bgnd("����.",')',0);
	     if(MNEMO_ON==mnON)
	     	{
			if(MNEMO_TIME>=100)sub_bgnd("�����  y�",'y',-8);
	     	else sub_bgnd("����� y�.",'y',-8);
	     	int2lcd(MNEMO_TIME,'y',0);
	     	}
	     else sub_bgnd("����.",'y',-4);
	     int2lcd(UMAX,'!',1);
	     int2lcd(UB0,'@',1);
	     int2lcd(UB20,'#',1);
	     int2lcd(USIGN,'^',1);
	     int2lcd(UMN,'&',0);
	     int2lcd(U0B,'>',1);
	     } 
	int2lcd(TMAX,'$',0);
	int2lcd(IKB,'j',2);
	int2lcd(KVZ,'[',3);
	int2lcd(IMAX,']',1);
	int2lcd(IMIN,'{',1);
	int2lcd(IZMAX,'J',1); 
	int2lcd(TZAS,'!',0);
	int2lcd(TBAT,'q',0);
	int2lcd(UMAXN,'F',0); 
	serial2lcd(AUSW_MAIN_NUMBER,'w',sub_ind1);
	
//int2lcdyx(MAIN_IST,0,3,0);
//int2lcdyx((short)web_param_input,0,6,0);	     
	} 

else if (ind==iDef)
	{
/*	 
#if(UKU_VERSION==300)
#ifdef _24_
	ptrs[0]=" ����220/24-24�     ";
	ptrs[1]=" ����220/24-12�     ";
	ptrs[2]=sm_exit;
#else	
	ptrs[0]=" ����220/60-10�     ";
	ptrs[1]=" ����220/48-10�     ";
	ptrs[2]=" ����220/60-5�      ";
	ptrs[3]=" ����220/48-5�      ";
	ptrs[4]=sm_exit;
#endif
#endif	
	
#if(UKU_VERSION==900) 
#ifdef _24_
	ptrs[0]=" ����220/24-50�     ";
	ptrs[1]=" ����220/24-25�-2���";
	ptrs[2]=" ����220/24-25�-1���";	
	ptrs[3]=sm_exit;
#else		
	ptrs[0]=" ����220/60-24�     ";
	ptrs[1]=" ����220/48-24�     ";
	ptrs[2]=" ����220/60-12�-2���";
	ptrs[3]=" ����220/48-12�-2���";
	ptrs[4]=" ����220/60-12�-1���";
	ptrs[5]=" ����220/48-12�-1���";
	ptrs[6]=" ����220/48-40�     ";
	ptrs[7]=" ����220/60-30�     ";
	ptrs[8]=" ����220/48-20�-1���";
	ptrs[9]=" ����220/68-15�-1���";
	ptrs[10]=sm_exit;
#endif	
#endif*/

	ptrs[0]=	" 60�-40�-2/2-1000.01";
	ptrs[1]=	" 60�-20�-2/2-1000.01";
	ptrs[2]=	" 60�-24�-2/2-950    ";
	ptrs[3]=	" 60�-12�-2/2-950    ";
	ptrs[4]=	" 60�-12�-2/2-360    ";
	ptrs[5]=	" 60�-6�-2/2-360     ";
	ptrs[6]=	" 48�-40�-2/2-1000.01";
	ptrs[7]=	" 48�-20�-2/2-1000.01";
	ptrs[8]=	" 48�-24�-2/2-950    ";
	ptrs[9]=	" 48�-12�-2/2-950    ";
	ptrs[10]=	" 48�-12�-2/2-360    ";
	ptrs[11]=	" 48�-6�-2/2-360     ";
	ptrs[12]=	" 24�-50�-2/2-1000.01";
	ptrs[13]=	" 24�-25�-2/2-1000.01";
	ptrs[14]=	" 24�-24�-2/2-360    ";
	ptrs[15]=	" 24�-12�-2/2-360    ";
	ptrs[16]=sm_exit;

if(bFL5)ptrs[default_temp]=sm_;
	
//#ifdef MOSKOW	ptrs[2]=sm13;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("����������� ���.-�� ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	
  	} 	
	        



else if(ind==iSet_T)
	{
	static char phase_cnt;
	if(++phase_cnt>=15)
	     {
	     phase_cnt=0;
	     if(++phase>=3)phase=0;
	     }
	ptrs[0]=" 0%:0^:0& 0</>  /0{ ";
	ptrs[1]=sm_;
	if(phase==0)ptrs[2]="    � � - �����     ";
     if(phase==1)ptrs[2]="   � � - ���������  ";
     if(phase==2)ptrs[2]="     �  - �����     ";
	
	bgnd_par(" ���������  ������� ",ptrs[0],ptrs[1],ptrs[2]);
     if(sub_ind==0)lcd_buffer[42]='^';
     else if(sub_ind==1)lcd_buffer[45]='^';
     else if(sub_ind==2)lcd_buffer[48]='^';
     else if(sub_ind==3)lcd_buffer[51]='^';
     else if(sub_ind==4)lcd_buffer[54]='^';
     else if(sub_ind==5)lcd_buffer[58]='^';
  
 	int2lcd(LPC_RTC->SEC,'&',0);
 	int2lcd(LPC_RTC->MIN,'^',0);
 	int2lcd(LPC_RTC->HOUR,'%',0);
 	
 	int2lcd(LPC_RTC->DOM,'<',0);
 	sub_bgnd(sm_mont[LPC_RTC->MONTH],'>',0);
 	int2lcd(LPC_RTC->YEAR,'{',0);
 	if(bFL2)
 	     {
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     }  

	//int2lcdyx('�',3,19,0);
	}  

else if(ind==iSet_T_avt)
	{
	if(SNTP_ENABLE==0)		ptrs[0]=	" ���������          ";
	else if(SNTP_ENABLE==1)	ptrs[0]=	" ������        1 ���";
	else if(SNTP_ENABLE==2)	ptrs[0]=	" ������      1 �����";
	else if(SNTP_ENABLE==3)	ptrs[0]=	" ������     1 ������";

	if(SNTP_ENABLE==0)
		{
							ptrs[1]=	sm_exit;
							ptrs[2]=	sm_;
							ptrs[3]=	sm_;
		}
	else 
		{
		if((SNTP_GMT>=0)&&(SNTP_GMT<=9))			ptrs[1]=	" ������� ���� GMT+! ";
		else if((SNTP_GMT>=10)&&(SNTP_GMT<=13))		ptrs[1]=	" ������� ���� GMT+ !";
		else if((SNTP_GMT<0)&&(SNTP_GMT>-10))		ptrs[1]=	" ������� ���� GMT-! ";
		else if((SNTP_GMT<=-10)&&(SNTP_GMT>=-12))	ptrs[1]=	" ������� ���� GMT- !";
		}
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>1) index_set=sub_ind-1;

	if(lc640_read_int(EE_SNTP_WEB_ENABLE)==1)
		{
		ptrs[2]=	" ������������� �����";
		ptrs[3]=	"     ��������       ";
		}
	else
		{
		ptrs[2]=	" ������������� �����";
		ptrs[3]=	" IP 000.000.000.00# ";
		}
	ptrs[4]=	" ����������������   ";
	ptrs[5]=	sm_exit;
	ptrs[6]=	sm_;
	
	bgnd_par(	"    �������������   ",
				"    ������� (SNTP)  ",
				ptrs[index_set],
				ptrs[index_set+1]);
  
 	int2lcd(abs(SNTP_GMT),'!',0);
	if(sub_ind==2)		ip2lcd(lc640_read_int(EE_SNTP_IP1),lc640_read_int(EE_SNTP_IP2),lc640_read_int(EE_SNTP_IP3),lc640_read_int(EE_SNTP_IP4),'#',(sub_ind1+1));
	else 				ip2lcd(lc640_read_int(EE_SNTP_IP1),lc640_read_int(EE_SNTP_IP2),lc640_read_int(EE_SNTP_IP3),lc640_read_int(EE_SNTP_IP4),'#',0);

	pointer_set(2);
	//int2lcdyx(udp_callback_cnt,0,3,0);
	
	} 

else if (ind==iApv)
	{ 
	ptrs[0]=" ��� 1� ������� !   ";
	if(apv_on1!=apvON)
	     {
	     ptrs[1]=" �����              ";
	     ptrs[2]=sm_;
	     ptrs[3]=sm_;
	     ptrs[4]=sm_;
	     simax=1;
	     }
	else
	     {
	     if(apv_on2!=apvON)
	          {
	          ptrs[1]=" ��� 2� ������� @   ";
	          ptrs[2]=" �����              ";
	          ptrs[3]=sm_;
	          ptrs[4]=sm_;
	          simax=2;
	          }
	     else 
	          {
               ptrs[1]=" ��� 2� ������� @   ";
	          ptrs[2]=" ������ ���2     #�.";
	          ptrs[3]=" �����              ";
	          ptrs[4]=sm_;
	          simax=3;	          
	          }     
	     }     
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;	
     bgnd_par("   ��� ����������   ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	if(apv_on1==apvON)sub_bgnd(smon,'!',0);
	else sub_bgnd(smoff,'!',0);
	
	if(apv_on2==apvON)
	     {
	     sub_bgnd(smon,'@',0);
	     int2lcd(apv_on2_time,'#',0);
	     }
	else sub_bgnd(smoff,'@',0);	
     
 //    int2lcdyx(lc640_read_int(EE_APV_ON1),2,19,0);
 //    int2lcdyx(apv_on1,3,19,0);
  	} 


else if (ind==iTst)
	{ 
	ptrs[0]=" ���� ������    (   ";
	ptrs[1]=" ���� ��������������";
	ptrs[2]=" ���1               ";
	ptrs[3]=" ���2               ";
	ptrs[4]=" ���1+���2          ";
	ptrs[5]=" �����              ";
	ptrs[6]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("        ����        ",
     		ptrs[index_set],
     		ptrs[index_set+1],
     		ptrs[index_set+2]);
	
	pointer_set(1);
 
	if(tst_state[0]==tstOFF)sub_bgnd(smoff,'(',0);
	else if(tst_state[0]==tstON)sub_bgnd(smon,'(',0);	

 /*   	if(tst_state[1]==tstOFF)sub_bgnd(smoff,')',0);
	else if(tst_state[1]==tstON)sub_bgnd(smon,')',0);*/
	} 

else if (ind==iTst_klbr)
	{ 
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par(" ���� ��������������",
     	    " ����         <     ",
     	    " I���=           :A ",
     	    sm_exit);
	
	pointer_set(1);
 
    	if(tst_state[1]==tstOFF)sub_bgnd(smoff,'<',0);
	else if(tst_state[1]==tstON)sub_bgnd(smon,'<',0);

     int2lcd_mmm(Ibat,':',2);	
	//int2lcdyx(tst_state[1],0,19,0);			
 	} 

else if (ind==iTst_BPS1)
	{ 
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("     ���� ���1      ",
     	    " U�=@  $     ���=  #",
     	    " U1=    <� I1=    >�",
     	    sm_exit);
	
	pointer_set(1);
 
     if(tst_state[2]==tstOFF)
     	{
     	sub_bgnd("Umin",'@',0);   
     	MSG_IND2PWM_SRC1=30;
     	}
	else if(tst_state[2]==tstON)
		{
		sub_bgnd("Umax",'@',0);
		MSG_IND2PWM_SRC1=970;
		}
	else if(tst_state[2]==tstU)
		{
		sub_bgnd("U20",'@',0);
		MSG_IND2PWM_SRC1=0x5555;
		}
     sub_bgnd("(   $)",'$',0);
     
     int2lcd(Us[0],'<',1);
     int2lcd(Is[0],'>',1);	
     int2lcd(cntrl_stat1,'#',0);		
     int2lcd(u_necc,'$',1);
	
	//int2lcdyx(adc_buff_[2],0,19,0);
	//int2lcdyx(adc_buff[2][0],0,10,0);
			
 	} 



else if (ind==iTst_BPS2)
	{ 
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("     ���� ���2      ",
     	    " U�=@  $     ���=  #",
     	    " U2=    [� I2=    ]�",
     	    sm_exit);
	
	pointer_set(1);
 
     if(tst_state[3]==tstOFF)
     	{
     	sub_bgnd("Umin",'@',0);   
     	MSG_IND2PWM_SRC2=30;
     	}
	else if(tst_state[3]==tstON)
		{
		sub_bgnd("Umax",'@',0);
		MSG_IND2PWM_SRC2=970;
		}
	else if(tst_state[3]==tstU)
		{
		sub_bgnd("U20",'@',0);
		MSG_IND2PWM_SRC2=0x5555;
		}
	sub_bgnd("(   $)",'$',0);
	
     int2lcd(Us[1],'[',1);
     int2lcd(Is[1],']',1);
     int2lcd(cntrl_stat2,'#',0);	
     int2lcd(u_necc,'$',1);
	//int2lcdyx(adc_buff_[0],0,19,0);
	//int2lcdyx(adc_buff[0][0],0,10,0);			
 	}

/*
const char sm360[]	={"        ����        "};
const char sm361[]	={" ���� ������    (   "};
const char sm362[]	={" ���� ��������������"};
const char sm363[]	={" ���1               "};
const char sm364[]	={" ���2               "};
const char sm365[]	={" ���1+���2          "};
const char sm367[]	={" ���� ��������������"};
const char sm368[]	={" ����         <     "};
const char sm369[]	={" I���=           :A "};
const char sm370[]	={"     ���� ���1      "};
const char sm371[]	={" U�=@  $     ���=  #"};
const char sm372[]	={" U1=    <� I1=    >�"};
const char sm373[]	={"     ���� ���2      "};
const char sm374[]	={" U�=@  $     ���=  #"};
const char sm375[]	={" U2=    [� I2=    ]�"};
const char sm376[]	={"   ���� ���1+���2   "};
const char sm377[]	={" U�=@  $       #   !"};
const char smumax[]	={"Umax"}; 
const char smumin[]	={"Umin"};
const char smu20[]	={"U20"}; 
const char smu20_[]	={"(   $)"};	
*/
else if (ind==iTst_BPS12)
	{ 
	ptrs[0]=" U�=@  $       #   !";
	ptrs[1]=" U1=    <� I1=    >�";
	ptrs[2]=" U2=    [� I2=    ]�";
	ptrs[3]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("   ���� ���1+���2   ",
     	    ptrs[index_set],
     	    ptrs[index_set+1],
     	    ptrs[index_set+2]);
	
	pointer_set(1);
 

     if(tst_state[4]==tstOFF)
     	{
     	sub_bgnd("Umin",'@',0);   
     	MSG_IND2PWM_SRC1=30;
     	MSG_IND2PWM_SRC2=30;
     	}
	else if(tst_state[4]==tstON)
		{
		sub_bgnd("Umax",'@',0);
     	MSG_IND2PWM_SRC1=970;
     	MSG_IND2PWM_SRC2=970;
     	}		
	else if(tst_state[4]==tstU)
		{
		sub_bgnd("U20",'@',0);
		MSG_IND2PWM_SRC1=0x5555;
		MSG_IND2PWM_SRC2=0x5555;
		} 
	sub_bgnd("(   $)",'$',0);
	
     int2lcd(Us[0],'<',1);
     int2lcd(Is[0],'>',1);	
     int2lcd(cntrl_stat1,'#',0);
     int2lcd(Us[1],'[',1);
     int2lcd(Is[1],']',1);
     int2lcd(cntrl_stat2,'!',0);
     int2lcd(u_necc,'$',1);
 	}  	
 	
else if(ind==iStr)
	{
	ptrs[0]=" �������           @";
	ptrs[1]=" ����������        !";
	ptrs[2]=" �������� ������.  #";
	ptrs[3]=" ����� ���������   $";
	ptrs[4]=" ��� ���           %";
	ptrs[5]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
	bgnd_par("      ���������     ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
		
	int2lcd(NUMIST,'!',0); 
	int2lcd(NUMBAT,'@',0);
	int2lcd(NUMDT,'#',0);
	int2lcd(NUMSK,'$',0);
	if(KINDSRC == 1) sub_bgnd("360",'%',-2);
	else if(KINDSRC == 2) sub_bgnd("950",'%',-2);
	else if(KINDSRC == 3) sub_bgnd("1000.01",'%',-6);
	else sub_bgnd("�����.",'%',-5);
	}    

else if (ind==iExt_set)
	{ 
	ptrs[0]=" ������ ������. N1  ";
	ptrs[1]=" ������ ������. N2  ";
	ptrs[2]=" ������ ������. N3  ";
	ptrs[3]=" ����� ������� N1   ";
	ptrs[4]=" ����� ������� N2   ";
	ptrs[5]=" ����� ������� N3   ";
	ptrs[6]=" ����� ������� N4   ";
	ptrs[7]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("  ������� �������   ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	}

else if (ind==iLan_set)
	{
	char sss[10]="abcdef";
	char i,i_flag;
	 
	ptrs[0]=	" Ethernet         ! ";
	ptrs[1]=	" DHCP������       @ ";
	ptrs[2]=	" IP�����            ";
	ptrs[3]=	"  000.000.000.00#   ";
	ptrs[4]=	" ����� �������      ";
	ptrs[5]=	"  000.000.000.00$   ";
	ptrs[6]=	" ����               ";
	ptrs[7]=	"  000.000.000.00)   ";
	ptrs[8]=	" ����.������       [";
	ptrs[9]=	" ����.������       ]";
	ptrs[10]=	" Community <        ";
	ptrs[11]=	" ������� ��� TRAP N1";
	ptrs[12]=	"  000.000.000.00%   ";
	ptrs[13]=	" ������� ��� TRAP N2";
	ptrs[14]=	"  000.000.000.00^   ";
	ptrs[15]=	" ������� ��� TRAP N3";
	ptrs[16]=	"  000.000.000.00&   ";
	ptrs[17]=	" ������� ��� TRAP N4";
	ptrs[18]=	"  000.000.000.00*   ";
	ptrs[19]=	" ������� ��� TRAP N5";
	ptrs[20]=	"  000.000.000.00(   ";
	ptrs[21]=	" ������ ���������   ";
	ptrs[22]=	" WEB���������� >    ";
	ptrs[23]=	" �����              ";

	
	if(!ETH_IS_ON)
		{
		ptrs[1]=" �����              ";
		ptrs[2]="                    ";
		ptrs[3]="                    ";
		}

	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;

     bgnd_par(	" ��������� Ethernet ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);
	
	pointer_set(1);
     if(ETH_IS_ON)
     	{
     	sub_bgnd("���.",'!',-3);   
     	}
     else 
     	{
     	sub_bgnd("����.",'!',-4);   
     	}

     if(ETH_DHCP_ON)
     	{
     	sub_bgnd("���.",'@',-3);   
     	}
     else 
     	{
     	sub_bgnd("����.",'@',-4);   
     	}
		  
	if(sub_ind==2)	ip2lcd(ETH_IP_1,ETH_IP_2,ETH_IP_3,ETH_IP_4,'#',(sub_ind1+1));
	else ip2lcd(ETH_IP_1,ETH_IP_2,ETH_IP_3,ETH_IP_4,'#',0);
	if(sub_ind==4)	ip2lcd(ETH_MASK_1,ETH_MASK_2,ETH_MASK_3,ETH_MASK_4,'$',(sub_ind1+1));
	else ip2lcd(ETH_MASK_1,ETH_MASK_2,ETH_MASK_3,ETH_MASK_4,'$',0);
	if(sub_ind==6)	ip2lcd(ETH_GW_1,ETH_GW_2,ETH_GW_3,ETH_GW_4,')',(sub_ind1+1));
	else ip2lcd(ETH_GW_1,ETH_GW_2,ETH_GW_3,ETH_GW_4,')',0);

	int2lcd(ETH_SNMP_PORT_READ,'[',0);
	int2lcd(ETH_SNMP_PORT_WRITE,']',0);

	if( (ETH_TRAP1_IP_1==255) && (ETH_TRAP1_IP_2==255) && (ETH_TRAP1_IP_3==255) && (ETH_TRAP1_IP_4==255) ) sub_bgnd("    ���������    ",'%',-14);
	else
		{
		if(sub_ind==11)	ip2lcd(ETH_TRAP1_IP_1,ETH_TRAP1_IP_2,ETH_TRAP1_IP_3,ETH_TRAP1_IP_4,'%',(sub_ind1+1));
		else ip2lcd(ETH_TRAP1_IP_1,ETH_TRAP1_IP_2,ETH_TRAP1_IP_3,ETH_TRAP1_IP_4,'%',0);
		}

	if( (ETH_TRAP2_IP_1==255) && (ETH_TRAP2_IP_2==255) && (ETH_TRAP2_IP_3==255) && (ETH_TRAP2_IP_4==255) ) sub_bgnd("    ���������    ",'^',-14);
	else
		{
		if(sub_ind==13)	ip2lcd(ETH_TRAP2_IP_1,ETH_TRAP2_IP_2,ETH_TRAP2_IP_3,ETH_TRAP2_IP_4,'^',(sub_ind1+1));
		else ip2lcd(ETH_TRAP2_IP_1,ETH_TRAP2_IP_2,ETH_TRAP2_IP_3,ETH_TRAP2_IP_4,'^',0);
		}

	if( (ETH_TRAP3_IP_1==255) && (ETH_TRAP3_IP_2==255) && (ETH_TRAP3_IP_3==255) && (ETH_TRAP3_IP_4==255) ) sub_bgnd("    ���������    ",'&',-14);
	else
		{
		if(sub_ind==15)	ip2lcd(ETH_TRAP3_IP_1,ETH_TRAP3_IP_2,ETH_TRAP3_IP_3,ETH_TRAP3_IP_4,'&',(sub_ind1+1));
		else ip2lcd(ETH_TRAP3_IP_1,ETH_TRAP3_IP_2,ETH_TRAP3_IP_3,ETH_TRAP3_IP_4,'&',0);
		}

	if( (ETH_TRAP4_IP_1==255) && (ETH_TRAP4_IP_2==255) && (ETH_TRAP4_IP_3==255) && (ETH_TRAP4_IP_4==255) ) sub_bgnd("    ���������    ",'*',-14);
	else
		{
		if(sub_ind==17)	ip2lcd(ETH_TRAP4_IP_1,ETH_TRAP4_IP_2,ETH_TRAP4_IP_3,ETH_TRAP4_IP_4,'*',(sub_ind1+1));
		else ip2lcd(ETH_TRAP4_IP_1,ETH_TRAP4_IP_2,ETH_TRAP4_IP_3,ETH_TRAP4_IP_4,'*',0);
		}

	if( (ETH_TRAP5_IP_1==255) && (ETH_TRAP5_IP_2==255) && (ETH_TRAP5_IP_3==255) && (ETH_TRAP5_IP_4==255) ) sub_bgnd("    ���������    ",'(',-14);
	else
		{
		if(sub_ind==19)	ip2lcd(ETH_TRAP5_IP_1,ETH_TRAP5_IP_2,ETH_TRAP5_IP_3,ETH_TRAP5_IP_4,'(',(sub_ind1+1));
		else ip2lcd(ETH_TRAP5_IP_1,ETH_TRAP5_IP_2,ETH_TRAP5_IP_3,ETH_TRAP5_IP_4,'(',0);
		}

/*	if((sub_ind==2)&&(sub_ind1==0)&&(bFL2))
		{
		sub_bgnd("   ",'#',-2);
		}
	else int2lcd(ETH_IP_1,'#',0);

	if((sub_ind==2)&&(sub_ind1==1)&&(bFL2))
		{
		sub_bgnd("   ",'$',-2);
		}
	else int2lcd(ETH_IP_2,'$',0);

	if((sub_ind==2)&&(sub_ind1==2)&&(bFL2))
		{
		sub_bgnd("   ",'%',-2);
		}
	else int2lcd(ETH_IP_3,'%',0);

	if((sub_ind==2)&&(sub_ind1==3)&&(bFL2))
		{
		sub_bgnd("   ",'^',-2);
		}
	else int2lcd(ETH_IP_4,'^',0);*/


	//int2lcdyx(sub_ind,0,1,0);	
	//int2lcdyx(index_set,0,3,0);
	//int2lcdyx(sub_ind1,0,5,0);
	//for(i=0;(i<9)&&(snmp_community[i]))

	for(i=0;i<9;i++)
		{
		sss[i]=snmp_community[i];
		}
	sss[9]=0;		

	if(sub_ind==10)community2lcd(sss,'<',sub_ind1,1);
	else (char)community2lcd(sss,'<',sub_ind1,0);

	for(i=0;i<3;i++)
		{
		sss[i]=snmp_web_passw[i];
		}
	sss[3]=0;		

	if(sub_ind==21)community2lcd(sss,'>',sub_ind1,1);
	else community2lcd(sss,'>',sub_ind1,0);
		
	//int2lcdyx(snmp_community[0],0,4,0);
	//int2lcdyx(snmp_community[11],0,9,0);
	//int2lcdyx(snmp_community[2],0,14,0);
	//int2lcdyx(snmp_community[sub_ind1],0,19,0);	
	}
		
else if (ind==iExt_dt)
	{ 
	ptrs[0]=" �����������     @�C";
	ptrs[1]=" tmax            #�C";
	ptrs[2]=" tmin            $�C";
	ptrs[3]=" ����            [  ";
	ptrs[4]=" ����            ]  ";
	ptrs[5]=" �������         (  ";
	ptrs[6]=" RS232           )  ";
	ptrs[7]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>1) index_set=sub_ind-1;
     bgnd_par("  ������� ������    ","   ����������� N!   ",ptrs[index_set],ptrs[index_set+1]);
	
	pointer_set(2);
	int2lcd(sub_ind1+1,'!',0);
	int2lcd_mmm(tout[sub_ind1],'@',0);
	if(!TMAX_EXT_EN[sub_ind1])int2lcd_mmm(TMAX_EXT[sub_ind1],'#',0);
	else sub_bgnd("����.",'#',-2);
	if(!TMIN_EXT_EN[sub_ind1])int2lcd_mmm(TMIN_EXT[sub_ind1],'$',0);
	else sub_bgnd("����.",'$',-2);
	if(!T_EXT_REL_EN[sub_ind1])sub_bgnd("���.",'[',-2);
	else sub_bgnd("����.",'[',-2);
	if(!T_EXT_ZVUK_EN[sub_ind1])sub_bgnd("���.",']',-2);
	else sub_bgnd("����.",']',-2);
	if(!T_EXT_LCD_EN[sub_ind1])sub_bgnd("���.",'(',-2);
	else sub_bgnd("����.",'(',-2);
	if(!T_EXT_RS_EN[sub_ind1])sub_bgnd("���.",')',-2);
	else sub_bgnd("����.",')',-2);	
	
	//int2lcdyx(sub_ind,0,1,0);	
	//int2lcdyx(index_set,0,3,0);
	}	
else if (ind==iExt_sk)
	{ 
	ptrs[0]=" ��������� - @      ";
	ptrs[1]=" ���������          ";
	ptrs[2]=" ��������� - #      ";
	ptrs[3]=" ����            [  ";
	ptrs[4]=" ����            ]  ";
	ptrs[5]=" �������         (  ";
	ptrs[6]=" RS232           )  ";
	ptrs[7]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("  ����� ������� N!  ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	int2lcd(sub_ind1+1,'!',0);
	if(in_stat_out[sub_ind1]==255)sub_bgnd("�������",'@',0);
	else sub_bgnd("������.",'@',0);
	if(!SK_SIGN[sub_ind1])sub_bgnd("�������",'#',0);
	else sub_bgnd("������.",'#',0);
	if(!TMIN_EXT_EN[sub_ind1])int2lcd_mmm(TMIN_EXT[sub_ind1],'$',0);
	else sub_bgnd("����.",'$',-6);
	if(!SK_REL_EN[sub_ind1])sub_bgnd("���.",'[',-2);
	else sub_bgnd("����.",'[',-2);
	if(!SK_ZVUK_EN[sub_ind1])sub_bgnd("���.",']',-2);
	else sub_bgnd("����.",']',-2);
	if(!SK_LCD_EN[sub_ind1])sub_bgnd("���.",'(',-2);
	else sub_bgnd("����.",'(',-2);
	if(!SK_RS_EN[sub_ind1])sub_bgnd("���.",')',-2);
	else sub_bgnd("����.",')',-2);	
	
	//int2lcdyx(sub_ind,0,1,0);	
	//int2lcdyx(index_set,0,3,0);
	}		
else if(ind==iK_pdp)
	{
/*	
const char sm500[]	={" �������� ��  ����  "};
const char sm501[]	={"  ������� ��������  "};
const char sm502[]	={"   ���������� ���   "};
const char sm503[]	={"   �������� 4-10�   "};*/
 	
 	bgnd_par(	"�������� ���-�� ����",
 			"  ������� ��������  ",
 			"   ���������� ���   ",
 			#if(UKU_VERSION==900)
 			"   �������� 4-10�   "
 			#endif
 			#if(UKU_VERSION==300)
 			"   �������� 3-4�    "
 			#endif
 			);
     }    

else if(ind==iK)
	{
	ptrs[0]=" ����               ";
     ptrs[1]=" �������            ";
	ptrs[2]=" ���1               ";
     ptrs[3]=" ���2               ";
     ptrs[4]=" ������� �������    ";
     ptrs[5]=sm_exit;
	
	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("     ����������     ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

	pointer_set(1);	 
	}    

else if(ind==iK_bat)
	{
	//static char ind_cnt;
	ptrs[0]=" U��� =     @�      ";
	ptrs[1]=" ������������ U���  ";
	ptrs[2]="  �������� � ��� �  ";
     ptrs[3]=" I��� =     #�      ";
     if(phase==0)
          {
          ptrs[4]="   ������� � ���    ";
          ptrs[5]="���������� ���� I���";
          }
     else          
          {
          ptrs[4]=" ������������ I���  ";
          ptrs[5]="  �������� � ��� �  ";
          }
     ptrs[6]=" t��� =    $�C      ";
     ptrs[7]=" ������������ t���  ";
     ptrs[8]="  �������� � ��� �  ";
     ptrs[9]=sm_exit;
     ptrs[10]=sm_;
     ptrs[11]=sm_;
     
     if((sub_ind==3)&&(phase==0))MSG_IND2OUT_EN_RELSAM=1;
	/*if(sub_ind==0)ptrs[4]="  ������������ U��� ";
	else if(sub_ind==1)
	     {
	     ind_cnt++;
	     if(ind_cnt<15)ptrs[4]         ="��� ���������� ���� ";
          else if(ind_cnt<30)ptrs[4]    ="������� 0, ��� < >  ";
          else if(ind_cnt<45)ptrs[4]    ="��� ���������� I��� ";
          if(ind_cnt>=45)ind_cnt=0;
	     }
	else if(sub_ind==2)ptrs[4]="  ������������ t��� ";*/     
	//if((sub_ind-index_set)>2)index_set=sub_ind-2;
	//else if(sub_ind<index_set)index_set=sub_ind;
	if((sub_ind==0)||(sub_ind==1)||(sub_ind==2))index_set=0;
	else if((sub_ind==3)||(sub_ind==4)||(sub_ind==5))index_set=3;
	else if((sub_ind==6)||(sub_ind==7)||(sub_ind==8))index_set=6;
	else index_set=9;
	bgnd_par(" ���������� ������� ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	int2lcd(Ubat,'@',1);
	int2lcd_m(Ibat,'#',2);
	int2lcd(t_b,'$',0);
	
	//int2lcdyx(adc_buff_[4],0,4,0);
	//int2lcdyx(adc_buff_[8],0,19,0); 
	//int2lcdyx(Kubat,0,14,0);
	//int2lcdyx(Kibat0,0,14,0);	
	//int2lcdyx(Kibat1,0,19,0);
	
	
     MSG_IND2OUT_DIS_SRC1=1;
     MSG_IND2OUT_DIS_SRC2=1;
     if((sub_ind==1)&&(phase==0))MSG_IND2OUT_EN_RELSAM=1;
	}  	

else if(ind==iK_src)
	{
	if((phase==1)&&(Ibat>-10)&&(Ibat<10))phase=2;
	ptrs[0]=" I��� =    #�       ";
     if(phase==0)
          {
          ptrs[1]="   ������� � ���    ";
          ptrs[2]="���������� ���� I���";
          }
     else if(phase==1)
          {
          ptrs[1]="     ���������      ";
          ptrs[2]="    ��   �������    ";
          }     
     else          
          {
          ptrs[1]=" ������������ I���  ";
          ptrs[2]="  �������� � ��� �  ";
          }	
     ptrs[3]=" U��� =    @�       ";
     ptrs[4]=" ������������ U���  ";
     ptrs[5]="  �������� � ��� �  "; 
     ptrs[6]=" t��� =   $�C       ";    
     if(ND[sub_ind1])
          {
          ptrs[7]=sm_;
          if(bFL5)ptrs[7]=" ������ ����������  ";
          ptrs[8]=sm_;
          }
     else         
          {
          ptrs[7]=" ������������ t���  ";
          ptrs[8]="  �������� � ��� �  ";
          }	
     ptrs[9]=sm_exit;
     ptrs[10]=sm_;
     ptrs[11]=sm_;

     if((sub_ind==0)||(sub_ind==1)||(sub_ind==2))index_set=0;
	else if((sub_ind==3)||(sub_ind==4)||(sub_ind==5))index_set=3;
	else if((sub_ind==6)||(sub_ind==7)||(sub_ind==8))index_set=6;
	else index_set=9;
	
	bgnd_par("  ���������� ���!   ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	int2lcd(sub_ind1+1,'!',0);
	int2lcd(Us[sub_ind1],'@',1);
	int2lcd(Is[sub_ind1],'#',1);
	int2lcd(t_i[sub_ind1],'$',0); 
	//int2lcdyx(adc_buff_[sub_ind1],2,5,0);
//	int2lcdyx(Kusrc[sub_ind1],3,5,0);
	
	if(sub_ind1==0)
	     {
	     if((sub_ind==0)&&((phase==0)||(phase==1)))
	          {
	          MSG_IND2OUT_DIS_SRC1=1;
	          MSG_IND2OUT_EN_SRC2=1;
	          }
	     else           
	          {
	          MSG_IND2OUT_EN_SRC1=1;
	          MSG_IND2OUT_DIS_SRC2=1;
	          }
	     }
	 else if(sub_ind1==1)
	     {
	     if((sub_ind==0)&&((phase==0)||(phase==1)))
	          {
	          MSG_IND2OUT_DIS_SRC2=1;
	          MSG_IND2OUT_EN_SRC1=1;
	          }
	     else           
	          {
	          MSG_IND2OUT_EN_SRC2=1;
	          MSG_IND2OUT_DIS_SRC1=1;
	          }
	     }
	MSG_IND2PWM_SRC1=900;
	MSG_IND2PWM_SRC2=900;         
/*int2lcdyx(sub_ind1,0,0,0);
int2lcdyx(sub_ind,0,1,0);
int2lcdyx(phase,0,2,0);
int2lcdyx(MSG_IND2OUT_DIS_SRC1,0,3,0);
int2lcdyx(MSG_IND2OUT_DIS_SRC2,0,4,0);  
int2lcdyx(MSG_IND2OUT_EN_SRC1,0,5,0);
int2lcdyx(MSG_IND2OUT_EN_SRC2,0,6,0); */

//int2lcdyx(cntrl_stat1,0,19,0); 
//int2lcdyx(cntrl_stat2,0,15,0); 
/*int2lcdyx(adc_buff_[3],2,19,0); */
	//int2lcdyx(adc_buff_[1],0,3,0);
	//int2lcdyx(adc_buff_[3],0,8,0);
	//int2lcdyx(cntrl_stat1,0,13,0);

/*	int2lcdyx(MSG_IND2OUT_DIS_SRC1,0,10,0);
	int2lcdyx(MSG_IND2OUT_DIS_SRC1_OLD,0,11,0);
	int2lcdyx(MSG_IND2OUT_DIS_SRC2,0,12,0);
	int2lcdyx(MSG_IND2OUT_DIS_SRC2_OLD,0,13,0);*/


	//int2lcdyx(cntrl_stat1,0,19,0);  
	}  
	
else if(ind==iK_net)
	{
	ptrs[0]=" U =     @�         ";
     ptrs[1]=sm_exit;
	ptrs[2]=sm_;
	
	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("   ���������� ����  ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	int2lcd(Unet,'@',0);

	//int2lcdyx(unet_buff_,0,4,0);
	//int2lcdyx(Kunet,0,14,0);
     }
     
else if(ind==iK_load)
	{
	ptrs[0]=" U��� =     @�      ";
     ptrs[1]=" I��� =     #�      ";
     ptrs[2]=" t��� =    $�C      ";
     ptrs[3]=sm_exit;
	
	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(" ���������� ������� ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	int2lcd(Ubat,'@',1);
	int2lcd_m(Ibat,'#',2);
	int2lcd(t_b,'$',0); 
	} 

else if(ind==iK_t_out)
	{
     ptrs[0]=" t�����1=      !��  ";
	ptrs[1]=" t�����2=      @��  ";
	ptrs[2]=" t�����3=      #��  ";
     ptrs[3]=sm_exit;
	
	if((sub_ind-index_set)>1)index_set=sub_ind-1;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(" ���������� ������� ","      ��������      ",ptrs[index_set],ptrs[index_set+1]);

	pointer_set(2);	
	if(ND_out[0]&&bFL2)sub_bgnd("����������",'!',-5);
	else int2lcd_mmm(tout[0],'!',0);
	if(ND_out[1]&&bFL2)sub_bgnd("����������",'@',-5);
	else int2lcd_mmm(tout[1],'@',0);
	if(ND_out[2]&&bFL2)sub_bgnd("����������",'#',-5);
	else int2lcd_mmm(tout[2],'#',0);
	
	//int2lcdyx(adc_buff_out_[0],0,4,0);
	//int2lcdyx(adc_buff_out_[1],0,10,0);
	//int2lcdyx(adc_buff_out_[2],0,17,0);
	} 
	
else if(ind==iJ_bat)
	{
	if(BAT_IS_ON==bisON)ptrs[0]=" �������  0!/@  /0# ";
	else ptrs[0]=" �������� 0!/@  /0# ";
     ptrs[1]=" �����.���.     $A*�";
     ptrs[2]=" ���������      %�. ";
     ptrs[3]=" �������� �������   ";
     ptrs[4]=" ������������� �����";
     ptrs[5]=" �������            ";
     ptrs[6]=sm_exit;	
	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(" ���������� ������  ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	pointer_set(1);	

	int2lcd(BAT_DAY_OF_ON,'!',0);
	sub_bgnd(sm_mont[BAT_MONTH_OF_ON],'@',0);
	int2lcd(BAT_YEAR_OF_ON,'#',0); 
	
	
	/*if(BAT_C_IZM!=0x5555)int2lcd(BAT_C_IZM,'$',0);
	else*/
	int2lcd(BAT_C_NOM,'$',0);
	int2lcd(BAT_RESURS,'%',0);
	
	/*int2lcd(sec__,'&',0);
 	int2lcd(min__,'^',0);
 	int2lcd(hour__,'%',0);
 	
 	int2lcd(RTC_DOM,'<',0);
 	sub_bgnd(sm_month[month__],'>');
 	int2lcd(lc640_read_int(KE_CNT),'{',0);*/
	//int2lcdyx(lc640_read_int(KE_CNT),3,8,0);
	//int2lcdyx(lc640_read_int(KE_PTR),3,14,0);
	}
else if(ind==iPrl_bat_in_out)
	{
	if(BAT_IS_ON==bisON)ptrs[0]="��� ��������� ���.-�";
	else  ptrs[0]="��� �������� �������";
	bgnd_par(ptrs[0],"  �������� ������   ",sm_,sm_);
	
     int2lcdyx(parol[0],2,8,0);
     int2lcdyx(parol[1],2,9,0);
     int2lcdyx(parol[2],2,10,0);
     lcd_buffer[68+sub_ind]='�';	
   //  int2lcdyx(sub_ind,2,18,0); 
    //  int2lcdyx(but,3,18,0);                
	}		   

else if(ind==iLog_reset_prl)
	{
	ptrs[0]="��� ������� ������� ";
	bgnd_par(ptrs[0],"  �������  ������   ",sm_,sm_);
	
     int2lcdyx(parol[0],2,8,0);
     int2lcdyx(parol[1],2,9,0);
     int2lcdyx(parol[2],2,10,0);
     lcd_buffer[68+sub_ind]='�';	
	}

else if(ind==iJ_bat_ke_sel)
	{
	if(av_j_si_max==0)
		{
		bgnd_par(	"      �������       ",
				"  �������� �������  ",
		         	" ������ ����        ",
		         	" �����              ");
		lcd_buffer[60]=1;
		sub_ind=0;
		index_set=0;
		}
	else if(av_j_si_max==1)
		{
		bgnd_par(	"      �������       ",
				"  �������� �������  ",
				" (                  ",
				" �����              ");
		pointer_set(2);
		}	
	else
		{
		if(sub_ind<index_set) index_set=sub_ind;
		else if((sub_ind-index_set)>1) index_set=sub_ind-1;
		if(index_set==(av_j_si_max-1)) 
		
		bgnd_par(	"      �������       ",
				"  �������� �������  ",
				" (                  ",
				" �����              ");

		else 
		bgnd_par(	"      �������       ",
				"  �������� �������  ",
				" (                  ",
				" [                  ");

		pointer_set(2);
		}
		
 	event_data2ind(content[index_set],'(');
 	event_data2ind(content[index_set+1],'[');
     }

else if(ind==iJ_bat_ke)
	{
	unsigned short tempUI/*,tempUI*/;
//	unsigned long tempUL;
	char av_head[4],av_data_on[8],av_data_off[8],av_data[4];
	short av_head_int[2];
	
	bgnd_par(sm_,sm_,sm_,sm_);

     tempUI=(unsigned)sub_ind2;
	tempUI*=32;
	tempUI+=EVENT_LOG;
     
     lc640_read_long_ptr(tempUI,av_head);
     lc640_read_long_ptr(tempUI+4,(char*)av_head_int);
     lc640_read_long_ptr(tempUI+8,av_data_on);
     lc640_read_long_ptr(tempUI+12,&(av_data_on[4])); 
     lc640_read_long_ptr(tempUI+16,av_data_off);
     lc640_read_long_ptr(tempUI+20,&(av_data_off[4]));      
	lc640_read_long_ptr(tempUI+24,av_data);  
	
	
	ptrs[0]=" ������             ";
	ptrs[1]=" 0%/(  /0^ 0@:0#:0$ ";

	if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[2]=" �� ��������        ";
			ptrs[3]="			   	    ";
			av_j_si_max_=0;                    
			}
	else
		{
		ptrs[2]=" ���������          ";
		ptrs[3]=" 0q/w  /0r 0i:0l:0s ";
		ptrs[4]=" �������     z�*�.  ";
		av_j_si_max_=2;
		}


	bgnd_par(	"  �������� �������  ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

		
	int2lcd(av_data_on[4],'@',0);
	int2lcd(av_data_on[5],'#',0);
	int2lcd(av_data_on[6],'$',0);
	int2lcd(av_data_on[2],'%',0);
	int2lcd(av_data_on[0],'^',0); 
	if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
	sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
	int2lcd(av_data_off[4],'i',0);
	int2lcd(av_data_off[5],'l',0);
	int2lcd(av_data_off[6],'s',0);
	int2lcd(av_data_off[2],'q',0);
	int2lcd(av_data_off[0],'r',0); 
	if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
	sub_bgnd(sm_mont[av_data_off[1]],'w',0);

	//av_j_si_max=2;				
	//int2lcdyx(av_j_si_max,0,3,0);
	//int2lcdyx(index_set,0,9,0);
 /*	
	int2lcdxy(sub_ind,0x60,0);
	
	int2lcdxy(sub_ind2,0xc0,0);*/	

	int2lcd(av_head_int[0],'z',1);
	}

else if(ind==iJ_bat_vz_sel)
	{
	if(av_j_si_max==0)
		{
		bgnd_par(	"      �������       ",
				"�����������. �������",
		         	" ������ ����        ",
		         	" �����              ");
		lcd_buffer[60]=1;
		sub_ind=0;
		index_set=0;
		} 
	else if(av_j_si_max==1)
		{
		bgnd_par(	"      �������       ",
				"�����������. �������",
				" (                  ",
				" �����              ");
		pointer_set(2);		
		index_set=0;
		}	
	else
		{
		if(sub_ind<index_set) index_set=sub_ind;
		else if((sub_ind-index_set)>1) index_set=sub_ind-1;
		if(index_set==(av_j_si_max-1)) 
		bgnd_par(	"      �������       ",
				"�����������. �������",
				" (                  ",
				" �����              ");

		else 
		bgnd_par(	"      �������       ",
				"�����������. �������",
				" (                  ",
				" [                  ");
				
		pointer_set(2);

		}

 	event_data2ind(content[index_set],'(');
 	event_data2ind(content[index_set+1],'[');

	}

else if(ind==iJ_bat_vz)
	{
	unsigned short tempUI;
//	unsigned long tempUL;
	char av_head[4],av_data_on[8],av_data_off[8],av_data[4];
	short av_head_int[2];
	
	bgnd_par(sm_,sm_,sm_,sm_);
   //	tempUI=lc640_read_int(PTR_EVENT_LOG);
   //	tempUI=ptr_carry(tempUI,64,-1*((signed)sub_ind2)); 
     tempUI=(unsigned)sub_ind2;
	tempUI*=32;
	tempUI+=EVENT_LOG;
     
     lc640_read_long_ptr(tempUI,av_head);
     lc640_read_long_ptr(tempUI+4,(char*)av_head_int);
     lc640_read_long_ptr(tempUI+8,av_data_on);
     lc640_read_long_ptr(tempUI+12,&(av_data_on[4])); 
     lc640_read_long_ptr(tempUI+16,av_data_off);
     lc640_read_long_ptr(tempUI+20,&(av_data_off[4]));      
	lc640_read_long_ptr(tempUI+24,av_data);  
	
	ptrs[0]=" ������             ";
	ptrs[1]=" 0%/(  /0^ 0@:0#:0$ ";

	if((av_data_off[0]=='A')&&(av_data_off[1]=='A'))
			{
			ptrs[2]=" �� ��������        ";
			ptrs[3]="			   	    ";
			av_j_si_max_=0;                    
			}
	else
		{
		ptrs[2]=" ���������          ";
		ptrs[3]=" 0q/w  /0r 0i:0l:0s ";
		av_j_si_max_=2;
		}


	bgnd_par(	"������������� ������",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

		
	int2lcd(av_data_on[4],'@',0);
	int2lcd(av_data_on[5],'#',0);
	int2lcd(av_data_on[6],'$',0);
	int2lcd(av_data_on[2],'%',0);
	int2lcd(av_data_on[0],'^',0); 
	if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
	sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
	int2lcd(av_data_off[4],'i',0);
	int2lcd(av_data_off[5],'l',0);
	int2lcd(av_data_off[6],'s',0);
	int2lcd(av_data_off[2],'q',0);
	int2lcd(av_data_off[0],'r',0); 
	if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
	sub_bgnd(sm_mont[av_data_off[1]],'w',0);

	}	

else if(ind==iJ_bat_wrk_sel)
	{
	if(av_j_si_max==0)
		{
		bgnd_par(	"      �������       ",
				"      �������       ",
		         	" ������ ����        ",
		         	" �����              ");
		lcd_buffer[60]=1;
		sub_ind=0;
		index_set=0;
		} 
	else if(av_j_si_max==1)
		{
		bgnd_par(	"      �������       ",
				"      �������       ",
				" (                  ",
				" �����              ");
		pointer_set(2);		
		index_set=0;
		}	
	else
		{
		if(sub_ind<index_set) index_set=sub_ind;
		else if((sub_ind-index_set)>1) index_set=sub_ind-1;
		if(index_set==(av_j_si_max-1)) 
		bgnd_par(	"      �������       ",
				"      �������       ",
				" (                  ",
				" �����              ");

		else 
		bgnd_par(	"      �������       ",
				"      �������       ",
				" (                  ",
				" [                  ");
				
		pointer_set(2);

		}

 	event_data2ind(content[index_set],'(');
 	event_data2ind(content[index_set+1],'[');
	}


else if(ind==iJ_bat_wrk)
	{
	unsigned short tempUI/*,tempUI*/;
//	unsigned long tempUL;
	char av_head[4],av_data_on[8],av_data_off[8],av_data[4];
	short av_head_int[2];
	
	bgnd_par(sm_,sm_,sm_,sm_);
   //	tempUI=lc640_read_int(PTR_EVENT_LOG);
   //	tempUI=ptr_carry(tempUI,64,-1*((signed)sub_ind2)); 
     tempUI=(unsigned)sub_ind2;
	tempUI*=32;
	tempUI+=EVENT_LOG;
     
     lc640_read_long_ptr(tempUI,av_head);
     lc640_read_long_ptr(tempUI+4,(char*)av_head_int);
     lc640_read_long_ptr(tempUI+8,av_data_on);
     lc640_read_long_ptr(tempUI+12,&(av_data_on[4])); 
     lc640_read_long_ptr(tempUI+16,av_data_off);
     lc640_read_long_ptr(tempUI+20,&(av_data_off[4]));      
	lc640_read_long_ptr(tempUI+24,av_data);  
	
	

	ptrs[0]=" ������             ";
	ptrs[1]=" 0%/(  /0^ 0@:0#:0$ ";
	ptrs[2]="          U���=  <� ";
	ptrs[3]=" ���������          ";
	ptrs[4]=" 0q/w  /0r 0i:0l:0s ";
	ptrs[5]="          U���=  >� ";
	ptrs[6]=" ������        z�*� ";

	bgnd_par(	"      ������        ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

		
	int2lcd(av_data_on[4],'@',0);
	int2lcd(av_data_on[5],'#',0);
	int2lcd(av_data_on[6],'$',0);
	int2lcd(av_data_on[2],'%',0);
	int2lcd(av_data_on[0],'^',0); 
	if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
	sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		
	int2lcd(av_data_off[4],'i',0);
	int2lcd(av_data_off[5],'l',0);
	int2lcd(av_data_off[6],'s',0);
	int2lcd(av_data_off[2],'q',0);
	int2lcd(av_data_off[0],'r',0); 
	if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
	sub_bgnd(sm_mont[av_data_off[1]],'w',0);
	
	
	int2lcd(av_head_int[0],'z',1);
	int2lcd(av_data_on[3]+(av_data_on[7]*256),'<',1);
	int2lcd(av_head_int[1],'>',1);	
	

	}

	
else if((ind==iSet_prl)||(ind==iK_prl)||(ind==iSpc_prl_vz)
	||(ind==iSpc_prl_ke)||(ind==iAusw_prl)||(ind==iPrltst))
	{
	bgnd_par("  �������  ������   ",sm_,sm_,sm_);
	int2lcdyx(parol[0],1,8,0);
     int2lcdyx(parol[1],1,9,0);
     int2lcdyx(parol[2],1,10,0);
     //lcd_buffer[48+sub_ind]='�';	
     lcd_buffer[48+sub_ind]='�';
	}	
	
			
//int2lcdyx(u_necc,0,19,0);
//int2lcdyx(cntrl_stat1,0,3,0);
//int2lcdyx(cntrl_stat2,0,7,0);
//int2lcdyx(u_necc,0,19,0);
//int2lcdyx(ind,1,19,0);
//int2lcdyx(sub_ind,2,19,0);
//int2lcdyx(index_set,3,19,0);
//int2lcdyx(Kisrc[0],1,19,0);
//int2lcdyx(Kisrc[1],2,19,0);
//int2lcdyx(retcntsec,7,16,0); 
//int2lcdyx(plazma[0],1,20,0);
//int2lcdyx(plazma[1],2,20,0);

else if(ind==iDnd)
     {
     bgnd_par("      ������        "
             ,"    �������� !!!    "
             ,"                    "
             ,"                    ");	
     }
else if(ind==iPdp1)
     {
     bgnd_par("    �������� !!!    "
             ,"  �������� �������  "
             ,"     ������ ���     "
             ,"  ���������� ������ ");	
     }  
//int2lcdyx(ptr_ind,0,0,0);
else if(ind==iFWabout)
	{

	bgnd_par(	" ������             ",
				" ������  0000.00.00 ",
#ifdef WG12232L3
				" WG12232L3          ",
#else
				"                    ",
#endif
				"                    ");
	int2lcdyx(BUILD_YEAR,1,12,0);
	int2lcdyx(BUILD_MONTH,1,15,0);
	int2lcdyx(BUILD_DAY,1,18,0);
	
	sprintf(&lcd_buffer[9],"%d.%d.%d",HARDVARE_VERSION,SOFT_VERSION,BUILD);
	}

if((bFL2)&&(fl_simv_len))
	{
	for(i=fl_simv_num;i<fl_simv_num+fl_simv_len;i++)
		{
		lcd_buffer[i]=' ';
		}
	}
/*
if(bFL5)
	{
	for(i=4;i<12;i++)
		{
		lcd_buffer[i]=' ';
		}
	}	*/

/*	int2lcdyx(GET_REG(LPC_GPIO0->FIOPIN,8,1),0,0,0);
	int2lcdyx(GET_REG(LPC_GPIO0->FIOPIN,9,1),0,2,0);
		
	int2lcdyx(GET_REG(LPC_GPIO0->FIOSET,8,1),0,4,0);
	int2lcdyx(GET_REG(LPC_GPIO0->FIOSET,9,1),0,6,0);

	int2lcdyx(bp_tumbler[0],0,8,0);
	int2lcdyx(bp_tumbler[1],0,10,0);
	
	char2lcdhyx(St,0,19);
	char2lcdhyx(St_[0],0,17);
	char2lcdhyx(St_[1],0,15);*/	

//char2lcdhyx(MAIN_IST,0,19);
#endif

//int2lcdyx(ind,0,3,0);		   
//int2lcdyx(cnt_av_umin[0],0,7,0);
//int2lcdyx(cnt_av_umin[1],0,11,0);
} 

#define butU   247
#define butU_  119
#define butD   251
#define butD_  123
#define butL   254
#define butL_  126
#define butR   253
#define butR_  125
#define butE   239
#define butE_  111
#define butUD  243
#define butLR   252
#define butLR_  252-128

//-----------------------------------------------
void but_an(void)
{
#ifndef MINISIZE
signed short temp_SS;
signed int deep,i,cap,ptr;
char av_head[4];

if(!n_but)goto but_an_end;

mnemo_cnt=300;//MNEMO_TIME;
av_beep=0x0000;
av_rele=0x0000;

 if(but==butUD)	 
     {
	 //bwd_stop=1;
     if(ind!=iDeb)
          {
          b[ptr_ind++]=a;
          ind=iDeb;
          sub_ind=0;
          }
     else 
          {
          a=b[--ptr_ind];
          }     
     }
else if(ind==iDeb)
	{
	if(but==butR)
		{
		sub_ind++;
		index_set=0;
		sub_ind1=0;
		gran_ring_char(&sub_ind,0,5);
		}
	else if(but==butL)
		{
		sub_ind--;
		index_set=0;
		sub_ind1=0;
		gran_ring_char(&sub_ind,0,5);
		}
	else if(but==butU)
	     {
	     sub_ind1--;
	     gran_char(&sub_ind1,0,9);
	     //lc640_write_int(ptr_ki_src[0],lc640_read_int(ptr_ki_src[0])+10);
	     }	
     else if(but==butD)
	     {
	     sub_ind1++;
	     gran_char(&sub_ind1,0,9); 
	     //lc640_write_int(ptr_ki_src[0],lc640_read_int(ptr_ki_src[0])-10);
	     }	
     else if(but==butE)
         	{
          //a=b[--ptr_ind];
		if(sub_ind==2)
			{
			lc640_write_int(ptr_ki_bat0,adc_buff_[4]);
			}
		else if(sub_ind==3)
			{
			unet_buff_max=0;
			unet_buff_min=5000;
			}
          }            				
	}
else if(ind==iDeb)
	{
	if(but==butR)
		{
		sub_ind++;
		index_set=0;
		gran_ring_char(&sub_ind,0,2);
		}
	else if(but==butL)
		{
		sub_ind--;
		index_set=0;
		gran_ring_char(&sub_ind,0,2);
		}
	else if(but==butU)
	     {
	     index_set--;
	     gran_char(&index_set,0,4);
	     //lc640_write_int(ptr_ki_src[0],lc640_read_int(ptr_ki_src[0])+10);
	     }	
     else if(but==butD)
	     {
	     index_set++;
	     gran_char(&index_set,0,4); 
	     //lc640_write_int(ptr_ki_src[0],lc640_read_int(ptr_ki_src[0])-10);
	     }	
     else if(but==butE)
         	{
          a=b[--ptr_ind];
          }            				
	}

else if(ind==iMn)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,12);
		//suz_temp=1;
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,12);
		}	
	else if(but==butE_)
		{
		snmp_trap_send("���� ���� ����",0xffff);   
		}
	else if(but==butD_)
		{
		     tree_up(iLog,0,0,0);
		     ret(1000);
		}	
	else if(but==butL)
		{
		ind=iMn;
		sub_ind=0;
		//vz_mem_hndl(0);
		}
	else if(but==butR)
		{
		//vz_mem_hndl(1);
		}
	else if(but==butR_)
		{
		tree_up(iSet,0,0,0);
		}						
	else if(sub_ind==1)
		{
		if(but==butE)
		     {
		     tree_up(iBat,0,0,0);
		     ret(1000);
		     }
		}
     else if(sub_ind==2)
		{
		if(but==butE)
		     {
		     tree_up(iSrc,0,0,0);
		     ret(1000);
		     }
		}
     else if(sub_ind==3)
		{
		if(but==butE)
		     {
		     tree_up(iSrc,0,0,1);
		     ret(1000);
		     }
		}		

     else if(sub_ind==4)
		{
		if(but==butE)
		     {
		     tree_up(iLoad,0,0,0);
		     ret(1000);
		     }
		}		

     else if(sub_ind==5)
		{
		if(but==butE)
		     {
		     tree_up(iNet,0,0,0);
		     ret(1000);
		     }
		}     	

 /*    else if(sub_ind==6)
		{
		if(but==butE)
		     {
			if(ETH_IS_ON)
				{
				tree_up(iLan,0,0,0);
				ret(1000);
				}
			else 
				{
				show_mess("     ����������     ",
						"      Ethernet      ",
						"     ���������      ",
						"    � ����������    ",
						2000);
				}
		     }
		}

     else if(sub_ind==7)
		{
		if(but==butE)
		     {
		     tree_up(iSpc,0,0,0);
		     ret(1000);
		     }
		}	

     else if(sub_ind==8)
		{
		if(but==butE)
		     {
		     tree_up(iLog,0,0,0);
		     ret(1000);
		     }
		}	

     else if(sub_ind==9)
		{
		if(but==butE)
		     {
			tree_up(iJ_bat,0,0,0);
		     ret(1000);
			}
		}	

    	else if(sub_ind==10)
		{
		if(but==butE)
		     {
			tree_up(iAusw,0,0,0);
		     ret(1000);
			}
		}	

     else if(sub_ind==11)
		{
		if(but==butE)
		     {
			tree_up(iSet_prl,0,0,0);
		     ret(50);
		     parol_init();
			}
		}	
     else if(sub_ind==12)
		{
		if(but==butE)
		     {
			St_[0]&=0xe3;
			St_[1]&=0xe3;
			}
		}		
     else if(sub_ind==13)
		{
		if(but==butE)
		     {
			sub_ind=0;
			}
		}
		
*/		
     else if(sub_ind==6)
		{
		if(but==butE)
		     {
		     tree_up(iSpc,0,0,0);
		     ret(1000);
		     }
		}	

     else if(sub_ind==7)
		{
		if(but==butE)
		     {
		     tree_up(iLog,0,0,0);
		     ret(1000);
		     }
		}	

     else if(sub_ind==8)
		{
		if(but==butE)
		     {
			tree_up(iJ_bat,0,0,0);
		     ret(1000);
			}
		}	

    	else if(sub_ind==9)
			{
			if(but==butE)
		     	{
		     	tree_up(iFWabout,0,0,0);
		     	}
			}
/*		{
		if(but==butE)
		     {
			tree_up(iAusw,0,0,0);
		     ret(1000);
			}
		}*/	

     else if(sub_ind==10)
		{
		if(but==butE)
		     {
			tree_up(iSet_prl,0,0,0);
		     ret(50);
		     parol_init();
			}
		}	
     else if(sub_ind==11)
		{
		if(but==butE)
		     {
			St_[0]&=0xe3;
			St_[1]&=0xe3;
			}
		}		
     else if(sub_ind==12)
		{
		if(but==butE)
		     {
			sub_ind=0;
			}
		}			
		
		
					
	}

else if(ind==iBat)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,4);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,4);
		}
	else if((but==butL)||((sub_ind==4)&&(but==butE)))
	     {
	     //a=b[--ptr_ind];
	     tree_down(0,0);
	     ret(0);
	     }
	else if(but==butD_)
		{
		sub_ind=4;
		}		     
     }

else if(ind==iSrc)
	{
	ret(1000);
	if((but==butD)&&!((sub_ind1==1)&&(NUMIST==1)))
		{
		sub_ind++;
		gran_char(&sub_ind,0,2);
		}
	else if((but==butU)&&!((sub_ind1==1)&&(NUMIST==1)))
		{
		sub_ind--;
		gran_char(&sub_ind,0,2);
		}
	else if((but==butL)||((sub_ind==2)&&(but==butE)))
	     {
	     //a=b[--ptr_ind];
	     tree_down(0,0);
	     ret(0);	     
	     }
	else if(but==butD_)
		{
		sub_ind=2;
		}		     
     }

else if(ind==iLoad)
	{
     if((but==butE)||(but==butL))
	     {
	     tree_down(0,0);
	     ret(0);
	     }
     }  
          
else if(ind==iNet)
	{
     if((but==butE)||(but==butL))
	     {
	     tree_down(0,0);
	     ret(0);
	     }
     }

else if(ind==iSpc)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,3);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,3);
		}
	else if(but==butD_)
		{
		sub_ind=3;
		}				
	else if(sub_ind==0)
	     {
	     if(but==butE)
	     	{
	     	tree_up(iSpc_prl_ke,0,0,0);
	     	ret(50);
	     	parol_init();
	     	}
	     }		
	else if(sub_ind==1)
		{
		if(but==butE)
	     	{
	     	tree_up(iSpc_prl_vz,0,0,0);
	     	ret(50);
	     	parol_init();
	     	}
	     }
	else if(sub_ind==2)
		{
		if(but==butE)
	     	{
	     	tree_up(iAvz,0,0,0);
			ret(1000);
	     	}
	     }	     
	else if((but==butL)||((sub_ind==3)&&(but==butE)))
	     {
	     tree_down(0,0);
	     ret(0);
	     }
     }

else if(ind==iKe)
	{
	ret(1000);
	if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,1);
		}
	else if(but==butD)
		{ 
		sub_ind++;
		gran_char(&sub_ind,0,1);
		}
	else if(but==butD_)
		{
		sub_ind=1;
		}				
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			if(spc_stat==spc_KE/*p1*/) spc_stat=spc_OFF;
			else if (ke_start()==1)
				{
				//b[ptr_ind++]=a;
				//ind=iKednd;
				//sub_ind=0;
				//ret_ind(b[ptr_ind-1].i,b[ptr_ind-1].s_i,15);
				tree_up(iKednd,0,0,0);
				ret(15);
				}
			else if (ke_start()==2)
				{
				/*b[ptr_ind++]=a;
				ind=iKednd;
				sub_ind=1;
				ret_ind(b[ptr_ind-1].i,b[ptr_ind-1].s_i,15);*/
				tree_up(iKednd,1,0,0);
				ret(15);				
				}
			else if (ke_start()==3)
				{
				tree_up(iKednd,2,0,0);
				ret(15);				
				}	
			else if (ke_start()==4)
				{
				tree_up(iKednd,3,0,0);
				ret(15);				
				}										
			} 	             
		else if(sub_ind==1)
			{
			//a=b[--ptr_ind];	
			tree_down(-1,0);
			ret(0);			
			} 	
		}
	else if(but==butL)	
	 	{
		tree_down(-1,0);
		ret(0);	
	 	} 
	}
else if(ind==iVz)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,4);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,4);
		}
	else if(but==butD_)
		{
		sub_ind=4;
		}				
	else if(sub_ind==0)
		{
		speed=1;
		if((but==butR)||(but==butR_))VZ_HR++;
		else if((but==butL)||(but==butL_))VZ_HR--;
		gran(&VZ_HR,1,24);
		lc640_write_int(EE_VZ_HR,VZ_HR);
		}
	else if(sub_ind==1)
		{
		if(spc_stat==spc_VZ)
			{
			vz_mem_hndl(0);
			spc_stat=spc_OFF;
			
			}
		else if(!(St&0x03)&&(spc_stat==spc_OFF))
			{
			spc_stat=spc_VZ;
			cnt_vz_sec=0L;
			cnt_vz_sec_=(SEC_IN_HOUR*VZ_HR);
			vz_mem_hndl(1);
			}
		} 	  		
	else if(sub_ind==2)
		{
		if(but==butE)
			{
			tree_down(-1,0);
			ret(0);
			}
		}			
	} 

else if(ind==iAvz)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,simax);
		if(sub_ind==3)sub_ind=4;
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,simax);
		if(sub_ind==3)sub_ind=2;
		}
	else if(but==butD_)
		{
		sub_ind=simax;
		}				
	else if(sub_ind==0)
		{
		if(but==butL)
			{
			if(AVZ==AVZ_1)AVZ=AVZ_OFF;
			else if(AVZ==AVZ_2)AVZ=AVZ_1;
			else if(AVZ==AVZ_3)AVZ=AVZ_2; 
			else if(AVZ==AVZ_6)AVZ=AVZ_3;
			else if(AVZ==AVZ_12)AVZ=AVZ_6;			
			else AVZ=AVZ_12;
			lc640_write_int(EE_AVZ,AVZ);
			}
		else if((but==butR)||(but==butE))
			{
			if(AVZ==AVZ_1)AVZ=AVZ_2;
			else if(AVZ==AVZ_2)AVZ=AVZ_3;
			else if(AVZ==AVZ_3)AVZ=AVZ_6; 
			else if(AVZ==AVZ_6)AVZ=AVZ_12;
			else if(AVZ==AVZ_12)AVZ=AVZ_OFF;			
			else AVZ=AVZ_1;
			lc640_write_int(EE_AVZ,AVZ);
			} 
		if(AVZ!=AVZ_OFF)next_date_hndl(AVZ);		
		}       	
	else if(sub_ind==1)
		{
		if((but==butE)&&(simax==1))
			{
			tree_down(0,0);
			}
		else if(simax==4)
			{
			if((but==butL)||(but==butL_))
				{
				speed=1;
				AVZ_TIME--;
				gran(&AVZ_TIME,1,24);
				lc640_write_int(EE_AVZ_TIME,AVZ_TIME);
				}
			else if((but==butR)||(but==butR_))
				{
				speed=1;
				AVZ_TIME++;
				gran(&AVZ_TIME,1,24);
				lc640_write_int(EE_AVZ_TIME,AVZ_TIME);
				}				
			}
		}		
		
	else if(sub_ind==4)
		{
		if((but==butE)&&(simax==4))
			{
			tree_down(0,0);
			ret(0);
			}
		}			
	}
	     
else if(ind==iLog)
	{
	ret_ind_sec(0,0);
	ret_ind(0,0,0);
	if (but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max+1);
		}
	else if (but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max+1);
          
		}  

	else if (but==butD_)
		{
		sub_ind=av_j_si_max;
		}  
		
	else if(but==butE)
		{  
		if((sub_ind==av_j_si_max+1)&&(av_j_si_max!=0))
			{
			tree_up(iLog_reset_prl,0,0,0);
			parol_init();
			/*lc640_write(CNT_EVENT_LOG,0);
			lc640_write(PTR_EVENT_LOG,0);
			tree_down(0,0);
			avar_ind_stat=0;
			avar_stat=0;
			avar_stat_old=0;*/				
			}
					
		else if((sub_ind==av_j_si_max)||(av_j_si_max==0))
			{
			tree_down(0,0);
			ret(0);
			}
			
		else 
			{
			/*ind=iLog_;
			sub_ind1=sub_ind;
			index_set=0;
			sub_ind=0;*/
			tree_up(iLog_,0,0,sub_ind);
			}	
			
		} 

	else if(but==butR)
		{
	    //	avar_bat_hndl(0,1);	
	    	//avar_bps_hndl(0,1,2);
		ke_mem_hndl(2000);
		}
	else if(but==butR_)
		{
	    	//avar_bat_hndl(0,0);
		//avar_bps_hndl(0,0,2);	
		}		
	else if(but==butL)
		{
	    	//avar_s_hndl(1,0,1);
		//avar_bps_hndl(1,1,1);
		//vz_mem_hndl(0);	
		}
				
	else if(but==butL_)
		{           
		//avar_bps_hndl(1,0,1);	
		}	 		
		
	}

else if(ind==iLog_)
	{          
	if(but==butU)
		{
		index_set--;
		gran_char(&index_set,0,av_j_si_max);
		}
	else if(but==butD)
		{
		if(index_set==av_j_si_max)tree_down(0,0);
		else 
			{
			index_set++;
			gran_char(&index_set,0,av_j_si_max);
			}
		}
	else 
		{
		//ind=iLog;
		//sub_ind=sub_ind1;
		tree_down(0,0);
		}		
	}	

else if(ind==iAusw)
	{
	if(but==butD)
		{
		index_set++;
		gran_char(&index_set,0,8);
		}
	else if(but==butU)
		{
		index_set--;
		gran_char(&index_set,0,8);
		}
	else if(but==butD_)
		{
		index_set=8;
		}				
	else if(but==butE_)
		{
		tree_up(iAusw_prl,0,0,0);
		ret(50);
		parol_init();
		}	
     else if(index_set==8)
	     {
	     if(but==butE)
	          {
	          tree_down(0,0);
	          ret(0);
	          }
	     }		
    else  if(but==butL)
	     {
          tree_down(0,0);
          ret(0);
	     }			     	
	}

else if(ind==iAusw_set)
	{
	if(but==butD)
		{
		sub_ind++;
		if(sub_ind==5)sub_ind++;
		if(sub_ind==6)sub_ind++;
		gran_char(&sub_ind,0,9);
		if((sub_ind>6)&&(index_set<1))index_set=1;
		if((sub_ind>7)&&(index_set<2))index_set=2;
		if((sub_ind>8)&&(index_set<3))index_set=3;
		}
	else if(but==butU)
		{
		sub_ind--;
		if(sub_ind==6)sub_ind--;
		if(sub_ind==5)sub_ind--;
		gran_char(&sub_ind,0,9);
		if((sub_ind<5)&&(index_set>2))index_set=2;
		if((sub_ind<4)&&(index_set>1))index_set=1;
		if((sub_ind<1)&&(index_set))index_set=0;
		}
	else if(but==butD_)
		{
		sub_ind=9;
		}			
	else if((but==butE_)||((but==butE)&&(sub_ind==9)))
		{
		fl_simv(0,0,0);
		tree_down(-1,0);
		ret(0);
		}
			
     else if(sub_ind==0)
	     {
/*	     if((but==butR)||(but==butR_))
	     	{
			if(AUSW_MAIN==4812)AUSW_MAIN=4824;
	          else if(AUSW_MAIN==4824)AUSW_MAIN=6012;
	          else if(AUSW_MAIN==6012)AUSW_MAIN=6024;
	          else AUSW_MAIN=4812;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }
	     else if((but==butL)||(but==butL_))
	          {
	          if(AUSW_MAIN==4812)AUSW_MAIN=6024;
	          else if(AUSW_MAIN==4824)AUSW_MAIN=4812;
	          else if(AUSW_MAIN==6012)AUSW_MAIN=4824;
	          else AUSW_MAIN=6012;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }*/

#if(UKU_VERSION==900)

#ifdef _24_


	     if((but==butR)||(but==butR_))
	     	{
			if(AUSW_MAIN==2450)AUSW_MAIN=2425;
	          else AUSW_MAIN=2450;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }
	     else if((but==butL)||(but==butL_))
	          {
			if(AUSW_MAIN==2450)AUSW_MAIN=2425;
	          else AUSW_MAIN=2450;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }

#else


	     if((but==butR)||(but==butR_))
	     	{
			if(AUSW_MAIN==6024)AUSW_MAIN=4824;
               else if(AUSW_MAIN==4824)AUSW_MAIN=6012;
               else if(AUSW_MAIN==6012)AUSW_MAIN=4812;
               else if(AUSW_MAIN==4812)AUSW_MAIN=6040;
               else if(AUSW_MAIN==6040)AUSW_MAIN=4840;
               else if(AUSW_MAIN==4840)AUSW_MAIN=6020;
               else if(AUSW_MAIN==6020)AUSW_MAIN=4820;
               else AUSW_MAIN=6024;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }
	     else if((but==butL)||(but==butL_))
	          {
			if(AUSW_MAIN==6024)AUSW_MAIN=4820;
               else if(AUSW_MAIN==4824)AUSW_MAIN=6024;
               else if(AUSW_MAIN==6012)AUSW_MAIN=4824;
               else if(AUSW_MAIN==4812)AUSW_MAIN=6012;
               else if(AUSW_MAIN==6040)AUSW_MAIN=4812;
               else if(AUSW_MAIN==4840)AUSW_MAIN=6040;
               else if(AUSW_MAIN==6020)AUSW_MAIN=4840;
               else AUSW_MAIN=6020;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }

#endif				
#endif 

#if(UKU_VERSION==300)
#ifdef _24_

	     if((but==butR)||(but==butR_))
	     	{
			if(AUSW_MAIN==2424)AUSW_MAIN=2412;
	          else AUSW_MAIN=2424;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }
	     else if((but==butL)||(but==butL_))
	          {
			if(AUSW_MAIN==2424)AUSW_MAIN=2412;
	          else AUSW_MAIN=2424;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }

#else

	     if((but==butR)||(but==butR_))
	     	{
			if(AUSW_MAIN==6010)AUSW_MAIN=4810;
               else if(AUSW_MAIN==4810)AUSW_MAIN=6005;
               else if(AUSW_MAIN==6005)AUSW_MAIN=4805;
               else AUSW_MAIN=6010;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }
	     else if((but==butL)||(but==butL_))
	          {
			if(AUSW_MAIN==6010)AUSW_MAIN=4805;
               else if(AUSW_MAIN==4810)AUSW_MAIN=6010;
               else if(AUSW_MAIN==6005)AUSW_MAIN=4810;
               else AUSW_MAIN=6005;
	          lc640_write_int(EE_AUSW_MAIN,AUSW_MAIN);
	          }


#endif				
#endif    
		}

	          	          
	    	
	     
     else if(sub_ind==1)
	     {
	     speed=1;
	     if(but==butR)
	          {
	          AUSW_DAY++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_DAY+=2;
		     }
	     else if(but==butL)
	          {
	          AUSW_DAY--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_DAY-=2;
		     }
		else if(but==butLR)
	          {
	          lc640_write_int(EE_AUSW_DAY,LPC_RTC->DOM);
	          lc640_write_int(EE_AUSW_MONTH,LPC_RTC->MONTH);
	          lc640_write_int(EE_AUSW_YEAR,LPC_RTC->YEAR);
	          sub_ind=4;
		     }     
		gran(&AUSW_DAY,1,31);     		     		     
		lc640_write_int(EE_AUSW_DAY,AUSW_DAY); 	
	     }
	     	
     else if(sub_ind==2)
	     {
	     speed=1;
	     if(but==butR)
	          {
	          AUSW_MONTH++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_MONTH+=2;
		     }
	     else if(but==butL)
	          {
	          AUSW_MONTH--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_MONTH-=2;
		     }
		else if(but==butLR)
	          {
	          lc640_write_int(EE_AUSW_DAY,LPC_RTC->DOM);
	          lc640_write_int(EE_AUSW_MONTH,LPC_RTC->MONTH);
	          lc640_write_int(EE_AUSW_YEAR,LPC_RTC->YEAR);
	          sub_ind=4;
		     }		     
		gran(&AUSW_MONTH,1,12);     		     		     
		lc640_write_int(EE_AUSW_MONTH,AUSW_MONTH);
	     }		
	     
     else if(sub_ind==3)
	     {
	     speed=1;
	     if(but==butR)
	          {
	          AUSW_YEAR++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_YEAR+=5;
		     }
	     else if(but==butL)
	          {
	          AUSW_YEAR--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_YEAR-=5;
		     }
		else if(but==butLR)
	          {
	          lc640_write_int(EE_AUSW_DAY,LPC_RTC->DOM);
	          lc640_write_int(EE_AUSW_MONTH,LPC_RTC->MONTH);
	          lc640_write_int(EE_AUSW_YEAR,LPC_RTC->YEAR);
	          sub_ind=4;
		     }		     
		gran(&AUSW_YEAR,1,12);     		     		     
		lc640_write_int(EE_AUSW_YEAR,AUSW_YEAR);
	     }		          			     		
	     
     else if(sub_ind==4)
	     {
	     speed=1;
	     if(but==butR)
	          {
	          AUSW_MAIN_NUMBER++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_MAIN_NUMBER+=10;
		     }
	     else if(but==butL)
	          {
	          AUSW_MAIN_NUMBER--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_MAIN_NUMBER-=10;
		     }
		gran_long(&AUSW_MAIN_NUMBER,9000,999999L);     		     		     
		lc640_write_long(EE_AUSW_MAIN_NUMBER,AUSW_MAIN_NUMBER);
		lc640_write_long(EE_AUSW_UKU_NUMBER,AUSW_MAIN_NUMBER);
	     }				     		

    else if(sub_ind==6)
	     {
     	speed=1;
	     if(but==butR)
	          {
	          AUSW_UKU_NUMBER++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_UKU_NUMBER+=10;
		     }
	     else if(but==butL)
	          {
	          AUSW_UKU_NUMBER--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_UKU_NUMBER-=10;
		     }
		gran_long(&AUSW_UKU_NUMBER,1,999999);     		     		     
		lc640_write_long(EE_AUSW_UKU_NUMBER,AUSW_UKU_NUMBER);
	     }
	     
  else if(sub_ind==7)
	     {
     	speed=1;
	     if(but==butR)
	          {
	          AUSW_BPS1_NUMBER++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_BPS1_NUMBER+=10;
		     }
	     else if(but==butL)
	          {
	          AUSW_BPS1_NUMBER--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_BPS1_NUMBER-=10;
		     }
		gran_long(&AUSW_BPS1_NUMBER,20000,999999);     		     		     
		lc640_write_long(EE_AUSW_BPS1_NUMBER,AUSW_BPS1_NUMBER);
	     }	     
	     
 else if(sub_ind==8)
	     {
     	speed=1;
	     if(but==butR)
	          {
	          AUSW_BPS2_NUMBER++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_BPS2_NUMBER+=10;
		     }
	     else if(but==butL)
	          {
	          AUSW_BPS2_NUMBER--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_BPS2_NUMBER-=10;
		     }
		gran_long(&AUSW_BPS2_NUMBER,20000,999999);     		     		     
		lc640_write_long(EE_AUSW_BPS2_NUMBER,AUSW_BPS2_NUMBER);
	     }	     	     
	     
else if(sub_ind==9)
	     {
     	speed=1;
	     if(but==butR)
	          {
	          AUSW_RS232++;
	          }
	     else if(but==butR_)
	          {
	          AUSW_RS232+=10;
		     }
	     else if(but==butL)
	          {
	          AUSW_RS232--;
		     }
	     else if(but==butL_)
	          {
	          AUSW_RS232-=10;
		     }
		gran(&AUSW_RS232,0,1000);     		     		     
		lc640_write_long(EE_AUSW_BPS2_NUMBER,AUSW_BPS2_NUMBER);
	     }	
	else if(sub_ind==10)
	     {
	     if(but==butE)
	     	{
	     	tree_down(-1,0);
	     	ret(0);
	     	}
	     }    	     	     
	}

else if(ind==iSet)
	{

/*     ptrs[0]=" �����������        ";
	ptrs[1]=" ����� � ����       ";
     ptrs[2]=" ���������          ";
     ptrs[3]=" �������� ������. N<";
	ptrs[4]=" ��.����.   (       ";
	ptrs[5]=" ���������� ������� ";
	ptrs[6]="  ������    )       ";
	ptrs[7]=" ��� ����������     ";
     ptrs[8]=" Umax=       !�     ";
     ptrs[9]=" U�0�=       @�     ";
     ptrs[10]=" U�20�=      #�     ";
     ptrs[11]=" U����=      ^�     ";
     ptrs[12]=" Umin.����=  &�     ";
	ptrs[13]=" U0�=        >�     ";
	ptrs[14]=" I��.=       )�     ";
     ptrs[15]=" I�.���.=    <�     ";
     ptrs[16]=" Imax=       ]A     ";
     ptrs[17]=" Kimax=      {      ";
     ptrs[18]=" K���.���.=    [    ";
     ptrs[19]=" T�.���.�.�. !�     ";
	ptrs[20]=" tmax=       $�C    ";
     ptrs[21]=" ������� �������    ";
     ptrs[22]=sm_exit; 
     ptrs[23]=" ����������         "; 
     ptrs[24]=" ����               ";     */	
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		sub_ind1=0;
		if(sub_ind==2)index_set=1;
		if(sub_ind==3)sub_ind=4;
		if(sub_ind==8)index_set=7;
		if(sub_ind==9)sub_ind=10;
		if(sub_ind==11)index_set=10;
		if(sub_ind==12)sub_ind=13;
		gran_char(&sub_ind,0,32);
		}
	else if(but==butU)
		{
		sub_ind--;
		sub_ind1=0;
		if(sub_ind==3)sub_ind=2;
		if(sub_ind==9)sub_ind=8;
		if(sub_ind==12)sub_ind=11;
		gran_char(&sub_ind,0,32);
		}
	else if(but==butD_)
		{
		sub_ind=30;
		}
		
	else if(sub_ind==0)
	     {
	     if(but==butE)
	          {
	          tree_up(iDef,0,0,0);
	          ret(1000);
	          default_temp=20;
	          }
	     }	
	
     else if(sub_ind==1)
		{
		if(but==butE)
		     {
		     tree_up(iSet_T,0,0,0);
		     ret(1000);
		     phase=0;
		     }
		}
			
     else if(sub_ind==2)
		{
		if(but==butE)
		     {
		     tree_up(iSet_T_avt,0,0,0);
		     ret(1000);
		     phase=0;
		     }
		}
								 
     else if(sub_ind==4)
		{
		if(but==butE)
		     {
		     tree_up(iStr,0,0,0);
		     ret(1000);
		     index_set=0;
		     }
		}	
	
	else if(sub_ind==5)
	     {
	     if(but==butR)MNEMO_TIME++;
	     else if(but==butR_)MNEMO_TIME+=10;
	     else if(but==butL)MNEMO_TIME--;
	     else if(but==butL_)MNEMO_TIME-=10;
	    /* else if(but==butE)
	     	{
	     	if(MNEMO_ON==mnON)lc640_write_int(EE_MNEMO_ON,mnOFF);
	     	else lc640_write_int(EE_MNEMO_ON,mnON);
	     	}*/
	     if(((MNEMO_TIME<5)||(MNEMO_TIME>300))&&(MNEMO_ON!=mnOFF))lc640_write_int(EE_MNEMO_ON,mnOFF);	
	     if(((MNEMO_TIME>=5)&&(MNEMO_TIME<=300))&&(MNEMO_ON!=mnON))lc640_write_int(EE_MNEMO_ON,mnON);
	     gran(&MNEMO_TIME,4,301);
	     lc640_write_int(EE_MNEMO_TIME,MNEMO_TIME);
	     speed=1;
	     }
				     		
	else if(sub_ind==6)
	     {
	     if(MAIN_IST==0)
	     	{
	     	lc640_write_int(EE_MAIN_BPS,1);
	     	cnt_src[0]=10;
	     	}
	     else
	     	{
	     	lc640_write_int(EE_MAIN_BPS,0);
	     	cnt_src[1]=10;
	     	} 
	     }	
	
	
	     
	else if(sub_ind==7)
	     {
		if(ZV_ON)ZV_ON=0;
		else ZV_ON=1;
	     lc640_write_int(EE_ZV_ON,ZV_ON);
	     speed=1;
	     }	
	
	else if(sub_ind==8)
	     {
		if(AV_OFF_AVT)AV_OFF_AVT=0;
		else AV_OFF_AVT=1;
	     lc640_write_int(EE_AV_OFF_AVT,AV_OFF_AVT);
	     speed=1;
	     }	

	else if(sub_ind==10)
		{
		if(but==butE)
			{
			tree_up(iApv,0,0,0);
			ret(1000);
			}
		}	

	else if(sub_ind==11)
		{
		if(but==butR)TBAT++;
		else if(but==butR_)TBAT+=10;
		else if(but==butL)TBAT--;
		else if(but==butL_)TBAT-=10;
		gran(&TBAT,5,60);
		lc640_write_int(EE_TBAT,TBAT);
		speed=1;
		}	
	                    	     	
	else if(sub_ind==13)
	     {
	     if(but==butR)UMAX++;
	     else if(but==butR_)UMAX+=10;
	     else if(but==butL)UMAX--;
	     else if(but==butL_)UMAX-=10;
	     gran(&UMAX,10,1000);
	     lc640_write_int(EE_UMAX,UMAX);
	     speed=1;
	     }
	     
	else if(sub_ind==14)
	     {
	     if(but==butR)UB0++;
	     else if(but==butR_)UB0+=10;
	     else if(but==butL)UB0--;
	     else if(but==butL_)UB0-=10;
	     gran(&UB0,10,1000);
	     lc640_write_int(EE_UB0,UB0);
	     speed=1;
	     }
	     
	else if(sub_ind==15)
	     {
	     if(but==butR)UB20++;
	     else if(but==butR_)UB20+=10;
	     else if(but==butL)UB20--;
	     else if(but==butL_)UB20-=10;
	     gran(&UB20,10,1000);
	     lc640_write_int(EE_UB20,UB20);
	     speed=1;
	     }	

	else if(sub_ind==16)
	     {
	     if(but==butR)USIGN++;
	     else if(but==butR_)USIGN=((USIGN/10)+1)*10;
	     else if(but==butL)USIGN--;
	     else if(but==butL_)USIGN=((USIGN/10)-1)*10;
	     gran(&USIGN,10,1000);
	     lc640_write_int(EE_USIGN,USIGN);
	     speed=1;
	     }	
	else if(sub_ind==17)
	     {
	     if(but==butR)UMN++;
	     else if(but==butR_)UMN+=10;
	     else if(but==butL)UMN--;
	     else if(but==butL_)UMN-=10;
	     gran(&UMN,1,220);
	     lc640_write_int(EE_UMN,UMN);
	     speed=1;
	     }	
 	else if(sub_ind==18)
	     {
	     if(but==butR)UMAXN++;
	     else if(but==butR_)UMAXN+=10;
	     else if(but==butL)UMAXN--;
	     else if(but==butL_)UMAXN-=10;
	     gran(&UMAXN,1,300);
	     lc640_write_int(EE_UMAXN,UMAXN);
	     speed=1;
	     }
	else if(sub_ind==19)
	     {
	     if(but==butR)U0B++;
	     else if(but==butR_)U0B+=10;
	     else if(but==butL)U0B--;
	     else if(but==butL_)U0B-=10;
	     gran(&U0B,10,1000);
	     lc640_write_int(EE_U0B,U0B);
	     speed=1;
	     }	
	     
	else if(sub_ind==20)
	     {
	     if(but==butR)IKB++;
	     else if(but==butR_)IKB+=10;
	     else if(but==butL)IKB--;
	     else if(but==butL_)IKB-=10;
	     gran(&IKB,1,500);
	     lc640_write_int(EE_IKB,IKB);
	     speed=1;
	     }		
            
	else if(sub_ind==21)
	     {
	     if(but==butR)IZMAX++;
	     else if(but==butR_)IZMAX+=10;
	     else if(but==butL)IZMAX--;
	     else if(but==butL_)IZMAX-=10;
	     gran(&IZMAX,10,200);
	     lc640_write_int(EE_IZMAX,IZMAX);
	     speed=1;
	     }   

	else if(sub_ind==22)
	     {
	     if(but==butR)IMAX++;
	     else if(but==butR_)IMAX+=10;
	     else if(but==butL)IMAX--;
	     else if(but==butL_)IMAX-=10;
	     gran(&IMAX,1,500);
	     lc640_write_int(EE_IMAX,IMAX);
	     speed=1;
	     }		
	else if(sub_ind==23)
	     {
	     if(but==butR)IMIN++;
	     else if(but==butR_)IMIN+=10;
	     else if(but==butL)IMIN--;
	     else if(but==butL_)IMIN-=10;
	     gran(&IMIN,1,IMAX);
	     lc640_write_int(EE_IMIN,IMIN);
	     speed=1;
	     }	     
/*	else if(sub_ind==23)
	     {
	     if(but==butR)KIMAX++;
	     else if(but==butR_)KIMAX+=10;
	     else if(but==butL)KIMAX--;
	     else if(but==butL_)KIMAX-=10;
	     gran(&KIMAX,5,10);
	     lc640_write_int(EE_KIMAX,KIMAX);
	     speed=1;
	     }*/
	
	else if(sub_ind==24)
	     {
	     if ((but==butR)||(but==butR_))KVZ+=5;
		if ((but==butL)||(but==butL_))KVZ-=5;
		gran(&KVZ,1005,1030); 	          
		lc640_write_int(EE_KVZ,KVZ);
	     speed=1;
	     }
	     
	else if(sub_ind==25)
		{
		if ((but==butR)||(but==butR_))TZAS++;
		if ((but==butL)||(but==butL_))TZAS--;
		gran(&TZAS,0,3);
		lc640_write_int(EE_TZAS,TZAS);
		speed=1; 
		}	
			       	        
	else if(sub_ind==26)
	     {
	     if(but==butR)TMAX++;
	     else if(but==butR_)TMAX+=10;
	     else if(but==butL)TMAX--;
	     else if(but==butL_)TMAX-=10;
	     gran(&TMAX,10,100);
	     lc640_write_int(EE_TMAX,TMAX);
	     speed=1;
	     }	

    else if(sub_ind==27)
		{
		if(but==butE)
		     {
		     tree_up(iLan_set,0,0,0);
		     ret(1000);
		     }
		}		
		     	     	     		     	     
	else if(sub_ind==28)
		{
		if(but==butE)
		     {
		     tree_up(iExt_set,0,0,0);
		     ret(1000);
		     }
		}

 	else if(sub_ind==29)
		{
		long t6,t7,t1,t2,t3;
		if(sub_ind1==1)t6=1L;
		if(sub_ind1==2)t6=10L;
		if(sub_ind1==3)t6=100L;
		if(sub_ind1==4)t6=1000L;
		if(sub_ind1==5)t6=10000L;
		if(sub_ind1==6)t6=100000L;
		t7=t6*10L;
		if(but==butE_)
			{
			if(sub_ind1==0)sub_ind1=6;
			else 
				{
				sub_ind1--;
				gran_ring_char(&sub_ind1,1,6);
				}
			speed=0;
			}
		
		t1=AUSW_MAIN_NUMBER%t7;
		t1/=t6;
		t2=t1*t6;

		if(sub_ind1)
			{
		    if((but==butR)||(but==butR_))
				{
				t1++;
				speed=1;
				}
		    else if((but==butL)||(but==butL_))
				{
				t1--;
				speed=1;
				}
			gran_ring_long(&t1, 0L, 9L);	    
	
			t3=t1*t6;
	
			AUSW_MAIN_NUMBER-=t2;
			AUSW_MAIN_NUMBER+=t3;
			//else if(but==butEL_)AUSW_MAIN_NUMBER=15000;
			//if(AUSW_MAIN_NUMBER<13000)AUSW_MAIN_NUMBER=200000;
			//if(AUSW_MAIN_NUMBER>200000)AUSW_MAIN_NUMBER=13000;
			if((but==butR)||(but==butR_)||(but==butL)||(but==butL_))gran_ring_long(&AUSW_MAIN_NUMBER, 1L, 999999L);
		    lc640_write_int(EE_AUSW_MAIN_NUMBER,(short)(AUSW_MAIN_NUMBER&0x0000ffffUL));
			lc640_write_int(EE_AUSW_MAIN_NUMBER+2,(short)((AUSW_MAIN_NUMBER&0xffff0000UL)>>16UL));
		    speed=1;
			}
	    }   
						
	else if(sub_ind==30)
		{
		if(but==butE)
		     {
		     tree_down(-1,0);
		     ret(0);
		     }
		}		
	else if(sub_ind==31)
		{
		if(but==butE)
		     {		
			tree_up(iK_prl,0,0,0);
			parol_init();
			ret(50);
			}						
		}			
	else if(sub_ind==32)
		{
		if(but==butE)
		     {
		     tree_up(iPrltst,0,0,0);
		     parol_init();
		     }
		}			
     }		


  
else if(ind==iDef)
	{
/*
#if(UKU_VERSION==300)
#ifdef _24_
#define SIMAXIDEF 2
#else 
#define SIMAXIDEF 4
#endif
#endif
	
#if(UKU_VERSION==900)

#ifdef _24_
#define SIMAXIDEF 3
#else 
#define SIMAXIDEF 10
#endif

#endif	*/

/*
else if (ind==iDef)
	{ 
#if(UKU_VERSION==300)
#ifdef _24_
	ptrs[0]=" ����220/24-24�     ";
	ptrs[1]=" ����220/24-12�     ";
	ptrs[2]=sm_exit;
#else	
	ptrs[0]=" ����220/60-10�     ";
	ptrs[1]=" ����220/48-10�     ";
	ptrs[2]=" ����220/60-5�      ";
	ptrs[3]=" ����220/48-5�      ";
	ptrs[4]=sm_exit;
#endif
#endif	
	
#if(UKU_VERSION==900) 
#ifdef _24_
	ptrs[0]=" ����220/24-50�     ";
	ptrs[1]=" ����220/24-25�-2���";
	ptrs[2]=" ����220/24-25�-1���";	
	ptrs[3]=sm_exit;
#else		
	ptrs[0]=" ����220/60-24�     ";
	ptrs[1]=" ����220/48-24�     ";
	ptrs[2]=" ����220/60-12�-2���";
	ptrs[3]=" ����220/48-12�-2���";
	ptrs[4]=" ����220/60-12�-1���";
	ptrs[5]=" ����220/48-12�-1���";
	ptrs[6]=" ����220/48-40�     ";
	ptrs[7]=" ����220/60-30�     ";
	ptrs[8]=" ����220/48-20�-1���";
	ptrs[9]=" ����220/68-15�-1���";
	ptrs[10]=sm_exit;
#endif	
*/

#define SIMAXIDEF 16
	
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,SIMAXIDEF);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,SIMAXIDEF);
		}
	else if(but==butD_)
		{
		sub_ind=SIMAXIDEF;
		}

	else if(but==butE)
		{
		if(sub_ind==0)
			{
			def_set_1(/*ausw*/6040,/*umax*/750,/*ub0*/701,/*ub20*/681,/*usign*/540,/*imax*/120,/*imin*/80,/*uob*/600,/*numi*/2,/*kindsrc*/1000);
			
			}
		if(sub_ind==1)
			{
			def_set_1(/*ausw*/6020,/*umax*/750,/*ub0*/701,/*ub20*/681,/*usign*/540,/*imax*/250,/*imin*/80,/*uob*/600,/*numi*/2,/*kindsrc*/1000);
			
			}
		if(sub_ind==2)
			{
			def_set_1(/*ausw*/6024,/*umax*/750,/*ub0*/701,/*ub20*/681,/*usign*/540,/*imax*/72,/*imin*/48,/*uob*/600,/*numi*/2,/*kindsrc*/950);
			
			}
		if(sub_ind==3)
			{
			def_set_1(/*ausw*/6012,/*umax*/750,/*ub0*/701,/*ub20*/681,/*usign*/540,/*imax*/150,/*imin*/48,/*uob*/600,/*numi*/2,/*kindsrc*/950);
			
			}
		if(sub_ind==4)
			{
			def_set_1(/*ausw*/6012,/*umax*/750,/*ub0*/701,/*ub20*/681,/*usign*/540,/*imax*/36,/*imin*/24,/*uob*/600,/*numi*/2,/*kindsrc*/360);
			
			}
		if(sub_ind==5)
			{
			def_set_1(/*ausw*/6006,/*umax*/750,/*ub0*/701,/*ub20*/681,/*usign*/540,/*imax*/80,/*imin*/24,/*uob*/600,/*numi*/2,/*kindsrc*/360);
			
			}
		if(sub_ind==6)
			{
			def_set_1(/*ausw*/4840,/*umax*/600,/*ub0*/561,/*ub20*/545,/*usign*/432,/*imax*/120,/*imin*/80,/*uob*/480,/*numi*/2,/*kindsrc*/1000);
			
			}
		if(sub_ind==7)
			{
			def_set_1(/*ausw*/4820,/*umax*/600,/*ub0*/561,/*ub20*/545,/*usign*/432,/*imax*/250,/*imin*/80,/*uob*/480,/*numi*/2,/*kindsrc*/1000);
			
			}
		if(sub_ind==8)
			{
			def_set_1(/*ausw*/4824,/*umax*/600,/*ub0*/561,/*ub20*/545,/*usign*/432,/*imax*/72,/*imin*/48,/*uob*/480,/*numi*/2,/*kindsrc*/950);
			
			}
		if(sub_ind==9)
			{
			def_set_1(/*ausw*/4812,/*umax*/600,/*ub0*/561,/*ub20*/545,/*usign*/432,/*imax*/150,/*imin*/48,/*uob*/480,/*numi*/2,/*kindsrc*/950);
			
			}
		if(sub_ind==10)
			{
			def_set_1(/*ausw*/4812,/*umax*/600,/*ub0*/561,/*ub20*/545,/*usign*/432,/*imax*/36,/*imin*/24,/*uob*/480,/*numi*/2,/*kindsrc*/360);
			
			}
		if(sub_ind==11)
			{
			def_set_1(/*ausw*/4806,/*umax*/600,/*ub0*/561,/*ub20*/545,/*usign*/432,/*imax*/80,/*imin*/24,/*uob*/480,/*numi*/2,/*kindsrc*/360);
			
			}
		if(sub_ind==12)
			{
			def_set_1(/*ausw*/2450,/*umax*/300,/*ub0*/281,/*ub20*/272,/*usign*/216,/*imax*/150,/*imin*/100,/*uob*/240,/*numi*/2,/*kindsrc*/1000);
			
			}
		if(sub_ind==13)
			{
			def_set_1(/*ausw*/2425,/*umax*/300,/*ub0*/281,/*ub20*/272,/*usign*/216,/*imax*/300,/*imin*/100,/*uob*/240,/*numi*/2,/*kindsrc*/1000);
			
			}
		if(sub_ind==14)
			{
			def_set_1(/*ausw*/2424,/*umax*/300,/*ub0*/281,/*ub20*/272,/*usign*/216,/*imax*/72,/*imin*/48,/*uob*/240,/*numi*/2,/*kindsrc*/360);
			
			}
		if(sub_ind==15)
			{
			def_set_1(/*ausw*/2412,/*umax*/300,/*ub0*/281,/*ub20*/272,/*usign*/216,/*imax*/150,/*imin*/48,/*uob*/240,/*numi*/2,/*kindsrc*/360);
			
			}

		if(sub_ind==SIMAXIDEF)
			{
               //a=b[--ptr_ind];
        	tree_down(0,0);
			}
		default_temp=sub_ind;
		}
/*	
#if(UKU_VERSION==900)

#ifdef _24_
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			def_set(300,282,273,220,160,240,2);
			lc640_write_int(EE_AUSW_MAIN,2450);
			}
		else if(sub_ind==1)
			{
			def_set(300,282,273,220,320,240,2);
			lc640_write_int(EE_AUSW_MAIN,2425);
			}	
		else if(sub_ind==2)
			{
			def_set(300,282,273,220,160,240,1);
			lc640_write_int(EE_AUSW_MAIN,2425);
			}				
		else if(sub_ind==SIMAXIDEF)
			{
               //a=b[--ptr_ind];
               tree_down(0,0);
			}
		default_temp=sub_ind;	
		}
#else		
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			def_set(750,705,681,550,80,600,2);
			lc640_write_int(EE_AUSW_MAIN,6024);

			}
		else if(sub_ind==1)
			{
			def_set(600,564,545,440,80,480,2);
			lc640_write_int(EE_AUSW_MAIN,4824);
			}	
		else if(sub_ind==2)
			{
			def_set(750,705,681,550,300,600,2);
			lc640_write_int(EE_AUSW_MAIN,6012);
			}
		else if(sub_ind==3)
			{
			def_set(600,564,545,440,300,480,2);
			lc640_write_int(EE_AUSW_MAIN,4812);
			}				
		else if(sub_ind==4)
			{
			def_set(750,705,681,550,80,600,1);
			lc640_write_int(EE_AUSW_MAIN,6012);
			}
		else if(sub_ind==5)
			{
			def_set(600,564,545,440,800,480,1);
			lc640_write_int(EE_AUSW_MAIN,4812);
			}	
		else if(sub_ind==6)
			{
			def_set(600,564,545,440,80,480,2);
			lc640_write_int(EE_AUSW_MAIN,4840);
			}		
		else if(sub_ind==7)
			{
			def_set(750,705,681,550,80,600,2);
			lc640_write_int(EE_AUSW_MAIN,6030);
			}	
		else if(sub_ind==8)
			{
			def_set(600,564,545,440,800,480,1);
			lc640_write_int(EE_AUSW_MAIN,4820);
			}	
		else if(sub_ind==9)
			{
			def_set(750,705,681,550,80,600,1);
			lc640_write_int(EE_AUSW_MAIN,6015);
			}												
		else if(sub_ind==SIMAXIDEF)
			{
			//a=b[--ptr_ind];
			tree_down(0,0);
			ret(0);
			}
		default_temp=sub_ind;	
		}
#endif		
#endif   

#if(UKU_VERSION==300)
#ifdef _24_
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			def_set(300,282,273,220,60,240,2);
			lc640_write_int(EE_AUSW_MAIN,2424);
			}
		else if(sub_ind==1)
			{
			def_set(300,282,273,220,60,240,1);
			lc640_write_int(EE_AUSW_MAIN,2412);
			}	
		else if(sub_ind==SIMAXIDEF)
			{
               //a=b[--ptr_ind];
               tree_down(0,0);
			}
		default_temp=sub_ind;	
		}
#else
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			def_set(750,705,681,550,30,600,2);
			lc640_write_int(EE_AUSW_MAIN,6010);
			}
		else if(sub_ind==1)
			{
			def_set(600,564,545,440,30,480,2);
			lc640_write_int(EE_AUSW_MAIN,4810);
			}	
		else if(sub_ind==2)
			{
			def_set(750,705,681,550,30,600,1);
			lc640_write_int(EE_AUSW_MAIN,6005);
			}	
		else if(sub_ind==3)
			{
			def_set(600,564,545,440,30,480,1);
			lc640_write_int(EE_AUSW_MAIN,4805);
			}	

		default_temp=sub_ind;	
		}
#endif				
#endif    	     			
*/		
/*	else if(sub_ind==SIMAXIDEF)
	     {
	     if(but==butE)
	          {
	          a=b[--ptr_ind];
	          }
	     }	*/



	}
	     
else if(ind==iStr)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butD_)
		{
		sub_ind=5;
		}				
	else if(sub_ind==0)
	     {
	     if(NUMBAT==0)lc640_write_int(EE_NUMBAT,1);
	     else lc640_write_int(EE_NUMBAT,0);
	     }	
     else if(sub_ind==1)
	     {
	     if(NUMIST==1)lc640_write_int(EE_NUMIST,2);
	     else lc640_write_int(EE_NUMIST,1);
          }	
     else if(sub_ind==2)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMDT++;
	     	gran(&NUMDT,0,3);
	     	lc640_write_int(EE_NUMDT,NUMDT);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMDT--;
	     	gran(&NUMDT,0,3);
	     	lc640_write_int(EE_NUMDT,NUMDT);
	     	}
          }	
     else if(sub_ind==3)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMSK++;
	     	gran(&NUMSK,0,4);
	     	lc640_write_int(EE_NUMSK,NUMSK);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMSK--;
	     	gran(&NUMSK,0,4);
	     	lc640_write_int(EE_NUMSK,NUMSK);
	     	}
          }	  
     else if(sub_ind==4)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	KINDSRC++;
	     	gran(&KINDSRC,1,3);
	     	lc640_write_int(EE_KINDSRC,KINDSRC);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	KINDSRC--;
	     	gran(&KINDSRC,1,3);
	     	lc640_write_int(EE_KINDSRC,KINDSRC);
	     	}
          }	   		                 
    else if(sub_ind==5)
	     {
	     if(but==butE)
	          {
			tree_down(0,0);
	          }
          }	          
	}     

else if (ind==iLan_set)
	{
	char si_max;
	ret(1000);

	si_max=1;
	if(ETH_IS_ON!=0)si_max=23;

	if(but==butD)
		{
		sub_ind++;

		if((sub_ind==2)&&(index_set==0))
			{
			index_set=1;
			sub_ind1=0;
			}
		if(sub_ind==3) 
			{
			sub_ind=4;
			index_set=3;
			sub_ind1=0;
			}
		if(sub_ind==5) 
			{
			sub_ind=6;
			index_set=5;
			sub_ind1=0;
			}
		if(sub_ind==7) 
			{
			sub_ind=8;
			//index_set=3;
			sub_ind1=0;
			}
		if(sub_ind==10) 
			{
			//sub_ind=6;
			//index_set=9;
			sub_ind1=0;
			}
		if(sub_ind==11) 
			{
			//sub_ind=6;
			index_set=10;
			sub_ind1=0;
			}
		if(sub_ind==12) 
			{
			sub_ind++;
			}
		if(sub_ind==13) 
			{
			//sub_ind=6;
			index_set=12;
			sub_ind1=0;
			}
		if(sub_ind==14) 
			{
			sub_ind++;
			}
		if(sub_ind==15) 
			{
			//sub_ind=6;
			index_set=14;
			sub_ind1=0;
			}
		if(sub_ind==16) 
			{
			sub_ind++;
			}
		if(sub_ind==17) 
			{
			//sub_ind=6;
			index_set=16;
			sub_ind1=0;
			}
		if(sub_ind==18) 
			{
			sub_ind++;
			}
		if(sub_ind==19) 
			{
			//sub_ind=6;
			index_set=18;
			sub_ind1=0;
			}
		if(sub_ind==20) 
			{
			sub_ind++;
			}
		if(sub_ind==21) 
			{
			//sub_ind=6;
			index_set=20;
			sub_ind1=0;
			}
		if(sub_ind==22) 
			{
			sub_ind++;
			}
		
		gran_char(&sub_ind,0,si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,si_max);
		if(sub_ind==22) 
			{
			sub_ind--;
			}
		if(sub_ind==20) 
			{
			sub_ind--;
			}		
		if(sub_ind==18) 
			{
			sub_ind--;
			}		
		if(sub_ind==16) 
			{
			sub_ind--;
			}
		if(sub_ind==14) 
			{
			sub_ind--;
			}
		if(sub_ind==12) 
			{
			sub_ind--;
			}
		if(sub_ind==7) 
			{
			sub_ind--;
			}
		if(sub_ind==5) 
			{
			sub_ind--;
			}
		if(sub_ind==3) 
			{
			sub_ind--;
			}
		}
	else if(but==butD_)
		{
		sub_ind=si_max;
		}
	else if(but==butLR_)
		{
		lc640_write_int(EE_ETH_IS_ON,1);
		lc640_write_int(EE_ETH_DHCP_ON,0);
		lc640_write_int(EE_ETH_IP_1,192);
		lc640_write_int(EE_ETH_IP_2,168);
		lc640_write_int(EE_ETH_IP_3,1);
		lc640_write_int(EE_ETH_IP_4,61);
		lc640_write_int(EE_ETH_MASK_4,0);
		lc640_write_int(EE_ETH_MASK_2,255);
		lc640_write_int(EE_ETH_MASK_3,255);
		lc640_write_int(EE_ETH_MASK_1,255);
		lc640_write_int(EE_ETH_GW_1,192);
		lc640_write_int(EE_ETH_GW_2,168);
		lc640_write_int(EE_ETH_GW_3,1);
		lc640_write_int(EE_ETH_GW_4,254);
		lc640_write_int(EE_ETH_SNMP_PORT_READ,161);
		lc640_write_int(EE_ETH_SNMP_PORT_WRITE,162);
		lc640_write_int(EE_COMMUNITY,'p');
		lc640_write_int(EE_COMMUNITY+2,'u');
		lc640_write_int(EE_COMMUNITY+4,'b');
		lc640_write_int(EE_COMMUNITY+6,'l');
		lc640_write_int(EE_COMMUNITY+8,'i');
		lc640_write_int(EE_COMMUNITY+10,'c');
		lc640_write_int(EE_COMMUNITY+12,0);
		lc640_write_int(EE_COMMUNITY+14,0);
		lc640_write_int(EE_ETH_TRAP1_IP_1,255);
		lc640_write_int(EE_ETH_TRAP1_IP_2,255);
		lc640_write_int(EE_ETH_TRAP1_IP_3,255);
		lc640_write_int(EE_ETH_TRAP1_IP_4,255);
		lc640_write_int(EE_ETH_TRAP2_IP_1,255);
		lc640_write_int(EE_ETH_TRAP2_IP_2,255);
		lc640_write_int(EE_ETH_TRAP2_IP_3,255);
		lc640_write_int(EE_ETH_TRAP2_IP_4,255);
		lc640_write_int(EE_ETH_TRAP3_IP_1,255);
		lc640_write_int(EE_ETH_TRAP3_IP_2,255);
		lc640_write_int(EE_ETH_TRAP3_IP_3,255);
		lc640_write_int(EE_ETH_TRAP3_IP_4,255);
		lc640_write_int(EE_ETH_TRAP4_IP_1,255);
		lc640_write_int(EE_ETH_TRAP4_IP_2,255);
		lc640_write_int(EE_ETH_TRAP4_IP_3,255);
		lc640_write_int(EE_ETH_TRAP4_IP_4,255);
		lc640_write_int(EE_ETH_TRAP5_IP_1,255);
		lc640_write_int(EE_ETH_TRAP5_IP_2,255);
		lc640_write_int(EE_ETH_TRAP5_IP_3,255);
		lc640_write_int(EE_ETH_TRAP5_IP_4,255);
		str_copy(place_holder,"                                                                      ");
		for (i=0;i<70;i++)lc640_write(EE_HTTP_LOCATION+i,place_holder[i]);
		}						
	else if(sub_ind==0)
	     {
	     if((but==butE)||(but==butL)||(but==butR))
	     	{
	     	if(ETH_IS_ON)lc640_write_int(EE_ETH_IS_ON,0);
			else lc640_write_int(EE_ETH_IS_ON,1);
	     	}
	     }	
     else if((sub_ind==1)&&(ETH_IS_ON))
	     {
		if((but==butE)||(but==butL)||(but==butR))
	     	{
	     	if(ETH_DHCP_ON)lc640_write_int(EE_ETH_DHCP_ON,0);
			else lc640_write_int(EE_ETH_DHCP_ON,1);
	     	}
		}	
     else if(sub_ind==2)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_1++;
				gran_ring(&ETH_IP_1,0,255);
				lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_1--;
				gran_ring(&ETH_IP_1,0,255);
				lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_2++;
				gran_ring(&ETH_IP_2,0,255);
				lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_2--;
				gran_ring(&ETH_IP_2,0,255);
				lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_3++;
				gran_ring(&ETH_IP_3,0,255);
				lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_3--;
				gran_ring(&ETH_IP_3,0,255);
				lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_4++;
				gran_ring(&ETH_IP_4,0,255);
				lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_4--;
				gran_ring(&ETH_IP_4,0,255);
				lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
				}
			speed=1;
			}

          }
     else if(sub_ind==4)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_1++;
				gran_ring(&ETH_MASK_1,0,255);
				lc640_write_int(EE_ETH_MASK_1,ETH_MASK_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_1--;
				gran_ring(&ETH_MASK_1,0,255);
				lc640_write_int(EE_ETH_MASK_1,ETH_MASK_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_2++;
				gran_ring(&ETH_MASK_2,0,255);
				lc640_write_int(EE_ETH_MASK_2,ETH_MASK_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_2--;
				gran_ring(&ETH_MASK_2,0,255);
				lc640_write_int(EE_ETH_MASK_2,ETH_MASK_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_3++;
				gran_ring(&ETH_MASK_3,0,255);
				lc640_write_int(EE_ETH_MASK_3,ETH_MASK_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_3--;
				gran_ring(&ETH_MASK_3,0,255);
				lc640_write_int(EE_ETH_MASK_3,ETH_MASK_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_4++;
				gran_ring(&ETH_MASK_4,0,255);
				lc640_write_int(EE_ETH_MASK_4,ETH_MASK_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_4--;
				gran_ring(&ETH_MASK_4,0,255);
				lc640_write_int(EE_ETH_MASK_4,ETH_MASK_4);
				}
			speed=1;
			}
		}
     else if(sub_ind==6)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_1++;
				gran_ring(&ETH_GW_1,0,255);
				lc640_write_int(EE_ETH_GW_1,ETH_GW_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_1--;
				gran_ring(&ETH_GW_1,0,255);
				lc640_write_int(EE_ETH_GW_1,ETH_GW_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_2++;
				gran_ring(&ETH_GW_2,0,255);
				lc640_write_int(EE_ETH_GW_2,ETH_GW_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_2--;
				gran_ring(&ETH_GW_2,0,255);
				lc640_write_int(EE_ETH_GW_2,ETH_GW_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_3++;
				gran_ring(&ETH_GW_3,0,255);
				lc640_write_int(EE_ETH_GW_3,ETH_GW_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_3--;
				gran_ring(&ETH_GW_3,0,255);
				lc640_write_int(EE_ETH_GW_3,ETH_GW_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_4++;
				gran_ring(&ETH_GW_4,0,255);
				lc640_write_int(EE_ETH_GW_4,ETH_GW_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_4--;
				gran_ring(&ETH_GW_4,0,255);
				lc640_write_int(EE_ETH_GW_4,ETH_GW_4);
				}
			speed=1;
			}
		}
      else if(sub_ind==8)
	     {
		if(but==butR)ETH_SNMP_PORT_READ++;
		else if(but==butR_)ETH_SNMP_PORT_READ+=10;
		else if(but==butL)ETH_SNMP_PORT_READ--;
		else if(but==butL_)ETH_SNMP_PORT_READ-=10;
		speed=1;
		lc640_write_int(EE_ETH_SNMP_PORT_READ,ETH_SNMP_PORT_READ);
		}

     else if(sub_ind==9)
	     {
		if(but==butR)ETH_SNMP_PORT_WRITE++;
		else if(but==butR_)ETH_SNMP_PORT_WRITE+=10;
		else if(but==butL)ETH_SNMP_PORT_WRITE--;
		else if(but==butL_)ETH_SNMP_PORT_WRITE-=10;
		speed=1;
		lc640_write_int(EE_ETH_SNMP_PORT_WRITE,ETH_SNMP_PORT_WRITE);
		}					
     else if(sub_ind==10)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,8);
	     	}
		if((but==butR)||(but==butR_))
			{
			snmp_community[sub_ind1]++;
			if(snmp_community[sub_ind1]<32) snmp_community[sub_ind1]=32;
			else if ((snmp_community[sub_ind1]>32)&&(snmp_community[sub_ind1]<48)) snmp_community[sub_ind1]=48;
			else if ((snmp_community[sub_ind1]>57)&&(snmp_community[sub_ind1]<65)) snmp_community[sub_ind1]=65;
			else if ((snmp_community[sub_ind1]>90)&&(snmp_community[sub_ind1]<97)) snmp_community[sub_ind1]=97;
			else if (snmp_community[sub_ind1]>122) snmp_community[sub_ind1]=32;
				//gran_ring(&ETH_GW_1,0,255);
			lc640_write_int(EE_COMMUNITY+(sub_ind1*2),snmp_community[sub_ind1]);
			speed=1;
			}
		if((but==butL)||(but==butL_))
			{
			snmp_community[sub_ind1]--;
			if(snmp_community[sub_ind1]<32) snmp_community[sub_ind1]=122;
			else if ((snmp_community[sub_ind1]>32)&&(snmp_community[sub_ind1]<48)) snmp_community[sub_ind1]=32;
			else if ((snmp_community[sub_ind1]>57)&&(snmp_community[sub_ind1]<65)) snmp_community[sub_ind1]=57;
			else if ((snmp_community[sub_ind1]>90)&&(snmp_community[sub_ind1]<97)) snmp_community[sub_ind1]=90;
			else if (snmp_community[sub_ind1]>122) snmp_community[sub_ind1]=122;
			//gran_ring(&ETH_GW_1,0,255);
			lc640_write_int(EE_COMMUNITY+(sub_ind1*2),snmp_community[sub_ind1]);
			speed=1;
			}
		}
 
     else if(sub_ind==11)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_1++;
				gran_ring(&ETH_TRAP1_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_1,ETH_TRAP1_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_1--;
				gran_ring(&ETH_TRAP1_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_1,ETH_TRAP1_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_2++;
				gran_ring(&ETH_TRAP1_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_2,ETH_TRAP1_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_2--;
				gran_ring(&ETH_TRAP1_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_2,ETH_TRAP1_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_3++;
				gran_ring(&ETH_TRAP1_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_3,ETH_TRAP1_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_3--;
				gran_ring(&ETH_TRAP1_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_3,ETH_TRAP1_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_4++;
				gran_ring(&ETH_TRAP1_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_4,ETH_TRAP1_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_4--;
				gran_ring(&ETH_TRAP1_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_4,ETH_TRAP1_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==13)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_1++;
				gran_ring(&ETH_TRAP2_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_1,ETH_TRAP2_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_1--;
				gran_ring(&ETH_TRAP2_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_1,ETH_TRAP2_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_2++;
				gran_ring(&ETH_TRAP2_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_2,ETH_TRAP2_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_2--;
				gran_ring(&ETH_TRAP2_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_2,ETH_TRAP2_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_3++;
				gran_ring(&ETH_TRAP2_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_3,ETH_TRAP2_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_3--;
				gran_ring(&ETH_TRAP2_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_3,ETH_TRAP2_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_4++;
				gran_ring(&ETH_TRAP2_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_4,ETH_TRAP2_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_4--;
				gran_ring(&ETH_TRAP2_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_4,ETH_TRAP2_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==15)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_1++;
				gran_ring(&ETH_TRAP3_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_1,ETH_TRAP3_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_1--;
				gran_ring(&ETH_TRAP3_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_1,ETH_TRAP3_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_2++;
				gran_ring(&ETH_TRAP3_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_2,ETH_TRAP3_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_2--;
				gran_ring(&ETH_TRAP3_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_2,ETH_TRAP3_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_3++;
				gran_ring(&ETH_TRAP3_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_3,ETH_TRAP3_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_3--;
				gran_ring(&ETH_TRAP3_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_3,ETH_TRAP3_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_4++;
				gran_ring(&ETH_TRAP3_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_4,ETH_TRAP3_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_4--;
				gran_ring(&ETH_TRAP3_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_4,ETH_TRAP3_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==17)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_1++;
				gran_ring(&ETH_TRAP4_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_1,ETH_TRAP4_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_1--;
				gran_ring(&ETH_TRAP4_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_1,ETH_TRAP4_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_2++;
				gran_ring(&ETH_TRAP4_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_2,ETH_TRAP4_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_2--;
				gran_ring(&ETH_TRAP4_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_2,ETH_TRAP4_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_3++;
				gran_ring(&ETH_TRAP4_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_3,ETH_TRAP4_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_3--;
				gran_ring(&ETH_TRAP4_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_3,ETH_TRAP4_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_4++;
				gran_ring(&ETH_TRAP4_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_4,ETH_TRAP4_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_4--;
				gran_ring(&ETH_TRAP4_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_4,ETH_TRAP4_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==19)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_1++;
				gran_ring(&ETH_TRAP5_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_1,ETH_TRAP5_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_1--;
				gran_ring(&ETH_TRAP5_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_1,ETH_TRAP5_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_2++;
				gran_ring(&ETH_TRAP5_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_2,ETH_TRAP5_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_2--;
				gran_ring(&ETH_TRAP5_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_2,ETH_TRAP5_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_3++;
				gran_ring(&ETH_TRAP5_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_3,ETH_TRAP5_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_3--;
				gran_ring(&ETH_TRAP5_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_3,ETH_TRAP5_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_4++;
				gran_ring(&ETH_TRAP5_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_4,ETH_TRAP5_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_4--;
				gran_ring(&ETH_TRAP5_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_4,ETH_TRAP5_IP_4);
				}
			speed=1;
			}
		}
	else if(sub_ind==21)
	    {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,2);
	     	}
		if((but==butR)||(but==butR_))
			{
			snmp_web_passw[sub_ind1]++;
			if(snmp_web_passw[sub_ind1]<32) snmp_web_passw[sub_ind1]=32;
			else if ((snmp_web_passw[sub_ind1]>32)&&(snmp_web_passw[sub_ind1]<48)) snmp_web_passw[sub_ind1]=48;
			else if ((snmp_web_passw[sub_ind1]>57)&&(snmp_web_passw[sub_ind1]<65)) snmp_web_passw[sub_ind1]=65;
			else if ((snmp_web_passw[sub_ind1]>90)&&(snmp_web_passw[sub_ind1]<97)) snmp_web_passw[sub_ind1]=97;
			else if (snmp_web_passw[sub_ind1]>122) snmp_web_passw[sub_ind1]=32;
				//gran_ring(&ETH_GW_1,0,255);
			lc640_write_int(EE_WEB_PASSWORD+(sub_ind1*2),snmp_web_passw[sub_ind1]);
			speed=1;
			}
		if((but==butL)||(but==butL_))
			{
			snmp_web_passw[sub_ind1]--;
			if(snmp_web_passw[sub_ind1]<32) snmp_web_passw[sub_ind1]=122;
			else if ((snmp_web_passw[sub_ind1]>32)&&(snmp_web_passw[sub_ind1]<48)) snmp_web_passw[sub_ind1]=32;
			else if ((snmp_web_passw[sub_ind1]>57)&&(snmp_web_passw[sub_ind1]<65)) snmp_web_passw[sub_ind1]=57;
			else if ((snmp_web_passw[sub_ind1]>90)&&(snmp_web_passw[sub_ind1]<97)) snmp_web_passw[sub_ind1]=90;
			else if (snmp_web_passw[sub_ind1]>122) snmp_web_passw[sub_ind1]=122;
			//gran_ring(&ETH_GW_1,0,255);
			lc640_write_int(EE_WEB_PASSWORD+(sub_ind1*2),snmp_web_passw[sub_ind1]);
			speed=1;
			}
		}															          
															          
    else if(sub_ind==si_max)
	     {
	     if(but==butE)
	          {
	          tree_down(0,0);
	          }
          }	          	
	}

else if (ind==iExt_set)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,7);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,7);
		}
	else if(but==butD_)
		{
		sub_ind=7;
		}				
	else if(sub_ind==0)
	     {
	     if(but==butE)
	     	{
	     	tree_up(iExt_dt,1,0,0);
	     	}
	     }	
     else if(sub_ind==3)
	     {
		if(but==butE)
	     	{
	     	tree_up(iExt_sk,1,0,0);
	     	}
          }	
     else if(sub_ind==4)
	     {
		if(but==butE)
	     	{
	     	tree_up(iExt_sk,1,0,1);
	     	}
          }	          
    else if(sub_ind==7)
	     {
	     if(but==butE)
	          {
	          tree_down(0,0);
	          }
          }	          	
	}
	
else if (ind==iExt_dt)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,1,7);
		}
	else if(but==butU)
		{
		if(sub_ind==1)index_set=0;
		else sub_ind--;
		gran_char(&sub_ind,1,7);
		}	
	else if(but==butD_)
		{
		sub_ind=7;
		}			
		
	else if(sub_ind==1) 
		{
		if(but==butE)
			{
			if(!TMAX_EXT_EN[sub_ind1])lc640_write_int(ADR_TMAX_EXT_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_TMAX_EXT_EN[sub_ind1],0);
			}
		else if((but==butR)||(but==butR_))
			{
			TMAX_EXT[sub_ind1]++;
			}	
		else if((but==butL)||(but==butL_))
			{
			TMAX_EXT[sub_ind1]--;
			}	
		gran(&TMAX_EXT[sub_ind1],-50,100);
		if(lc640_read_int(ADR_TMAX_EXT[sub_ind1])!=TMAX_EXT[sub_ind1]) lc640_write_int(ADR_TMAX_EXT[sub_ind1],TMAX_EXT[sub_ind1]);			
		speed=1;
		}
	else if(sub_ind==2) 
		{
		if(but==butE)
			{
			if(!TMIN_EXT_EN[sub_ind1])lc640_write_int(ADR_TMIN_EXT_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_TMIN_EXT_EN[sub_ind1],0);
			}
		else if((but==butR)||(but==butR_))
			{
			TMIN_EXT[sub_ind1]++;
			}	
		else if((but==butL)||(but==butL_))
			{
			TMIN_EXT[sub_ind1]--;
			}	
		gran(&TMIN_EXT[sub_ind1],-50,100);
		if(lc640_read_int(ADR_TMIN_EXT[sub_ind1])!=TMIN_EXT[sub_ind1]) lc640_write_int(ADR_TMIN_EXT[sub_ind1],TMIN_EXT[sub_ind1]);			
		speed=1;
		}		
	else if(sub_ind==3) 
		{
		if(but==butE)
			{
			if(!T_EXT_REL_EN[sub_ind1])lc640_write_int(ADR_T_EXT_REL_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_T_EXT_REL_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==4) 
		{
		if(but==butE)
			{
			if(!T_EXT_ZVUK_EN[sub_ind1])lc640_write_int(ADR_T_EXT_ZVUK_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_T_EXT_ZVUK_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==5) 
		{
		if(but==butE)
			{
			if(!T_EXT_LCD_EN[sub_ind1])lc640_write_int(ADR_T_EXT_LCD_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_T_EXT_LCD_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==6) 
		{
		if(but==butE)
			{
			if(!T_EXT_RS_EN[sub_ind1])lc640_write_int(ADR_T_EXT_RS_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_T_EXT_RS_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==7) 
		{
		if(but==butE)
			{
			tree_down(0,0);
			//a=b[--ptr_ind];
			}
		}												
	}	

else if (ind==iExt_sk)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if(sub_ind==2)sub_ind=3;
		gran_char(&sub_ind,1,7);
		
		}
	else if(but==butU)
		{
		if(sub_ind==1)index_set=0;
		else sub_ind--;
		if(sub_ind==2)sub_ind=1;
		gran_char(&sub_ind,1,7);
		}	
	else if(but==butD_)
		{
		sub_ind=7;
		}			
	else if(sub_ind==1) 
		{
		if(but==butE)
			{
			if(!SK_SIGN[sub_ind1])lc640_write_int(ADR_SK_SIGN[sub_ind1],0xffff);
			else lc640_write_int(ADR_SK_SIGN[sub_ind1],0);
			}
		}
	else if(sub_ind==3) 
		{
		if(but==butE)
			{
			if(!SK_REL_EN[sub_ind1])lc640_write_int(ADR_SK_REL_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_SK_REL_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==4) 
		{
		if(but==butE)
			{
			if(!SK_ZVUK_EN[sub_ind1])lc640_write_int(ADR_SK_ZVUK_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_SK_ZVUK_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==5) 
		{
		if(but==butE)
			{
			if(!SK_LCD_EN[sub_ind1])lc640_write_int(ADR_SK_LCD_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_SK_LCD_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==6) 
		{
		if(but==butE)
			{
			if(!SK_RS_EN[sub_ind1])lc640_write_int(ADR_SK_RS_EN[sub_ind1],0xffff);
			else lc640_write_int(ADR_SK_RS_EN[sub_ind1],0);
			}
		}	
	else if(sub_ind==7) 
		{
		if(but==butE)
			{
			//a=b[--ptr_ind];
			tree_down(0,0);
			}
		}												
	}	
			
else if(ind==iApv)
     {
     ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,simax);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,simax);
		}
	else if(but==butD_)
		{
		sub_ind=simax;
		}			
	else if(but==butE)
	     {
	     if(sub_ind==simax)
	          {
	          //a=b[--ptr_ind];
	          tree_down(0,0);
	          }
	     else if(sub_ind==0)   
	          {
	          if(apv_on1==apvON)lc640_write_int(EE_APV_ON1,apvOFF);
	          else lc640_write_int(EE_APV_ON1,apvON);
	          }
          else if((sub_ind==1)&&(apv_on1==apvON))   
	          {
	          if(apv_on2==apvON)lc640_write_int(EE_APV_ON2,apvOFF);
	          else lc640_write_int(EE_APV_ON2,apvON);
	          }	 
          }
     
     else if((sub_ind==2)&&(apv_on2==apvON))   
          {
	     if((but==butR)||(but==butR_))
	          {
	          signed short tempSS;
	          tempSS=apv_on2_time;
	          tempSS++;
	          gran/*_ring*/(&tempSS,1,24);
	          lc640_write_int(EE_APV_ON2_TIME,tempSS);
	          }
          else if((but==butL)||(but==butL_))
	          {
	          signed short tempSS;
	          tempSS=apv_on2_time;
	          tempSS--;
	          gran/*_ring*/(&tempSS,1,24);
	          lc640_write_int(EE_APV_ON2_TIME,tempSS);
	          }	          
	     speed=1;
	     }		
     } 


else if(ind==iSet_T)
	{
	signed char temp;
	if(but==butR)
		{
		sub_ind++;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butL)
		{
		sub_ind--;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butE)
		{
		a=b[--ptr_ind];
		}	
	else if(sub_ind==0)
	     {
	     temp=LPC_RTC->HOUR;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,0,23);
			LPC_RTC->HOUR=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,0,23);
			LPC_RTC->HOUR=temp;
	          }	
	     speed=1;               
	     }
     else if(sub_ind==1)
	     {
	     temp=LPC_RTC->MIN;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,0,59);
			LPC_RTC->MIN=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,0,59);
			LPC_RTC->MIN=temp;
	          }	
	     speed=1;               
	     }
     else if(sub_ind==2)
	     {
	     if((but==butU)||(but==butU_))
	          {
	          LPC_RTC->SEC=0;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          LPC_RTC->SEC=0;
	          }	
	     speed=1;               
	     }

     else if(sub_ind==3)
	     {
	     temp=LPC_RTC->DOM;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,1,31);
	          LPC_RTC->DOM=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,1,31);
	          LPC_RTC->DOM=temp;
	          }	
	     speed=1;               
	     }
     else if(sub_ind==4)
	     {
	     temp=LPC_RTC->MONTH;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,1,12);
	          LPC_RTC->MONTH=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,1,12);
	          LPC_RTC->MONTH=temp;
	          }	
	     speed=1;               
	     }	  
     else if(sub_ind==5)
	     {
	     temp=LPC_RTC->YEAR;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,0,99);
	          LPC_RTC->YEAR=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,0,99);
	          LPC_RTC->YEAR=temp;
	          }	
	     speed=1;               
	     }		        
	}

else if(ind==iSet_T_avt)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if(SNTP_ENABLE==0)gran_char(&sub_ind,0,1);
		else gran_char(&sub_ind,0,5);
		if(sub_ind==2)
			{
			index_set=2;
			}
		if(sub_ind==3)
			{
			sub_ind=4; 
			index_set=3;
			}
		}
	else if(but==butU)
		{
		sub_ind--;
		if(SNTP_ENABLE==0)gran_char(&sub_ind,0,1);
		else gran_char(&sub_ind,0,5);
		if(sub_ind==3)
			{
			sub_ind=2;
			index_set=2;
			} 
		}
	else if(sub_ind==0)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	SNTP_ENABLE++;
	     	gran(&SNTP_ENABLE,0,3);
	     	lc640_write_int(EE_SNTP_ENABLE,SNTP_ENABLE);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	SNTP_ENABLE--;
	     	gran(&SNTP_ENABLE,0,3);
	     	lc640_write_int(EE_SNTP_ENABLE,SNTP_ENABLE);
	     	}
          }
	else if(sub_ind==1)
		{
		if(SNTP_ENABLE==0)
		 	{
			if(but==butE)
	          	{
				tree_down(0,0);
	          	}
			}
		else 
			{
	     	if((but==butR)||(but==butR_))
	     		{
	     		SNTP_GMT++;
	     		gran(&SNTP_GMT,-12,13);
	     		lc640_write_int(EE_SNTP_GMT,SNTP_GMT);
	     		}
	     
	     	else if((but==butL)||(but==butL_))
	     		{
	     		SNTP_GMT--;
	     		gran(&SNTP_GMT,-12,13);
	     		lc640_write_int(EE_SNTP_GMT,SNTP_GMT);
	     		}
			}
		}	     			  
	else if(sub_ind==2)
		{
		if(but==butE)
	     	{
	     	if(lc640_read_int(EE_SNTP_WEB_ENABLE)==1)lc640_write_int(EE_SNTP_WEB_ENABLE,0);
			else lc640_write_int(EE_SNTP_WEB_ENABLE,1);
	     	}
		else if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			short _temp;
			if((but==butR)||(but==butR_))
				{
				_temp=lc640_read_int(EE_SNTP_IP1);
				_temp++;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP1,_temp);
				}
			else if((but==butL)||(but==butL_))
				{
				_temp=lc640_read_int(EE_SNTP_IP1);
				_temp--;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP1,_temp);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			short _temp;
			if((but==butR)||(but==butR_))
				{
				_temp=lc640_read_int(EE_SNTP_IP2);
				_temp++;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP2,_temp);
				}
			else if((but==butL)||(but==butL_))
				{
				_temp=lc640_read_int(EE_SNTP_IP2);
				_temp--;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP2,_temp);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			short _temp;
			if((but==butR)||(but==butR_))
				{
				_temp=lc640_read_int(EE_SNTP_IP3);
				_temp++;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP3,_temp);
				}
			else if((but==butL)||(but==butL_))
				{
				_temp=lc640_read_int(EE_SNTP_IP3);
				_temp--;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP3,_temp);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			short _temp;
			if((but==butR)||(but==butR_))
				{
				_temp=lc640_read_int(EE_SNTP_IP4);
				_temp++;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP4,_temp);
				}
			else if((but==butL)||(but==butL_))
				{
				_temp=lc640_read_int(EE_SNTP_IP4);
				_temp--;
				gran_ring(&_temp,0,255);
				lc640_write_int(EE_SNTP_IP4,_temp);
				}
			speed=1;
			}
    	}
     else if(sub_ind==4)
		{
		if(but==butE_)
	        {
			if(lc640_read_int(EE_SNTP_WEB_ENABLE)==1)
				{
				Rem_IP[0]=SNTP_IP1;
				Rem_IP[1]=SNTP_IP2;
				Rem_IP[2]=SNTP_IP3;
				Rem_IP[3]=SNTP_IP4;
				}
			else
				{
				Rem_IP[0]=(char)lc640_read_int(EE_SNTP_IP1);
				Rem_IP[1]=(char)lc640_read_int(EE_SNTP_IP2);
				Rem_IP[2]=(char)lc640_read_int(EE_SNTP_IP3);
				Rem_IP[3]=(char)lc640_read_int(EE_SNTP_IP4);
				}
			sntp_requ();
	        }
		}	
     else if(sub_ind==5)
		{

			if(but==butE)
	          	{
				tree_down(0,0);
	          	}
	
		}					          
	}     
	     	
else if (ind==iTst)
	{
	ret(1000);
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
 	else if (sub_ind==0)
		{
		if(but==butE)
			{
 			if(tst_state[0]!=tstOFF)tst_state[0]=tstOFF;
 			else tst_state[0]=tstON;
   			}
		 }   
 	else if (sub_ind==1)
		{
		if (but==butE)
			{
			tree_up(iTst_klbr,0,0,0);
			ret(1000);
   			}
		 }
    else if (sub_ind==2)
		{
		if (but==butE)
			{
			tree_up(iTst_BPS1,0,0,0);
			ret(1000);
			cnt_src[1]=10;
   			}
		}	

    else if (sub_ind==3)
		{
		if (but==butE)
			{
			tree_up(iTst_BPS2,0,0,0);
			ret(1000);
			cnt_src[1]=10;	
   			}
		}
		
    else if (sub_ind==4)
		{
		if (but==butE)
			{
			tree_up(iTst_BPS12,0,0,0);	
			ret(1000);
   			}
		}
   else if (sub_ind==5)
		{
		if (but==butE)
			{
			bRESET=1;
			}
		}		
    else if (sub_ind==6)
		{
		speed=1; 
		if(but==butE)
			{
             	tree_down(0,0);
             	ret(0);
               St&=0xf8;
           	St_[0]&=0x01;
			St_[1]&=0x01;
			avar_bat_hndl(0);
			avar_unet_hndl(0);
			avar_src_reset(0);
			avar_src_reset(1);
   			}
		}			
  
     	
     	
 		
	}

else if (ind==iTst_klbr)
	{
	ret(1000);
	if(but==butU)
     	{
    		sub_ind=0;
       	}
 	else if(but==butD)
     	{
     	sub_ind=2;
     	}
	else if(but==butD_)
		{
		sub_ind=2;
		}		     	
 	else if (sub_ind==0)
		{
		if (but==butE)
			{
 	          if(tst_state[1]!=tstOFF)tst_state[1]=tstOFF;
 			else tst_state[1]=tstON;
   			}
		 }
 	else if (sub_ind==2)
		{
		if (but==butE)
			{
 			//a=b[--ptr_ind];
 			tree_down(0,0);
 			ret(0);
   			}
	     }	
	}	 

else if (ind==iTst_BPS1)
	{
	ret(1000);
	if(but==butU)
     	{
    		sub_ind=0;
       	}
 	else if(but==butD)
     	{
     	sub_ind=2;
     	}
     else if(but==butD_)
		{
		sub_ind=2;
		}			
 	else if (sub_ind==0)
		{
		if (but==butE)
			{
 			if(tst_state[2]==tstOFF)tst_state[2]=tstON;
 			else if(tst_state[2]==tstON)tst_state[2]=tstU;
 			else tst_state[2]=tstOFF;
   			}
		 }
 	else if (sub_ind==2)
		{
		if (but==butE)
			{
 			tree_down(0,0);
 			ret(0);
   			}
	     }	
	}	 

else if (ind==iTst_BPS2)
	{
	ret(1000);
	if(but==butU)
     	{
    		sub_ind=0;
       	}
 	else if(but==butD)
     	{
     	sub_ind=2;
     	}
	else if(but==butD_)
		{
		sub_ind=2;
		}		     	
 	else if (sub_ind==0)
		{
		if (but==butE)
			{
 			if(tst_state[3]==tstOFF)tst_state[3]=tstON;
 			else if(tst_state[3]==tstON)tst_state[3]=tstU;
 			else tst_state[3]=tstOFF;
   			}
		 }
 	else if (sub_ind==2)
		{
		if (but==butE)
			{
 			tree_down(0,0);
 			ret(0);
   			}
	     }	
	}


else if (ind==iTst_BPS12)
	{
	ret(1000);
	if(but==butU)
     	{
    		sub_ind=0;
       	}
 	else if(but==butD)
     	{
     	sub_ind=3;
     	}
	else if(but==butD_)
		{
		sub_ind=3;
		}		     	
 	else if(sub_ind==0)
		{
		if(but==butE)
			{
 			if(tst_state[4]==tstOFF)tst_state[4]=tstON;
 			else if(tst_state[4]==tstON)tst_state[4]=tstU;
 			else tst_state[4]=tstOFF;
   			}
		 }
 	else if(sub_ind==3)
		{
		if(but==butE)
			{
 			tree_down(0,0);
 			ret(0);
   			}
	     }	
	}	

else if(ind==iK)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butD_)
		{
		sub_ind=5;
		}				
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			tree_up(iK_net,0,0,0);	
			ret(1000);		
			}
		else if(sub_ind==1)
			{
			tree_up(iK_bat,0,0,0);	
			ret(1000);
			}
		else if(sub_ind==2)
			{
			tree_up(iK_src,0,0,0);	
			ret(1000);
			}
		else if(sub_ind==3)
			{
			tree_up(iK_src,0,0,1);	
			ret(1000);
			}		
          
         else if(sub_ind==4)
			{
			tree_up(iK_t_out,0,0,0);	
			ret(1000);			
			}				
          else if(sub_ind==5)
			{
	          tree_down(-1,0);
	          ret(0);
               }	               			
		}			
	}

else if(ind==iK_bat)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if((sub_ind==1)||(sub_ind==2))sub_ind=3;
		else if((sub_ind==4)||(sub_ind==5))sub_ind=6;
		else if((sub_ind==7)||(sub_ind==8))sub_ind=9;
		gran_char(&sub_ind,0,9);
		phase=0;
		}
	else if(but==butU)
		{
		sub_ind--;
		if((sub_ind==1)||(sub_ind==2))sub_ind=0;
		else if((sub_ind==4)||(sub_ind==5))sub_ind=3;
		else if((sub_ind==7)||(sub_ind==8))sub_ind=6;
		gran_char(&sub_ind,0,9);
		phase=0;
		}
	else if(but==butD_)
		{
		sub_ind=9;
		}			
	else if(sub_ind==0)
		{
		temp_SS=lc640_read_int(ptr_ku_bat);
	     if(but==butR) temp_SS++;
	     else if(but==butR_)	temp_SS+=2;
	     else if(but==butL) temp_SS--;
	     else if(but==butL_)	temp_SS-=2;
		gran(&temp_SS,1300,1600);
		lc640_write_int(ptr_ku_bat,temp_SS);					
		speed=1;			
		}
					
	else if(sub_ind==3)
		{
		temp_SS=lc640_read_int(ptr_ki_bat1);
		if(but==butR) temp_SS++;
		else if(but==butR_)	temp_SS+=3;
		else if(but==butL) temp_SS--;
		else if(but==butL_)	temp_SS-=3;
		else if(but==butE)
		     {
		     if(phase==0)
		          {
		          lc640_write_int(ptr_ki_bat0,adc_buff_[4]);
		          phase=1;
				}
		     }
		gran(&temp_SS,1000,8000);
		lc640_write_int(ptr_ki_bat1,temp_SS);					
		speed=1;
		phase=1;			
		}					
	else if(sub_ind==6)
		{
		temp_SS=lc640_read_int(ptr_kt_bat);
		if(but==butR) temp_SS++;
		else if(but==butR_)	temp_SS+=3;
		else if(but==butL) temp_SS--;
		else if(but==butL_)	temp_SS-=3;
		gran(&temp_SS,1800,2500);
		lc640_write_int(ptr_kt_bat,temp_SS);				
		speed=1;			
		}	
	else if(sub_ind==9)
		{
		if(but==butE)
			{
			//a=b[--ptr_ind];
			//sub_ind++;
			tree_down(0,1);
			ret(0);
			}
		}			
	}
	
	else if(ind==iK_src)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if((sub_ind==1)||(sub_ind==2))sub_ind=3;
		else if((sub_ind==4)||(sub_ind==5))sub_ind=6;
		else if((sub_ind==7)||(sub_ind==8))sub_ind=9;
		gran_char(&sub_ind,0,9);
		phase=0;
		}
	else if(but==butU)
		{
		sub_ind--;
		if((sub_ind==1)||(sub_ind==2))sub_ind=0;
		else if((sub_ind==4)||(sub_ind==5))sub_ind=3;
		else if((sub_ind==7)||(sub_ind==8))sub_ind=6;
		gran_char(&sub_ind,0,9);
		phase=0;
		}
	else if(but==butD_)
		{
		sub_ind=9;
		}		
			
	else if(sub_ind==0)
		{
		if(phase==0)
		     {
		     if(but==butE)
		          {
		          //#if(UKU_VERSION==300)
				  	if(KINDSRC==1)
						{
		          		if(sub_ind1==0)temp_SS=adc_buff_[3];
		          		if(sub_ind1==1)temp_SS=adc_buff_[1];
				  		}
                    //#else
					else
						{
						if(sub_ind1==0)temp_SS=adc_buff_[1];
		          		if(sub_ind1==1)temp_SS=adc_buff_[3];
						}
		          //#endif
		          lc640_write_int(ptr_ki0_src[sub_ind1],temp_SS);
		     	phase=1;
		          }
		     else phase=1;     
		     }
		else if(phase==2)
		     {
			temp_SS=lc640_read_int(ptr_ki_src[sub_ind1]);
		     if(but==butR) temp_SS++;
	     	else if(but==butR_)	temp_SS+=2;
	     	else if(but==butL) temp_SS--;
	     	else if(but==butL_)	temp_SS-=2;
			gran(&temp_SS,100,1200);
	     	lc640_write_int(ptr_ki_src[sub_ind1],temp_SS);
			speed=1;			
	     	}
	     }	
					
	else if(sub_ind==3)
		{
		temp_SS=lc640_read_int(ptr_ku_src[sub_ind1]);
	     if(but==butR) temp_SS++;
		else if(but==butR_)	temp_SS+=2;
		else if(but==butL) temp_SS--;
		else if(but==butL_)	temp_SS-=2;
		gran(&temp_SS,900,1300);
		lc640_write_int(ptr_ku_src[sub_ind1],temp_SS);					
		speed=1;			
		}					
	else if(sub_ind==6)
		{
		temp_SS=lc640_read_int(ptr_kt_src[sub_ind1]);
		if(but==butR) temp_SS++;
		else if(but==butR_)	temp_SS+=3;
		else if(but==butL) temp_SS--;
		else if(but==butL_)	temp_SS-=3;
		gran(&temp_SS,1800,3000);
		lc640_write_int(ptr_kt_src[sub_ind1],temp_SS);					
		speed=1;			
		}	
	else if(sub_ind==9)
		{
		if(but==butE)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}	
	

else if(ind==iK_net)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,1);
		phase=0;
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,1);
		phase=0;
		}
	else if(but==butD_)
		{
		sub_ind=1;
		}				
	else if(sub_ind==0)
		{
		temp_SS=lc640_read_int(ptr_ku_net);
		if(but==butR) temp_SS++;
		else if(but==butR_)	temp_SS+=10;
		else if(but==butL) temp_SS--;
		else if(but==butL_)	temp_SS-=10;
		gran(&temp_SS,400,1000);
		lc640_write_int(ptr_ku_net,temp_SS);				
		speed=1;			
		}
	else if(sub_ind==1)
		{
		if(but==butE)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}		
else if(ind==iK_t_out)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,3);

		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,3);
		}	
	else if(but==butD_)
		{
		sub_ind=3;
		}				
 	else if((sub_ind>=0)&&(sub_ind<=2))
 		{
 		unsigned short adr__;
 		if(sub_ind==0)adr__=KTOUT0;
 		else if(sub_ind==1)adr__=KTOUT1;
 		else if(sub_ind==2)adr__=KTOUT2;
 		temp_SS=lc640_read_int(adr__);

		if(but==butR)
			{
			temp_SS++;
			}
		else if(but==butR_)
			{
			temp_SS+=5;
			}	
		else if(but==butL)
			{
			temp_SS--;
			}
		else if(but==butL_)
			{
			temp_SS-=5;
			}				
		speed=1;
		gran(&temp_SS,850,1050);
		lc640_write_int(adr__,temp_SS); 	
 		}    
  
     
     else if(sub_ind==3)
		{
		if(but==butE) 
			{
			//a=b[--ptr_ind];
			tree_down(0,0);
			ret(0);
			}
          }			
	}	

else if((ind==iPrl_bat_in_out)||(ind==iSet_prl)||(ind==iK_prl)
	||(ind==iSpc_prl_vz)||(ind==iSpc_prl_ke)||(ind==iAusw_prl)
	||(ind==iPrltst)||(ind==iLog_reset_prl))
	{
	ret(50);
	if(but==butR)
		{
		sub_ind++;
		gran_ring_char(&sub_ind,0,2);
		}
	else if(but==butL)
		{
		sub_ind--;
		gran_ring_char(&sub_ind,0,2);
		}	
	else if(but==butU)
		{
		parol[sub_ind]++;
		gran_ring_char(&parol[sub_ind],0,9);
		}	
	else if(but==butD)
		{
		parol[sub_ind]--;
		gran_ring_char(&parol[sub_ind],0,9);
		}	
	else if(but==butE)
		{
		unsigned short tempU;
		tempU=parol[2]+(parol[1]*10U)+(parol[0]*100U);
		
		if(ind==iPrl_bat_in_out)
		     {
		     if(BAT_IS_ON!=bisON)
		          {
		          if(tempU==PAROL_BAT_IN)
		               {
		               lc640_write_int(EE_BAT_IS_ON,bisON);
		               lc640_write_int(EE_BAT_DAY_OF_ON,LPC_RTC->DOM);
		               lc640_write_int(EE_BAT_MONTH_OF_ON,LPC_RTC->MONTH);
		               lc640_write_int(EE_BAT_YEAR_OF_ON,LPC_RTC->YEAR);
		               lc640_write_int(EE_BAT_C_REAL,0x5555);
		               lc640_write_int(EE_BAT_RESURS,0);
		               
//		               lc640_write(KE_PTR,0);
//					lc640_write(VZ_PTR,0);
//					lc640_write(WRK_PTR,0);
//					lc640_write(KE_CNT,0);
//					lc640_write(VZ_CNT,0);
//					lc640_write(WRK_CNT,0);
//					lc640_write(BAT_AVAR_CNT,0);
//					lc640_write(BAT_AVAR_PTR,0);					
		               
                         //a=b[--ptr_ind];
                         tree_down(0,0);
		               }
		          else
		               {
		               ind=iDnd;
		               //ret_ind(b[--ptr_ind].i,b[ptr_ind].s_i,5);
		               ret(20);
     	               }
		          }      
               else		          
		          {
		          if(tempU==PAROL_BAT_OUT)
		               {
		               lc640_write_int(EE_BAT_IS_ON,bisOFF);
		               lc640_write_int(EE_BAT_DAY_OF_ON,LPC_RTC->DOM);
		               lc640_write_int(EE_BAT_MONTH_OF_ON,LPC_RTC->MONTH);
		               lc640_write_int(EE_BAT_YEAR_OF_ON,LPC_RTC->YEAR);
		               //a=b[--ptr_ind];
		               tree_down(0,0);
		               ret(0);
		               
		               }
	               else
		               {
     	               ind=iDnd;
		               //ret_ind(b[--ptr_ind].i,b[ptr_ind].s_i,5);	
		               //tree_down(0,0);
		               ret(20);	               
		               }		               
		          }     
               }
		
		else if(ind==iSet_prl)
			{
	     	if(tempU==PAROL_SET) 
				{
				/*ind=iSet;
				sub_ind=0;
				index_set=0;*/
				tree_up(iSet,0,0,0);
				ret(1000);
				}
			else 
				{
				ind=iDnd;
				ret(20);
				}
			}
		else	if(ind==iK_prl)
			{
	     	if(tempU==PAROL_KALIBR) 
				{
				//ind=iK_pdp;
				//ret_ind(iK,0,15);
				tree_up(iK,0,0,0);
				tree_up(iK_pdp,0,0,0);
				
				ret(50);
				}
			else 
				{
				ind=iDnd;
				ret(20);
				}
			} 
	
		else	if(ind==iAusw_prl)
			{
	     	if(tempU==PAROL_AUSW) 
				{
				/*ind=iAusw_set;
				sub_ind=0;
				index_set=0;*/
				tree_up(iAusw_set,0,0,0);
				default_temp=10;
				ret(0);
				}
			else 
				{
				ind=iDnd;
				ret(15);
				}
			} 	
			
		else	if(ind==iSet_st_prl)
			{
	     	if(tempU==PAROL_DEFAULT) 
				{
	//			ind=iDefault;
				sub_ind=1;
				index_set=0;
				default_temp=10;
				}
			else 
				{
				ind=iDnd;
				ret_ind(iSet,0,10);
				}
			} 
						
		else if(ind==iPrltst)
			{
			if(tempU==PAROL_TST) 
				{
				ind=iTst;
				sub_ind=0;
				index_set=0;
				tst_state[0]=tstOFF;
				tst_state[1]=tstOFF;
				tst_state[2]=tstOFF;
				tst_state[3]=tstOFF;
				tst_state[4]=tstOFF;
				tst_state[5]=tstOFF;
				}
	  		else 
				{
				ind=iDnd;
				}
			}
		else if(ind==iSpc_prl_ke)
			{
			if(tempU==PAROL_KE) 
				{
				/*ind=iKe;
				sub_ind=0;
				index_set=0;*/
				tree_up(iKe,0,0,0);
				}
	  		else 
				{	
				ind=iDnd;
				ret_ind(b[--ptr_ind].i,0,5);
				}
			}
		else if(ind==iSpc_prl_vz)
			{
			if(tempU==PAROL_VZ) 
				{
				/*ind=iVz;
				sub_ind=0;
				index_set=0;*/
				tree_up(iVz,0,0,0);
     			}
	  		else 
				{
				ind=iDnd;
		          ret_ind(b[--ptr_ind].i,1,5);
     	          }
			}
		else if(ind==iLog_reset_prl)
			{
			if(tempU==PAROL_LOG_RESET) 
				{
				tree_down(0,0);
				lc640_write(CNT_EVENT_LOG,0);
				lc640_write(PTR_EVENT_LOG,0);
				tree_down(0,0);
				//avar_ind_stat=0;
				//avar_stat=0;
				//avar_stat_old=0;
	    	    show_mess("                    ",
	          			"   ������ �������   ",
	          			"      ������!!!     ",
	          			"                    ",1000);
				//ret(1000);
				}
	  		else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       ������       ",
	          			"     ��������!!!    ",
	          			"                    ",1000);
				}  
			}
		}
	}
else if(ind==iJ_bat)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,6);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,6);
		}
	else if(but==butD_)
		{
		sub_ind=6;
		}				
	else if((but==butL)&&(sub_ind!=1))
		{
		tree_down(0,0);
		ret_ind(0,0,0);
		}		
	else if(sub_ind==0)
	     {
	     if(but==butE)
	          {
	          b[ptr_ind++]=a;
	          if(BAT_IS_ON==bisON) ind=iPrl_bat_in_out;
	          else 
	               {
	               ind=iPdp1;
	               ret_ind(iPrl_bat_in_out,0,10);
	               }
	          parol_init();
	          }
	     }
	else if(sub_ind==1)
	     {
	     if(but==butR)BAT_C_NOM++;
	     else if(but==butR_)BAT_C_NOM+=10;
	     else if(but==butL)BAT_C_NOM--;
	     else if(but==butL_)BAT_C_NOM-=10;
	     gran(&BAT_C_NOM,0,200);
	     lc640_write_int(EE_BAT_C_NOM,BAT_C_NOM);
	     speed=1;
	     }		     
	else if(sub_ind==3)
	     {
		if(but==butE)
			{ 
               cap=0;
			deep=lc640_read_int(CNT_EVENT_LOG);
			ptr=lc640_read_int(PTR_EVENT_LOG);
			
			if(deep>63)
				{
				deep=0;
			     ptr=0;
			     }
			     			
			for(i=0;i<deep;i++)
				{
				lc640_read_long_ptr(EVENT_LOG+(32*ptr),av_head);
				
				if((av_head[0]=='B')&&(av_head[1]==sub_ind1)&&(av_head[2]=='K')) 	//���� ������ ���������� ������� 'K'(�������� �������)
					{
					cap++;
					content[cap-1]=ptr;
					}
					
				ptr=ptr_carry(ptr,64,-1); 
	
				} 
				
			/*ind=iBatJKE;
			sub_ind=0;*/

			tree_up(iJ_bat_ke_sel,0,0,0);
			
			av_j_si_max=cap;
			if(av_j_si_max>63)av_j_si_max=0;
			} 
	     } 	     
	else if(sub_ind==4)
	     {
/*	     if(but==butE)	
	     	{
	     	tree_up(iJ_bat_vz_sel,0,0,0);
	     	}*/
		if(but==butE)
			{ 
               cap=0;
			deep=lc640_read_int(CNT_EVENT_LOG);
			ptr=lc640_read_int(PTR_EVENT_LOG);
			
			if(deep>63)
				{
				deep=0;
			     ptr=0;
			     }
			     
			for(i=0;i<deep;i++)
				{
				lc640_read_long_ptr(EVENT_LOG+(32*ptr),av_head);
				
				if((av_head[0]=='B')/*&&(av_head[1]==sub_ind1)*/&&(av_head[2]=='Z')) 	//���� ������ ���������� ������� 'z'(������������� �����)
					{
					cap++;
					content[cap-1]=ptr;
					}
					
				ptr=ptr_carry(ptr,64,-1); 
				} 
				
			tree_up(iJ_bat_vz_sel,0,0,0);   
			
			av_j_si_max=cap;
			if(av_j_si_max>63)av_j_si_max=0;
			} 
		else if(but==butR)
			{
			//vz_mem_hndl(0,5);
			//vz_mem_hndl(1,6);	       
			} 

	     } 
	else if(sub_ind==5)
	     {
		if(but==butE)
			{ 
               cap=0;
			deep=lc640_read_int(CNT_EVENT_LOG);
			ptr=lc640_read_int(PTR_EVENT_LOG);

			if(deep>63)
				{
				deep=0;
			     ptr=0;
			     }
			for(i=0;i<deep;i++)
				{
				lc640_read_long_ptr(EVENT_LOG+(32*ptr),av_head);
				
				if((av_head[0]=='B')&&(av_head[1]==0)&&(av_head[2]=='W')) 	//���� ������ ���������� ������� 'W'(�������)
					{
					cap++;
					content[cap-1]=ptr;
					}
				ptr=ptr_carry(ptr,64,-1); 
				} 
				
			tree_up(iJ_bat_wrk_sel,0,0,0);			

			av_j_si_max=cap;
			if(av_j_si_max>63)av_j_si_max=0;
			} 
		else if(but==butR)
			{
			//vz_mem_hndl(0,5);
			//vz_mem_hndl(1,6);	       
			} 

	     } 	         	
     else if(sub_ind==6)
	     {
	     if(but==butE)
	          {
	          tree_down(0,0);
	          }
	     }		     
		
	} 
else if(ind==iJ_bat_ke_sel)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max);
		} 
	else if(but==butD_)
		{
		sub_ind=av_j_si_max;
		
		}		
	else if(but==butE)
		{
 		if(sub_ind==av_j_si_max)
			{
			tree_down(0,0);
			}
		else 
			{
			sub_ind2=content[sub_ind];
			tree_up(iJ_bat_ke,0,0,sub_ind);
			ret(100);			
			}	
		}
	else if(but==butL)
		{	
		tree_down(0,0);
		}			
	else if(but==butR)ke_mem_hndl(355);	 
	}
	
else if(ind==iJ_bat_ke)
	{
	ret(100);
	if(but==butD)
		{
		if(index_set<av_j_si_max_)
			{
			index_set++;
			}
		else 
			{
			tree_down(0,0);
			ret_ind(0,0,0);
			}	
		}
	else if(but==butU)
		{
		if(index_set)index_set--;
		}	
	else 
		{
		tree_down(0,0);
		ret_ind(0,0,0);
		}	
	}	
	
else if(ind==iJ_bat_vz_sel)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max);
		} 
	else if(but==butD_)
		{
		sub_ind=av_j_si_max;
		
		}		
	else if(but==butE)
		{
		if(sub_ind==av_j_si_max)
			{
			tree_down(0,0);				
			}		
		else 
			{
			sub_ind2=content[sub_ind];
			tree_up(iJ_bat_vz,0,0,sub_ind);
			ret(100);
			}	
		}
	else if(but==butL)
		{	
		tree_down(0,0);
		}	 
	}
	
else if(ind==iJ_bat_vz)
	{
	ret(100);
	if(but==butD)
		{
		if(index_set<av_j_si_max_)
			{
			index_set++;
			}
		else 
			{
			tree_down(0,0);
			ret_ind(0,0,0);
			}	
		}
	else if(but==butU)
		{
		if(index_set)index_set--;
		}	
	else 
		{
		tree_down(0,0);
		ret_ind(0,0,0);
		}
	}	

else if(ind==iJ_bat_wrk_sel)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max);
		} 
	else if(but==butD_)
		{
		sub_ind=av_j_si_max;
		
		}		
	else if(but==butE)
		{
		 if(sub_ind==av_j_si_max)
			{
			tree_down(0,0);
			ret(0);
			}
		else 
			{
			sub_ind2=content[sub_ind];
			tree_up(iJ_bat_wrk,0,0,sub_ind);
			ret(100);
			}	
		} 
	else if(but==butL)
		{
		tree_down(0,0);
		}		
	else if(but==butR)
		{
		//wrk_mem_hndl(255);
		}		
	}
	
else if(ind==iJ_bat_wrk)
	{
	ret(100);
	if(but==butD)
		{
		if(index_set<4)
			{
			index_set++;
			}
		else 
			{
			tree_down(0,0);
			ret_ind(0,0,0);
			}	
		}
	else if(but==butU)
		{
		if(index_set)index_set--;
		}	
	else 
		{
		tree_down(0,0);
		ret_ind(0,0,0);
		}	
	}
else if(ind==iFWabout)
	{
	ret(1000);
	if(but==butE)
	     {
	     tree_down(0,0);
	     ret(0);
	     }
	}				   
but_an_end:
n_but=0;
#endif
}	

#define BUT_ON 4
#define BUT_ONL 20 
//-----------------------------------------------
void but_drv(void)
{

but_n=LPC_GPIO2->FIOPIN|(0xFFFFFFFFUL&(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2))&(~(1UL<<BUT3))&(~(1UL<<BUT4)));
if((but_n==0xffffffffUL)||(but_n!=but_s))
 	{
 	speed=0;
 
   	if (((but0_cnt>=BUT_ON)||(but1_cnt!=0))&&(!l_but))
  		{
   	     n_but=1;
          but=but_s;

          }
   	if (but1_cnt>=but_onL_temp)
  		{
   	     n_but=1;
 
          but=but_s&0x7f;
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
    			but=but=but_s&0x7f;
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
*/
LPC_GPIO2->FIODIR&=~(1UL<<BUT0)&~(1UL<<BUT1)&~(1UL<<BUT2)&~(1UL<<BUT3)&~(1UL<<BUT4);
	   
}
//-----------------------------------------------
static void timer_poll () 
{
if (SysTick->CTRL & 0x10000) 
     {
     timer_tick ();
     tick = __TRUE;
     }
}

//-----------------------------------------------
void watchdog_enable (void) 
{
LPC_WDT->WDTC=2000000;
LPC_WDT->WDCLKSEL=0;
LPC_WDT->WDMOD=3;
LPC_WDT->WDFEED=0xaa;
LPC_WDT->WDFEED=0x55;
}

//-----------------------------------------------
void watchdog_reset (void) 
{
LPC_WDT->WDFEED=0xaa;
LPC_WDT->WDFEED=0x55;
}

//***********************************************
//***********************************************
//***********************************************
//***********************************************
//***********************************************
void SysTick_Handler (void) 	 /* SysTick Interrupt Handler (1ms)    */
{
//LPC_GPIO0->FIODIR|=0x00000001;
//LPC_GPIO0->FIOSET|=0x00000001;           



//LPC_GPIO0->FIOCLR|=0x00000001;
}

//===============================================
//===============================================
//===============================================
//===============================================
int main (void) 	                        
{ 
long i;
char mac_adr[6] = { 0x00,0x73,0x04,50,60,70 };
char ind_reset_cnt=0;

i=200000;
while(--i){};

SystemInit();



SysTick->LOAD = (SystemFrequency / 10) - 1;
SysTick->CTRL = 0x05;

init_timer( 0,SystemFrequency/1000/4 - 1 ); // 1ms	
enable_timer( 0 );

/*lcd_debug_start();

while(1)
{
lcd_debug_loop();
} */


LPC_GPIO1->FIODIR  |= 1<<27;                
	;
//FIO1MASK = 0x00000000;	 
LPC_GPIO0->FIODIR  |= 1<<27;
LPC_GPIO0->FIOSET  |= 1<<27;

SET_REG(LPC_GPIO0->FIODIR,0,10,1); //���� ������� 

lcd_init();  
lcd_on();
lcd_clear();
		
LPC_GPIO4->FIODIR |= (1<<29);           /* LEDs on PORT2 defined as Output    */
rtc_init();
pwm_init();
ind=iMn; 
//snmp_plazma=15;
UARTInit(0, 9600);	/* baud rate setting */

#ifdef LAN_OFF
if(lc640_read_int(EE_ETH_IS_ON)==1) lc640_write_int(EE_ETH_IS_ON,0);
#endif


AUSW_MAIN_NUMBER=lc640_read_long(EE_AUSW_MAIN_NUMBER);
NUMIST=lc640_read_long(EE_NUMIST);

mac_adr[5]=*((char*)&AUSW_MAIN_NUMBER);
mac_adr[4]=*(((char*)&AUSW_MAIN_NUMBER)+1);
mac_adr[3]=*(((char*)&AUSW_MAIN_NUMBER)+2);
mem_copy (own_hw_adr, mac_adr, 6);

snmp_Community[0]=(char)lc640_read_int(EE_COMMUNITY);
//if((snmp_Community[0]==0)||(snmp_Community[0]==' '))snmp_Community[0]=0;
snmp_Community[1]=(char)lc640_read_int(EE_COMMUNITY+2);
if((snmp_Community[1]==0)||(snmp_Community[1]==' '))snmp_Community[1]=0;
snmp_Community[2]=(char)lc640_read_int(EE_COMMUNITY+4);
if((snmp_Community[2]==0)||(snmp_Community[2]==' '))snmp_Community[2]=0;
snmp_Community[3]=(char)lc640_read_int(EE_COMMUNITY+6);
if((snmp_Community[3]==0)||(snmp_Community[3]==' '))snmp_Community[3]=0;
snmp_Community[4]=(char)lc640_read_int(EE_COMMUNITY+8);
if((snmp_Community[4]==0)||(snmp_Community[4]==' '))snmp_Community[4]=0;
snmp_Community[5]=(char)lc640_read_int(EE_COMMUNITY+10);
if((snmp_Community[5]==0)||(snmp_Community[5]==' '))snmp_Community[5]=0;
snmp_Community[6]=(char)lc640_read_int(EE_COMMUNITY+12);
if((snmp_Community[6]==0)||(snmp_Community[6]==' '))snmp_Community[6]=0;
snmp_Community[7]=(char)lc640_read_int(EE_COMMUNITY+14);
if((snmp_Community[7]==0)||(snmp_Community[7]==' '))snmp_Community[7]=0;
snmp_Community[8]=(char)lc640_read_int(EE_COMMUNITY+16);
if((snmp_Community[8]==0)||(snmp_Community[8]==' '))snmp_Community[8]=0;
snmp_Community[9]=0;

bRESET_RESET=1;
if(lc640_read_int(EE_ETH_IS_ON)==1)
	{
	bgnd_par(		"                    ",
     		"    �������������   ",
     		"      Ethernet      ",
     		"                    ");
	bitmap_hndl();
	lcd_out(lcd_bitmap);
	init_TcpNet ();

	init_ETH();
	//mem_copy (&localm[NETIF_ETH], &ip_config, sizeof(ip_config));

	}
bRESET_RESET=0;
//event2snmp(2);

reload_hndl();

/*
socket_tcp = tcp_get_socket (TCP_TYPE_SERVER, 0, 10, tcp_callback);
if (socket_tcp != 0) 
	{
    tcp_listen (socket_tcp, 502);
  	}
*/

socket_udp = udp_get_socket (0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
if (socket_udp != 0) 
	{
    udp_open (socket_udp, PORT_NUM);
  	}

adc_init();

#ifdef LAN_OFF
can1_init(BITRATE125K25MHZ);
FullCAN_SetFilter(0,0x0e9);
#endif

UARTInit(0, 9600);	/* baud rate setting */

watchdog_enable();
time_sinc_hndl_main_cnt=20L;

while(1)
     {
     timer_poll ();
     main_TcpNet ();
     
	if(bRXIN0)
     	{
		bRXIN0=0;
		uart_in0();
		}

     if(b100Hz)
		{
		b100Hz=0;

		//adc_drv5();
		but_drv();
		but_an(); 

  
		}

     if(bADC)
		{
		bADC=0;

		adc_drv5();
  
		}

		
	if(b33Hz)
		{
		b33Hz=0;
		}
			 
	if(b10Hz)
		{
		b10Hz=0;

	     unet_drv();
	     src_drv(0);
		src_drv(1);
	     ind_hndl();
		bitmap_hndl();
		lcd_out(lcd_bitmap);
         	ret_hndl();

		//timer_tick ();
      	//tick = __TRUE;  

          /*LPC_GPIO4->FIODIR|=(1<<29);
          LPC_GPIO4->FIOPIN^=(1<<29);*/
 		}
			
	if(b5Hz)
		{
		b5Hz=0;

		samokalibr_drv();
		ret_ind_hndl();
		matemat();
		time_drv();
		kb_drv();
		zar_superviser_drv();
		u_necc_hndl();
		out_out();   
		bat_drv();   
		rele_drv();  
		beep_hndl();
		memo_read(); 
//          plazma_mib=12345;
//          plazma_mib1=123456;
		snmp_data();

		while (bwd_stop)
			{
			}
		watchdog_reset();


		if(!bRESET)
			{
			LPC_GPIO2->FIODIR|=(1<<10);
          	LPC_GPIO2->FIOPIN^=(1<<10);
			}
		}

	if(b2Hz)
		{
		b2Hz=0;
		info_for_snmp();
		http_data();
		}
										
	if(b1Hz)
		{
		b1Hz=0; //33


		cntrl_hndl();
		cntrl_drv();
		ret_ind_sec_hndl();  
		spc_drv();
		zar_drv();
		cntrl_blok_hndl(); 
          avg_hndl();
		apv_drv();
		ubat_old_drv();
 		avz_hndl();
		mnemo_hndl(); /**/
		snmp_Community[0]='a';

		//if(++ind_reset_cnt>=30)
			//{
			//ind_reset_cnt=0;
		//lcd_init();
			//lcd_on();
			//lcd_clear();
			//}
		if(!bRESET)
			{
			//rs232_data_out_1();
			}
		time_sinc_hndl();
		}
     }
}
/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/



