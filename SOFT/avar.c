#include "avar.h"
#include "LPC17XX.H" 
#include "main.h"
#include "control.h"
#include "eeprom_map.h"
#include "25lc640.h"

//-----------------------------------------------
//Аварии источников
char cnt_av_umax[2],cnt_av_umin[2],cnt_av_t[2];

//-----------------------------------------------
//Флаги аварий
unsigned short av_beep,av_rele,av_stat;


//-----------------------------------------------
void avar_src_reset(char in)
{
cnt_av_umax[in]=0;
cnt_av_umin[in]=0;
cnt_av_t[in]=0;
St_[in]&=0xe3;
cnt_src[0]=10;
cnt_src[1]=10 ;
} 

//-----------------------------------------------
void avar_bat_hndl(char in)
{

char data[4];
unsigned int event_ptr,lc640_adr,event_ptr_find,event_cnt;

if(in==1)
	{

	St|=0x02;
	av_stat|=0x0002;
	av_rele|=0x0002;
	av_beep|=0x0002; 
    
	event_ptr=lc640_read_int(PTR_EVENT_LOG);
	event_ptr++;	
	if(event_ptr>63)event_ptr=0;	
	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
     event_cnt=lc640_read_int(CNT_EVENT_LOG);
	if(event_cnt!=63)event_cnt=event_ptr;
	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
	data[0]='B';
	data[1]=0;
	data[2]='C';
	data[3]=0;
	lc640_write_long_ptr(lc640_adr,data);

	data[0]=0;
	data[1]=0;
	data[2]=0;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+4,data);

	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+8,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+12,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+16,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+28,data);
	

	snmp_trap_send("BAT №1 Alarm, lost",5,1,1);

	}

else if(in==0)
	{

	St&=0xfd;
	av_stat&=0xfffd;
	av_rele&=0xfffd;
	av_beep&=0xfffd;
		
     event_ptr=lc640_read_int(PTR_EVENT_LOG);
	if(event_ptr>63) event_ptr=63;
	event_ptr_find=event_ptr;
	
avar_bat_hndl_lbl1: 

	lc640_adr=EVENT_LOG+(event_ptr_find*32);

     lc640_read_long_ptr(lc640_adr,data);
     
     if(!((data[0]=='B')&&(data[1]==0)&&(data[2]=='C')))
     	{        
     	if(event_ptr_find)event_ptr_find--;
     	else event_ptr_find=63;
     	if(event_ptr_find==event_ptr)goto avar_bat_hndl_end;
     	else goto avar_bat_hndl_lbl1;
     	}
     else 
     	{
     	lc640_read_long_ptr(lc640_adr+16,data);
     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
     		{        
     		if(event_ptr_find)event_ptr_find--;
         		else event_ptr_find=63;
         	    	if(event_ptr_find==event_ptr)goto avar_bat_hndl_end;
     		else goto avar_bat_hndl_lbl1;
     		}

     	}
     		
	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+16,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+28,data);
	

	
	}
	
avar_bat_hndl_end:
__nop();
}

