#include <stdio.h>
#include <stdlib.h>
#include "Eprom.h"
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "ThreeDays.h"
#include "code.h"
#include "iec.h"
#include "stm32f2xx.h"
#include "rtc.h"

extern void TIM3_IRQHandler(void);
//volatile char TimeLeft;

/************************************************/
/*	¹¦ÄÜ£»×Ô¼ìº¯ÊýBootÏÔÊ¾º¯Êý
Èë¿Ú²ÎÊý£ºÎÞ
³ö¿Ú²ÎÊý£ºÎÞ
/************************************************/
void Boot_Paintintial();
void Boot_Paintintial()
{
	char i;
	CLEAR1();	
	if(LANGUAGE==0)	//Ó¢ÎÄ½çÃæ
	{

		/* ±íÍ·SELFDIAG AND TIMESET */
		CTAB[2]='S';	CTAB[3]='E';	CTAB[4]='L';	CTAB[5]='F';
		CTAB[6]='D';	CTAB[7]='I';	CTAB[8]='A';	CTAB[9]='G';
		CTAB[11]='A';	CTAB[12]='N';	CTAB[13]='D';
		CTAB[15]='T';	CTAB[16]='I';	CTAB[17]='M';	CTAB[18]='E';
		CTAB[19]='S';	CTAB[20]='E';	CTAB[21]='T';		
		CW_PR(0,1,22);
		
		/* Ð´ÈëµÚÒ»ÐÐÊý¾ÝDIGA RESULT */
		CTAB[0]='D';	CTAB[1]='I';	CTAB[2]='G';	CTAB[3]='A';	
		CTAB[5]='R';	CTAB[6]='E';	CTAB[7]='S';	CTAB[8]='U';	CTAB[9]='L';
		CTAB[10]='T';
		CW_PR(5,3,11);

		SelfDiagnosis_Partpaint();
		

		
		/* Ð´ÈëµÚÊ®ÐÐÊý¾Ý TIME SET*/
		CTAB[0]='T';	CTAB[1]='I';	CTAB[2]='M';		
		CTAB[3]='E';	CTAB[5]='S';	CTAB[6]='E';	CTAB[7]='T';
		CTAB[8]=':';
		CTAB[9]='2';	CTAB[10]='0';
		CTAB[13]='/';	CTAB[16]='/';	CTAB[19]='/';	CTAB[22]=':';
		CW_PR(5,14,23);
		


		
		/* Ð´ÈëµÚÊ®Ò»ÐÐÊý¾Ý DIAGNOSIS LOG*/				
		CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='T';	CTAB[4]='D';
		CTAB[5]='O';	CTAB[6]='N';	CTAB[7]='E';	CTAB[8]=',';
		CTAB[9]='E';	CTAB[10]='N';	CTAB[11]='T';	CTAB[12]='E';
		CTAB[13]='R';	CTAB[15]='E';	CTAB[16]='N';	CTAB[17]='T';	
		CTAB[19]='K';	CTAB[20]='E';	CTAB[21]='Y';
								
		CW_PR(5,18,22);
		
		CTAB[0]='A';	CTAB[1]='F';	CTAB[2]='T';	CTAB[3]='E';
		CTAB[4]='R';	CTAB[8]='S';	
		CTAB[10]='J';	CTAB[11]='U';	CTAB[12]='M';	CTAB[13]='P';
		CTAB[15]='A';	CTAB[16]='U';	CTAB[17]='T';	CTAB[18]='O';	
		CTAB[19]='M';	CTAB[20]='A';	CTAB[21]='T';
		CTAB[22]='I';	CTAB[23]='C';	CTAB[24]='A';	CTAB[25]='L';
		CTAB[26]='L';	CTAB[27]='Y';	
								
		CW_PR(5,22,28);

		W_DIAMOND(3,3);		//Íê³ÉÑ¡¶¨¿òµÄÏÔÊ¾
		W_HDIAMOND(3,14);
		W_HDIAMOND(3,18);
	
	}
 	
 	else	//ÖÐÎÄ½çÃæ
 	{
 		W_XLINE(0,319,25);	
		W_CLEARXLINE(0,319,22);
		W_CLEARXLINE(0,319,230);
		
 		CCW_PR1(1,7,0xd7d4,1);		//µÚÒ»ÐÐÄÚÈÝ"×Ô¼ìºÍÊ±¼äÉèÖÃ²Ëµ¥"
 		CCW_PR1(3,7,0xbcec,1);
     	CCW_PR1(5,7,0xbacd,1);		
    	CCW_PR1(7,7,0xcab1,1);
 		CCW_PR1(9,7,0xbce4,1);
 	 	CCW_PR1(11,7,0xc9e8,1);
 	 	CCW_PR1(13,7,0xd6c3,1);		
 		CCW_PR1(15,7,0xb2cb,1);
  		CCW_PR1(17,7,0xb5a5,1);
  				
 		CCW_PR1(35,7,0xcad6,1);
 		CCW_PR1(37,7,0xb6Af,1);
 		
 		
 	 	CCW_PR1(6,32,0xd7d4,1);		//µÚ¶þÐÐÄÚÈÝ"×Ô¼ì½á¹û"
 		CCW_PR1(8,32,0xbcec,1);
  		CCW_PR1(10,32,0xbde1,1);
 		CCW_PR1(12,32,0xb9fb,1);		
 		
 		SelfDiagnosis_Partpaint();
 	 	
		
   		CCW_PR1(6,192,0xcab1,1);	//µÚÊ®Ò»ÐÐÄÚÈÝ"Ê±¼äÉèÖÃ:"
 		CCW_PR1(8,192,0xbce4,1);
 	 	CCW_PR1(10,192,0xc9e8,1);
 	 	CCW_PR1(12,192,0xd6c3,1);
 	 	CCW_PR1(14,192,0x1aa0,0);
 
  		CTAB[0]='2';	CTAB[1]='0';	CTAB[4]='/';CTAB[7]='/';	CTAB[10]='/';
		CTAB[13]=':';
		CW_PR(16,25,27);  
 
 
 
   		CCW_PR1(6,216,0xc9e8,1);	//µÚÊ®¶þÐÐÄÚÈÝ"ÉèÖÃÍê±Ï£¬°´ÏÂent¼ü"
 		CCW_PR1(8,216,0xd6c3,1);
 	 	CCW_PR1(10,216,0xcdea,1);
 	 	CCW_PR1(12,216,0xb1cf,1);
 		CW_PR3(14,28,',');	 	
   		CCW_PR1(15,216,0xb0b4,1);	
		CCW_PR1(17,216,0xcfc2,1);
		CW_PR3(19,28,'E');
		CW_PR3(20,28,'N');
		CW_PR3(21,28,'T');
	   	CCW_PR1(22,216,0xbcfc,1);	
		
		CCW_PR1(24,216,0x1860,0);
   		CCW_PR1(28,216,0xc3eb,1);	//Ãë×Ô¶¯Ìø×ª	
		CCW_PR1(30,216,0xd7d4,1);				
   		CCW_PR1(32,216,0xb6af,1);	
		CCW_PR1(34,216,0xccf8,1);		
   		CCW_PR1(36,216,0xd7aa,1);	
   		CCW_PR1(38,216,0x1880,0);	
	
		
	 	W_DIAMOND(3,36);
		W_HDIAMOND(3,196);
		W_HDIAMOND(3,220);
 
 	}

	W_YLINE(0,0,239);
	W_YLINE(319,0,239);	


	DISASCII(LANGUAGE?18:16,LANGUAGE?25:14,iyear);			//ÏÔÊ¾¹ú¼ÊÊ±¼äµÄÊýÖµ
	DISASCII(LANGUAGE?21:19,LANGUAGE?25:14,imonth);
	DISASCII(LANGUAGE?24:22,LANGUAGE?25:14,iday);
	DISASCII(LANGUAGE?27:25,LANGUAGE?25:14,ihour);
	DISASCII(LANGUAGE?30:28,LANGUAGE?25:14,iminute);
	
//	IntialIRQB();			//IRQBÖÐ¶Ï¿ªÆô
	flag_on=1;
	Selfdiag(0);				//ÔËÐÐ×Ô¼ìº¯Êý
	Diagresult_Paint(Diaglogs);	//°Ñ×Ô¼ì½á¹ûÏÔÊ¾ÔÚLCD
	
	//IPR2&=~IPR2_IRQB_IPL1_MASK;	//¹Ø±ÕIRQBµÄÖÐ¶Ï
	//IPR2&=~IPR2_IRQB_IPL0_MASK; 
 }
 
 
