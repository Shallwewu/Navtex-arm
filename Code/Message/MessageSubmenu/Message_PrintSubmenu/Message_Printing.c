#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "printer.h"
#include "iec.h"
#include "code.h"
//********************************************/
/*	功能：子菜单Message_Printing界面的显示
入口参数：无
出口参数：无
/*********************************************/
void Message_Printing_Paintintial();
void Message_Printing_Paintintial()
{
	byte i;


    if(LANGUAGE==0)
    {
	    CTAB[0]='N';  CTAB[1]='O';  CTAB[2]='T';  CTAB[3]='E';  CTAB[4]=':';
	    
	    if(State13parameter==0&&PublicReturn!=4)CW_PR(9,10,5);
	    else CW_PR(9,14,5);	//第一行显示内容"NOTE:"
	      
	    CTAB[1]='P';  CTAB[2]='R';   CTAB[3]='I';  CTAB[4]='N';   CTAB[5]='T';   CTAB[6]='I';
	    CTAB[7]='N';  CTAB[8]='G';CTAB[9]='!';   
	    //CTAB[11]='E';  CTAB[12]='N';  CTAB[13]='T';  CTAB[14]='E';  CTAB[15]='R';
	     
	    if(State13parameter==0&&PublicReturn!=4)CW_PR(9,11,10);
	    else CW_PR(9,16,10);	//第二行显示内容"PRINTINT! ENTER"

	    //CTAB[2]='C';   CTAB[3]='L';    CTAB[4]='R';	    CTAB[6]='T';    CTAB[7]='O';
	    //CTAB[9]='S';   CTAB[10]='T';   CTAB[11]='O';	    CTAB[12]='P';   CTAB[13]='!'; 
	    
	    //if(State13parameter==0)CW_PR(9,12,14); 
	    //else CW_PR(9,17,14);		//第三行显示内容"CLR TO STOP!"   
    }

    else
    {
 		CCW_PR1(9,112,0xcce1,1);	//第一行显示内容"提示:"
 		CCW_PR1(11,112,0xcabe,1);
 		CCW_PR1(13,112,0x1aa0,0);
  
 		CCW_PR1(15,112,0xb4f2,1);	//第二行显示内容"打印中"
		CCW_PR1(17,112,0xd3a1,1);
		CCW_PR1(19,112,0xd6d0,1);
 		//CCW_PR1(21,104,0x1780,0);
 		
		CCW_PR1(15,136,0xc7eb,1);
		CCW_PR1(17,136,0xb5c8,1);
		CCW_PR1(19,136,0xb4fd,1);
		CCW_PR1(21,136,0x1780,0);
 		 		
 	//	CCW_PR1(9,128,0xb0b4,1);	//第三行显示内容"按下CLR键返回"
	//	CCW_PR1(11,128,0xcfc2,1);
	//	CCW_PR1(16,128,0xbcfc,1);
 	//	CCW_PR1(18,128,0xb7b5,1);
 	//	CCW_PR1(20,128,0xbbd8,1);
  	//	CCW_PR1(22,128,0x1920,0);
	
	//	if(State13parameter==0&&PublicReturn!=4)
	//	{
	//	    CW_PR3(13,11,'C');
	 //       CW_PR3(14,11,'L');
	   //  	CW_PR3(15,11,'R'); 
		//}
	//	else
	//	{
	//		CW_PR3(13,17,'C');
	//     	CW_PR3(14,17,'L');
	//    	CW_PR3(15,17,'R');
	//	}
    }
    	
    WFRAME(); 		//弹出子菜单框图显示 
    	
//	for(i=0;i<3;i++)
//	{
//		W_CLEARXLINE(65,206,172+i);
//	   	W_CLEARYLINE(65+i,158,172);
//	   	W_CLEARYLINE(204+i,158,172);
//	   	W_XLINE(65,206,155+i);		
//	}

}
//********************************************/
/*	功能：打印完毕自动返回函数
入口参数：无
出口参数：无
/*********************************************/
void Message_Printing_Printover();
void Message_Printing_Printover() //return to savesubmenu 
{
	if(Checkinfo.Printover == 1)
	{
		Checkinfo.Printover=0;
		FLAG=0;
		switch(PublicReturn)
		{
			case 0:{BUFFER1[0]=0;STATE=1;State1parameter=10;}break;//返回到信息正文界面,越过两极菜单，对应两极菜单置零
			case 1:{BUFFER2[0]=0;STATE=20;}break;			//返回到存储界面的子菜单
			case 2:{BUFFER2[0]=0;STATE=20;}break;			//返回到存储界面的子菜单
															//打印完毕则返回到存储子菜单，越过两极菜单，对应两极菜单置零
			case 3:{STATE=200;State200parameter=10;}break;	//返回到打印复选界面
			case 4:{
						BUFFER4[0]=0;
						BUFFER2[0]=0;
						BUFFER3[0]=0;
						BUFFER4[1]=0;
						BUFFER4[2]=0;
						BUFFER4[3]=0;
						STATE=20;
					}break;									//打印完毕，调处至信息存储子菜单中间越过3级，把用到的BUFFER全部置零
		//	case 0:{PublicReturn=0;BUFFER1[0]=0;STATE=1;State1parameter=10;}break;//返回到信息正文界面,越过两极菜单，对应两极菜单置零
		//	case 1:{BUFFER2[0]=0;PublicReturn=0;RunSaveSubMenu();}break;//返回到存储界面的子菜单
		//	case 2:{BUFFER2[0]=0;PublicReturn=0;RunSaveSubMenu();}break;//返回到存储界面的子菜单
																//打印完毕则返回到存储子菜单，越过两极菜单，对应两极菜单置零
		//	case 3:{PublicReturn=0;RunSaveLockSubMenu(10);}break;//返回到打印复选界面
		//	case 4:{
		//				BUFFER4[0]=0;
		//				BUFFER2[0]=0;
		//				BUFFER3[0]=0;
		//				BUFFER4[1]=0;
		//				BUFFER4[2]=0;
		//				BUFFER4[3]=0;
		//				RunSaveSubMenu();
		//			}break;	//打印完毕，调处至信息存储子菜单中间越过3级，把用到的BUFFER全部置零
			default:break;			
		}
		CLEAR2();
		PublicReturn=0;
		now_printing=0;

	}
}

