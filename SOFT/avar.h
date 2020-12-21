
//-----------------------------------------------
//Аварии источников
extern char cnt_av_umax[2],cnt_av_umin[2],cnt_av_t[2];

//-----------------------------------------------
//Флаги аварий
extern unsigned short av_beep,av_rele,av_stat;

void avar_bps_reset(char in);
void avar_bps_hndl(char bps, char in, char v);
void avar_bat_hndl(char in);
void wrk_mem_hndl(unsigned short in);
void vz_mem_hndl(unsigned short in);
void ke_mem_hndl(unsigned short in);
void avar_unet_hndl(char in);
void avar_src_hndl(char src, char in, char v);
void avar_src_reset(char in);
void reload_hndl(void);