/************************************************/
/*	¹¦ÄÜ£»ÉÏÏÂ°´¼ü´¦Àíº¯Êý£¬Ñ¡ÔñËùÐèÑ¡Ïî
Èë¿Ú²ÎÊý£ºÎÞ
³ö¿Ú²ÎÊý£ºÎÞ
/************************************************/
void Boot_Updn();
void Boot_Updn()
 {

	if(G_Key==UP||G_Key==DOWN)
	{
		if (G_Key==UP)
		{
			G_Key=0;		//°´¼üÇåÁã
			if(BUFFER[0]==1 || BUFFER[0]==2 )	//·Ç×îÉÏÔòÉÏÒÆ,0 1 2 3Îª¶Ô±È¶È¡¢·äÃù¡¢¹ú¼ÊÊ±¼äºÍ±¾µØÊ±¼ä
			{
				BUFFER[0]=BUFFER[0]-1;        //·Ç×îÉÏÔòÉÏÒÆ
				
				if(BUFFER[0]==0)				//ÏÔÊ¾Ñ¡¶¨µÄÑ¡¶¨¿ò
				{
					W_DIAMOND(3,LANGUAGE?36:3);	
					W_HDIAMOND(3,LANGUAGE?196:14);	
				}
				
				if(BUFFER[0]==1)
				{
					W_DIAMOND(3,LANGUAGE?196:14);	
					W_HDIAMOND(3,LANGUAGE?220:18);	
				}
			}

			

			
		 	/*  TODÉèÖÃ£­Ê±¼äÊäÈë£­¼Ó  */

			if (BUFFER[0]==3&&iyear<99)            //Äê¼Ó1 Ö»±íÊ¾ºóÈýÎ»£¬³õÊ¼ÖµÎª08£¬·¶Î§08£­99
			{
				iyear=iyear+1;
			}
				
			if (BUFFER[0]==4&&imonth<12)        	//ÔÂ¼Ó1,³õÊ¼ÖµÎª1£¬·¶Î§1£­12,Í¬Ê±ÐèÒªÐÞ¸Ä¶ÔÓ¦µÄÌìÊý£¬ÒÔÃâÔÚÄ³Ð©ÔÂ·Ý³öÏÖ²»¸ÃÓÐµÄÌìÊý
			{
				imonth=imonth+1;
				if(imonth==4||imonth==6||imonth==9||imonth==11) 
				{
					if (iday>30 )					//Ð¡ÔÂÌìÊý30,´ËÊ±ÌìÊýÈô³¬¹ý30Ìì£¬»Ö¸´µ½30Ìì
					iday=30;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //±íÊ¾ÈòÄê£¬2ÔÂÌìÊý29,´ËÊ±ÌìÊýÈô³¬¹ý29Ìì£¬»Ö¸´µ½29Ìì
					{
						if (iday>29 )
						iday=29;
					}
					else							//·ÇÈòÄê£¬2ÔÂÌìÊý28,´ËÊ±ÌìÊýÈô³¬¹ý28Ìì£¬»Ö¸´µ½28Ìì
					{
						if (iday>28 )
						iday=28; 
					}
				}
			}
			
			if (BUFFER[0]==5)       				//ÈÕ¼Ó1,³õÊ¼ÖµÎª1£¬·¶Î§1£­31,1-30,1-29,1-28
			{
				if(imonth==1||imonth==3||imonth==5||imonth==7||imonth==8||imonth==10||imonth==12)   //´óÔÂ£¬Ã¿ÔÂÌìÊý31Ìì
				{
					if (iday<31 )
					iday=iday+1;
				}
				
				if(imonth==4||imonth==6||imonth==9||imonth==11)     	//Ð¡ÔÂ£¬Ã¿ÔÂÌìÊý30Ìì
				{
					if (iday<30 )
					iday=iday+1;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //±íÊ¾ÈòÄê£¬2ÔÂÌìÊý29
					{
						if (iday<29 )
						iday=iday+1;
					}
					else							//·ÇÈòÄê£¬2ÔÂÌìÊý28
					{
						if (iday<28 )
						iday=iday+1; 
					}
				}
			}
				
			
			if (BUFFER[0]==6&&ihour<23)       	//Ê±¼Ó1,³õÊ¼ÖµÎª0£¬·¶Î§0£­23
			{
				ihour=ihour+1;
			}
				
			
			if (BUFFER[0]==7&&iminute<59)       	//·Ö¼Ó1,³õÊ¼ÖµÎª0£¬·¶Î§0£­59
			{
				
				iminute=iminute+1;
			}
			
			

			
		}
		
		if (G_Key==DOWN)
		{
			G_Key=0;								//°´¼üÇåÁã
			if(BUFFER[0]==0||BUFFER[0]==1)        
			{
				BUFFER[0]=BUFFER[0]+1;       	//·Ç×îÏÂÔòÏÂÒÆ
				
				if(BUFFER[0]==1)				//ÏÔÊ¾Ñ¡¶¨µÄÑ¡¶¨¿ò
				{
					W_DIAMOND(3,LANGUAGE?196:14);	
					W_HDIAMOND(3,LANGUAGE?36:3);	
				}
				
				if(BUFFER[0]==2)
				{
					W_DIAMOND(3,LANGUAGE?220:18);	
					W_HDIAMOND(3,LANGUAGE?196:14);	
				}       
			}

			
	
		 	/*  TODÉèÖÃ£­Ê±¼äÊäÈë£­¼õ  */
	
			if (BUFFER[0]==3&&iyear>14 )       	//Äê¼õ1 Ö»±íÊ¾ºóÈýÎ»£¬³õÊ¼ÖµÎª2008
			{
				iyear=iyear-1;
			}
				
			
			if (BUFFER[0]==4&&imonth>1)        //ÔÂ¼õ1,³õÊ¼ÖµÎª1£¬×îÐ¡Îª1£¬Í¬Ê±ÐèÒªÐÞ¸Ä¶ÔÓ¦µÄÌìÊý£¬ÒÔÃâÔÚÄ³Ð©ÔÂ·Ý³öÏÖ²»¸ÃÓÐµÄÌìÊý
			{
				imonth=imonth-1;
				
				if(imonth==4||imonth==6||imonth==9||imonth==11) 
				{
					if (iday>30 )					//Ð¡ÔÂÌìÊý30,´ËÊ±ÌìÊýÈô³¬¹ý30Ìì£¬»Ö¸´µ½30Ìì
					iday=30;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //±íÊ¾ÈòÄê£¬2ÔÂÌìÊý29,´ËÊ±ÌìÊýÈô³¬¹ý29Ìì£¬»Ö¸´µ½29Ìì
					{
						if (iday>29 )
						iday=29;
					}
					else							//·ÇÈòÄê£¬2ÔÂÌìÊý28,´ËÊ±ÌìÊýÈô³¬¹ý28Ìì£¬»Ö¸´µ½28Ìì
					{
						if (iday>28 )
						iday=28; 
					}
				}
			}
			
			if (BUFFER[0]==5&&iday >1)       	//ÈÕ¼õ1,³õÊ¼ÖµÎª1£¬×îÐ¡Îª1
			{
				iday=iday-1;
			}
			
			if (BUFFER[0]==6&&ihour>0)       	//Ê±¼õ1,³õÊ¼ÖµÎª0£¬×îÐ¡Îª0
			{
				ihour=ihour-1;
			}
				
			if (BUFFER[0]==7&&iminute>0)      //·Ö¼õ1,³õÊ¼ÖµÎª0£¬×îÐ¡Îª0
			{
				iminute=iminute-1;
			}
			
		}

		DISASCII(LANGUAGE?18:16,LANGUAGE?25:14,iyear);			//ÏÔÊ¾¹ú¼ÊÊ±¼äµÄÊýÖµ
		DISASCII(LANGUAGE?21:19,LANGUAGE?25:14,imonth);
		DISASCII(LANGUAGE?24:22,LANGUAGE?25:14,iday);
		DISASCII(LANGUAGE?27:25,LANGUAGE?25:14,ihour);
		DISASCII(LANGUAGE?30:28,LANGUAGE?25:14,iminute);
	}

	
}
/************************************************/
/*	¹¦ÄÜ£»×óÓÒ°´¼ü´¦Àíº¯Êý£¬Òº¾§¼ì²âº¯Êý
Èë¿Ú²ÎÊý£ºÎÞ
³ö¿Ú²ÎÊý£ºÎÞ
/************************************************/
void Boot_Leftright() ;
void Boot_Leftright()                
{
	byte i;
	if (G_Key==RIGHT||G_Key==LEFT)
    {
    
	
		if(BUFFER[0]>=3&&BUFFER[0]<=7&&G_Key==RIGHT)
		{
			BUFFER[0]=((BUFFER[0]-3)+1)%5+3;
		}
		
		
		if(BUFFER[0]>=3&&BUFFER[0]<=7&&G_Key==LEFT)
		{
			BUFFER[0]=((BUFFER[0]-3)+4)%5+3;
		}
	

	
		G_Key=0;				//°´¼üÇåÁã
		


	 	if (BUFFER[0]==3)		//¹ú¼ÊÊ±¼äµ×²¿ºáÏßµÄÌø×ª
	 	{
	 		W_XLINE(LANGUAGE?128:112,LANGUAGE?159:143,LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?168:152,LANGUAGE?183:167,LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?240:224,LANGUAGE?255:239,LANGUAGE?208:120);			 		 	
	 	}

	 	
	 	if (BUFFER[0]==4)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?168:152,LANGUAGE?183:167,LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?128:112,LANGUAGE?159:143,LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?192:176,LANGUAGE?207:191,LANGUAGE?208:120);			 		 	
	 	}
	 	
	 	if (BUFFER[0]==7)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?240:224,LANGUAGE?255:239,LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?216:200,LANGUAGE?231:215,LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?128:112,LANGUAGE?159:143,LANGUAGE?208:120);			 		 	
	 	}

	 	
	 	
	 	if (BUFFER[0]==5||BUFFER[0]==6)	
	 	{
	 		int i;
	 		i=(BUFFER[0]-5)*24;
	 		W_XLINE(LANGUAGE?(192+i):(176+i),LANGUAGE?(207+i):(191+i),LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?(168+i):(152+i),LANGUAGE?(183+i):(167+i),LANGUAGE?208:120);
	 		W_CLEARXLINE(LANGUAGE?(216+i):(200+i),LANGUAGE?(231+i):(215+i),LANGUAGE?208:120);			 		 	
	 	}


				
    }
}
 