//********************************************/
/*	功能：打印中断强行返回函数
入口参数：无
出口参数：无
/*********************************************/
void Message_Printing_Return();
void Message_Printing_Return()
{
	if(G_Key == CLR) 
	{
		G_Key=0;
		FLAG=0;
		switch(PublicReturn)
		{
			case 0:{
			//if(State13parameter==0&&PublicReturn!=4)STATE=11;else STATE=20;
			        if(State13parameter==1||State13parameter==2)STATE=20;}break;	//返回到信息正文界面子菜单	
			case 1:{STATE=201;CLEAR2();}break;	//返回到存储界面的打印子菜单
			case 2:{STATE=201;CLEAR2();}break;	//返回到存储界面的打印子菜单
			case 3:{STATE=200;State200parameter=10;}break;//返回到打印复选界面
	    	case 4:{STATE=2010;}break;	//越级返回上一界面复选打印界面		
		//	case 0:{STATE=11;}break;//返回到信息正文界面子菜单	
		//	case 1:{PublicReturn=0;RunSavePrintSubMenu();}break;//返回到存储界面的打印子菜单
		//	case 2:{PublicReturn=0;RunSavePrintSubMenu();}break;//返回到存储界面的打印子菜单
		//	case 3:{PublicReturn=0;RunSaveLockSubMenu(10);}break;//返回到打印复选界面
		//	case 4:{PublicReturn=0;RunSavePitchPrint();}break;//越级返回上一界面复选打印界面
		//	default:break;	
		

				
		}
		CLEAR2();
		PublicReturn=0;
	}
}







//**************************************************************/
/*	功能：本界面作为打印界面子界面的公共界面
入口参数：byte 类型，记录从何菜单进入,用PublicReturn来记录
	      0 由信息内容界面调用
		  1 由打印单条信息界面调用
		  2 由打印状态界面调用
		  3 由打印人工复选界面选定信息调用
		  4 批处理信息的打印
出口参数：无
/***************************************************************/
void RunMessage_Printing()	//暂时未考虑打印机打印传输
{
    maske=0;
    maskc=0;
	Message_Printing_Paintintial();
	
	switch(PublicReturn)
	{
		case 0:	Printmessage(Messagetoprank[Messagenownumber]);break;			//打印一条信息的函数
		case 1:	Printmessage(Messagetoprank[Messageinfo.nownumber[0]]);break;	//打印一条信息的函数
		case 2:	Printstate();break; 							//打印接收机状态的函数
		case 3:	Printselect();break; 							//打印复选的函数
		case 4:	Selectgiven(BUFFER4[1],BUFFER4[2],BUFFER4[3],PitchDAPro);break;
		default:break;
	}

	while(FLAG)
	{
		Message_Printing_Printover();
		Message_Printing_Return();
		run_tip();
	}
  	
}