#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"



/********************************************************/
/*功能；完成上下移动标记和左下角信息的显示数
入口参数：无
出口参数：无
/********************************************************/   
void LockMenu_biaoji2();
void LockMenu_biaoji2()
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
void LockMenu_Paint2();
void LockMenu_Paint2()
{	
	char i,j;
	j=0;
	for(i=BUFFERSELECT[21];(i>=0&&(BUFFERSELECT[21]-i)<6);i--)
	{	
		W_MSGTOP(i,5+4*j,1);
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
void Fuxuanbiaoji2();
void Fuxuanbiaoji2()
{
	if(Messagesavetop[Msglockrank[Mulnownumber]].select==1) W_CHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);	//复选选定打勾
	else  W_CANCALCHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);									//清除复选标记
}


/********************************************************/
/*功能；锁定复选或打印复选的显示
入口参数：无
出口参数：无
/********************************************************/
void LockLockSubMenu_Paintintial();
void LockLockSubMenu_Paintintial()
{

	byte i;
	if(Selectsubback==10) 
	RecoverData();	//从子菜单返回，只需恢复被覆盖的数据
	else 
	{

		if(LANGUAGE==0)
		{

		     /* 写入表头第一行数据MULTI_UNLOCK */
			CTAB[2]='M';	CTAB[3]='U';	CTAB[4]='L';	CTAB[5]='T';	CTAB[6]='I';	 CTAB[7]='-';
			CTAB[8]='U';	CTAB[9]='N';	CTAB[10]='L';	CTAB[11]='O';	CTAB[12]='C';	 CTAB[13]='K';
			CW_PR(0,1,14);
	
		     /* 写入表头第二行数据ID FREQ LINES DATE TIME  */
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

			
	 		CCW_PR1(1,3,0xd0c5,1);		//表头内容"信息解锁"
	 		CCW_PR1(3,3,0xcfa2,1);
	 		CCW_PR1(5,3,0xbde2,1);
	 		CCW_PR1(7,3,0xcbf8,1);
	 		
	 		
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
		CW_PR(0,29,16); //完成字符区显示
		

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
   		BUFFERSELECT[21]=Messagenumber-1;//初始化加载BUFFERSELECT[21]的值为最后一条信息的编号
   		Mulnownumber=Messagenumber-1;
		LockMenu_Paint2();					//信息摘要的显示
		LockMenu_biaoji2();					//完成上下移动标记和左下角信息的显示数

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
void LockLockSubMenu_Updn();
void LockLockSubMenu_Updn()
{

		if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
		{
			if(G_Key == DOWN&&Mulnownumber>0)
			{	
				if((Mulnownumber+5)>BUFFERSELECT[21])	//此时下选的那条信息在LCD显示屏中
				{
					Mulnownumber--;			//当前所选信息减1
					W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//对应滑块的修改，滑块用于标记当前所选信息
					W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+1);
				}
				
				else if((Mulnownumber+5)==BUFFERSELECT[21])	//此时下选的那条信息不在LCD显示屏中
				{
					Mulnownumber--;		//当前所选信息减1
					BUFFERSELECT[21]--;	//页面首条信息也须减1
					LockMenu_Paint2();	//LCD须重新显示，有新的信息要显示
				}
				LockMenu_biaoji2();		//完成上下移动标记和左下角信息的显示数
				G_Key=0;				
			}
				
	
			else if(G_Key == UP&&((Mulnownumber+1)<Messagenumber))
			{	

				
				if(Mulnownumber==BUFFERSELECT[21])
				{
					Mulnownumber++;		//当前所选信息加1	
					BUFFERSELECT[21]++;	//页面首条信息也须加1
					LockMenu_Paint2();	//LCD须重新显示，有新的信息要显示
				}
				
				else if(Mulnownumber<BUFFERSELECT[21])
				{
					Mulnownumber++;	//当前所选信息加1
					W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//对应滑块的修改，滑块用于标记当前所选信息
					W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+9);
				}
				LockMenu_biaoji2();	//完成上下移动标记和左下角信息的显示数
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
void LockLockSubMenu_Leftright();
void LockLockSubMenu_Leftright()
{
	if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
	{	
		if(G_Key == RIGHT&&Mulnownumber>=Maxpagenum)	//往下翻页用Mulnownumber来做判断
														//Mulnownumber的值大于最大页面信息数则可翻页
		{

			Mulnownumber=Mulnownumber-Maxpagenum;//当前所选信息跳转	
			BUFFERSELECT[21]=BUFFERSELECT[21]-Maxpagenum;			

			LockMenu_Paint2();	//信息摘要的显示
			LockMenu_biaoji2();	//完成上下移动标记和左下角信息的显示数
			G_Key=0;			
		}
		else if(G_Key == LEFT&&(BUFFERSELECT[21]+Maxpagenum<Messagenumber))	//往上翻页用BUFFER[0]来做判断
																					//BUFFER[0]的值减去最大页面信息数小于总信息数则可翻页
		{
			Mulnownumber=Mulnownumber+Maxpagenum;
			BUFFERSELECT[21]=BUFFERSELECT[21]+Maxpagenum;
			LockMenu_Paint2();	//信息摘要的显示
			LockMenu_biaoji2();	//完成上下移动标记和左下角信息的显示数
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
void LockLockSubMenu_Return();
void LockLockSubMenu_Return()
{
	if(G_Key == CLR&&STATE==300)//作为锁定复选
	{
		sword i=0;

		BUFFERSELECT[21]=0;

		for(i=0;i<Messagenumber;i++)	//复选标记位全部清零
		Messagesavetop[Msglockrank[i]].select=0;
		BUFFER1[0]=0;			//越一级跳出中间的全局变量清零
		FLAG=0;					//结束循环
		STATE=2;				//本界面的两种菜单返回都到SaveMenu，状态为2
		State2parameter=2;		//入口参数为2，锁定复选界面返回锁定菜单
		G_Key=0;
	}

}


/*****************************************/
/*功能；复选的选定
入口参数：无
出口参数：无
/****************************************/
void LockLockSubMenu_Dealing();
void LockLockSubMenu_Dealing()
{
	if(G_Key == ENT)
	{
		Messagesavetop[Msglockrank[Mulnownumber]].select=(Messagesavetop[Msglockrank[Mulnownumber]].select+1)%2;
		Fuxuanbiaoji2();	//复选结果的显示	
		G_Key=0;		//按键清零
	}
}


/*****************************************/
/*功能；解锁复选的子菜单
入口参数：无
出口参数：无
/****************************************/
void LockLockSubMenu_Star();
void LockLockSubMenu_Star()
{
	if(G_Key == STAR&&STATE==300)
	{

//		ProtectData();			//保护被弹出界面覆盖的数据
		FLAG=0;					//结束循环
		STATE=2000;				//SaveLockSubSure的状态为2000
		State2000parameter=1;	//入口参数1，作为解锁复选的子菜单
		G_Key=0;				//按键清零
	}

}


/*********************************************************/
/*	功能；解锁复选菜单，用于进行多条信息的解锁
		  信息有无选定根据信息头文件当中的select位来判定
          本菜单用到的全局变量有
		  BUFFERSELECT[21] 页面首条显示信息编号
		  Mulnumber作为复选界面的当前所在信息条数
		  Selectsubback用于进入复选界面的界面参数保护
入口参数：into  记录从何菜单进入
出口参数：无
/*********************************************************/
void RunLockLockSubMenu(unsigned char into)
{
    maske=0;
    maskc=0;
	Selectsubback=into;
	LockLockSubMenu_Paintintial();
	
	while(FLAG)
	{
		LockLockSubMenu_Updn();
		LockLockSubMenu_Leftright();
		LockLockSubMenu_Dealing();
		LockLockSubMenu_Star();
		LockLockSubMenu_Return();
		run_tip();
	}
}