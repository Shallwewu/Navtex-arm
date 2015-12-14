#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
/********************************************************/
/*??;Messageinfo.nownumber[]????
????:?
????:?
/********************************************************/
void Nownumber(char mode);
void Nownumber(char mode)
{
	sword i=0;
	if(mode)		//Nownumber[1]????,??????????
	{
		if(Messageinfo.locknumber[0]>0)
		{
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) 
				{
					Messageinfo.nownumber[1]=i;
					break;	
				}
			}				
		}
		else
		Messageinfo.nownumber[1]=0;		//??nownumber[1],????????????		
	}

	else		 //Nownumber[0]????,??????????			
	{
		if(Messageinfo.savenumber[0]>0)
		Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
		else
		Messageinfo.nownumber[0]=0;		
	}	
}

/********************************************************/
/*??;??????????????????
????:?
????:?
/********************************************************/
void SaveMenu_biaoji();
void SaveMenu_biaoji()
{

	if(Messageinfo.nownumber[Returnback]>0) W_DOWNMOVE(39,29);
	else W_CLEARUPDN(39,29);
	
	if(Messageinfo.nownumber[Returnback]<(Messagenumber-1)) W_UPMOVE(39,3);
	else W_CLEARUPDN(39,3);
	

	DISASCIII(12,29,Messagenumber-Messageinfo.nownumber[Returnback]);		
}

