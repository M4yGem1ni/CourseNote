#ifndef __NIXIE__
#define __NIXIE__
extern unsigned char Nixie_Buf[];
void Nixie(unsigned char loc,unsigned char num);
void Nixie_SetBuf(unsigned char loc,unsigned char Data);
void Nixie_Loop();

#endif