/***************************************************************/
/*	¹¦ÄÜ£»CLR°´¼ü´¦Àíº¯Êý£¬·µ»Øµ½ÉÏ²ã½çÃæÎ¬»¤²Ëµ¥
Èë¿Ú²ÎÊý£ºÎÞ
³ö¿Ú²ÎÊý£ºÎÞ
/***************************************************************/
void Boot_Return();
void Boot_Return()
{


	if (G_Key==CLR&&BUFFER[0]>=3&&BUFFER[0]<=7)                  		//ÔÚ¹ú¼ÊÊ±¼äÎ»ÖÃÏÂ°´ÏÂclr·µ»Ø
	{
		G_Key=0;					//°´¼üÇåÁã
		W_CLEARXLINE(LANGUAGE?128:112,LANGUAGE?255:239,LANGUAGE?208:120);	//Çå³ýÏÂ»®Ïß

		W_DIAMOND(3,LANGUAGE?196:14);		
		

		
		BUFFER[0]=1;       //BUFFER[0]=1±íÊ¾Ìø»Ø±¾µØÊ±¼ä
	}


}
 
/***************************************************************/
/*	¹¦ÄÜ£»ENT°´¼ü´¦Àíº¯Êý£¬½øÐÐ×Ô¼ì²Ù×÷£¬»òÕß²é¿´×Ô¼ìÈÕÖ¾
Èë¿Ú²ÎÊý£ºÎÞ
³ö¿Ú²ÎÊý£ºÎÞ
/***************************************************************/
void Boot_Dealing();
void Boot_Dealing()
{

	 if(G_Key==ENT||TimeLeft<0)
	 {
	 	G_Key=0;

	 	if (BUFFER[0]==1&&TimeLeft>=0)					//½øÈë¹ú¼ÊÊ±¼äÉèÖÃ
	 	{
	 		BUFFER[0]=3;
	 		W_XLINE(LANGUAGE?128:112,LANGUAGE?159:143,LANGUAGE?208:120);
	 		W_HDIAMOND(3,LANGUAGE?196:14);	 		 	
	 	}
	    
	 	if (BUFFER[0]==2||TimeLeft<0)					//½øÈë±¾µØÊ±¼äµÄÊ±²îÉèÖÃ
	 	{
	 	/*zzy modified@2010-10-9£¬µ±×Ô¶¯¼õÍêºó¹Ø±ÕÃëÖÐ¶Ï*/
	// 		IPR6&=0xFFCF;			//¹Ø±ÕTODµÄÃëÖÐ¶Ï
//			TODCS&=0xfff7;//	¹Ø±ÕÃëÖÐ¶Ï
      TIM3->CR1&=0xfffe;  // ¹Ø¶¨Ê±Æ÷
	//-----------modified ended------------		
	 		BUFFER[0]=0;
//	 		TODCS=TODCS&0xfffe;	//TODEN=0,¹Ø±ÕTODÄ£¿é
//			TODDAY=DatesToDays(iyear,imonth,iday);
//			TODHR=ihour;		//°ÑÐ¡Ê±ÖÃÈëTODHR	
//			TODMIN=iminute;		//°Ñ·ÖÖÓÖÃÈëTODMIN
//			TODCSL=0x7a93;//7b17;		//ÊäÈëTODÄ£¿éµÄÊ±ÖÓÎª31.25Khz£¬½øÐÐ0x7b11+1µÄÔ¤·ÖÆµ²úÉú1HzÂö³å
//			TODCS|=0x0001;		//¿ªÆôTODÄ£¿é
//			TODCS&=0xfff7; 
			RTC_TimeRegulate(iyear,imonth,iday,ihour,iminute);
			//rtc save time
			timestruct.year=iyear;
			timestruct.month=imonth;
			timestruct.day=iday;
			timestruct.hour=ihour;
			timestruct.minute=iminute;   
	 		FLAG=0;
			STATE=1;			//STATEÎªÅÐ¶¨½øÈëºÎ½çÃæµÄÈë¿Ú²ÎÊý£¬³õÊ¼»¯½øÈëÐÅÏ¢ÕýÎÄ½çÃæ
			State1parameter=0;	//Èë¿Ú²ÎÊý0
			CLEAR1();		//ÇåÒ»ÇøºÍ¶þÇøµÄ´æ´¢¿Õ¼ä
//			SaveTime();
	 	}	      
	 }
}

