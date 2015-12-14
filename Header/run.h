#ifndef __run_H
#define __run_H
#include "define.h"
void IntialOriginal(void);

void Timedisplay(void);//时间显示程序


void Rankfuction(char,char);//存储列表排序函数

void Ranktime(void);



void RunBoot(void);
void IntialIRQB(void);
void Diagresult_Paint(char list);

void IntialNormal(void);
void Init_Fpga(void);
void Fpga_reset(void);

void RunSaveMenu(unsigned char into);

void RunMainMenu(unsigned char into);
void RunLanguageChoose(void);

void RunTimeLocation(void);

//*Message*//
void RunMessage(unsigned char into);

void RunMessageSubmenu(void);
void RunMessage_LockSubmenu(void);//包括存储信息的锁定和解锁
void RunMessage_PrintSubmenu(unsigned char into);
void RunMessage_OverCapacity(unsigned char into);
void RunMessage_PrintError(void);
void RunMessage_Printing(void);

void SaveMenu_Paint1(void);

//                  savemenu           //
void RunSaveSubMenu(void);

void Nownumber(char mode);

//                  savemenu-nomessage           //



//                  savemenu-savesubmenu           //
void RunSaveRankSubMenu(unsigned char into);
void RunSaveLockSubMenu(unsigned char into);
void RunSavePrintSubMenu(void);

//                  savemenu-savesubmenu-saveranksubmenu           //
void RunSaveRangeChoose(void);

//                  savemenu-savesubmenu-savelocksubmenu       
void RunSaveLockSubSure(unsigned char into);



void RunSavePitchPrint(void);




//                savemenu-savesubmenu-saveranksubmenu-saverangechoose  //
void RunSaveRanking(void);

//                savemenu-savesubmenu-saveprintsubmenu-savepitchprint      //
void RunSaveAllMessage(void);

//                  lockmenu           //
void RunLockSubMenu(void);

void RunLockLockSubMenu(unsigned char into);








//	mainmenu    //									
void RunAutomode(unsigned char into);
void RunManualmode(unsigned char into);
void RunMessagetypemenu(unsigned char into);
void RunRxstation(void);
void RunDisplaySetting(void);
void RunLanguageSetting(void);
void RunMaintain(byte into);
void RunSelfDiagnosis(void);
void RunNavtexState(void);
void RunReceiveSetting(void);
void RunAutomodeSubmenu(byte into);
void RunDiaglog(void);
void RunRecoverFactory(void);
word Power(short int mici);

//显示
void run_tip(void);
//键盘//

void isrIRQprocess(void);
void IRQBjietiao(void);//8k中断

//FLASH//
void RunNewmsgtip(void);

 void Selfdiag(char temp);//自检函数
 void SelfDiagnosis_Partpaint(void);
 void LcdDisplay(void);//界面显示函数
  void readalleeprom(void);  //@wuxianwei
#endif
