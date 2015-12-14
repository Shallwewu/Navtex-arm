#include <stdio.h>
#include <stdlib.h>
#include "iec.h"
#include "run.h"
#include "printer.h"
#include "ThreeDays.h"
#include "code.h"
#include "rtc.h"
#include "misc.h"
#include "stm32f2xx_exti.h"
#include "stm32f2xx.h"
#include "usart.h"
#define BAUD_IEC 3


static char alarm1text[28]="NAVTEX:NAVIGATIONAL WARNING";
static char alarm2text[30]="NAVTEX:METEOROLOGICAL WARNING";
static char alarm3text[37]="NAVTEX:SEARCH AND RESCUE INFORMATION";
static char alarm4text[28]="NAVTEX:RECEIVER MALFUNCTION";
static char alarm5text[34]="NAVTEX:BUILT IN SELF TEST FAILURE";
static char alarm6text[23]="NAVTEX:GENERAL FAILURE";
static char nrmstartdata[2];
//volatile int iec_trans(char array[] ,int length);
static sword checksum(char array[],sword ml);
static void iec_check_start(char rx_data);
static void iec_check_end(char rx_data);
static void iec_check_data(char rx_data);
static char iec_check_data_sum(char *p,char num,char sum1,char sum2);
static sword gps(char array[],sword length);
static sword gps1(char array[],sword length);
static void nrm(sword length);
static void iec_time_reset(void);
void CloseRS232_iec(void);
/*
volatile int iec_send_list[600];
volatile int iec_send_sum;
volatile bice[75][82];
volatile char checkdata[6];
char iec_rx_data[70];		//有效数据存储
volatile unsigned char iec_rx_array[500];//接收数据缓冲区
*/
//*******************************************/
/*功能；信息正文进行IEC61162转换
入口参数：char array[] ---信息正文首地址,int length---正文长度
出口参数：转换后IEC61162信息长度
/********************************************/
sword iec_trans(char array[] ,sword length)
{
	sword checksum(char array[],sword);
	sword i,j,k,l;
	sword cs1,cs2;
	sword meslength,mesnum;
	sword bicer;
	char ch;
	char time[3]={0,0,0};

	meslength=length-2;



	mesnum=(meslength-9)/25+((meslength-9)%25?1:0);
	k=6;
	bicer=0;l=0;	
	for(i=0;i<75&&k<(meslength-4)+1;i++)
	{    
	    bice[i][0]=0x24;//$
		bice[i][1]=0x2D;//0x47;//-
		bice[i][2]=0x2D;//0x50;//-
		bice[i][3]=0x4E;//0x54;//N
		bice[i][4]=0x52;//0x58;//R
		bice[i][5]=0x58;//0x54;//X

		bice[i][6]=0x2c;
		bice[i][10]=0x2c;
		bice[i][14]=0x2c;
		bice[i][17]=0x2c;
		bice[i][22]=0x2c;
		bice[i][24]=0x2c;
		bice[i][31]=0x2c;
		bice[i][34]=0x2c;
		bice[i][37]=0x2c;
		bice[i][42]=0x2c;
		bice[i][46]=0x2c;
		bice[i][49]=0x2c;
		bice[i][51]=0x2c;

		
		
		bice[i][7]=mesnum/100+'0';
		bice[i][8]=(mesnum/10)%10+'0';
		bice[i][9]=mesnum%10+'0';
		
		
		bice[i][11]=(i+1)/100+'0';
		bice[i][12]=((i+1)/10)%10+'0';
		bice[i][13]=(i+1)%10+'0';

		bice[i][15]=0+'0';
		bice[i][16]=0+'0';
		
		bice[i][18]=array[0];
		bice[i][19]=array[1];
		bice[i][20]=array[2];
		bice[i][21]=array[3];

		bice[i][23]=(Messagesavetop[PrtStart->xulie].frequency==1)?'2':((Messagesavetop[PrtStart->xulie].frequency==2)?'1':'3');
		                                                                               //1:518khz 2:486khz 3:4209.5khz
		                                                                               //2        4  1      3
		
		
	    bice[i][25]=Messagesavetop[PrtStart->xulie].time[0]/10+'0';//hour
	    bice[i][26]=Messagesavetop[PrtStart->xulie].time[0]%10+'0';
        bice[i][27]=Messagesavetop[PrtStart->xulie].time[1]/10+'0';//minute
        bice[i][28]=Messagesavetop[PrtStart->xulie].time[1]%10+'0';
      	bice[i][29]='0';                                           //second
    	bice[i][30]='0';
    	
    	bice[i][32]=Messagesavetop[PrtStart->xulie].date[2]/10+'0'; //day
    	bice[i][33]=Messagesavetop[PrtStart->xulie].date[2]%10+'0';
    	
    	bice[i][35]=Messagesavetop[PrtStart->xulie].date[1]/10+'0'; //month
    	bice[i][36]=Messagesavetop[PrtStart->xulie].date[1]%10+'0';
    	
    	bice[i][38]='2';                                             //year
    	bice[i][39]='0';
    	bice[i][40]=Messagesavetop[PrtStart->xulie].date[2]/10+'0'; 
    	bice[i][41]=Messagesavetop[PrtStart->xulie].date[2]%10+'0';
    	
    	bice[i][43]=(meslength-9)/100+'0';
    	bice[i][44]=((meslength-9)/10)%10+'0';
    	bice[i][45]=(meslength-9)%10+'0';
    	
   	
    	bice[i][50]='A';
    	
    	
    	bice[i][77]=0x2a;
		bice[i][80]=0x0d;
		bice[i][81]=0x0a;
    	

		for(j=52;j<77&&k<(meslength-4)+1;j++)
		{
		    bice[i][j]=array[k];
		    k++;
		    if(array[k]=='*')bicer++;
		}
	
		
	}
	
	bice[i-1][47]=bicer/10+'0';
	bice[i-1][48]=bicer%10+'0';
	bice[i-1][j]=0x2a;
	bice[i-1][j+3]=0x0d;
	bice[i-1][j+4]=0x0a;
	cs1=checksum(bice[i],j)>>4;
	cs2=checksum(bice[i],j)-(checksum(bice[i],j)>>4)*16;
 	bice[i-1][j+1]=((cs1>=0&&cs1<=9)?'0':('a'-10))+cs1;
	bice[i-1][j+2]=((cs2>=0&&cs2<=9)?'0':('a'-10))+cs2;
	
	
	
	for(l=0;l<i;l++)
	{
	    bice[l][47]=bicer/10+'0';
	    bice[l][48]=bicer%10+'0';
		cs1=checksum(bice[l],77)>>4;
	    cs2=checksum(bice[l],77)-(checksum(bice[l],77)>>4)*16;
 	    bice[l][78]=((cs1>=0&&cs1<=9)?'0':('a'-10))+cs1;
	    bice[l][79]=((cs2>=0&&cs2<=9)?'0':('a'-10))+cs2;
	}
	
	return (i-1)*82+j+5;
}
//*******************************************/
/*功能；
入口参数：char array[] ---信息正文首地址,int ml
出口参数：
/********************************************/
sword checksum(char array[],sword ml)
{
	sword b;
	sword i;
	b=array[1];
	for(i=2;i<ml;i++)
		b=b^array[i];
	return b;

}
//*******************************************/
/*功能；GPS数据接收头判断
入口参数：char rx_data---当前接收到数据
出口参数：无
/********************************************/
void iec_check_start(char rx_data)
{
	char i=0;
	if(iec_rx.start_flag==0)//信号头判断
	{
		for(i=0;i<5;i++)
		{
			checkdata[i]=checkdata[i+1];
		}
		checkdata[i]=rx_data;
			
		if(checkdata[0]=='$'&&checkdata[1]=='G'&&checkdata[2]=='P'&&checkdata[3]=='R'&&checkdata[4]=='M'&&checkdata[5]=='C')//判断是否为接收头信号"$GPGLL"	
			iec_rx.start_flag=1;
		else if(checkdata[0]=='$'&&checkdata[3]=='N'&&checkdata[4]=='R'&&checkdata[5]=='M')
		{
			iec_rx.start_flag=2;
			nrmstartdata[0]=checkdata[1];
			nrmstartdata[1]=checkdata[2];
		}
		else if(checkdata[0]=='$'&&checkdata[1]=='G'&&checkdata[2]=='P'&&checkdata[3]=='G'&&checkdata[4]=='G'&&checkdata[5]=='A')
		{
			iec_rx.start_flag=3;
		}
	}
	else	//接收信号中将缓冲区清0
	{
		for(i=0;i<6;i++)
		{
			checkdata[i]=0;
		}
	}
}
//*******************************************/
/*功能；GPS数据接收尾判断
入口参数：char rx_data---当前接收到数据
出口参数：无
/********************************************/
void iec_check_end(char rx_data)
{
	char i=0;
	if(iec_rx.start_flag==1&&rx_data=='\n')//已收到信号头且收到信息尾部
	{	
		iec_rx.end_flag=1;	
	}
	else if(iec_rx.start_flag==2&&rx_data=='\n')//已收到信号头且收到信息尾部
	{	
		iec_rx.end_flag=2;	
	}
	else if(iec_rx.start_flag==3&&rx_data=='\n')//已收到信号头且收到信息尾部
	{	
		iec_rx.end_flag=3;	
	}

}
//*******************************************/
/*功能；GPS数据判断
入口参数：char rx_data---当前接收到数据
出口参数：无
/********************************************/
void iec_check_data(char rx_data)
{
	char i=0,b1,b2;
	unsigned char b=0;
	if(iec_rx.start_flag==1)//已收到信号头
	{
		iec_rx_array[iec_rx.nownum++]=rx_data;
		if(iec_rx.end_flag==1)//已收到信息尾
		{
			if(iec_rx.nownum>=55&&iec_rx.nownum<=75)
			{
				iec_rx_data[0]='$';
				iec_rx_data[1]='G';
				iec_rx_data[2]='P';
				iec_rx_data[3]='R';
				iec_rx_data[4]='M';
				iec_rx_data[5]='C';
				for(i=0;i<iec_rx.nownum;i++)
				{
					iec_rx_data[i+6]=iec_rx_array[i];
				}
				iec_rx.data_valid_flag=iec_check_data_sum(&iec_rx_data[1],iec_rx.nownum,iec_rx_data[iec_rx.nownum+2],iec_rx_data[iec_rx.nownum+3]);
				if(iec_rx.data_valid_flag==1)
				{
					iec_rx.allnum=iec_rx.nownum+6;
					auto_area=gps(iec_rx_data,iec_rx.allnum);
					iec_time_reset();
					iec_rx.new_flag=1;
					CloseRS232_iec();
					IntialIRQB();
							
				}
				iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;		
			}
			else
			{
				iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;
			}
		}
		else if(iec_rx.nownum>=500)
		{
			iec_rx.nownum=0;
			iec_rx.time++;
			if(iec_rx.time==5)
			{
				CloseRS232_iec();
				IntialIRQB();
				iec_rx.time=0;	
			}
		}
	}
	else if(iec_rx.start_flag==3)//已收到信号头
	{
		iec_rx_array[iec_rx.nownum++]=rx_data;
		if(iec_rx.end_flag==3)//已收到信息尾
		{
			if(iec_rx.nownum>=55&&iec_rx.nownum<=75)
			{
				iec_rx_data[0]='$';
				iec_rx_data[1]='G';
				iec_rx_data[2]='P';
				iec_rx_data[3]='G';
				iec_rx_data[4]='G';
				iec_rx_data[5]='A';
				for(i=0;i<iec_rx.nownum;i++)
				{
					iec_rx_data[i+6]=iec_rx_array[i];
				}
				iec_rx.data_valid_flag=iec_check_data_sum(&iec_rx_data[1],iec_rx.nownum,iec_rx_data[iec_rx.nownum+2],iec_rx_data[iec_rx.nownum+3]);
				if(iec_rx.data_valid_flag==1)
				{
					iec_rx.allnum=iec_rx.nownum+6;
					auto_area=gps1(iec_rx_data,iec_rx.allnum);
					iec_time_reset();
					iec_rx.new_flag=1;
					CloseRS232_iec();
					IntialIRQB();
							
				}
				iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;		
			}
			else			{
				iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;
			}
		}
		else if(iec_rx.nownum>=500)
		{
			iec_rx.nownum=0;
			iec_rx.time++;
			if(iec_rx.time==5)
			{
				CloseRS232_iec();
				IntialIRQB();
				iec_rx.time=0;	
			}
		}
	}
	
	else if(iec_rx.start_flag==2)//已收到信号头
	{
		iec_rx_array[iec_rx.nownum++]=rx_data;
		if(iec_rx.end_flag==2)//已收到信息尾
		{
			
			
				iec_rx_data[0]='$';
				iec_rx_data[1]=nrmstartdata[0];
				iec_rx_data[2]=nrmstartdata[1];
				iec_rx_data[3]='N';
				iec_rx_data[4]='R';
				iec_rx_data[5]='M';
				for(i=0;i<iec_rx.nownum;i++)
				{
					iec_rx_data[i+6]=iec_rx_array[i];
				}
				iec_rx.data_valid_flag=iec_check_data_sum(&iec_rx_data[1],iec_rx.nownum,iec_rx_data[iec_rx.nownum+2],iec_rx_data[iec_rx.nownum+3]);
				if(iec_rx.data_valid_flag==1)
				{
					iec_rx.allnum=iec_rx.nownum+6;
				//	auto_area=
				    nrm(iec_rx.allnum);
				    
				//	iec_time_reset();
					iec_rx.new_flag=2;
					CloseRS232_iec();		
			    //     CloseRS232();
					IntialIRQB();
			
							
				}
				iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;		
			
		/*	else
			{
				iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;
			}
		*/
		}
		else if(iec_rx.nownum>=500)
		{
			iec_rx.nownum=0;
			iec_rx.time++;
			if(iec_rx.time==5)
			{
				CloseRS232_iec();
				IntialIRQB();
				iec_rx.time=0;	
			}
		}
	}
//	else
//	{
//		iec_rx.nownum=0;
//		iec_rx.time++;
//		if(iec_rx.time==5)
//		{
//			CloseRS232_iec();
//			IntialIRQB();
//			iec_rx.time=0;	
//		}
//	}
}
//*******************************************/
/*功能；GPS数据校验和判断
入口参数：char *p----有效GPS数据首地址
		  char num---有效GPS数据长度
		  char sum1--校验和第一个字符
		  char sum2--校验和第二个字符
出口参数：校验和标志：1---有效   -1---出错
/********************************************/
char iec_check_data_sum(char *p,char num,char sum1,char sum2)
{
	char b,b1,b2,data_valid_flag;
	sword i;
	b=*p;
	for(i=1;i<num;i++)
		b=b^(*(p+i));
	b1=b/16;
	b2=b%16;
	if(b1<=9)
		b1=b1+48;	//0-9
	else
		b1=b1+55;	//A-F
	if(b2<=9)
		b2=b2+48;	//0-9
	else
		b2=b2+55;	//A-F	
	if(b1==sum1&&b2==sum2)
		data_valid_flag=1;
	else
		data_valid_flag=-1;
	return data_valid_flag;
}
//
sword gps(char array[],sword length)
{
	sword i,j;
	sword lat,lon;
	sword lato,lono;
	sword lat_tz,lon_tz;
	sword dot;
	sword b[4];
	sword k;
	char ch;
	sword meslength;
	sword timezone;



	sword a[16][17]={{18,19,19,19,20,20,20,20,20,21,21,21,21,21,17,18,18},
	               {18,1,1,19,20,20,20,20,20,21,21,21,21,21,17,18,18},
	               {4,1,1,1,0,0,0,0,0,13,13,13,13,13,12,4,4},
	               {4,1,1,1,0,0,0,0,0,13,13,13,13,12,12,4,4},
	               {4,2,2,3,3,0,0,0,0,13,13,13,13,12,12,4,4},
	               {4,2,2,3,3,0,0,0,0,13,11,11,11,12,12,4,4},
	               {4,2,2,3,3,0,0,0,11,11,11,11,11,12,12,4,4},
	               {4,2,2,0,9,9,8,8,11,11,11,11,11,12,12,12,4},
	               {4,2,2,0,8,8,8,11,11,11,11,11,12,12,12,12,12},
	               {5,5,2,2,8,8,8,8,11,11,11,11,11,12,12,12,12},
	               {5,5,2,2,8,8,8,8,11,11,10,10,14,14,14,12,12},
	               {5,5,7,7,8,8,8,8,11,11,10,10,14,14,14,16,16},
	               {5,5,7,7,7,8,8,8,10,10,10,10,14,14,14,16,16},
	               {5,5,7,7,7,8,8,8,10,10,10,10,14,14,14,15,15},
	               {5,5,7,7,7,7,7,10,10,10,10,10,14,14,14,15,15},
	               {6,6,7,7,7,7,7,10,10,10,10,14,14,14,14,15,15}};

	
	meslength=length;
	dot=0;
	for(i=0;i<meslength;i++){
		if(array[i]=='R'&&array[i+1]=='M'&&array[i+2]=='C'){
			gpslldt[2][3]=array[i+5]-'0'+(array[i+4]-'0')*10;
			gpslldt[2][4]=array[i+7]-'0'+(array[i+6]-'0')*10;
		}
		if(array[i]==',')
		{
			dot++;

		if(dot==3){
			lato=array[i+2]-'0'+(array[i+1]-'0')*10;
			gpslldt[0][0]=lato;
			gpslldt[0][1]=(array[i+3]-'0')*10+array[i+4]-'0';
			for(k=0;k<4;k++){
				if(array[i+6+k]>='0'&&array[i+6+k]<='9'&&array[i+5]=='.')b[k]=array[i+6+k]-'0';
				else b[k]=0;
			}
			gpslldt[0][2]=b[0]*10+b[1];
			gpslldt[0][3]=b[2]*10+b[3];
		}

		if(dot==4){
			if(array[i+1]=='N'){
				lat=lato+90;
				gpslldt[0][4]=1;
			}
			else 
			{
				lat=90-lato;
				gpslldt[0][4]=0;
			}
		}

		if(dot==5){
			lono=(array[i+1]-'0')*100+(array[i+2]-'0')*10+(array[i+3]-'0');
			gpslldt[1][0]=lono;
			gpslldt[1][1]=(array[i+4]-'0')*10+array[i+5]-'0';
			for(k=0;k<4;k++){
				if(array[i+7+k]>='0'&&array[i+7+k]<='9')b[k]=array[i+7+k]-'0';
				else b[k]=0;
			}
			gpslldt[1][2]=b[0]*10+b[1];
			gpslldt[1][3]=b[2]*10+b[3];
		}

		if(dot==6){
				if(array[i+1]=='E'){	
				lon=lono;
				gpslldt[1][4]=0;
			}
			else 
			{
				lon=360-lono;
				gpslldt[1][4]=1;
			}
		}

		if(dot==9){
			gpslldt[2][0]=(array[i+5]-'0')*10+array[i+6]-'0';
			gpslldt[2][1]=(array[i+3]-'0')*10+array[i+4]-'0';
			gpslldt[2][2]=(array[i+1]-'0')*10+array[i+2]-'0';
		}
		}


		

	}


	if(lat>=0&&lat<55) lat_tz=15;
	else if(lat>=55&&lat<60) lat_tz=14;
	else if(lat>=60&&lat<72) lat_tz=13;
	else if(lat>=72&&lat<78) lat_tz=12;
	else if(lat>=78&&lat<84) lat_tz=11;
	else if(lat>=84&&lat<90) lat_tz=10;
	else if(lat>=90&&lat<96) lat_tz=9;
	else if(lat>=96&&lat<100) lat_tz=8;
	else if(lat>=100&&lat<120) lat_tz=7;
	else if(lat>=120&&lat<131) lat_tz=6;
	else if(lat>=131&&lat<135) lat_tz=5;
	else if(lat>=135&&lat<139) lat_tz=4;
	else if(lat>=139&&lat<146) lat_tz=3;
	else if(lat>=146&&lat<156) lat_tz=2;
	else if(lat>=156&&lat<166) lat_tz=1;
	else lat_tz=0;


	if(lon>=30&&lon<55) lon_tz=4;
	else if(lon>=55&&lon<65) lon_tz=5;
	else if(lon>=65&&lon<79) lon_tz=6;
	else if(lon>=79&&lon<97) lon_tz=7;
	else if(lon>=97&&lon<125) lon_tz=8;
	else if(lon>=125&&lon<142) lon_tz=9;
	else if(lon>=142&&lon<160) lon_tz=10;
	else if(lon>=160&&lon<170) lon_tz=11;
	else if(lon>=170&&lon<180) lon_tz=12;
	else if(lon>=180&&lon<191) lon_tz=13;
	else if(lon>=191&&lon<240) lon_tz=14;
	else if(lon>=240&&lon<265) lon_tz=15;
	else if(lon>=265&&lon<293) lon_tz=16;
	else if(lon>=293&&lon<333) lon_tz=0;
	else if(lon>=333&&lon<348) lon_tz=1;
	else if(lon>=348&&lon<355) lon_tz=2;
	else lon_tz=3;


	timezone=a[lat_tz][lon_tz];




	return timezone;
}
sword gps1(char array[],sword length)
{
	sword i,j;
	sword lat,lon;
	sword lato,lono;
	sword lat_tz,lon_tz;
	sword dot;
	sword b[4];
	sword k;
	char ch;
	sword meslength;
	sword timezone;



	sword a[16][17]={{18,19,19,19,20,20,20,20,20,21,21,21,21,21,17,18,18},
	               {18,1,1,19,20,20,20,20,20,21,21,21,21,21,17,18,18},
	               {4,1,1,1,0,0,0,0,0,13,13,13,13,13,12,4,4},
	               {4,1,1,1,0,0,0,0,0,13,13,13,13,12,12,4,4},
	               {4,2,2,3,3,0,0,0,0,13,13,13,13,12,12,4,4},
	               {4,2,2,3,3,0,0,0,0,13,11,11,11,12,12,4,4},
	               {4,2,2,3,3,0,0,0,11,11,11,11,11,12,12,4,4},
	               {4,2,2,0,9,9,8,8,11,11,11,11,11,12,12,12,4},
	               {4,2,2,0,8,8,8,11,11,11,11,11,12,12,12,12,12},
	               {5,5,2,2,8,8,8,8,11,11,11,11,11,12,12,12,12},
	               {5,5,2,2,8,8,8,8,11,11,10,10,14,14,14,12,12},
	               {5,5,7,7,8,8,8,8,11,11,10,10,14,14,14,16,16},
	               {5,5,7,7,7,8,8,8,10,10,10,10,14,14,14,16,16},
	               {5,5,7,7,7,8,8,8,10,10,10,10,14,14,14,15,15},
	               {5,5,7,7,7,7,7,10,10,10,10,10,14,14,14,15,15},
	               {6,6,7,7,7,7,7,10,10,10,10,14,14,14,14,15,15}};

	
	meslength=length;
	dot=0;
	for(i=0;i<meslength;i++){
		if(array[i]=='G'&&array[i+1]=='G'&&array[i+2]=='A'){
			gpslldt[2][3]=array[i+5]-'0'+(array[i+4]-'0')*10;
			gpslldt[2][4]=array[i+7]-'0'+(array[i+6]-'0')*10;
		}
		if(array[i]==',')
		{
			dot++;

		if(dot==2){
			lato=array[i+2]-'0'+(array[i+1]-'0')*10;
			gpslldt[0][0]=lato;
			gpslldt[0][1]=(array[i+3]-'0')*10+array[i+4]-'0';
			for(k=0;k<4;k++){
				if(array[i+6+k]>='0'&&array[i+6+k]<='9'&&array[i+5]=='.')b[k]=array[i+6+k]-'0';
				else b[k]=0;
			}
			gpslldt[0][2]=b[0]*10+b[1];
			gpslldt[0][3]=b[2]*10+b[3];
		}

		if(dot==3){
			if(array[i+1]=='N'){
				lat=lato+90;
				gpslldt[0][4]=1;
			}
			else 
			{
				lat=90-lato;
				gpslldt[0][4]=0;
			}
		}

		if(dot==4){
			lono=(array[i+1]-'0')*100+(array[i+2]-'0')*10+(array[i+3]-'0');
			gpslldt[1][0]=lono;
			gpslldt[1][1]=(array[i+4]-'0')*10+array[i+5]-'0';
			for(k=0;k<4;k++){
				if(array[i+7+k]>='0'&&array[i+7+k]<='9')b[k]=array[i+7+k]-'0';
				else b[k]=0;
			}
			gpslldt[1][2]=b[0]*10+b[1];
			gpslldt[1][3]=b[2]*10+b[3];
		}

		if(dot==5){
				if(array[i+1]=='E'){	
				lon=lono;
				gpslldt[1][4]=0;
			}
			else 
			{
				lon=360-lono;
				gpslldt[1][4]=1;
			}
		}

		
		}


		

	}


	if(lat>=0&&lat<55) lat_tz=15;
	else if(lat>=55&&lat<60) lat_tz=14;
	else if(lat>=60&&lat<72) lat_tz=13;
	else if(lat>=72&&lat<78) lat_tz=12;
	else if(lat>=78&&lat<84) lat_tz=11;
	else if(lat>=84&&lat<90) lat_tz=10;
	else if(lat>=90&&lat<96) lat_tz=9;
	else if(lat>=96&&lat<100) lat_tz=8;
	else if(lat>=100&&lat<120) lat_tz=7;
	else if(lat>=120&&lat<131) lat_tz=6;
	else if(lat>=131&&lat<135) lat_tz=5;
	else if(lat>=135&&lat<139) lat_tz=4;
	else if(lat>=139&&lat<146) lat_tz=3;
	else if(lat>=146&&lat<156) lat_tz=2;
	else if(lat>=156&&lat<166) lat_tz=1;
	else lat_tz=0;


	if(lon>=30&&lon<55) lon_tz=4;
	else if(lon>=55&&lon<65) lon_tz=5;
	else if(lon>=65&&lon<79) lon_tz=6;
	else if(lon>=79&&lon<97) lon_tz=7;
	else if(lon>=97&&lon<125) lon_tz=8;
	else if(lon>=125&&lon<142) lon_tz=9;
	else if(lon>=142&&lon<160) lon_tz=10;
	else if(lon>=160&&lon<170) lon_tz=11;
	else if(lon>=170&&lon<180) lon_tz=12;
	else if(lon>=180&&lon<191) lon_tz=13;
	else if(lon>=191&&lon<240) lon_tz=14;
	else if(lon>=240&&lon<265) lon_tz=15;
	else if(lon>=265&&lon<293) lon_tz=16;
	else if(lon>=293&&lon<333) lon_tz=0;
	else if(lon>=333&&lon<348) lon_tz=1;
	else if(lon>=348&&lon<355) lon_tz=2;
	else lon_tz=3;


	timezone=a[lat_tz][lon_tz];




	return timezone;
}