/***************************************************/
/*	¹¦ÄÜ£»×Ô¼ì²Ëµ¥£¬½øÐÐ½ÓÊÕ»ú×Ô¼ì£¬Òº¾§×Ô¼ì£¬²¢¿É
          ²é¿´×Ô¼ìÈÕÖ¾
          
Èë¿Ú²ÎÊý£ºÎÞ
³ö¿Ú²ÎÊý£ºÎÞ
/***************************************************/ 
void RunBoot();
void RunBoot()
{
//	ReadTime();	//¼ÓÔØÊ±¼ä
	FLAG=1;
	TimeLeft=30;
//	IPR6|=0x0010;			//ÉèÖÃTODµÄÃëÖÐ¶ÏµÄÖÐ¶Ï¼¶±ðÎª10
	Boot_Paintintial();
	TIM3->CR1 |= 0x01;   //¿ª¶¨Ê±Æ÷
	TIM3_IRQHandler();			//ÏÔÊ¾µ±Ç°Ê£ÓàÌø×ªÊ±¼ä£¬Íê±Ïºó¿ªÆôÃëÖÐ¶Ï
	
	while(FLAG)
	{
		Boot_Updn();
		Boot_Leftright();		
		Boot_Dealing();
		Boot_Return();	
	}
//    TODCS&=0xfff7;
}
	
