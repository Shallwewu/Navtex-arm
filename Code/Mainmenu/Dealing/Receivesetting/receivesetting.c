#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "printer.h"
#include "code.h"

//起始波特率输入在屏幕中位置 英文(18,14) 中文(18,15)

/*********************************************/
/*	功能：误码率设定显示函数
入口参数：无
出口参数：无
/*********************************************/
void Receiversetting_Paint_Cer();
void Receiversetting_Paint_Cer()
{
   
	   if(Receiverset[0]==0) 			//误码率开，英文显示：ON,中文显示：开
	   {
	   		if(LANGUAGE==0)
	   		{
	   			CW_PR3(17,5,'O');
	   			CW_PR3(18,5,'N');
	   			CW_PR3(19,5,' ');
	   		}
	   		else CCW_PR1(13,40,0xbfaa,1);
	   }
	   
	   if(Receiverset[0]==1)			//误码率关，英文显示：OFF 中文显示：关
	   {
	   		if(LANGUAGE==0)
	   		{
		   		CW_PR3(17,5,'O');
		   		CW_PR3(18,5,'F');
		   		CW_PR3(19,5,'F');   			
	   		}
			else
			CCW_PR1(13,40,0xb9d8,1); 	
	   }
	   		
}

/*********************************************/
/*	功能：数据输出设定显示函数
入口参数：无
出口参数：无
/*********************************************/
void Receiversetting_Paint_Dataout(); 
void Receiversetting_Paint_Dataout()
{
	if(Receiverset[1]==2)			//数据输出关
	{					

   		if(LANGUAGE==0)				//英文显示：OFF
   		{
			CTAB[0]='O';	CTAB[1]='F';	CTAB[2]='F';	
			CW_PR(17,10,3);
   		}
   		else 						//中文显示：关
   		{
  			CCW_PR1(18,80,0xb9d8,1);		
  			CCW_PR1(20,80,0x1760,0);  			
   		}			
	}
	
	if(Receiverset[1]==1)			//选择自动
	{

   		if(LANGUAGE==0)				//英文显示：AUTO
   		{
			CTAB[0]='A';	CTAB[1]='U';	CTAB[2]='T';	CTAB[3]='O';	
			CW_PR(17,10,4);
   		}
   		else 						//中文显示：自动
   		{
  			CCW_PR1(18,80,0xd7d4,1);		
  			CCW_PR1(20,80,0xb6af,1);  			
   		}
	}
	
	if(Receiverset[1]==0)			//选择手动
	{
		if(LANGUAGE==0)				//英文显示：MANUAL
		{
			CTAB[0]='M';	CTAB[1]='A';	CTAB[2]='N';	CTAB[3]='U';
			CTAB[4]='A';	CTAB[5]='L';		
			CW_PR(17,10,6);			//中文显示：手动
		}
		
   		else 
   		{
	 		CCW_PR1(18,80,0xcad6,1);		
	  		CCW_PR1(20,80,0xb6af,1);			
   		}
	}	
}


/*********************************************/
/*	功能：数据输出格式设定显示函数
入口参数：无
出口参数：无
/*********************************************/
void Receiversetting_Paint_Datafom(); 
void Receiversetting_Paint_Datafom()
{
	   if(Receiverset[2]==0)			//选择开，中文:开 英文:ON
	   {
	   		if(LANGUAGE==0)
	   		{ 
		   		CW_PR3(20,12,'O');
		   		CW_PR3(21,12,'N');
		   		CW_PR3(22,12,' ');
		   	}
		   	else CCW_PR1(18,96,0xbfaa,1);	
	   }
	   
	   if(Receiverset[2]==1)			//选择关，中文:关 英文;OFF 
	   {
	   		if(LANGUAGE==0)
	   		{   		
		   		CW_PR3(20,12,'O');
		   		CW_PR3(21,12,'F');
		   		CW_PR3(22,12,'F');
	   		}
	   		else CCW_PR1(18,96,0xb9d8,1);	
	   }	
}
/*********************************************/
/*	功能：波特率设定显示函数，中英文显示一样
入口参数：无
出口参数：无
/*********************************************/
void Receiversetting_Paint_Baudrat(); 	
void Receiversetting_Paint_Baudrat()
{
	if(Receiverset[3]==2)		//4800Bps
	{
		CTAB[0]='4';	CTAB[1]='8';	CTAB[2]='0';	CTAB[3]='0';
		CTAB[5]='B';	CTAB[6]='p';	CTAB[7]='s';		
		CW_PR(18,LANGUAGE?15:14,8);
	}
	
	if(Receiverset[3]==1)		//9600Bps
	{
		CTAB[0]='9';	CTAB[1]='6';	CTAB[2]='0';	CTAB[3]='0';
		CTAB[5]='B';	CTAB[6]='p';	CTAB[7]='s';		
		CW_PR(18,LANGUAGE?15:14,8);
	}
	
	if(Receiverset[3]==0)		//19.2KBps
	{
		CTAB[0]='1';	CTAB[1]='9';	CTAB[2]='.';	CTAB[3]='2';
		CTAB[4]='K';	CTAB[5]='B';	CTAB[6]='p';	CTAB[7]='s';		
		CW_PR(18,LANGUAGE?15:14,8);
	}	
}

