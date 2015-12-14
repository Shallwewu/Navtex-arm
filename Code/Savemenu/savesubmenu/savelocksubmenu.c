#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
/********************************************************/
/*功能；完成上下移动标记和左下角信息的显示数
入口参数：无
出口参数：无
/********************************************************/ 
void SaveMenu_biaoji1();
void SaveMenu_biaoji1()
{
	if(Mulnownumber>0) W_DOWNMOVE(39,29);
	else W_CLEARUPDN(39,29);
	
	if(Mulnownumber<(Messagenumber-1)) W_UPMOVE(39,1);
	else W_CLEARUPDN(39,1);
	DISASCIII(16,29,Messagenumber);
	DISASCIII(12,29,Messagenumber-Mulnownumber);
}


/********************************************************/
/*功能；完成信息摘要的显示
入口参数：无
出口参数：无
/********************************************************/
void SaveMenu_Paint1();
void SaveMenu_Paint1()
{	
	sword i,j;
	j=0;
	for(i=BUFFERSELECT[21];(i>=0&&(BUFFERSELECT[21]-i)<6);i--)
	{	
		W_MSGTOP(i,5+4*j,0);
		j++;	
	}
	if(j<6)
	{
		for (j;j<6;j++)
		W_CLEARMSGTOP(5+4*j);		
	}
}
/********************************************************/
/*功能；完成复选标记的显示
入口参数：无
出口参数：无
/********************************************************/
void Fuxuanbiaoji();
void Fuxuanbiaoji()
{
	if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1) W_CHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);	//复选选定打勾
	else  W_CANCALCHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);									//清除复选标记
}

/********************************************************/
/*功能；锁定复选或打印复选的显示
入口参数：无
出口参数：无
/********************************************************/
void SaveLockSubMenu_Paintintial();
void SaveLockSubMenu_Paintintial()
{
	byte i;
	if(Selectsubback==10) RecoverData();	//从子菜单返回，只需恢复被覆盖的数据
	else 
	{
		if(LANGUAGE==0)
		{
		     /* 写入表头第一行数据 */
			CTAB[2]='M';	CTAB[3]='U';	CTAB[4]='L';	CTAB[5]='T';	CTAB[6]='I';	 CTAB[7]='-';
			CTAB[8]='C';	CTAB[9]='H';	CTAB[10]='O';	CTAB[11]='O';	CTAB[12]='S';	 CTAB[13]='E';
			CW_PR(0,1,14);

		     /* 写入表头第二行数据 */
			CTAB[4]='I';	 CTAB[5]='D';	 CTAB[10]='F';	 CTAB[11]='R';	  CTAB[12]='E'; CTAB[13]='Q';
		    CTAB[16]='L';   CTAB[17]='I';  CTAB[18]='N';  CTAB[19]='E';   CTAB[20]='S';
		    CTAB[23]='D';   CTAB[24]='A';  CTAB[25]='T';  CTAB[26]='E';   CTAB[31]='T'; 
		    CTAB[32]='I';   CTAB[33]='M';  CTAB[34]='E';     
			CW_PR(0,3,35);	
		}
		
		else
		{

		    CLEARXLINE(0,39,3);		//调整显示窗口
			CLEARXLINE(0,39,4);
			CLEARXLINE(0,39,5);
			CLEARXLINE(0,39,22);	
			XLINE(0,39,19);
			
	 		CCW_PR1(1,3,0xb8b4,1);	//复选菜单
	 		CCW_PR1(3,3,0xd1a1,1);
	 		CCW_PR1(5,3,0xb2cb,1);
	 		CCW_PR1(7,3,0xb5a5,1);
	 		
	  		CW_PR3(4,3,'I');CW_PR3(5,3,'D');	//标志符内容"频率 行数 日期 时间"
	 		CCW_PR1(10,20,0xc6b5,1);
	 		CCW_PR1(12,20,0xc2ca,1);
	 		CCW_PR1(16,20,0xd0d0,1);
	 		CCW_PR1(18,20,0xcafd,1);
	 	 	CCW_PR1(23,20,0xcab1,1);
	 		CCW_PR1(25,20,0xbce4,1);
	 	 	CCW_PR1(31,20,0xc5c5,1);
	 		CCW_PR1(33,20,0xd0f2,1);					
		}

	     /* 写入数据 */
		CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='A';	CTAB[6]='M';
		CTAB[7]='O';	CTAB[8]='U';	CTAB[9]='N';	CTAB[10]='T';	CTAB[11]=':';
		CTAB[15]='/';
		CW_PR(0,29,16); 			//总信息数量和当前信息数的显示


		XLINE(0,37,36);			//界面框图的显示，一条信息摘要占有3行
		W_XLINE(304,309,36);
		XLINE(0,37,37);
		W_XLINE(304,309,37);
		XLINE(0,37,68);
		W_XLINE(304,309,68);
		XLINE(0,37,69);
		W_XLINE(304,309,69);
		XLINE(0,37,100);		
		W_XLINE(304,309,100);
		XLINE(0,37,196);
		W_XLINE(304,309,196);
		XLINE(0,37,197);
		W_XLINE(304,309,197);
		
		XLINE(0,39,229);
		CLEARXLINE(0,39,230);
		
		W_YLINE(0,0,239);
		W_YLINE(309,0,239);
		W_YLINE(319,0,239);			//完成图形区显示

  
   		W_BLOCK(39,5);				//能进入本菜单，必存在信息
//   		BUFFERSELECT[21]=Messageinfo.savenumber[0]-1;//初始化加载BUFFERSELECT[21]的值为最后一条信息的编号
//   		Mulnownumber=Messageinfo.savenumber[0]-1;
  		BUFFERSELECT[21]=Messagenumber-1;//初始化加载BUFFERSELECT[21]的值为最后一条信息的编号
  		Mulnownumber=Messagenumber-1;

		SaveMenu_Paint1();					//信息摘要的显示
		SaveMenu_biaoji1();					//完成上下移动标记和左下角信息的显示数

	}

	XLINE(0,37,101);
	W_XLINE(304,309,101);
	XLINE(0,37,132);
	W_XLINE(304,309,132);
	XLINE(0,37,133);
	W_XLINE(304,309,133);
	XLINE(0,37,164);
	W_XLINE(304,309,164);
	XLINE(0,37,165);		
	W_XLINE(304,309,165);

	W_Mode(35,3,32,1);	//手动，自动模式的显示
	Selectsubback=0;	//判断使用完毕，清零	
}