//-----------------------------------------------
void wrk_mem_hndl(unsigned short in)
{
char data[4];
unsigned short event_ptr,lc640_adr/*,event_ptr_find*/,event_cnt;
//unsigned char temp,temp_;
//unsigned short tempUI;
//unsigned long tempUL; 
signed short temp_temp;

if(ibat_integr==0) goto wrk_mem_hndl_end;

temp_temp=ubat_old[((ubat_old_cnt+1)&0x07)]; 


event_ptr=lc640_read_int(PTR_EVENT_LOG);
event_ptr++;	
if(event_ptr>63)event_ptr=0;	
lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
event_cnt=lc640_read_int(CNT_EVENT_LOG);
if(event_cnt!=63)event_cnt=event_ptr;
lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
data[0]='B';
data[1]=0; 
data[2]='W';
data[3]=0;

lc640_write_long_ptr(lc640_adr,data);

data[0]=*((char*)&ibat_integr);
data[1]=*(((char*)(&ibat_integr))+1);
data[2]=*((char*)&temp_temp);
data[3]=*(((char*)(&temp_temp))+1);
lc640_write_long_ptr(lc640_adr+4,data);

lc640_write_long_ptr(lc640_adr+8,(char*)&wrk_date[0]);
	
lc640_write_long_ptr(lc640_adr+12,(char*)&wrk_date[1]);

data[0]=LPC_RTC->YEAR;
data[1]=LPC_RTC->MONTH;
data[2]=LPC_RTC->DOM;
data[3]=0;
lc640_write_long_ptr(lc640_adr+16,data);

data[0]=LPC_RTC->HOUR;
data[1]=LPC_RTC->MIN;
data[2]=LPC_RTC->SEC;
data[3]=0;
lc640_write_long_ptr(lc640_adr+20,data);
	


	
wrk_mem_hndl_end:
__nop();	
}

//-----------------------------------------------
void vz_mem_hndl(unsigned short in)
{
char data[4];
unsigned int event_ptr,lc640_adr,event_ptr_find,event_cnt;
//char avar_simbol;
event_ptr=lc640_read_int(PTR_EVENT_LOG);

if(in==1)
	{
	event_ptr++;	
	if(event_ptr>63)event_ptr=0;	
	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
     event_cnt=lc640_read_int(CNT_EVENT_LOG);
	if(event_cnt!=63)event_cnt=event_ptr;
	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
	data[0]='B';
	data[1]=0; 
	data[2]='Z';
	data[3]=0;
	lc640_write_long_ptr(lc640_adr,data);

	data[0]=0;
	data[1]=0;
	data[2]=0;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+4,data);

	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+8,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+12,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+16,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+28,data);		
 	
	}

else if(in==0)
	{      
     
	event_ptr_find=event_ptr;

vz_mem_hndl_lbl1: 

	lc640_adr=EVENT_LOG+(event_ptr_find*32);

     lc640_read_long_ptr(lc640_adr,data);
     
     if(!((data[0]=='B')&&(data[2]=='Z')))
     	{        
     	if(event_ptr_find)event_ptr_find--;
     	else event_ptr_find=63;
     	if(event_ptr_find==event_ptr)goto vz_mem_hndl_end;
     	else goto vz_mem_hndl_lbl1;
     	}
     else 
     	{
     	lc640_read_long_ptr(lc640_adr+16,data);
     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
     		{        
     		if(event_ptr_find)event_ptr_find--;
         		else event_ptr_find=63;
         		if(event_ptr_find==event_ptr)goto vz_mem_hndl_end;
     		else goto vz_mem_hndl_lbl1;
     		}

     	}	


	
	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+16,data);
	
	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+28,data);
	
	}

vz_mem_hndl_end:
__nop(); 

}

//-----------------------------------------------
void ke_mem_hndl(unsigned short in)
{


char data[4];
unsigned int event_ptr,lc640_adr/*,event_ptr_find*/,event_cnt;
//unsigned char temp,temp_;
//unsigned int tempUI;
//unsigned long tempUL; 
signed temp_temp;

temp_temp=ubat_old[((ubat_old_cnt+1)&0x07)]; 

event_ptr=lc640_read_int(PTR_EVENT_LOG);
event_ptr++;	
if(event_ptr>63)event_ptr=0;	
lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
event_cnt=lc640_read_int(CNT_EVENT_LOG);
if(event_cnt!=63)event_cnt=event_ptr;
lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
data[0]='B';
data[1]=0; 
data[2]='K';
data[3]=0;

lc640_write_long_ptr(lc640_adr,data);

data[0]=*((char*)&in);
data[1]=*(((char*)(&in))+1);
data[2]=*((char*)&temp_temp);
data[3]=*(((char*)(&temp_temp))+1);
lc640_write_long_ptr(lc640_adr+4,data);

lc640_write_long_ptr(lc640_adr+8,(char*)&ke_date[0]);
	
lc640_write_long_ptr(lc640_adr+12,(char*)&ke_date[1]);

data[0]=LPC_RTC->YEAR;
data[1]=LPC_RTC->MONTH;
data[2]=LPC_RTC->DOM;
data[3]=0;
lc640_write_long_ptr(lc640_adr+16,data);

data[0]=LPC_RTC->HOUR;
data[1]=LPC_RTC->MIN;
data[2]=LPC_RTC->SEC;
data[3]=0;
lc640_write_long_ptr(lc640_adr+20,data);
 
}