/*********************************************/
/*	功能：打印方向设定显示函数，中英文显示一样
入口参数：无
出口参数：无
/*********************************************/
void Receiversetting_Paint_Printdir(); 
void Receiversetting_Paint_Printdir()
{
	if(Receiverset[4]==0)		//选择竖直，英文：UPRIGHT 中文：竖直
	{

   		if(LANGUAGE==0)
   		{
			CTAB[0]='U';	CTAB[1]='P';	CTAB[2]='R';	CTAB[3]='I';
			CTAB[4]='G';	CTAB[5]='H';	CTAB[6]='T';		
			CW_PR(25,16,7);
		}
		else
		{
		 	CCW_PR1(18,128,0xcafa,1);		
  			CCW_PR1(20,128,0xd6b1,1);	
		}
	}
	
	if(Receiverset[4]==1)		//选择横向，英文：INVERT 中文：横向
	{

   		if(LANGUAGE==0)
   		{
			CTAB[0]='I';	CTAB[1]='N';	CTAB[2]='V';	CTAB[3]='E';
			CTAB[4]='R';	CTAB[5]='T';		
			CW_PR(24,16,6);
   		}
   		else
   		{
   		 	CCW_PR1(18,128,0xbae1,1);		
  			CCW_PR1(20,128,0xcff2,1);	
   		}
	}	
}
/*********************************************/
/*	功能：INS输出口设置
入口参数：无
出口参数：无
/*********************************************/
void Receiversetting_Paint_INSoutput(); 
void Receiversetting_Paint_INSoutput()
{
	if(flag_auto_iec==0)		//选择手动，英文：MANUAL 中文：手动
	{

   		if(LANGUAGE==0)
   		{
			CTAB[0]='M';	CTAB[1]='A';	CTAB[2]='N';	CTAB[3]='U';
			CTAB[4]='A';	CTAB[5]='L';		
			CW_PR(17,19,6);
		}
		else
		{
		 	CCW_PR1(18,152,0xcad6,1);		
  			CCW_PR1(20,152,0xb6af,1);	
		}
	}
	
	if(flag_auto_iec==1)		//选择自动，英文：AUTO 中文：自动
	{

   		if(LANGUAGE==0)
   		{
			CTAB[0]='A';	CTAB[1]='U';	CTAB[2]='T';	CTAB[3]='O';
			CTAB[4]=' ';	CTAB[5]=' ';		
			CW_PR(17,19,6);
   		}
   		else
   		{
   		 	CCW_PR1(18,152,0xd7d4,1);		
  			CCW_PR1(20,152,0xb6af,1);	
   		}
	}	
}
//********************************************/
/*	功能：显示设置菜单Receivesetting的显示
入口参数：无
出口参数：无
/*********************************************/
void Receivesetting_Paintintial();
void Receivesetting_Paintintial()
{
	byte i;
//	CLEAR1();	//清一区和二区的存储空间
	if(LANGUAGE==0)
	{

		 /* 写入表头数据RECEIVER SET */
		CTAB[2]='R';	CTAB[3]='E';	CTAB[4]='C';	CTAB[5]='E';	CTAB[6]='I';
		CTAB[7]='V';	CTAB[8]='E';	CTAB[9]='R';
		CTAB[12]='S';	CTAB[13]='E';	CTAB[14]='T';
		CW_PR(0,1,15);
		

		 /* 写入第一行数据CER DISPSET: */
		CTAB[5]='C';	CTAB[6]='E';	CTAB[7]='R';	CTAB[9]='D';	CTAB[10]='I';
		CTAB[11]='S';	CTAB[12]='P';	CTAB[13]='S';	CTAB[14]='E'; 
		CTAB[15]='T';	CTAB[16]=':';	
		CW_PR(0,5,17);

		/* 写入第二行数据PRINTER*/
		CTAB[5]='P';	CTAB[6]='R';	CTAB[7]='I';	CTAB[8]='N';	CTAB[9]='T';	CTAB[10]='E';
		CTAB[11]='R';
		CW_PR(0,8,12);  

		/* 写入第三行数据DATA OUT */
		CTAB[8]='D';	CTAB[9]='A';	CTAB[10]='T';	CTAB[11]='A';	CTAB[13]='O';	CTAB[14]='U';
		CTAB[15]='T';
		CTAB[16]=':';
		CW_PR(0,10,17);

		/* 写入第四行数据 DATA FORMAT:*/
		CTAB[8]='D';	CTAB[9]='A';	CTAB[10]='T';	CTAB[11]='A';	CTAB[13]='F';	CTAB[14]='O';
		CTAB[15]='R';
		CTAB[16]='M';	CTAB[17]='A';	CTAB[18]='T';	CTAB[19]=':';
		CW_PR(0,12,20);

		/* 写入第五行数据BAUD RATE: */
		CTAB[8]='B';	CTAB[9]='A';	CTAB[10]='U';	CTAB[11]='D';	CTAB[13]='R';	CTAB[14]='A';
		CTAB[15]='T';
		CTAB[16]='E';	CTAB[17]=':';
		CW_PR(0,14,18);

		/* 写入第六行数据 PRINT DIRECTION:*/
		CTAB[8]='P';	CTAB[9]='R';	CTAB[10]='I';	CTAB[11]='N';	CTAB[12]='T';	
		CTAB[14]='D';
		CTAB[15]='I';	CTAB[16]='R';	CTAB[17]='E';	CTAB[18]='C';	CTAB[19]='T';	CTAB[20]='I';
		CTAB[21]='O';	CTAB[22]='N';	CTAB[23]=':';	
		CW_PR(0,16,24); 
		
		/* 写入第七行数据INS OUTPUT:*/
		CTAB[5]='I';	CTAB[6]='N';	CTAB[7]='S';	CTAB[8]=' ';	CTAB[9]='O';	CTAB[10]='U';
		CTAB[11]='T';	CTAB[12]='P';	CTAB[13]='U';	CTAB[14]='T';	CTAB[15]=':';
		CW_PR(0,19,16); 	
	}

	else
	{

		CLEARXLINE(0,39,22);
		XLINE(0,39,24);
		
		CCW_PR1(1,7,0xbdd3,1);		//第一行内容"接收机设置"
 		CCW_PR1(3,7,0xcad5,1);
 		CCW_PR1(5,7,0xbbfa,1);
 		CCW_PR1(7,7,0xc9e8,1);
 		CCW_PR1(9,7,0xd6c3,1);	
 		
 		CCW_PR1(5,40,0xcef3,1);		//第二行内容"误码率:开"
 		CCW_PR1(7,40,0xc2eb,1);
 		CCW_PR1(9,40,0xc2ca,1);
 		CCW_PR1(11,40,0x1aa0,0);
 		
  		CCW_PR1(5,64,0xb4f2,1);		//第三行内容"打印机"
 		CCW_PR1(7,64,0xd3a1,1);
 		CCW_PR1(9,64,0xbbfa,1);

 		CCW_PR1(8,80,0xcafd,1);		//第四行内容"数据输出:手动"
 		CCW_PR1(10,80,0xbedd,1);
 		CCW_PR1(12,80,0xcae4,1);
 		CCW_PR1(14,80,0xb3f6,1);
 		CCW_PR1(16,80,0x1aa0,0);

 		CCW_PR1(8,96,0xcafd,1);		//第五行内容"数据格式:开"
 		CCW_PR1(10,96,0xbedd,1);
 		CCW_PR1(12,96,0xb8f1,1);
 		CCW_PR1(14,96,0xcabd,1);
 		CCW_PR1(16,96,0x1aa0,0);
 
  		CCW_PR1(8,112,0xb2a8,1);	//第六行内容"波特率:"
 		CCW_PR1(10,112,0xccd8,1);
 		CCW_PR1(12,112,0xc2ca,1);
 		CCW_PR1(16,112,0x1aa0,0);

  		CCW_PR1(8,128,0xb4f2,1);	//第七行内容"打印方向:竖直"
 		CCW_PR1(10,128,0xd3a1,1);
 		CCW_PR1(12,128,0xb7bd,1);
 		CCW_PR1(14,128,0xcff2,1);
 		CCW_PR1(16,128,0x1aa0,0);
 		
		CCW_PR1(5,152,0x1c80,0);	//第八行内容"INS输出:"
 		CCW_PR1(7,152,0x1d20,0);
 		CCW_PR1(9,152,0x1dc0,0);
 		CCW_PR1(11,152,0xcae4,1);
 		CCW_PR1(13,152,0xb3f6,1);	
 		CCW_PR1(15,152,0x1aa0,0);	
	}


	W_YLINE(0,0,239);				//Y轴的两条边框显示
	W_YLINE(319,0,239);	
						
	W_DIAMOND(3,LANGUAGE?44:5);	   	//完成选定框的显示
	W_HDIAMOND(3,LANGUAGE?68:8);
	W_HDIAMOND(3,LANGUAGE?156:19);	
	for(i=0;i<4;i++)
	{
		W_HDIAMOND(6,LANGUAGE?(84+16*i):(10+2*i));
	}

	Receiversetting_Paint_Cer();		//误码率设定显示
	Receiversetting_Paint_Dataout();	//数据输出设定显示
	Receiversetting_Paint_Datafom(); 	//数据输出格式设定显示
	Receiversetting_Paint_Baudrat(); 	//波特率上的设定显示
	Receiversetting_Paint_Printdir(); 	//打印方向设定显示
	Receiversetting_Paint_INSoutput();	//INS输出模式显示
	W_Mode(35,7,32,1);					//手动，自动模式的显示
}