/********************************************************/
/*功能；UP和DOWN按键处理函数，实现信息的上下移动选定功能，
		Mulnownumber指当前所选定的信息
入口参数：无
出口参数：无
/********************************************************/
void SaveLockSubMenu_Updn();
void SaveLockSubMenu_Updn()
{
	if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
	{
		if(G_Key == DOWN&&Mulnownumber>0)
		{	
	
			if((Mulnownumber+5)==BUFFERSELECT[21])	//此时下选的那条信息不在LCD显示屏中
			{
				Mulnownumber--;		//当前所选信息减1	
				BUFFERSELECT[21]--;	//页面首条信息也须减1
				SaveMenu_Paint1();	//LCD须重新显示，有新的信息要显示
			}
			
			else if(Mulnownumber+5>BUFFERSELECT[21])
			{
				Mulnownumber--;		//当前所选信息减1
				W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//对应滑块的修改，滑块用于标记当前所选信息
				W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+1);
			}
			SaveMenu_biaoji1();		//完成上下移动标记和左下角信息的显示数
			G_Key=0;
		}
			
		
		else if(G_Key == UP&&((Mulnownumber+1)<Messagenumber))
		{	

			
			if(Mulnownumber==BUFFERSELECT[21])
			{
				Mulnownumber++;		//当前所选信息加1	
				BUFFERSELECT[21]++;	//页面首条信息也须加1
				SaveMenu_Paint1();	//LCD须重新显示，有新的信息要显示
			}
			
			else if(Mulnownumber<BUFFERSELECT[21])
			{
				Mulnownumber++;		//当前所选信息加1
				W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//对应滑块的修改，滑块用于标记当前所选信息
				W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+9);
			}
			SaveMenu_biaoji1();		//完成上下移动标记和左下角信息的显示数
			G_Key=0;		
		}
	}
}

