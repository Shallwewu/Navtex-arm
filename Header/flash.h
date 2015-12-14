#ifndef __flash_H
#define __flash_H

#include "define.h"
//char Check_SST_39VF160();

int Erase_One_Sector(uint32);
int Erase_One_Block (uint32);
//void Erase_Entire_Chip(void);
void Read_Chinese_Code(word Isn,char);
void WriteAMessToFlash(sword savenum,char *messagepoint);
void DelAMessFlash(sword);
char CFI_Query(void);
void ReadMessFlash(uint32 address,char *dout);
void Reset_Flash(void);
void ReadPrtMsg(void);
//void ZikuLoad();
void readflash(void);
//void Delay_1000_Milli_Seconds();
#endif