/***************************************************/
/*	功能；上下按键处理函数，进行选定项的选择
入口参数：无
出口参数：无
/***************************************************/ 
void Receivesetting_Updn();
void Receivesetting_Updn()
{
	if (G_Key==UP)
	{
		if(BUFFER1[0]==1 )                       //非最上则上移,0 1 误码率和打印
		{
			BUFFER1[0]=0;
			W_DIAMOND(3,LANGUAGE?44:5);	   
			W_HDIAMOND(3,LANGUAGE?68:8);     
		}
		else if(BUFFER1[0]==6)
		{
			BUFFER1[0]=1;
			W_DIAMOND(3,LANGUAGE?68:8);
			W_HDIAMOND(3,LANGUAGE?156:19);
		}
		else if(BUFFER1[0]>2 && BUFFER1[0]<=5 )        //非最上则上移,2 3 4 5 为打印子项
		{
			BUFFER1[0]=BUFFER1[0]-1; 
			W_DIAMOND(6,LANGUAGE?(84+(BUFFER1[0]-2)*16):(6+2*BUFFER1[0]));	   
			W_HDIAMOND(6,LANGUAGE?(84+(BUFFER1[0]-1)*16):(8+2*BUFFER1[0]));       
		}
		G_Key=0;
	}

	else if (G_Key==DOWN)
	{
		if(BUFFER1[0]==0 )                       //非最下则下移
		{
			BUFFER1[0]=1;
			W_HDIAMOND(3,LANGUAGE?44:5);	   
			W_DIAMOND(3,LANGUAGE?68:8);         
		}
		else if(BUFFER1[0]==1)
		{
			BUFFER1[0]=6;
			W_HDIAMOND(3,LANGUAGE?68:8);
			W_DIAMOND(3,LANGUAGE?156:19);
		}
		else if(BUFFER1[0]>=2 && BUFFER1[0]<5 )        //非最下则下移,3 4 5 6为信息警报、接收信息、警报信息、点击
		{
			BUFFER1[0]=BUFFER1[0]+1;
			W_DIAMOND(6,LANGUAGE?(84+(BUFFER1[0]-2)*16):(6+2*BUFFER1[0]));	   
			W_HDIAMOND(6,LANGUAGE?(84+(BUFFER1[0]-3)*16):(4+2*BUFFER1[0])); 		        
		}
		G_Key=0;
	}	
}