/********************************************************/
/*??;?????????
????:?
????:?
/********************************************************/
void SaveMenu_Paint();
void SaveMenu_Paint()
{	
	sword i,j=0;

	for(i=BUFFER[0];(i>=0&&(BUFFER[0]-i)<6);i--)	//??????
	{	
		W_MSGTOP(i,5+4*j,Returnback);
		j++;	
	}
	
	if(j<6)			//???????????
	{
		for (j;j<6;j++)
		W_CLEARMSGTOP(5+4*j);		
	}		

	
	
}
/********************************************************/
/*??;????????????
????:?
????:?
/********************************************************/
void SaveMenu_Paintintial();
void SaveMenu_Paintintial()	
{
	byte sortmode;					//sortmode????????
	sword i,l=0;
	if(subback==10) RecoverData();	//??????,??????????
	else 
	{
	CLEAR1();
		if(LANGUAGE==0)
		{

		     /* ????????? SAVEMENU SORT:*/
			if(Returnback!=1)
			{
				CTAB[2]='M';	CTAB[3]='S';	CTAB[4]='G';	CTAB[5]=' ';	CTAB[6]='L';	 CTAB[7]='I';
				CTAB[8]='S';	CTAB[9]='T';	CTAB[14]='S';	CTAB[15]='O';	CTAB[16]='R';	 CTAB[17]='T';
			    CTAB[18]=':';
				CW_PR(0,1,19);	
			}
			else
			{
				CTAB[2]='L';	CTAB[3]='O';	CTAB[4]='C';	CTAB[5]='K';	CTAB[6]='E';	 CTAB[7]='D';
				CTAB[8]=' ';	CTAB[9]='M';	CTAB[10]='S';	CTAB[11]='G';	CTAB[14]='S';	CTAB[15]='O';	
				CTAB[16]='R';	 CTAB[17]='T';	CTAB[18]=':';
				CW_PR(0,1,19);
			}
		     /* ????????? ID FREQ LINES DATE TIME */
			CTAB[4]='I';	 CTAB[5]='D';	 CTAB[10]='F';	 CTAB[11]='R';	  CTAB[12]='E'; CTAB[13]='Q';
		    /*CTAB[16]='L';   CTAB[17]='I';  CTAB[18]='N';  CTAB[19]='E';   CTAB[20]='S';*/
		    CTAB[23]='D';   CTAB[24]='A';  CTAB[25]='T';  CTAB[26]='E';   CTAB[31]='T'; 
		    CTAB[32]='I';   CTAB[33]='M';  CTAB[34]='E';     
			CW_PR(0,3,35);
	/*	    
			if(Returnback==1)	//??SaveMenu??????,??LOCK
		    {
		   		CW_PR3(2,1,'L');
		    	CW_PR3(3,1,'O');
		    	CW_PR3(4,1,'C');
		    	CW_PR3(5,1,'K');
		    }
	*/	    
			sortmode=Messageinfo.rankmode;	//??????????,??sortmode
		    
		    if(sortmode==0)  //?LCD????????????
		    {
		   		CTAB[0]='D';		CTAB[1]='A';	CTAB[2]='T';	CTAB[3]='E';
		   		CW_PR(19,1,4);					
		    } 
		    
		    if(sortmode==1)  
		    {
		   		CTAB[0]='R';		CTAB[1]='X';	CTAB[3]='S';	CTAB[4]='T';
		   		CTAB[5]='A';		CTAB[6]='T';
				CTAB[7]='I';		CTAB[8]='O';	CTAB[9]='N';	
		   		CW_PR(19,1,10);
		    }
		    if(sortmode==2)
		    {
		    	CTAB[0]='M';  CTAB[1]='S';  CTAB[2]='G';   CTAB[4]='T';  CTAB[5]='Y';
		    	CTAB[6]='P';  CTAB[7]='E';
		    	CW_PR(19,1,8);
		    }

		    if(sortmode==3)  
		    {
		   		CTAB[0]='U';		CTAB[1]='N';	CTAB[2]='R';	CTAB[3]='E';
		   		CTAB[4]='A';		CTAB[5]='D';
		   		CW_PR(19,1,8);					
		    }
		    
		    if(sortmode==4)  
		    {
		   		CTAB[0]='A';		CTAB[1]='R';	CTAB[2]='E';	CTAB[3]='A';
		   		CW_PR(19,1,4);					
		    }  		    
		}
		
		else	//????
		{
	 		
		    CLEARXLINE(0,39,3);		//??????
			CLEARXLINE(0,39,4);
			CLEARXLINE(0,39,5);
			CLEARXLINE(0,39,22);				    
			XLINE(0,39,19);
	
/*	 		CCW_PR1(1,3,Returnback?0xcbf8:0xb4e6,1);	//????"??(??)?? ??"
	 		CCW_PR1(3,3,Returnback?0xb6a8:0xb4a2,1);
	 		CCW_PR1(5,3,0xb2cb,1);
	 		CCW_PR1(7,3,0xb5a5,1);
*/
			CCW_PR1(1,3,Returnback?0xcbf8:0xd0c5,1);	//????"????/???? ??"
	 		CCW_PR1(3,3,Returnback?0xb6a8:0xcfa2,1);
	 		CCW_PR1(5,3,Returnback?0xd0c5:0xc1d0,1);
	 		CCW_PR1(7,3,Returnback?0xcfa2:0xb1ed,1);
	 	 	CCW_PR1(12,3,0xc5c5,1);
	 		CCW_PR1(14,3,0xd0f2,1);
	 		CW_PR3(16,1,':');
		    

			sortmode=Messageinfo.rankmode;	//??????????,??sortmode
		    if(sortmode==0) //?LCD????????????  
		    {
		 		CCW_PR1(17,3,0xCAB1,1);		//??
		 		CCW_PR1(19,3,0xBCE4,1);					
		    } 
		    
		    if(sortmode==1)  				//???
		    {
		 		CCW_PR1(17,3,0xB7A2,1);
		 		CCW_PR1(19,3,0xC9E4,1);	
		 		CCW_PR1(21,3,0xCCA8,1);						
		    }
		    
		    if(sortmode==2)  				//????
		    {
		 		CCW_PR1(17,3,0xD0C5,1);
		 		CCW_PR1(19,3,0xCFA2,1);	
		 		CCW_PR1(21,3,0xC0E0,1);
		 		CCW_PR1(23,3,0xB1F0,1);
		    }
		    
		    if(sortmode==3)  				//????
		    {
		 		CCW_PR1(17,3,0xCEB4,1);
		 		CCW_PR1(19,3,0xB6C1,1);	
		 		CCW_PR1(21,3,0xD0C5,1);
		 		CCW_PR1(23,3,0xCFA2,1);
		    }
		    
		    if(sortmode==4)  				//?????
		    {
		 		CCW_PR1(17,3,0xBABD,1);
		 		CCW_PR1(19,3,0xD0D0,1);	
		 		CCW_PR1(21,3,0xBEAF,1);
		 		CCW_PR1(23,3,0xB8E6,1);
				CCW_PR1(25,3,0xC7F8,1);		 							
		    }
		   		 		
	 		
	  		CW_PR3(4,3,'I');CW_PR3(5,3,'D');	//?????"ID ?? ?? ?? ??"
	 		CCW_PR1(9,20,0xc6b5,1);
	 		CCW_PR1(11,20,0xc2ca,1);
	 		//CCW_PR1(16,20,0xd0d0,1);
	 		//CCW_PR1(18,20,0xcafd,1);
	 	 	CCW_PR1(23,20,0xc8D5,1);
	 		CCW_PR1(25,20,0xC6DA,1);
	 	 	CCW_PR1(31,20,0xCAB1,1);
	 		CCW_PR1(33,20,0xBCE4,1);					
		}
		
	     
		CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='A';	CTAB[6]='M';
		CTAB[7]='O';	CTAB[8]='U';	CTAB[9]='N';	CTAB[10]='T';	CTAB[11]=':';
		CTAB[15]='/';
		CW_PR(0,29,16); //??????????????
		
		CTAB[1]='U';	CTAB[2]='N';	CTAB[3]='R';	CTAB[4]='E';	CTAB[5]='A';
		CTAB[6]='D';	CTAB[8]='M';	CTAB[9]='S';	CTAB[10]='G';	CTAB[11]=':';
		CW_PR(21,29,12); //????????
		DISASCIII(33,29,Unread);		
	


		
		XLINE(0,39,228);
		XLINE(0,39,229);
		CLEARXLINE(0,39,230);
		
		W_YLINE(0,0,239);
		W_YLINE(309,36,239);
		W_YLINE(319,0,239);//???????

		XLINE(0,39,36);			//???????,????????3?
		W_XLINE(304,309,36);
		XLINE(0,39,37);
		W_XLINE(304,309,37);


	 
	   
	   if(Messagenumber!=0)					//???????????
	   {
		   	if((subback!=1&&subback!=2)||(BUFFER[0]<0)) 	//????????????????????? 
		   	{
		   		W_BLOCK(39,5);
		   		BUFFER[0]=Messagenumber-1;	//?????BUFFER[0]????????????
		   		Messageinfo.nownumber[Returnback]=Messagenumber-1;
		   	}
		   	else		//???????????,???????
		   	{
				W_BLOCK(39,((BUFFER[0]-Messageinfo.nownumber[Returnback])%6)*4+5);		
	/*	   		if(Returnback==0)	//???????
		   		{
		   			W_BLOCK(39,((BUFFER[0]-Messageinfo.nownumber[Returnback])%6)*4+5);
					DISASCIII(16,29,Messageinfo.savenumber[0]-1);		//?????	   				
		   		}
		   		
		   		else
		   		{
		   			for(i=Messageinfo.nownumber[1];i<=BUFFER[0];i++)
		   			{
		   				if(Messagesavetop[Messagetoprank[i]].lock) l++; 
		   			}
		   		
		   			W_BLOCK(39,((l-1)%6)*4+5);	
		   			l=0;
		   			DISASCIII(16,29,Messageinfo.locknumber[0]-1);		//?????
		   		}*/
		   	} 	
//			if(BUFFER[0]<0)BUFFER[0]=Messagenumber-1;
			SaveMenu_Paint();					//???????
			SaveMenu_biaoji();					//??????????????????
	   
			DISASCIII(16,29,Messagenumber);		//?????

			XLINE(0,37,68);
			W_XLINE(304,309,68);
			//XLINE(0,37,69);
			//W_XLINE(304,309,69);

			XLINE(0,37,100);		
			W_XLINE(304,309,100);
			//XLINE(0,37,101);
			//W_XLINE(304,309,101);

			XLINE(0,37,132);
			W_XLINE(304,309,132);
			//XLINE(0,37,133);
			//W_XLINE(304,309,133);

			XLINE(0,37,164);
			W_XLINE(304,309,164);
			//XLINE(0,37,165);		
			//W_XLINE(304,309,165);
			
			XLINE(0,37,196);
			W_XLINE(304,309,196);
			//XLINE(0,37,197);
			//W_XLINE(304,309,197);			
	   }
	   
	   else										//???
	   {
		   	if(LANGUAGE==0)						//????
			{
				if(Returnback!=1)
				{
					CTAB[1]='N';	CTAB[2]='O';	CTAB[4]='M';	CTAB[5]='E';
					CTAB[6]='S';	CTAB[7]='S';	CTAB[8]='A';	CTAB[9]='G';
					CTAB[10]='E';	CTAB[11]='!';
					CW_PR(10,15,12);
				}
									//????:NO MESSAGE! 
				else
				{
					CTAB[1]='N';	CTAB[2]='O';	CTAB[4]='L';	CTAB[5]='O';
					CTAB[6]='C';	CTAB[7]='K';	CTAB[8]='E';	CTAB[9]='D';
					CTAB[10]=' ';	CTAB[11]='M';	CTAB[12]='E';	CTAB[13]='S';
					CTAB[14]='S';	CTAB[15]='A';	CTAB[16]='G';	CTAB[17]='E';
					CTAB[18]='!';
					CW_PR(10,15,19);
				}				
			}
			else								//????
			{
				if(Returnback!=1)
				{
					CCW_PR1(12,100,0xcede,1);
			 		CCW_PR1(14,100,0xd0c5,1);
			 	 	CCW_PR1(16,100,0xcfa2,1);
			 		CCW_PR1(18,100,0x1780,0);		//????:???!
				}
				else
				{
					CCW_PR1(12,100,0xcede,1);
					CCW_PR1(14,100,0xcbf8,1);
					CCW_PR1(16,100,0xb6a8,1);
			 		CCW_PR1(18,100,0xd0c5,1);
			 	 	CCW_PR1(20,100,0xcfa2,1);
			 		CCW_PR1(22,100,0x1780,0);		//????:?????!	
				}
			}
	   }
	   
	}
	if(Mode==1)
	{
		W_current_area(29,1,28,1,manual_area);	//???????????
	}		
	subback=0;			//subback??,????

	W_Mode(33,3,32,1);	//??,???????
	
}