void nrm(sword length)
{   
  //  void iec_send_single_alarm(char No);
    char nrmf;
    sword i,j,iec_temp;
    char areamk[26];
    char typemk[26];
    sword k1,k2; 
//    iec_send_sum=0;
    nrmf=(iec_rx_data[9]-'0')==2?1:((iec_rx_data[9]-'0')==3?3:((iec_rx_data[9]-'0')==1?2:0));
		                                         //1:518khz 2:486khz 3:4209.5khz 0
		                                         //2        4    1    3          其余
	for(i=0;i<7&&(i*4+j)<26;i++)
	{   
	    k1=(iec_rx_data[18-i]>='0'&&iec_rx_data[18-i]<='9')?(iec_rx_data[18-i]-'0'):(iec_rx_data[18-i]-'A'+10);
	    k2=(iec_rx_data[27-i]>='0'&&iec_rx_data[27-i]<='9')?(iec_rx_data[27-i]-'0'):(iec_rx_data[27-i]-'A'+10);
	    for(j=0;j<4&&(i*4+j)<26;j++)
	    {
	        
	        if(k1&(0x01<<j))areamk[i*4+j]=1;
	        else areamk[i*4+j]=0;
	        
	        if(k2&(0x01<<j))typemk[i*4+j]=1;
	        else typemk[i*4+j]=0;	    	
	    }
		
	}	
    switch(iec_rx_data[7])
    {
    	case('0'):
    	{   
    	    for(i=0;i<Messageinfo.nownumber[0];i++)
    	    {
    	    	if((areamk[Messagesavetop[Messagetoprank[i]].mark[0]-'A']==1)&&
    	    	   (typemk[Messagesavetop[Messagetoprank[i]].mark[1]-'A']==1)&&
                   (Messagesavetop[Messagetoprank[i]].frequency==nrmf))
    	    		//InsMsg(Messagetoprank[i]);
    	    		iec_InsMsg(Messagetoprank[i]);
    	    		}
    	    		
    	    	//	iec_send();
    	    		
    	    		iec_temp=0;
    StartRS232(USART2);	//开启打印机
     	
	while(iec_temp<iec_send_sum)
	{
		PrtStart->xulie=iec_send_list[iec_temp];	
	    ReadIecMsg();	//从FPGA读取所需打印信息
	    BadurateSet(BAUD_IEC);
        
    	Checkinfo.Printover = 0;
	 //	while(Checkinfo.Printover==0)
//		{			
//      }   
        //CloseRS232();
 //       StartRS232_iec(); 
//	iec_send_alarm();IPR2|=IPR2_IRQB_IPL1_MASK;	//开启IRQB的中断，设置中断级别为11
//		IPR2|=IPR2_IRQB_IPL0_MASK;	
 
	
		iec_temp++;
	}
//    	iec_send();	  
//		iec_send_single_alarm(1);
       iec_send_sum=0;

   	    break;	
    	}
    	case('1'):
    	{
    	    
    	    break;	
    	}
    	case('2'):
    	case('3'):
    	{
    	    for(i=0;i<26;i++)
    	    {
    	    	nrmareamk[i]=areamk[i];
    	    	nrmtypemk[i]=typemk[i];
    	    }
     	    nrmflag_on=1;
     	    nrmfre=nrmf;
    	    break;
    	}
    }
}
//*******************************************/
/*功能；报警读取
入口参数：char No----No:1--6
出口参数：无
/********************************************/
void ReadIecAlarm(char No);
void ReadIecAlarm(char No)
{
	word i=0,j=0,t;
	char time[3]={0,0,0};
	char temp=0,temp1=0,temp2=0;
	char *l=receiver_alarm;
	PrtStart->nowprint=receiver_alarm;
//head
	receiver_alarm[i++]=' ';
	receiver_alarm[i++]='$';
	receiver_alarm[i++]='-';
	receiver_alarm[i++]='-';
	receiver_alarm[i++]='A';
	receiver_alarm[i++]='L';
	receiver_alarm[i++]='R';
	receiver_alarm[i++]=',';
//time
	if(flag_on==1)
	{
		time[2]=ihour;
		time[1]=iminute;
//		TODCS|=TODCS_TOD_LOCK_MASK;		//开启TOD_Lock位，读取TOD模块中时间的寄存器 
		timestruct=GetTime();
		time[0]=timestruct.second;
//		TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位
	}
	else
	{	
//		TODCS|=TODCS_TOD_LOCK_MASK;		//开启TOD_Lock位，读取TOD模块中时间的寄存器 
		timestruct=GetTime();
		time[2]=timestruct.hour;
		time[1]=timestruct.minute;
		time[0]=timestruct.second;
//		TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位
	}
	receiver_alarm[i++]=time[2]/10+'0';
	receiver_alarm[i++]=time[2]%10+'0';
	receiver_alarm[i++]=time[1]/10+'0';
	receiver_alarm[i++]=time[1]%10+'0';
	receiver_alarm[i++]=time[0]/10+'0';
	receiver_alarm[i++]=time[0]%10+'0';
	receiver_alarm[i++]=',';
//alarm condition
	receiver_alarm[i++]='A';
	receiver_alarm[i++]=',';
//alarm acknowledge
	receiver_alarm[i++]='V';
	receiver_alarm[i++]=',';
//every kind of alarm added here
	switch(No)
	{
		case(1):
		{
//alarm number			
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='1';
			receiver_alarm[i++]=',';
//alarm text
			for(j=0;j<27;j++)
			{
				receiver_alarm[i++]=alarm1text[j];
			}
			receiver_alarm[i++]='*';		
		}break;
		case(2):
		{
//alarm number			
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='2';
			receiver_alarm[i++]=',';
//alarm text
			for(j=0;j<29;j++)
			{
				receiver_alarm[i++]=alarm2text[j];
			}
			receiver_alarm[i++]='*';	
		}break;
		case(3):
		{
//alarm number			
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='3';
			receiver_alarm[i++]=',';
//alarm text
			for(j=0;j<36;j++)
			{
				receiver_alarm[i++]=alarm3text[j];
			}
			receiver_alarm[i++]='*';	
		}break;
		case(4):
		{
//alarm number			
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='1';
			receiver_alarm[i++]=',';
//alarm text
			for(j=0;j<27;j++)
			{
				receiver_alarm[i++]=alarm4text[j];
			}
			receiver_alarm[i++]='*';	
		}break;
		case(5):
		{
//alarm number			
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='1';
			receiver_alarm[i++]=',';
//alarm text
			for(j=0;j<33;j++)
			{
				receiver_alarm[i++]=alarm5text[j];
			}
			receiver_alarm[i++]='*';	
		}break;
		case(6):
		{
//alarm number			
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='0';
			receiver_alarm[i++]='1';
			receiver_alarm[i++]=',';
//alarm text
			for(j=0;j<22;j++)
			{
				receiver_alarm[i++]=alarm6text[j];
			}
			receiver_alarm[i++]='*';	
		}break;
		default:
		{
			
		}break;
	}
//sum check
	temp=checksum(&receiver_alarm[0],i-1);
	temp1=temp>>4;
	temp2=temp&0x0f;
	receiver_alarm[i++]=((temp1>=0&&temp1<=9)?'0':('A'-10))+temp1;
	receiver_alarm[i++]=((temp2>=0&&temp2<=9)?'0':('A'-10))+temp2;
//end
	receiver_alarm[i++]='\r';
	receiver_alarm[i++]='\n';
	PrtStart->end=l+i-1;
}
//*******************************************/
/*功能；GPS时间重置
入口参数：无
出口参数：无
/********************************************/
void iec_time_reset(void)
{
//	TODCS=TODCS&0xfffe;	            			//TODEN=0,关闭TOD模块
	iyear=gpslldt[2][0];						//时间重置
	imonth=gpslldt[2][1];
	iday=gpslldt[2][2];
	ihour=gpslldt[2][3];
	iminute=gpslldt[2][4];
//	TODDAY=DatesToDays(iyear,imonth,iday);
//	TODHR=ihour;		//把小时置入TODHR	
//	TODMIN=iminute;		//把分钟置入TODMIN
//	TODCS|=0x0001;		//开启时钟 
	RTC_TimeRegulate(iyear,imonth,iday,ihour,iminute);
//  TIM3->CR1 |= 0x01;   //开定时器
}
//*******************************************/
/*功能；SCI1波特率的设置
入口参数：波特率设置参数
/********************************************/
void BadurateSet_iec(char badurate);
void BadurateSet_iec(char badurate)
{
	if(badurate==3)
	{
	USART_BaudRate(USART2,4800*3);		//波特率为4800bps	
	}
	else if(badurate==2)
	{
	USART_BaudRate(USART2,9600*3);			//波特率为9600bps	
	}		
	else if(badurate==1)
	{
	USART_BaudRate(USART2,19200*3);   	//波特率为19200bps
	}
}


