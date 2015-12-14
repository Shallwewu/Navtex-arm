#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //自己加的关于FPGA读写





void LcdDisplay();
void LcdDisplay()
{
	switch(STATE)
	{
		
		case(5):	//状态5进入时间界面
			{
				if(G_Key == MENU) 
				{
					CLEAR1();			//清一区和二区的存储空间
				}
				
				else if(G_Key == DISP) 
				{
					CLEAR1();			//清一区和二区的存储空间
				}
				break;
			}			
		
		
		case(1):	//状态1进入信息内容主界面，全局变量State1parameter为入口参数
					//进入该界面后分别用subback判断是否从子菜单进入 	
					//和用Returntype来判断返回时从何菜单出去
			{
/*				if(G_Key==LEFT||G_Key==RIGHT)
				{
					if (G_Key==LEFT)				//上一条信息处理
					{
						if(Messagenownumber>0)		//可以进行上翻信息
						{
							CLEAR1();			//清一区和二区的存储空间
						}
					}
					
					else if (G_Key==RIGHT&&(Returntype==1||Returntype==0||Returntype==3))		//存储信息处理的下翻信息处理
					{
						if(Messagenownumber<Messageinfo.savenumber[0]-1) 	//可以进行下翻处理
						{
							CLEAR1();			//清一区和二区的存储空间
						}
					}
				
					else if (G_Key==RIGHT&&(Returntype==2||Returntype==4))						//锁定信息处理的下翻信息处理
					{
						if(Messagenownumber<Messageinfo.locknumber[0]-1) 	//可以进行下翻处理
						{
							CLEAR1();			//清一区和二区的存储空间
						}			
					}
				}
				
				if (G_Key==STAR)
				{	
					ProtectData();
					CLEAR2();		//弹出子菜单区域数据清空
				}*/
				
				
				if (G_Key==MENU||G_Key==DISP||(G_Key==CLR&&Returntype!=0))	//跳转进入MainMenu界面，入口参数0
				{
					if(now_printing==0)	
						CLEAR1();			//清一区和二区的存储空间
				}
					

				break;	
			}
			



		case(10):	//状态10进入无信息内容界面，全局变量State10parameter为入口参数
					//进入该界面后用PublicReturn来表示 用于判断返回时从何菜单出去
			{
				if(G_Key==ENT)
				{
					CLEAR2();		//弹出子菜单区域数据清空
				}
				break;
			}
		
		case(11):	//状态11进入信息内容子界面
			{
				if (G_Key==CLR/*||G_Key==LEFT*/||G_Key==ENT)
				{
					CLEAR2();		//弹出子菜单区域数据清空
				}

				break;
			}
			
		case(12):	//状态12进入信息内容子界面下的锁定子菜单
			{
			
				if (G_Key==ENT)
				{
					if(BUFFER2[0]==0&&Messagesavetop[Messagetoprank[Messagenownumber]].lock==1)
						CLEAR1();
					else
					{
						CLEAR2();
					}
				}
				break;
			}
		
			
		case(13):	//状态13进入信息内容子界面下的打印子菜单，全局变量State13parameter为入口参数
					//进入该界面后用PublicReturn来表示 用于判断返回时从何菜单出去
			{
				if (G_Key==ENT)
				{
					CLEAR2();
				}
				break;
			}
											
		case(14):	//状态14进入锁定超容量菜单，全局变量State14parameter为入口参数
					//进入该界面后用subback来表示 用于判断返回时从何菜单出去
			{
				if (G_Key==ENT)
				{
					CLEAR2();
				}
				break;
			}
					
		case(15):	//状态15进入打印出错界面
			{
				if (G_Key==ENT)
				{
					CLEAR2();
				}
				break;
			}

		case(16):	//状态16进入打印中界面
			{
				
				break;
			}			
		
		case(2):	//存储界面和锁定界面公用状态2，全局变量State2parameter为入口参数
					//进入该界面后分别用subback判断是否从子菜单进入 	
					//和用Returnback来于判断返回时从何菜单出去
			{
				if(G_Key == STAR&&Messagenumber) 
				{
					ProtectData();				
					CLEAR2();	
				}
				else if(G_Key == DISP||G_Key == MENU) CLEAR1();
				else if(G_Key == ENT&&Messagenumber!=0) CLEAR1();
				break;	
			}
			
		case(20):	//状态20进入存储界面子菜单
			{
				if(/*G_Key == LEFT ||*/ G_Key == CLR)
				CLEAR2();
				else if(G_Key==ENT&&BUFFER1[0]==1)
				CLEAR1();
				else if(G_Key==ENT&&BUFFER1[0]!=1)
				CLEAR2();
				
				break;
			}
			
			
		case(200):	//存储菜单下打印复选和锁定复选菜单的公用状态200，全局变量State200parameter为入口参数
					//进入该界面后分别用Selectsubback判断是否从子菜单进入 	
					//和用Selectreturn来判断返回时从何菜单出去
			{
				if(G_Key == CLR) CLEAR1();
//				else if(BUFFERSELECT[Messagesavetop[Messagetoprank[Mulnownumber]].frequency]>Maxlocknum&&Selectreturn==0)
//				{
//					ProtectData();
//					CLEAR2();
//				}
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				}			
				break;	
			}				

		case(2000):	//存储和锁定菜单下的锁定和解锁确认的公用状态2000，全局变量State2000parameter为入口参数

			{
				if(G_Key == ENT&&BUFFER3[0] == 0)
				CLEAR1();
				else if(G_Key == ENT&&BUFFER3[0] == 1)
				CLEAR2();
				break;	
			}

		case(201):	//状态201进入存储界面子菜单下的打印子菜单
			{
				if(/*G_Key == LEFT || */G_Key == ENT || G_Key == CLR)
				CLEAR2();
				break;	
			}
		case(2010):	//状态2010进入存储界面子菜单下的打印子菜单中批处理菜单
			{
				if(/*G_Key == LEFT || */G_Key == CLR)
				CLEAR2();
				else if(G_Key==ENT&&BUFFER3[0]==2)
				CLEAR1();
				else if(G_Key==ENT&&BUFFER3[0]!=2)
				CLEAR2();				
				break;	
			}
		case(2011):	//批处理菜单下，存储和锁定打印菜单状态2011，全局变量State2011parameter为入口参数
					//进入该界面后分别用PitchDAPro判断是从什么菜单进入 	
				
			{
				if(G_Key == ENT&&(BUFFER4[0]==3||BUFFER4[0]==4))
				CLEAR2();
				break;	
			}
						
				
		case(202):	//存储界面和锁定界面下排序菜单公用界面，全局变量State202parameter为入口参数
					//进入该界面后分别用Rankback判断是从何菜单进入 	
					//和用Rankback来于判断返回时从何菜单出去
			{
				if(/*G_Key == LEFT || */G_Key == CLR || G_Key == ENT)
				CLEAR2();
				break;	
			}
			
		case(2020):	//锁定菜单和存储菜单下排序菜单公用范围选择菜单，状态2020
			{
				if(/*G_Key == LEFT || */G_Key == CLR || G_Key == ENT)
				CLEAR2();
				break;
			}
			
														
		case(30):	//状态30进入锁定界面子菜单
			{
				if(/*G_Key == LEFT || */G_Key == CLR)
				CLEAR2();
				else if(G_Key==ENT&&BUFFER1[0]==1)
				CLEAR1();
				else if(G_Key==ENT&&BUFFER1[0]!=1)
				CLEAR2();	
				break;
			}
		case(300):	//锁定菜单下锁定复选菜单状态300，全局变量State300parameter为入口参数
					//进入该界面后分别用Selectsubback判断是否从子菜单进入 	
			{
				if(G_Key == CLR) CLEAR1();
				if(G_Key == STAR) 
				{
					ProtectData();
					CLEAR2();
				}
				break;	
			}
			
			
							
		case(4)://状态4进入主菜单界面，全局变量State4parameter为入口参数
				//进入该界面后用backpage来表示 用于判断返回时从何菜单出去
			
			{
				if(G_Key == DISP || G_Key == CLR || G_Key == ENT)
				CLEAR1();
				break;
			}
			
			
		case(40):	//状态40进入发射台界面
			{
				if (G_Key == CLR)
				CLEAR1();
				else if(G_Key == ENT&&(BUFFER1[0] == 2||BUFFER1[0] == 3))
				CLEAR1();
				break;
			}
			
		case(400)://状态400进入自动模式设置界面，全局变量State400parameter为入口参数
				  //进入该界面后用subback来判断从何菜单进入
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				} 
				break;
			}
							
		case(401)://状态401进入手动模式设置界面，全局变量State401parameter为入口参数
				  //进入该界面后用subback来判断从何菜单进入
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				}
				break;
			}
			
		case(4000)://状态4000进入401和402公共子界面，全局变量State4000parameter为入口参数
				  //进入该界面后用parameter来判断从何菜单进入
			{
				if(G_Key==ENT) CLEAR2();
				break;
			}								
		
		case(41)://状态41进入信息类别设置界面，全局变量State41parameter为入口参数
			     //进入该界面后用subback来判断从何菜单进入
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==STAR)
				{
					ProtectData();
					CLEAR2();
				}
				break;
			}
			
		case(42):	//状态42进入显示设置界面
			{
				if (G_Key==CLR&&BUFFER1[0]<5) CLEAR1(); 
				break;
			}
		
		
		case(43):	//状态43进入接收机设置界面
			{
				if(G_Key==CLR&&(BUFFER1[0]==0||BUFFER1[0]==1||BUFFER1[0]==6))
				CLEAR1();	
				break;
			}
			
		case(44):	//状态44进入维护设置界面
			{
				if (G_Key==CLR) CLEAR1();
				else if(G_Key==ENT&&(BUFFER1[0]==0||BUFFER1[0]==2))
				{
					CLEAR1();
				}
				else if(G_Key==ENT&&BUFFER1[0]==1)
				{
					ProtectData();
					CLEAR2();
				}

				break;
			}
			
		case(440):	//状态440进入自检界面
			{
				if (G_Key==CLR||(G_Key==ENT&&BUFFER2[0]==2))
				CLEAR1();
				break;
			}
			
		case(4400):	//状态4400进入自检日志界面
			{
				if (G_Key==CLR) CLEAR1();
				break;
			}
			
		case(441):	//状态441进入接收机状态界面
			{
				if (G_Key==CLR) CLEAR1();				
				break;
			}						

		case(442):	//状态442进入恢复出厂设置确认菜单
			{
				if (G_Key==ENT&&BUFFER2[0]==1) CLEAR2();	
				break;
			}
						
		case(45):	//状态45进入语言选择界面
			{
				if(G_Key==ENT||G_Key==CLR/*||G_Key==LEFT*/)	CLEAR1();
				break;
			}				
	}
	
}