/********************************************************/
/*??;UP?DOWN??????,?????????????,
		Messageinfo.nownumber[Returnback]?????????
????:?
????:?
/********************************************************/
void SaveMenu_Updn();
void SaveMenu_Updn()
{
	if(Messagenumber)	//?????,???????
	{
		if(BUFFER[0]>=0&&BUFFER[0]<Messagenumber)
		{
			if(G_Key == DOWN&&Messageinfo.nownumber[Returnback]>0)
			{	

				if((Messageinfo.nownumber[Returnback]+5)==BUFFER[0])	//???????????LCD????
				{
					Messageinfo.nownumber[Returnback]--;	//???????1	
					BUFFER[0]--;							//?????????1
					SaveMenu_Paint();						//LCD?????,????????
				}
				
				if((Messageinfo.nownumber[Returnback]+5)>BUFFER[0])		//???????????LCD??
				{
					Messageinfo.nownumber[Returnback]--;	//???????1
					W_BLOCK(39,((BUFFER[0]-Messageinfo.nownumber[Returnback])%6)*4+5);		//???????,????????????
					W_CLEARBLOCK(39,((BUFFER[0]-Messageinfo.nownumber[Returnback])%6)*4+1);
				}
				SaveMenu_biaoji();							//??????????????????
				G_Key=0;	//????
			}
				
			
			else if(G_Key == UP&&((Messageinfo.nownumber[Returnback]+1)<Messagenumber))
			{	

				if(Messageinfo.nownumber[Returnback]==BUFFER[0])	//???????????LCD??
				{
					Messageinfo.nownumber[Returnback]++;//???????1	
					BUFFER[0]++;						//?????????1
					SaveMenu_Paint();					//LCD?????,????????
				}
				
				if(Messageinfo.nownumber[Returnback]<BUFFER[0])
				{
					Messageinfo.nownumber[Returnback]++;	//???????1
					W_BLOCK(39,((BUFFER[0]-Messageinfo.nownumber[Returnback])%6)*4+5);		//???????,????????????
					W_CLEARBLOCK(39,((BUFFER[0]-Messageinfo.nownumber[Returnback])%6)*4+9);
				}
			
				SaveMenu_biaoji();						//??????????????????
				G_Key=0;	//????
			}
		}
	}
}