//-----------------------------------------------
void avar_unet_hndl(char in)
{
 
//unsigned short temp_S,temp_S1; 
char data[4];
unsigned short event_ptr,lc640_adr,event_ptr_find,event_cnt;
  
if(in==1) 
	{
	St|=0x01;
	av_stat|=0x0001;
	av_rele|=0x0001;
	av_beep|=0x0001;		
	tzas_cnt=5*TZAS;

	event_ptr=lc640_read_int(PTR_EVENT_LOG);
	event_ptr++;	
	if(event_ptr>63)event_ptr=0;	
	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
     event_cnt=lc640_read_int(CNT_EVENT_LOG);
	if(event_cnt!=63)event_cnt=event_ptr;
	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
	data[0]='P';
	data[1]=0;
	data[2]='A';
	data[3]=0;
	lc640_write_long_ptr(lc640_adr,data);

	data[0]=0;//*((char*)&Unet_store);
	data[1]=0;//*(((char*)&Unet_store)+1);
	data[2]=0;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+4,data);

	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+8,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+12,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+16,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+28,data);				

     		
 	#ifdef _RS232_
	memo_out[0]=0x55;
     memo_out[1]=0x20+2;
     memo_out[2]=0;
     memo_out[3]=0;
     memo_out[4]=((UIB[4]>>4)&0x0f)+((UIB[4]<<4)&0xf0);
     memo_out[5]=0x55;
     memo_out[6]=0x55; 
     	
     memo_out[7]=crc_87(memo_out,7);
	memo_out[8]=crc_95(memo_out,7);
     usart_out_adr(memo_out,11); 		
	#endif

	snmp_trap_send("Main power is off",2,1,0);
	
	}

else if(in==2)
	{
	St|=0x05;
	av_stat|=0x0001;
	av_rele|=0x0001;
	av_beep|=0x0001;		
	tzas_cnt=5*TZAS;
	 
	event_ptr=lc640_read_int(PTR_EVENT_LOG);
	event_ptr++;	
	if(event_ptr>63)event_ptr=0;	
	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
     event_cnt=lc640_read_int(CNT_EVENT_LOG);
	if(event_cnt!=63)event_cnt=event_ptr;
	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
	data[0]='P';
	data[1]=0;
	data[2]='B';
	data[3]=0;
	lc640_write_long_ptr(lc640_adr,data);

	data[0]=0;//*((char*)&Unet_store);
	data[1]=0;//*(((char*)&Unet_store)+1);
	data[2]=0;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+4,data);

	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+8,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+12,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+16,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+28,data);				
	
	snmp_trap_send("Main power alarm, voltage increased",2,2,0);
	}