//*******************************************/
/*功能；SCI1的初始化配置，波特率为4800bps，8比特，无奇偶校验位(暂时反转)
入口参数：无
出口参数：无
/********************************************/
void IntialRS232_iec();
void IntialRS232_iec()
{   
   // int i;
//	GPIO_B_PER&=~GPIO_B_PER_PE10_MASK;		//PIN_DE GPIO enable
//	GPIO_B_DDR|=GPIO_B_DDR_DD10_MASK;		//PIN_DE OUTPUT
//	GPIO_B_DR&=~GPIO_B_DR_D10_MASK;			//PIN_DE set low level
	
//	SCI_1_CR&=~SCI_1_CR_M_MASK;		//Mbit位清零，数据为8位，一个起始位和一个结束位
//	SCI_1_CR|=SCI_1_CR_POL_MASK;	//暂时反转---用于接收电脑串口信号
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	BadurateSet_iec(3);				//波特率为4800bps 
	iec_rx.start_flag=0;
	iec_rx.end_flag=0;
	iec_rx.data_valid_flag=0;
	iec_rx.nownum=0;
	iec_rx.allnum=0;
	iec_rx.time=0;
	iec_rx.new_flag=0;
	iec_send_sum=0;
//	for(i=0;i<26;i++)
//	{
//	    nrmareamk[i]=0;
 //       nrmtypemk[i]=0;
		
//	}
    nrmflag_on=0;
}