/********************************************************/
/*??;LEFT?RIGHT??????,???????????,
		?????????????
		Messageinfo.nownumber[Returnback]?????????
????:?
????:?
/********************************************************/
void SaveMenu_Leftright();
void SaveMenu_Leftright()
{
	if(Messagenumber!=0)	//?????,???????
	{
		if(BUFFER[0]>=0&&BUFFER[0]<Messagenumber)
		{	
		
			if(G_Key == RIGHT&&Messageinfo.nownumber[Returnback]>=Maxpagenum)	//?????Messageinfo.nownumber[Returnback]????
			{																	//Messageinfo.nownumber[Returnback]???????????????
				Messageinfo.nownumber[Returnback]=Messageinfo.nownumber[Returnback]-Maxpagenum;
				BUFFER[0]=BUFFER[0]-Maxpagenum;		//????????			
				SaveMenu_Paint();					//???????
				SaveMenu_biaoji();					//??????????????????			
				G_Key=0;							//????
			}
			
			if(G_Key == LEFT&&((BUFFER[0]+Maxpagenum)<Messagenumber))	//?????BUFFER[0]????
			{														//BUFFER[0]?????????????????????
				Messageinfo.nownumber[Returnback]=Messageinfo.nownumber[Returnback]+Maxpagenum;
				BUFFER[0]=BUFFER[0]+Maxpagenum;
				SaveMenu_Paint();					//???????
				SaveMenu_biaoji();					//??????????????????					
				G_Key=0;							//????
			}
		}		
	}
}