else if(in==0 || in==4)
	{
	St&=0xfa;
	av_stat&=0xfffe;
	av_rele&=0xfffe;
	av_beep&=0xfffe; 
	avar_src_reset(0);
	blok_src_reset(0);
	avar_src_reset(1);
	blok_src_reset(1);	
	
	#ifdef _RS232_
	memo_out[0]=0x55;
     memo_out[1]=0x20+2;
     memo_out[2]=0;
     memo_out[3]=0;
     memo_out[4]=((UIB[4]>>4)&0x0f)+((UIB[4]<<4)&0xf0);
     memo_out[5]=0xAA;
     memo_out[6]=0xAA; 
   	
     memo_out[7]=crc_87(memo_out,7);
	memo_out[8]=crc_95(memo_out,7);
     usart_out_adr(memo_out,11); 		
	#endif	
	
     event_ptr=lc640_read_int(PTR_EVENT_LOG);
	event_ptr_find=event_ptr;
avar_unet_hndl_lbl1:
	lc640_adr=EVENT_LOG+(event_ptr_find*32);

     lc640_read_long_ptr(lc640_adr,data);
     
     if(!((data[0]=='P')&&(data[1]==0)&&((data[2]=='A')||(data[2]=='B'))))
     	{        
     	if(event_ptr_find)event_ptr_find--;
     	else event_ptr_find=63;
     	if(event_ptr_find==event_ptr)goto avar_unet_hndl_end;
     	else goto avar_unet_hndl_lbl1;
     	}
     else 
     	{
     	lc640_read_long_ptr(lc640_adr+16,data);
     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
     		{        
     		if(event_ptr_find)event_ptr_find--;
         		else event_ptr_find=63;
         		if(event_ptr_find==event_ptr)goto avar_unet_hndl_end;
     		else goto avar_unet_hndl_lbl1;
     		}

     	}	
	
	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+16,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+20,data); 
	
	data[0]=*((char*)(&unet_store));
	data[1]=*(((char*)(&unet_store))+1);
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+28,data);

	snmp_trap_send("Main power is on",2,1,1);
	}
	
avar_unet_hndl_end:
//#asm("nop")
__nop();	
}

//-----------------------------------------------
void avar_bps_hndl(char bps, char in, char v)
{

char data[4]; 
///unsigned short temp_S,temp_S1;
char avar_simbol;
unsigned short event_ptr,lc640_adr,event_ptr_find,event_cnt;

if(v==0)avar_simbol='T';
else if(v==1)avar_simbol='U';
else if(v==2)avar_simbol='u';
else if(v==3)avar_simbol='L';

   
if(in==1)
	{
	//src[bps]._last_avar=v;

	event_ptr=lc640_read_int(PTR_EVENT_LOG);
	event_ptr++;	
	if(event_ptr>63)event_ptr=0;	
	lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
     event_cnt=lc640_read_int(CNT_EVENT_LOG);
	if(event_cnt!=63)event_cnt=event_ptr;
	lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
	lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
	data[0]='S';
	data[1]=bps; 
	data[2]=avar_simbol;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr,data);

	data[0]=0;
	data[1]=0;
	data[2]=0;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+4,data);

	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+8,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+12,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+16,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='A';
	data[1]='A';
	data[2]='A';
	data[3]='A';
	lc640_write_long_ptr(lc640_adr+28,data);

	if(bps==0)
		{
		if(v==0)
		snmp_trap_send("BPS #1 Alarm, overheat",4,1,0);
		else if(v==1)
		snmp_trap_send("BPS #1 Alarm, voltage is up",4,1,1);
		else if(v==2)
		snmp_trap_send("BPS #1 Alarm, voltage is down",4,1,2);
		else if(v==3)
		snmp_trap_send("BPS #1 Alarm, connect is lost",4,1,3);
		}
	else if(bps==1)
		{
		if(v==0)
		snmp_trap_send("BPS #2 Alarm, overheat",4,2,0);
		else if(v==1)
		snmp_trap_send("BPS #2 Alarm, voltage is up",4,2,1);
		else if(v==2)
		snmp_trap_send("BPS #2 Alarm, voltage is down",4,2,2);
		else if(v==3)
		snmp_trap_send("BPS #2 Alarm, connect is lost",4,2,3);
		} 
	else if(bps==2)
		{
		if(v==0)
		snmp_trap_send("BPS #3 Alarm, overheat",4,3,0);
		else if(v==1)
		snmp_trap_send("BPS #3 Alarm, voltage is up",4,3,1);
		else if(v==2)
		snmp_trap_send("BPS #3 Alarm, voltage is down",4,3,2);
		else if(v==3)
		snmp_trap_send("BPS #3 Alarm, connect is lost",4,3,3);
		} 	
	}