//*******************************************/
/*功能，开启接收中断
入口参数：无
出口参数：无
/********************************************/
//void StartRS232_iec();
void StartRS232_iec()
{
   USART2->CR1|=USART_CR1_RE;
   USART2->CR1|=USART_CR1_RXNEIE;
	 USART_Cmd(USART2,ENABLE);	
}


//*******************************************/
/*功能；关闭传送和传送中断
入口参数：无
出口参数：无
/********************************************/
//void CloseRS232_iec();
void CloseRS232_iec()
{
   USART2->CR1&=~USART_CR1_RE;
   USART2->CR1&=~USART_CR1_RXNEIE;
	 USART_Cmd(USART2,DISABLE);	
}

//*******************************************/
/*功能；数据传送
入口参数：无
出口参数：无
/********************************************/
void USART2_IRQHandler(void)
{
//	#pragma interrupt saveall
	static sword num_tem=0;
	//IPR2&=~IPR2_IRQB_IPL1_MASK;	//关闭IRQB的中断
	//IPR2&=~IPR2_IRQB_IPL0_MASK; 
//	SCI_1_SR&=~SCI_1_SR_RDRF_MASK;		//RE位置0，receiver无效	
	iec_rx.rx_data=USART2->DR;
 //   if((++i)>100)
 //   {
//	    COPCTR=0xAAAA;
//	    COPCTR=0x5555;	
 //   }
	num_tem++;
	if(num_tem>800)
	{
	num_tem=0;
	//	iec_rx.new_flag=0;
					CloseRS232_iec();		
					IntialIRQB();              //@wu
							iec_rx.nownum=0;
				iec_rx.start_flag=0;
				iec_rx.end_flag=0;
				iec_rx.data_valid_flag=0;
				iec_rx.time=0;	
		
	}
//	iec_rx_array[iec_rx.nownum++]=iec_rx.rx_data;
//	if(iec_rx.nownum>=199)
//		iec_rx.nownum=0;
	iec_check_end(iec_rx.rx_data);
	iec_check_data(iec_rx.rx_data);
	iec_check_start(iec_rx.rx_data);
}
//*******************************************/
/*功能；在IEC传输队列中增加一条信息
入口参数：所需添加信息在Messagesavetop[]中的位置
出口参数：无
/********************************************/
void iec_InsMsg(short int xulie)
{
	iec_send_list[iec_send_sum++]=xulie;		
}
//*******************************************/
/*功能:传输当前所选定信息
入口参数：Messagesavetop[]数组序列号
出口参数：无
/********************************************/
void iec_send_message(short int num)
{
	PrtStart->xulie=num;
	ReadIecMsg();	//从FPGA读取所需打印信息
	BadurateSet(BAUD_IEC);
	StartRS232(USART2);	//开启打印机
}