/*****************************************/
/*??;?????????????
????:?
????:?
/****************************************/
void SaveMenu_Star();
void SaveMenu_Star()
{
	if(G_Key == STAR&&Messagenumber)
	{

		FLAG=0;					//????

		if(Returnback==0)//??????????
		{
			STATE=20;			//SaveSubMenu???20
		}
		
		if(Returnback==1)//??????????
		{
			STATE=30;			//LockSubMenu???30
		}
		G_Key=0;				//????
	}
}

/*****************************************************/
/*??;MENU?DISP??????,?????????
????:?
????:?
/*****************************************************/
void SaveMenu_Menuchange();
void SaveMenu_Menuchange()
{

	if((G_Key==MENU||G_Key==DISP)&&STATE==2)
	{
		BUFFER[0]=0;						//?????,??????
		BUFFERPRO[0]=0;
		BUFFERPRO[1]=0;
		FLAG=0;								//????
		Nownumber(Returnback);				//Nownumber[]????
		if(G_Key==MENU)
		{
			STATE=4;							//??MainMenu??
			if(Returnback) State4parameter=2;	//2?????????
			else 		   State4parameter=1; 	//1?????????			
		}
		
		else
		{
			if(Returnback)					//????????,?????????????
			{
				STATE=5;					//Timelocation????5
				//STATE=1;			//Message???1
				State1parameter=0;	//?????0			
			}
			else							//???????????
			{
				STATE=2;					//????Savemenu???2						
				State2parameter=5;			//?????5,??Savemenu??????
			}			
		}
		Returnback=0;					//?????,??????
		G_Key=0;						//????
	}
/*	int i=0;
	if(G_Key == MENU) //?????
	{
		BUFFER[0]=0;						//?????,??????
		BUFFERPRO[0]=0;
		BUFFERPRO[1]=0;
		FLAG=0;								//????
		STATE=4;							//??MainMenu??
		
		if(Returnback) State4parameter=2;	//2?????????
		else 		   State4parameter=1; 	//1?????????
		Returnback=0;						//?????,??????
		G_Key=0;							//????
	}
	

	else if(G_Key == DISP&&STATE==2) 
	{

		BUFFER[0]=0;
		BUFFERPRO[0]=0;
		BUFFERPRO[1]=0;					//?????,??????							
		FLAG=0;							//????
		if(Returnback)					//????????,?????????????
		{

					
			STATE=5;					//Timelocation????5			
		}
		else							//???????????
		{
			Messageinfo.nownumber[0]=Messagenumber-1;
			STATE=2;					//????Savemenu???2						
			State2parameter=5;			//?????5,??Savemenu??????
		}
		Returnback=0;					//?????,??????
		G_Key=0;						//????
	}*/
}