/***************************************************/
/*	功能；左右按键处理函数，对应选定项的设置
入口参数：无
出口参数：无
/***************************************************/   
void Receivesetting_Leftright();
void Receivesetting_Leftright()
{
	unsigned char i;
	if (G_Key==RIGHT||G_Key==LEFT)
	{
		if (BUFFER1[0]==0)                          		//误码率配置
		{   
		   	G_Key=0;              
		   	Receiverset[0]=(Receiverset[0]+1)%2;
			Receiversetting_Paint_Cer();
			Write_Char_Eprm(PRINTER_FORMAT,Receiverset[0]);	//误码率写入Eprom
		} 

		else if(BUFFER1[0]==2)									//输出数据配置
		{
			if(G_Key==RIGHT)
			{
				G_Key=0;
				Receiverset[1]=(Receiverset[1]+1)%3;
			}
			
			if(G_Key==LEFT)
			{
				G_Key=0;
				Receiverset[1]=(Receiverset[1]+2)%3;
			}   
			Receiversetting_Paint_Dataout();
			Write_Char_Eprm(PRINTER_FORMAT+1,Receiverset[1]);	//写入Eprom
		}


		else if (BUFFER1[0]==3)   								//数据格式配置                          
		{   
		   	G_Key=0;              
		   	Receiverset[2]=(Receiverset[2]+1)%2;
		   	Receiversetting_Paint_Datafom();
			Write_Char_Eprm(PRINTER_FORMAT+2,Receiverset[2]);	//写入Eprom
		}

		else if(BUFFER1[0]==4)									//波特率配置
		{
			if(G_Key==RIGHT)
			{
				G_Key=0;
				Receiverset[3]=(Receiverset[3]+1)%3;				
			}
			if(G_Key==LEFT)
			{
				G_Key=0;
				Receiverset[3]=(Receiverset[3]+2)%3;
			}
			Receiversetting_Paint_Baudrat(); 
			
			BadurateSet(Receiverset[3]+1);	//设置SCI的波特率
			Write_Char_Eprm(PRINTER_FORMAT+3,Receiverset[3]);	//写入Eprom					
		} 
		else if (BUFFER1[0]==5)   								//打印方向配置                         
		{   
		    G_Key=0;              
		    Receiverset[4]=(Receiverset[4]+1)%2;
			Receiversetting_Paint_Printdir();
			Write_Char_Eprm(PRINTER_FORMAT+4,Receiverset[4]);	//写入Eprom		   
		}
		else if (BUFFER1[0]==6)
		{   
		    G_Key=0;              
		    flag_auto_iec=flag_auto_iec?0:1;
			Receiversetting_Paint_INSoutput();
			Write_Char_Eprm(IEC_MODE,flag_auto_iec);	//写入Eprom		   
		}
	}
}
 