//*******************************************/
/*功能；传输所有信息
入口参数：无
出口参数：无
/********************************************/
//void iec_send(void);
void iec_send()
{
	static sword iec_temp2;
	iec_temp2=0;
	while(iec_temp2<iec_send_sum)
	{
		iec_send_message(iec_send_list[iec_temp2]);
//		ReadPrtMsg();	//从FPGA读取所需打印信息
//		StartRS232();	//开启打印机
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
			DataTran(USART2);
		};
		iec_temp2++;
	}
	iec_send_sum=0;
}

//*******************************************/
/*功能；传输单条报警信息函数
入口参数：无
出口参数：无
/********************************************/
void iec_send_single_alarm(char No);
void iec_send_single_alarm(char No)
{
	ReadIecAlarm(No);	//读取所需传送信息
	BadurateSet(BAUD_IEC);
	StartRS232(USART2);	//开启IEC传送
//	Checkinfo.Printover = 0;
}
//*******************************************/
/*功能；传输所有报警信息
入口参数：无
出口参数：无
/********************************************/
void iec_send_alarm()
{
	if(iec_alarm_data&0x01)
	{
		iec_send_single_alarm(1);
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
		  DataTran(USART2);
		};	
	}
	if(iec_alarm_data&0x02)
	{
		iec_send_single_alarm(2);
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
		  DataTran(USART2);			
		};	
	}
	if(iec_alarm_data&0x04)
	{
		iec_send_single_alarm(3);
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
		  DataTran(USART2);			
		};	
	}
	if(iec_alarm_data&0x08)
	{
		iec_send_single_alarm(4);
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
		  DataTran(USART2);			
		};	
	}
	if(iec_alarm_data&0x10)
	{
		iec_send_single_alarm(5);
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
		  DataTran(USART2);			
		};	
	}
	if(iec_alarm_data&0x20)
	{
		iec_send_single_alarm(6);
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
		  DataTran(USART2);			
		};	
	}
	iec_alarm_data=0;
	flag_on=0;
}