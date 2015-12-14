#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "printer.h"
#include "flash.h"
#include "code.h"

//extern void test_message(void);

int main()
{		
//  test_message();
	IntialNormal();	//正常启动加载函数
//	cleareeprom();
//	IntialOriginal();
//	readalleeprom();	
//	readflash();
//	SCR &= ~SCR_BOOT_MODE_MASK; 
//	SCR |= SCR_BOOT_MODE0_MASK;
//	COPTO=0xFFFF;
//	COPCTL|=COPCTL_CEN_MASK;	//COP使能
	while(1)
	{
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;
		switch(STATE)
		{
			
			case(5):	//状态5进入时间界面
				{
					RunTimeLocation();
					break;
				}			
			
			case(1):	//状态1进入信息内容主界面，全局变量State1parameter为入口参数
						//进入该界面后分别用subback判断是否从子菜单进入 	
  						//和用Returntype来判断返回时从何菜单出去
				{     
					RunMessage(State1parameter);
					break;	
				}
				
			case(11):	//状态11进入信息内容子界面
				{
					RunMessageSubmenu();
					break;
				}
				
			case(12):	//状态12进入信息内容子界面下的锁定子菜单
				{
					RunMessage_LockSubmenu();
					break;
				}
			
			case(13):	//状态13进入信息内容子界面下的打印子菜单，全局变量State13parameter为入口参数
						//进入该界面后用PublicReturn来表示 用于判断返回时从何菜单出去
				{
					RunMessage_PrintSubmenu(State13parameter);
					break;
				}
												
			case(14):	//状态14进入锁定超容量菜单，全局变量State14parameter为入口参数
						//进入该界面后用subback来表示 用于判断返回时从何菜单出去
				{
					RunMessage_OverCapacity(State14parameter);
					break;
				}
						
			case(15):	//状态15进入打印出错界面
				{   
					RunMessage_PrintError();
					break;
				}

			case(16):	//状态16进入打印中界面
				{
					RunMessage_Printing();
					break;
				}			
			
			case(2):	//存储界面和锁定界面公用状态2，全局变量State2parameter为入口参数
						//进入该界面后分别用subback判断是否从子菜单进入 	
  						//和用Returnback来于判断返回时从何菜单出去
				{   
				    IntialLCD(0);
					RunSaveMenu(State2parameter);
					break;	
				}
				
			case(20):	//状态20进入存储界面子菜单
				{
					RunSaveSubMenu();
					break;
				}
				
				
			case(200):	//存储菜单下打印复选和锁定复选菜单的公用状态200，全局变量State200parameter为入口参数
						//进入该界面后分别用Selectsubback判断是否从子菜单进入 	
  						//和用Selectreturn来判断返回时从何菜单出去
				{
					RunSaveLockSubMenu(State200parameter);
					break;	
				}				

			case(2000):	//存储和锁定菜单下的锁定和解锁确认的公用状态2000，全局变量State2000parameter为入口参数

				{
					RunSaveLockSubSure(State2000parameter);
					break;	
				}
	
			case(201):	//状态201进入存储界面子菜单下的打印子菜单
				{
					RunSavePrintSubMenu();
					break;	
				}
				
			case(2010):	//状态2010进入存储界面子菜单下的打印子菜单中批处理菜单
				{
					RunSavePitchPrint();
					break;	
				}
			case(2011):	//批处理菜单下，存储和锁定打印菜单状态2011，全局变量State2011parameter为入口参数
						//进入该界面后分别用PitchDAPro判断是从什么菜单进入 	
  					
				{
					RunSaveAllMessage();
					break;	
				}
								
			case(202):	//存储界面和锁定界面下排序菜单公用界面，全局变量State202parameter为入口参数
						//进入该界面后分别用Rankback判断是从何菜单进入 	
  						//和用Rankback来于判断返回时从何菜单出去
				{
					RunSaveRankSubMenu(State202parameter);
					break;	
				}
				
			case(2020):	//锁定菜单和存储菜单下排序菜单公用范围选择菜单，状态2020
				{
					RunSaveRangeChoose();
					break;
				}
				
			case(2021):	//锁定菜单和存储菜单下排序菜单范围选择确定菜单，状态2021
				{
					RunSaveRanking();
					break;
				}								
															
			case(30):	//状态30进入锁定界面子菜单
				{
					RunLockSubMenu();
					break;
				}
			case(300):	//锁定菜单下锁定复选菜单状态300，全局变量State300parameter为入口参数
						//进入该界面后分别用Selectsubback判断是否从子菜单进入 	
  						
				{
					RunLockLockSubMenu(State300parameter);
					break;	
				}
								
			case(4)://状态4进入主菜单界面，全局变量State4parameter为入口参数
					//进入该界面后用backpage来表示 用于判断返回时从何菜单出去
				
				{			
				    IntialLCD(0);
			  		RunMainMenu(State4parameter);
					break;
				}
				
			case(40):	//状态40进入发射台界面
				{
					RunRxstation();
					break;
				}
				
			case(400)://状态400进入自动模式设置界面，全局变量State400parameter为入口参数
					  //进入该界面后用subback来判断从何菜单进入
				{
					RunAutomode(State400parameter);
					break;
				}
								
			case(401)://状态401进入手动模式设置界面，全局变量State401parameter为入口参数
					  //进入该界面后用subback来判断从何菜单进入
				{
					RunManualmode(State401parameter);
					break;
				}
				
			case(4000)://状态4000进入401和402公共子界面，全局变量State4000parameter为入口参数
					  //进入该界面后用parameter来判断从何菜单进入
				{
					RunAutomodeSubmenu(State4000parameter);
					break;
				}								
			
			case(41)://状态41进入信息类别设置界面，全局变量State41parameter为入口参数
				     //进入该界面后用subback来判断从何菜单进入
				{
					RunMessagetypemenu(State41parameter);
					break;
				}
				
			case(42):	//状态42进入显示设置界面
				{
					RunDisplaySetting();
					break;
				}
			
			case(43):	//状态43进入接收机设置界面
				{
					RunReceiveSetting();
					break;
				}
				
			case(44):	//状态44进入维护设置界面
				{
					RunMaintain(State44parameter);
					break;
				}
				
			case(440):	//状态440进入自检界面
				{
					RunSelfDiagnosis();
					break;
				}
				
			case(4400):	//状态4400进入自检日志界面
				{
					RunDiaglog();
					break;
				}
				
			case(441):	//状态441进入接收机状态界面
				{
					RunNavtexState();					
					break;
				}						

			case(442):	//状态442进入恢复出厂设置确认菜单
				{
					RunRecoverFactory();
					break;
				}
							
			case(45):	//状态45进入语言选择界面
				{
					RunLanguageSetting();
					break;
				}
			default:
				{
					FLAG=0;
					STATE=1;	
					BUFFER[0]=0;
					State1parameter=0;		//为了指向新信息，这里直接表示从存储界面进入 ，且是DISP进入，无返回键可用modified@2010-8-17
					CLEAR1();
					break;				
				}					
		}    
	FLAG=1;	
	}   
}