/********************************************************/
/*功能；LEFT和RIGHT按键处理函数，实现信息的上下翻页功能，
		上下翻页指整个页面的切换。
		Mulnownumber指当前所选定的信息
入口参数：无
出口参数：无
/********************************************************/
void SaveLockSubMenu_Leftright();
void SaveLockSubMenu_Leftright()
{
	if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
	{	
		if(G_Key == RIGHT&&Mulnownumber>=Maxpagenum)	//往下翻页用Mulnownumber来做判断
														//Mulnownumber的值大于最大页面信息数则可翻页
		{
			Mulnownumber=Mulnownumber-Maxpagenum;
			BUFFERSELECT[21]=BUFFERSELECT[21]-Maxpagenum;//当前所选信息跳转			
			SaveMenu_Paint1();					//信息摘要的显示
			SaveMenu_biaoji1();					//完成上下移动标记和左下角信息的显示数			
			G_Key=0;
		}
		else if(G_Key == LEFT&&((BUFFERSELECT[21]+Maxpagenum)<Messagenumber))
																	//往上翻页用BUFFER[0]来做判断
		{															//BUFFER[0]的值减去最大页面信息数小于总信息数则可翻页			Mulnownumber=Mulnownumber+Maxpagenum;
			Mulnownumber=Mulnownumber+Maxpagenum;
			BUFFERSELECT[21]=BUFFERSELECT[21]+Maxpagenum;
			SaveMenu_Paint1();					//信息摘要的显示
			SaveMenu_biaoji1();					//完成上下移动标记和左下角信息的显示数				
			G_Key=0;
		}
	}
}



/*****************************************/
/*功能；本菜单的退出，锁定复选菜单隔一级跳出，
        打印复选隔3级跳出，中间级菜单使用到
        的全局变量必须全部清零
入口参数：无
出口参数：无
/****************************************/
void SaveLockSubMenu_Return();
void SaveLockSubMenu_Return()
{
	if(G_Key == CLR&&STATE==200)//作为锁定复选
	{
		sword i=0;

		BUFFERSELECT[21]=0;		//本菜单使用的全局变量清零
		BUFFERSELECT[1]=0;
		BUFFERSELECT[2]=0;
		BUFFERSELECT[3]=0;
		BUFFERSELECT[0]=0;
		for(i=0;i<Messagenumber;i++)	//复选标记位全部清零
		Messagesavetop[Messagetoprank[i]].select=0;

		BUFFER1[0]=0;			//越一级跳出中间的全局变量清零
		FLAG=0;					//结束循环
		STATE=2;				//本界面的两种菜单返回都到SaveMenu，状态为2
		State2parameter=1;		//入口参数为1
		if(Selectreturn==1)	  	//此时本界面作为打印复选菜单，越三级跳出，中间使用的全局变量清零	                               
		{
			BUFFER2[0]=0;
			BUFFER3[0]=0;
		}	
		G_Key=0;				//按键清零
	}
}



/*****************************************/
/*功能；复选的选定，对于锁定复选菜单，只有
        未锁定的信息能够加上复选标记
        对于打印复选，则无限制
入口参数：无
出口参数：无
/****************************************/
void SaveLockSubMenu_Dealing();
void SaveLockSubMenu_Dealing()  //只有未锁定的信息能够加上复选标记
{
	char i;
	if(G_Key == ENT&&Messagesavetop[Messagetoprank[Mulnownumber]].lock==0&&Selectreturn==0)//作为锁定复选
	{
        
        Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
        i=Messagesavetop[Messagetoprank[Mulnownumber]].frequency;
        if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[i]++;	//选定条件下，通道信息数量加1
						BUFFERSELECT[0]++;				//总锁定数量加1
					}
		if(BUFFERSELECT[i]<=Maxlocknum)Fuxuanbiaoji();
		else 
		{
		    Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
			BUFFERSELECT[i]--;	//清除选定，通道信息数量减1
			BUFFERSELECT[0]--;
			FLAG=0;					//结束循环
			State14parameter=1;		//入口参数1，表明由锁定复选调用	
			ProtectData();
			CLEAR2();			
			STATE=14;				//Message_OverCapacity的状态14
		
		}
/*		switch(Messagesavetop[Messagetoprank[Mulnownumber]].frequency)
		{
			case 1:   //处于518通道
			{

				if(BUFFERSELECT[1]<=Maxlocknum)	//通道1的锁定数量未满
				{
				//	Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
					if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[1]++;	//选定条件下，通道信息数量加1
						BUFFERSELECT[0]++;				//总锁定数量加1
					}
					
					else
					{
						BUFFERSELECT[1]--;	//清除选定，通道信息数量减1
						BUFFERSELECT[0]--;				//总信息数量减1						
					}
					Fuxuanbiaoji();			//显示复选结果
				}
				else
				{
				    
					FLAG=0;					//结束循环
					STATE=14;				//Message_OverCapacity的状态14
					State14parameter=1;		//入口参数1，表明由锁定复选调用				
				}
				break;
			}
			case 2:  //处于490通道，同上
			{
				if(BUFFERSELECT[2]<=Maxlocknum)
				{
				
				
			//		Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
					if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[2]++;
						BUFFERSELECT[0]++;
					}
					else
					{
						BUFFERSELECT[2]--;
						BUFFERSELECT[0]--;						
					}
				    Fuxuanbiaoji();					
				}
				else
				{
		
					FLAG=0;
					STATE=14;
					State14parameter=1;	
				}
				break;
				
			}
			default:	//处于4209.5通道，同上
			{
				if(BUFFERSELECT[3]<=Maxlocknum)
				{
			//		Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
					if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[3]++;
						BUFFERSELECT[0]++;
					}
					
					else
					{
						BUFFERSELECT[3]--;
						BUFFERSELECT[0]--;						
					}
					Fuxuanbiaoji();					
				}
				else
				{
				//	ProtectData();
					FLAG=0;
					STATE=14;
					State14parameter=1;	
				}
				
			}

		}*/
		G_Key=0;	
	}
	
	if(G_Key == ENT&&Selectreturn==1)	//打印复选
	{
		Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
		Fuxuanbiaoji();	//复选结果的显示
		G_Key=0;		//按键清零
	}
	
	
}