/***************************************************/
/*	功能；CLR按键处理函数，退出打印机设置的子选项
          退出当前菜单
入口参数：无
出口参数：无
/***************************************************/  
void Receivesetting_Return();
void Receivesetting_Return()
{
	if(G_Key==CLR&&BUFFER1[0]!=0&&BUFFER1[0]!=1&&BUFFER1[0]!=6)            	//跳出打印机的子选项
	{	
		char i;
		G_Key=0;												//按键清零
		W_DIAMOND(3,LANGUAGE?68:8);								//选定框的显示
		W_HDIAMOND(6,LANGUAGE?(84+(BUFFER1[0]-2)*16):(6+2*BUFFER1[0]));
		BUFFER1[0]=1;											//选择打印机选项
		for(i=1;i<5;i++)
		{
			Write_Char_Eprm(PRINTER_FORMAT+i,Receiverset[i]);	//打印设置写入Eprom	
		}
	}
	else if(G_Key==CLR&&(BUFFER1[0]==0||BUFFER1[0]==1||BUFFER1[0]==6))			//跳到MainMenu界面
	{
		G_Key=0;			//按键清零
		BUFFER1[0]=0;		//本菜单使用全局变量清零	
	    FLAG=0;         	//结束循环             
		STATE=4;			//MainMenu界面的状态为4
		State4parameter=0;	//入口参数为0
	}
}
 
 
//**************************************************/
/*	功能；ENT按键处理函数，进入打印机设置的子选项
入口参数：无
出口参数：无
/***************************************************/  
void Receivesetting_Dealing();
void Receivesetting_Dealing()
{
	if(G_Key==ENT&&BUFFER1[0]==1)
	{
		BUFFER1[0]=2; 	 				//进入打印子选项
		G_Key=0;						//按键清零
		W_HDIAMOND(3,LANGUAGE?68:8);	//选定框的显示
		W_DIAMOND(6,LANGUAGE?84:10);	
	}
}

//**************************************************/
/*	功能；接收机设置菜单：设置误码率开关，打印机的
          输出格式

入口参数：无
出口参数：无
/***************************************************/ 
void RunReceiveSetting();
void RunReceiveSetting()
{
    maske=0;
    maskc=0;
	Receivesetting_Paintintial();
	while(FLAG)                           
	{
		Receivesetting_Updn();
		Receivesetting_Leftright();		
		Receivesetting_Return();		
		Receivesetting_Dealing();
		run_tip();
	}

}