else if(in==0)
	{      
     

	event_ptr=lc640_read_int(PTR_EVENT_LOG);
	event_ptr_find=event_ptr;
	
avar_src_hndl_lbl1: 

	lc640_adr=EVENT_LOG+(event_ptr_find*32);

     lc640_read_long_ptr(lc640_adr,data);
     
     if(!((data[0]=='S')&&(data[1]==bps)&&(data[2]==avar_simbol)))
     	{        
     	if(event_ptr_find)event_ptr_find--;
     	else event_ptr_find=63;
     	if(event_ptr_find==event_ptr)goto avar_src_hndl_end;
     	else goto avar_src_hndl_lbl1;
     	}
     else 
     	{
     	lc640_read_long_ptr(lc640_adr+16,data);
     	if(!((data[0]=='A')&&(data[1]=='A')&&(data[2]=='A')&&(data[3]=='A')))
     		{        
     		if(event_ptr_find)event_ptr_find--;
         		else event_ptr_find=63;
         		if(event_ptr_find==event_ptr)goto avar_src_hndl_end;
     		else goto avar_src_hndl_lbl1;
     		}

     	}	


	
	data[0]=LPC_RTC->YEAR;
	data[1]=LPC_RTC->MONTH;
	data[2]=LPC_RTC->DOM;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+16,data);

	data[0]=LPC_RTC->HOUR;
	data[1]=LPC_RTC->MIN;
	data[2]=LPC_RTC->SEC;
	data[3]=0;
	lc640_write_long_ptr(lc640_adr+20,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+24,data);
	
	data[0]='B';
	data[1]='B';
	data[2]='B';
	data[3]='B';
	lc640_write_long_ptr(lc640_adr+28,data);
	
	}
	
avar_src_hndl_end:
__nop();
}

//-----------------------------------------------
void reload_hndl(void)
{
char data[4];
unsigned int event_ptr,lc640_adr/*,event_ptr_find*/,event_cnt;

event_ptr=lc640_read_int(PTR_EVENT_LOG);
event_ptr++;	
if(event_ptr>63)event_ptr=0;	
lc640_write_int(PTR_EVENT_LOG,event_ptr);	
	
event_cnt=lc640_read_int(CNT_EVENT_LOG);
if(event_cnt!=63)event_cnt=event_ptr;
lc640_write_int(CNT_EVENT_LOG,event_cnt); 
	
lc640_adr=EVENT_LOG+(lc640_read_int(PTR_EVENT_LOG)*32);
	
data[0]='U';
data[1]=0;
data[2]='R';
data[3]=0;
lc640_write_long_ptr(lc640_adr,data);

data[0]=0;
data[1]=0;
data[2]=0;
data[3]=0;
lc640_write_long_ptr(lc640_adr+4,data);

data[0]=LPC_RTC->YEAR;
data[1]=LPC_RTC->MONTH;
data[2]=LPC_RTC->DOM;
data[3]=0;
lc640_write_long_ptr(lc640_adr+8,data);

data[0]=LPC_RTC->HOUR;
data[1]=LPC_RTC->MIN;
data[2]=LPC_RTC->SEC;
data[3]=0;
lc640_write_long_ptr(lc640_adr+12,data);
	
data[0]='A';
data[1]='A';
data[2]='A';
data[3]='A';
lc640_write_long_ptr(lc640_adr+16,data);
	
data[0]='A';
data[1]='A';
data[2]='A';
data[3]='A';
lc640_write_long_ptr(lc640_adr+20,data);
	
data[0]='A';
data[1]='A';
data[2]='A';
data[3]='A';
lc640_write_long_ptr(lc640_adr+24,data);
	
data[0]='A';
data[1]='A';
data[2]='A';
data[3]='A';
lc640_write_long_ptr(lc640_adr+28,data);				
	
	
}