/*****************************************/
/*功能；锁定复选和打印复选的子菜单
入口参数：无
出口参数：无
/****************************************/
void SaveLockSubMenu_Star();
void SaveLockSubMenu_Star()
{
	if(G_Key == STAR&&Selectreturn==0&&STATE==200)	//跳转至锁定复选的子菜单SaveLockSubSure
	{
		FLAG=0;					//结束循环
		STATE=2000;				//SaveLockSubSure的状态为2000
		State2000parameter=0;	//入口参数0，作为锁定复选的子菜单
		G_Key=0;				//按键清零
	}
	
	else if(G_Key == STAR&&Selectreturn==1&&STATE==200)	//跳转至打印复选的子菜单Message_PrintSubmenu
	{
		G_Key=0;				//按键清零
		FLAG=0;					//结束循环
		STATE=13;				//Message_PrintSubmenu的状态为13
		State13parameter=3;		//入口参数为3，由打印人工复选界面选定信息调用
	}	
}


/*********************************************************/
/*	功能；锁定复选和打印复选共用，用于进行多条信息的打印或锁定
		  信息有无选定根据信息头文件当中的select位来判定
          本菜单用到的全局变量有
		  BUFFERSELECT[21] 页面首条显示信息编号
		  BUFFERSELECT[1] 518khz暂时通道锁定总数
		  BUFFERSELECT[2] 490khz暂时通道锁定总数 
		  BUFFERSELECT[3] 4209.5khz暂时通道锁定总数
		  BUFFERSELECT[0] 三通道暂时总的锁定信息数
		  Mulnumber作为复选界面的当前所在信息条数
		  Selectreturn用于复选界面的出口参数保护
		  Selectsubback用于进入复选界面的界面参数保护
入口参数：into  记录从何菜单进入
出口参数：无
/*********************************************************/
void RunSaveLockSubMenu(unsigned char into)//锁定复选界面和打印复选界面的公用
{
    maske=0;
    maskc=0;
	Selectsubback=into;
	if(into!=10)
	{
		BUFFERSELECT[0]=Messageinfo.locknumber[0];//初始化BUFFERSELECT[0]为零，用于记录锁定信息条数
		Selectreturn=into;
		BUFFERSELECT[1]=Messageinfo.locknumber[1];
		BUFFERSELECT[2]=Messageinfo.locknumber[2];
		BUFFERSELECT[3]=Messageinfo.locknumber[3];	
	}

	SaveLockSubMenu_Paintintial();
	
	while(FLAG)
	{
		SaveLockSubMenu_Updn();
		SaveLockSubMenu_Leftright();
		SaveLockSubMenu_Dealing();
		SaveLockSubMenu_Star();
		SaveLockSubMenu_Return();
		run_tip();

	}
  	
}