/*********************************************************/
/*	??;??Message??,?????????
????:?
????:?
/*********************************************************/ 
void SaveMenu_Dealing();
void SaveMenu_Dealing()
{
	sword i=0;
	if(Messagenumber)
	{
		if(G_Key == ENT&&STATE==2)
		{
			BUFFERPRO[0]=BUFFER[0];				//??BUFFER[0]??
			BUFFERPRO[1]=Messageinfo.nownumber[Returnback];
			BUFFER[0]=0;						//BUFFER[0]??
			FLAG=0;								//????
			STATE=1;							//Message???1
			if(Returnback==0) State1parameter=1;//????1,???????????????
			else 
			{
				State1parameter=2;				//????2,???????????????
				for(i=0;i<Messageinfo.savenumber[0];i++)	//Messageinfo.nownumber[1]?savemenu???Msglockrank,?Message???Messagetoprank[]
				{
					if(Msglockrank[Messageinfo.nownumber[1]]==Messagetoprank[i])
					{
						Messageinfo.nownumber[1]=i;
						break;
					}
				}
			}
			G_Key=0;							//????
		}
	}
}

/*********************************************************/
/*	??;???????????,????????????
          ???????????:
          subback:???????,0??????,10?????
                  2??????,1????????????
          Returnback:0?????????,1??????
          BUFFER[0]:??????????????????
          BUFFERPRO[0]:????????????Message??
                       ??,??BUFFER[0]
????:into  ????????
????:?
/*********************************************************/ 
void RunSaveMenu(byte into)
{
	sword i,n,j=0,k;
	word msgread;
    maske=0;
    maskc=0;
	subback=into;
	

	if(into==0||into==3)  //???????????
	{
		Returnback=0;
		Messagenumber=Messageinfo.savenumber[0];
		if(Messagenumber>600||Messagenumber<0)
		{
			Intial_Message();			//?????????
			Messagenumber=Messageinfo.savenumber[0];
		}
		for(i=0;i<75;i++)//3.?????????,?i?n??,
		{
			for(n=0;n<8;n++)
			{
				if((Eprommap[i]&(0x01<<n))==0) break;
			}
			if(n!=8)break;
		}
		if(n==8)
		{
			if(Messagenumber!=600)
			{
				Intial_Message();			//?????????
				Messagenumber=Messageinfo.savenumber[0];
				msgread=0;
				for(i=0;i<Messageinfo.savenumber[0];i++)
				{
					if(Messagesavetop[Messagetoprank[i]].read==1)
					msgread++;
				}
				Unread=msgread;
				Write_Int_Eprm(UNREAD_MSG,Unread);			//??Unread?Eprom
			}
		}
	}
	
	if(into==4||into==5) //???????????
	{
		Returnback=1;
		for(i=0;i<Messageinfo.savenumber[0];i++)
		{
			if(Messagesavetop[Messagetoprank[i]].lock==1)
			Msglockrank[j++]=Messagetoprank[i];
		}
		Messagenumber=j;
		if(Messagenumber>600||Messagenumber<0)
		{
			Intial_Message();			//?????????
			for(i=0;i<Messageinfo.savenumber[0];i++)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1)
				Msglockrank[j++]=Messagetoprank[i];
			}
			Messagenumber=j;
		}	
	}
	if(manual_area==0)
	{
 		manual_area=11;
		Eprom_ManualMsgMode_Save(RXSTATION_MANUAL);	//??????Eprom		
	}
	SaveMenu_Paintintial();
	while(FLAG)
	{

//			k=IRQP1;
//            COPCTR=0xAAAA;
//            COPCTR=0x5555;			
			SaveMenu_Updn();
			SaveMenu_Leftright();
			SaveMenu_Star();
			SaveMenu_Dealing();
			SaveMenu_Menuchange();
			run_tip();
//			if(counter_flag_s==10)
//				run_tip(flag_s);
	}
}