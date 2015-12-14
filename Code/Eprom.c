#include "stm32f2xx.h"
#include "Eprom.h"
#include "timedelay.h"
#include "define.h"
#include "ThreeDays.h"
#include "run.h"
#include "code.h"
#include "rtc.h"
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //自己加的关于FPGA读写

//*********************************/
/*功能；背光指令，传输至FPGA
入口参数：无
出口参数：无
/**********************************/
void TransBacklight(void);
void TransBacklight()
{
	if(Backlight==0)		//1级
		FPGARW(3605)=0x7;
	
	else if(Backlight==1)	//2级
		FPGARW(3605)=0x9;
	
	else if(Backlight==2)	//3级
		FPGARW(3605)=0xb;
	
	else if(Backlight==3)	//4级
		FPGARW(3605)=0xc;
	else					//5级
		FPGARW(3605)=0xf;
}

//*********************************/
/*功能；对比度指令，传输至FPGA
入口参数：无
出口参数：无
/**********************************/
void TransContrast();
void TransContrast()
{
	if(Contrast==0)			//1级
		FPGARW(3604)=0x6;
	
	else if(Contrast==1)	//2级
		FPGARW(3604)=0x9;
	
	else if(Contrast==2)	//3级
		FPGARW(3604)=0xc;
	
	else if(Contrast==3)	//4级
		FPGARW(3604)=0xf;
	
	else					//5级
		FPGARW(3604)=0x12;

}

void IIC_Init(void)
{
    RCC->AHB1ENR|= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR|= RCC_AHB1ENR_GPIOCEN;  
    GPIOA->MODER&= 0xfffcffff;           
    GPIOA->MODER|= 0x00010000;     //OUT
    GPIOA->OTYPER&= 0xfffffeff;    //PULL-PUSH MODE
    GPIOA->OSPEEDR&= 0xfffcffff;
    GPIOA->OSPEEDR|= 0x00020000;
    GPIOA->PUPDR&= 0xfffcffff;     //PULL-UP
    GPIOA->PUPDR|= 0x00010000;
    GPIOC->MODER&= 0xfff3ffff;
    GPIOC->MODER|= 0x00040000;     //OUT
    GPIOC->OTYPER&= 0xfffffdff;    //PULL-PUSH MODE
    GPIOC->OSPEEDR&= 0xfff3ffff;
    GPIOC->OSPEEDR|= 0x00080000;
    GPIOC->PUPDR&= 0xfff3ffff;    //PULL-UP
    GPIOC->PUPDR|= 0x00040000;
    GPIOA->ODR|= 0x00000100;    //PA8=1
    GPIOC->ODR|= 0x00000200;    //PC9=1
    IICStop();
}

void IICStart(void)
{
	SDA_OUT();
	GPIOC->ODR|=0x00000200;    //SDA=1
	GPIOA->ODR|=0x00000100;    //SCL=1
	delay_us(4);
	GPIOC->ODR&=0xfffffdff;    //SDA=0
	delay_us(4);
    GPIOA->ODR&=0xfffffeff;    //SCL=0
}

void IICStop(void)
{
	SDA_OUT();
  GPIOA->ODR&=0xfffffeff;    //SCL=0
	GPIOC->ODR&=0xfffffdff;    //SDA=0
	delay_us(4);
	GPIOA->ODR|=0x00000100;    //SCL=1
	GPIOC->ODR|=0x00000200;    //SDA=1
	delay_us(4);
}

void InI2C_OutputACK(u8 mAck)
{
	if(mAck==0)
	{
    GPIOA->ODR&=0xfffffeff;    //SCL=0
	SDA_OUT();
	GPIOC->ODR&=0xfffffdff;    //SDA=0
	delay_us(2);
	GPIOA->ODR|=0x00000100;    //SCL=1
	delay_us(2);
    GPIOA->ODR&=0xfffffeff;    //SCL=0		
	}
	else
	{
    GPIOA->ODR&=0xfffffeff;    //SCL=0
	SDA_OUT();
	GPIOC->ODR|=0x00000200;    //SDA=1
	delay_us(2);
	GPIOA->ODR|=0x00000100;    //SCL=1
	delay_us(2);
    GPIOA->ODR&=0xfffffeff;    //SCL=0		
	}
}

void IICWrite_ONE_BYTE(u8 txd)
{
	u8 t;
	u32 txd1,ucErrTime=0;
	SDA_OUT();
    GPIOA->ODR&=0xfffffeff;    //SCL=0
	for(t=0;t<8;t++)
	{
	    txd1=(u32)txd;
			GPIOC->ODR&=0xfffffdff;
	    GPIOC->ODR|=((((u32)txd1)&0x00000080)<<2);
		txd<<=1;
		delay_us(2);
	    GPIOA->ODR|=0x00000100;    //SCL=1
		delay_us(2);
        GPIOA->ODR&=0xfffffeff;    //SCL=0
		delay_us(2);
	}
	SDA_IN();
	GPIOC->ODR|=0x00000200;    //SDA=1
	delay_us(1);
	GPIOA->ODR|=0x00000100;    //SCL=1
	delay_us(1);
	while((GPIOC->IDR)&0x00000200)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IICStop();
		}
	}
    GPIOA->ODR&=0xfffffeff;    //SCL=0
}

u8 IICRead_ONE_BYTE(void)
{
	unsigned char i,receive=0;
	SDA_IN();
	for(i=0;i<8;i++)
	{
        GPIOA->ODR&=0xfffffeff;    //SCL=0
		delay_us(2);
	    GPIOA->ODR|=0x00000100;    //SCL=1
		receive<<=1;
		if((GPIOC->IDR)&0x00000200)
			receive++;
		delay_us(1);
	}
	return receive;
}

void Write_Char_Eprm(u16 WriteAddr,u8 data)
{
	IICStart();
    IICWrite_ONE_BYTE(0xA0); 
 	IICWrite_ONE_BYTE(WriteAddr>>8);
 	IICWrite_ONE_BYTE(WriteAddr%256);
 	IICWrite_ONE_BYTE(data);
 	IICStop();
 	delay_ms(10);
	if(WriteAddr==RX_WORKFRE)
		FPGARW(3602)=Workfre;	
}

u16 Read_Int_Eprm(u16 address)
{
	u8 addh=address>>8,addl=address&0x00ff,datah,datal;
	u16 data;
	IICStart();
    IICWrite_ONE_BYTE(0xA0);
    IICWrite_ONE_BYTE(addh);
    IICWrite_ONE_BYTE(addl);  
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 
	 
    datah=IICRead_ONE_BYTE();
	InI2C_OutputACK(0x00);
	
    datal=IICRead_ONE_BYTE();
	InI2C_OutputACK(0x80);
	
	IICStop();
	
	data=(unsigned int)datah<<8;
	data|=(unsigned int)datal;
	return data;
    
}

void Write_Int_Eprm(u16 address,u16 data)
{
	unsigned char addh=address>>8,addl=address&0x00ff;
	unsigned char datah=data>>8,datal=data&0x00ff,datahagain,datalagain;
    IICStart();
    IICWrite_ONE_BYTE(0xA0);	//写控制字
    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);    
 	IICWrite_ONE_BYTE(datah);	//先写入高字节，再写低字节
 	IICWrite_ONE_BYTE(datal);	
	IICStop();
	delay_ms(10);    
}

void IICWrite_ONE_MEHE(Messagetoptype * messagetop,u16 address)//无终止信号
{
    sword i,k,j=0;
    unsigned char addh=address>>8,addl=address&0x00ff,temph,templ,temph1,templ1;
    IICStart();
    IICWrite_ONE_BYTE(0xA0);       		//写控制字
    IICWrite_ONE_BYTE(addh);       		//写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);	
    for(i=0;i<4;i++)
    
    IICWrite_ONE_BYTE(messagetop->mark[i]);
    
    IICWrite_ONE_BYTE(messagetop->frequency);
    
    for(i=0;i<3;i++)
    {
        IICWrite_ONE_BYTE(messagetop->date[i]);
    }
    
    IICWrite_ONE_BYTE(messagetop->time[0]);
    IICWrite_ONE_BYTE(messagetop->time[1]);
    
    IICWrite_ONE_BYTE(messagetop->lock);
    IICWrite_ONE_BYTE(messagetop->read);
   
    temph=messagetop->flashadd>>8;	
    templ=messagetop->flashadd;
    IICWrite_ONE_BYTE(temph);	//先存高位
    IICWrite_ONE_BYTE(templ);   //再存低位
    
    IICWrite_ONE_BYTE(messagetop->flashmount);   	
 
    IICWrite_ONE_BYTE(messagetop->select);   
    IICWrite_ONE_BYTE(messagetop->area);
    IICWrite_ONE_BYTE(messagetop->dealed);
    IICWrite_ONE_BYTE(messagetop->cer);

	temph1=(messagetop->amount)>>8;	
    templ1=messagetop->amount;
    IICWrite_ONE_BYTE(temph1);	//先存高位
    IICWrite_ONE_BYTE(templ1);   //再存低位
    IICStop();
   	delay_ms(10);
}


/*************************************************************/
  /*功能；从Eprom指定位置，读一个消息头的程序
入口参数：address word型，需读取信息在Eprom中首存储地址
		  messagetop Messagetoptype*型，所读取信息存放的
		  结构体指针  
出口参数：无
/*************************************************************/
void IICRead_ONE_MEHE(u16 address,Messagetoptype * messagetop)
{
    u16 i,length;
    u8 addh=address>>8,addl=address&0x00ff;
    u8 temph,templ,temph1,templ1;
    
    IICStart();
    IICWrite_ONE_BYTE(0xA0);       //写控制字
    IICWrite_ONE_BYTE(addh);       //写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 
    for(i=0;i<4;i++)
    {
        messagetop->mark[i]=IICRead_ONE_BYTE();
        InI2C_OutputACK(0x00);
    }
    
    messagetop->frequency=IICRead_ONE_BYTE();
    InI2C_OutputACK(0x00);
     
    for(i=0;i<3;i++)
    {
        messagetop->date[i]=IICRead_ONE_BYTE();
       	InI2C_OutputACK(0x00);
    }
    messagetop->time[0]=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    messagetop->time[1]=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    messagetop->lock=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    messagetop->read=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
  
    temph=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    templ=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
	messagetop->flashadd=(unsigned int)temph<<8;
	messagetop->flashadd|=(unsigned int)templ;
	
    messagetop->flashmount=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00); 
   	   
    messagetop->select=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    messagetop->area=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    messagetop->dealed=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);

    messagetop->cer=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);	
	
    temph1=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
   	
    templ1=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x80);
   	
	messagetop->amount=(unsigned int)temph1<<8;
	messagetop->amount|=(unsigned int)templ1;
   	    
	IICStop();
}

//*********************************************************************/
/*功能；接收机存储信息初始化
入口参数：无
出口参数：
/**********************************************************************/
void Reset_Message();
void Reset_Message()
{
	u16 i,j,add=19328;
	byte addh,addl;
	for(i=0;i<95;i++)
	{
	     addh=add>>8;
	     addl=add&0x00ff;
	     IICStart();	
	     IICWrite_ONE_BYTE(0xA0);       	
         IICWrite_ONE_BYTE(addh);       		
         IICWrite_ONE_BYTE(addl);
	     for(j=0;j<64;j++)
	     {
             IICWrite_ONE_BYTE(0x00);
	     }
	     IICStop();	
	     add=add+0x0040;
   	   delay_ms(10);
	}
	Write_Int_Eprm(DAY,220);	
}
//*********************************************************************/
/*功能；加载接收机存储信息
入口参数：无
出口参数：
/**********************************************************************/
void Intial_Message();
void Intial_Message()
{
	unsigned char addh,addl;
	u16 i,n,j,t,address=FlashmapStart;
	u16 ss[500],temp; 
	addh=address>>8;
	addl=address&0x00ff;
	IICStart();
    IICWrite_ONE_BYTE(0xA0);    //写控制字
    IICWrite_ONE_BYTE(addh);	//写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 	//读取所需数据
	
/*************Flashmap参数的读取*******************/	
	for(i=0;i<300;i++)
	{
		Flashmap[i]=IICRead_ONE_BYTE();
		InI2C_OutputACK(0x00);
	}

/*************Eprommap参数的读取*******************/	
	for(i=0;i<75;i++)
	{
		Eprommap[i]=IICRead_ONE_BYTE();
		InI2C_OutputACK(0x00);
	}
	

/*************Messageinfo参数的读取*******************/	

    for(j=0;j<2;j++)			//nownumber[2]数组参数读取，int型			
    {
		Messageinfo.nownumber[j]=0;	       
        for(i=0;i<2;i++)
	    {     
	        Messageinfo.nownumber[j]|=(unsigned int)IICRead_ONE_BYTE();
	       	InI2C_OutputACK(0x00);
	        if(i!=1) Messageinfo.nownumber[j]=Messageinfo.nownumber[j]<<8;    //先读的是高位
	    }	
    }
    

	
    
    for(j=0;j<4;j++)			//savenumber[4]数组参数读取，int型
    {
        Messageinfo.savenumber[j]=0;
        for(i=0;i<2;i++)
	    {     
	        Messageinfo.savenumber[j]|=(unsigned int)IICRead_ONE_BYTE();
	    	InI2C_OutputACK(0x00);
	        if(i!=1) Messageinfo.savenumber[j]=Messageinfo.savenumber[j]<<8;    //先读的是高位
	    }	
    }    
    
     for(j=0;j<4;j++)			//locknumber[4]数组参数读取，int型
    {
        Messageinfo.locknumber[j]=0;
        for(i=0;i<2;i++)
	    {     
	        Messageinfo.locknumber[j]|=(unsigned int)IICRead_ONE_BYTE();
			InI2C_OutputACK(0x00);
	        if(i!=1) Messageinfo.locknumber[j]=Messageinfo.locknumber[j]<<8;    //先读的是高位
	    }	
    }   

    
    Messageinfo.rankmode=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x80);
    		

	IICStop();




/*************Messagetoprank[600]的读取*******************/	

	Unread=Read_Int_Eprm(UNREAD_MSG);

	j=0;
	
	for(i=0;i<75;i++)//3.查找当前的空余位置，用i和n记录,
	{
		for(n=0;n<8;n++)
		{
			if((Eprommap[i]&(0x01<<n))!=0)
			{
				Messagetoprank[j++]=i*8+n;
    			IICRead_ONE_MEHE((i*8+n)*(word)MESSTYPELENGTH,&Messagesavetop[i*8+n]);			
			}
			 
		}
	}
//获取nownumber[0] nownumber[1]
	Messageinfo.nownumber[0]=j-1;
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].lock==1)
		{
			t++;	
		}
	}
	if(t!=0)
		Messageinfo.nownumber[1]=t-1;
	else
		Messageinfo.nownumber[1]=0;
//获取savenumber[0] savenumber[1] savenumber[2] savenumber[3]
	Messageinfo.savenumber[0]=j;
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==1)
		{
			t++;	
		}
	}
	Messageinfo.savenumber[1]=t;
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==2)
		{
			t++;	
		}
	}
	Messageinfo.savenumber[2]=t;
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==3)
		{
			t++;	
		}
	}
	Messageinfo.savenumber[3]=t;
	
	
//获取locknumber[0] locknumber[1] locknumber[2] locknumber[3]	
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].lock==1)
		{
			t++;	
		}
	}
	Messageinfo.locknumber[0]=t;
	
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==1&&Messagesavetop[Messagetoprank[i]].lock==1)
		{
			t++;	
		}
	}
	Messageinfo.locknumber[1]=t;
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==2&&Messagesavetop[Messagetoprank[i]].lock==1)
		{
			t++;	
		}
	}
	Messageinfo.locknumber[2]=t;
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==3&&Messagesavetop[Messagetoprank[i]].lock==1)
		{
			t++;	
		}
	}
	Messageinfo.locknumber[3]=t;	
	
//unread
	t=0;
	for(i=0;i<j;i++)
	{
		if(Messagesavetop[Messagetoprank[i]].read==1)
		{
			t++;	
		}
	}
	Unread=t;	
//rankmode
	Messageinfo.rankmode=0;
	Ranktime();
/*	
	t=0;
	for(i=0;i<j;i++)
	{
		t=Messagesavetop[Messagetoprank[i]].flashadd;
		if(t==11298)
			break;
	}

	for(i=0;i<j;i++)
	{
		ss[i]=Messagesavetop[Messagetoprank[i]].flashadd;
	}
	for(i=0;i<j-1;i++)
		for(t=0;t<j-i-1;t++)
		{
			if(ss[t]>ss[t+1])
			{
				temp=ss[t];
				ss[t]=ss[t+1];
				ss[t+1]=temp;
			}
				
		}
*/
}



//*********************************************************************/
/*功能；自动模式发射台信息的存储
入口参数：无
出口参数：无*/
/**********************************************************************/
void Eprom_AutoMode_Save(void);
void Eprom_AutoMode_Save(void)
{
	word address=RXSTATION_AUTO;
	unsigned char addh,addl,i,j;
	byte datah,datal;
	  
    for(i=0;i<3;i++)
    {
  
  		address=RXSTATION_AUTO+64*i;
		addh=address>>8;
		addl=address&0x00ff;
		
     	IICStart();
	    IICWrite_ONE_BYTE(0xA0);	//写控制字
	    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
	    IICWrite_ONE_BYTE(addl);

		for(j=0;j<26;j++)//写入数据
		{		
        	datah=Auto[i][j]>>8,datal=Auto[i][j]&0x00ff;
			IICWrite_ONE_BYTE(datah);	//先写入高字节，再写低字节
			IICWrite_ONE_BYTE(datal);       	
		}

		
		
		IICStop();
		
   	delay_ms(10);


    }
	
}


//*********************************************************************/
/*功能；自动模式发射台信息的读取
入口参数：无
出口参数：无*/
/**********************************************************************/
void Eprom_AutoMode_Read(void);
void Eprom_AutoMode_Read(void)
{
	word address=RXSTATION_AUTO;
	unsigned char addh=address>>8,addl=address&0x00ff,i,j,t,stop;
	byte datah,datal;
	  
    for(i=0;i<3;i++)
    {
  
  		address=RXSTATION_AUTO+64*i;
		addh=address>>8;
		addl=address&0x00ff;
		
     	IICStart();
	    IICWrite_ONE_BYTE(0xA0);	//写控制字
	    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
	    IICWrite_ONE_BYTE(addl);
    	IICStart();
		IICWrite_ONE_BYTE(0xA1); 	//读取所需数据	    
	    
		for(j=0;j<26;j++)
		{		
        	for(t=0;t<2;t++)
        	{
	           	Auto[i][j]|=(unsigned int)IICRead_ONE_BYTE();//先读的是高位
	       		InI2C_OutputACK(0x00);
	   	    	if(t!=1) Auto[i][j]=Auto[i][j]<<8;      		
        	}
		}
	
		stop=IICRead_ONE_BYTE();
	    InI2C_OutputACK(0x80);
	    
		IICStop();
		
    }
	
}
//zzy revised@2010-7-1
void Eprom_ManualMsgMode_Save(word address)
{
	
	unsigned char addh,addl,i,j;	 
 	if(address==RXSTATION_MANUAL)	//手动模式发射台配置写入
 	{
		for(i=0;i<3;i++)
	    {
	  
	  		address=RXSTATION_MANUAL+64*i;
			addh=address>>8;
			addl=address&0x00ff;
			
	     	IICStart();
		    IICWrite_ONE_BYTE(0xA0);	//写控制字
		    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
		    IICWrite_ONE_BYTE(addl);

			for(j=0;j<26;j++)//写入数据
			{		
	        	IICWrite_ONE_BYTE(Manual[i][j]);       	
			}
			if(i==2)
			{
				IICWrite_ONE_BYTE(manual_area);
			}
			IICStop();
     	delay_ms(10);


	    }

 	}
 	
 	else
 	{
		for(i=0;i<3;i++)
	    {
	  
	  		address=RX_MSGTYPE+64*i;
			addh=address>>8;
			addl=address&0x00ff;
			
	     	IICStart();
		    IICWrite_ONE_BYTE(0xA0);	//写控制字
		    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
		    IICWrite_ONE_BYTE(addl);

			for(j=0;j<26;j++)//写入数据
			{		
	        	IICWrite_ONE_BYTE(MSGTYPE[i][j]);       	
			}
			IICStop();
     	delay_ms(10);
	    }
 	}

//   	IICStop();
//	Delay_10_Milli_Seconds();
			
	
}

//zzy revised@2010-7-1
void Eprom_ManualMsgMode_Read(word address)
{
	
	unsigned char addh,addl,i,j,stop;		 
 	if(address==RXSTATION_MANUAL)	//手动模式发射台配置写入
 	{
		for(i=0;i<3;i++)
	    {
	  
	  		address=RXSTATION_MANUAL+64*i;
			addh=address>>8;
			addl=address&0x00ff;
			
	     	IICStart();
		    IICWrite_ONE_BYTE(0xA0);	//写控制字
		    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
		    IICWrite_ONE_BYTE(addl);
	    	IICStart();
			IICWrite_ONE_BYTE(0xA1); 	//读取所需数据	    
		    
			for(j=0;j<26;j++)
			{		
	        	Manual[i][j]=IICRead_ONE_BYTE();//先读的是高位 
			   	InI2C_OutputACK(0x00);
			}
			if(i==2)
			{
				manual_area=IICRead_ONE_BYTE();
				InI2C_OutputACK(0x00);
			}
			
			stop=IICRead_ONE_BYTE();
		    InI2C_OutputACK(0x80);
		    
			IICStop();
			
	    }
//	    Manual[0][14]=0;		
 	}
 	
 	else
 	{
		for(i=0;i<3;i++)
	    {
	  
	  		address=RX_MSGTYPE+64*i;
			addh=address>>8;
			addl=address&0x00ff;
			
	     	IICStart();
		    IICWrite_ONE_BYTE(0xA0);	//写控制字
		    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
		    IICWrite_ONE_BYTE(addl);
	    	IICStart();
			IICWrite_ONE_BYTE(0xA1); 	//读取所需数据	    
		    
			for(j=0;j<26;j++)
			{		
	        	MSGTYPE[i][j]=IICRead_ONE_BYTE();//先读的是高位 
			   	InI2C_OutputACK(0x00);
			}
			stop=IICRead_ONE_BYTE();
		    InI2C_OutputACK(0x80);
			IICStop();
			
	    }
 	} 	
}
//*********************************************************************/
/*功能；IEC输出模式配置读取
入口参数：word address，IEC输出模式在Eprom的存储地址
出口参数：char型，读取的IEC输出模式*/
char iec_mode_read(word address);
char iec_mode_read(word address)
{
	unsigned char addh,addl;
	char result;
	addh=address>>8;
	addl=address&0x00ff;
	
 	IICStart();
    IICWrite_ONE_BYTE(0xA0);	//写控制字
    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);
	IICStart();
	IICWrite_ONE_BYTE(0xA1); 	//读取所需数据
	result=IICRead_ONE_BYTE();
	InI2C_OutputACK(0x80);
	IICStop();
   	delay_ms(10);
	return result;
}
//*********************************************************************/
/*功能；蜂鸣器配置信息的存储
入口参数：无
出口参数：无*/
/**********************************************************************/
void Eprom_Buzzer_Save(void);
void Eprom_Buzzer_Save(void)
{
	word address=RX_BUZZER;
	unsigned char addh=address>>8,addl=address&0x00ff,i;

	  
    IICStart();
    IICWrite_ONE_BYTE(0xA0);	//写控制字
    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);	
	for(i=0;i<4;i++)			//蜂鸣选项设置参数
	{
		IICWrite_ONE_BYTE((byte)Buzzer[i]);
	}
	IICStop(); 	
   	delay_ms(10);
}

//*********************************************************************/
/*功能；自检日志的存储
入口参数：char类型，需存储自检日志数组的位置
出口参数：无*/
/**********************************************************************/
void Eprom_Diaglog_Save(char diaglogs);
void Eprom_Diaglog_Save(char diaglogs)
{
	word address=DIAGRESULT+(word)diaglogs*64;
	unsigned char addh=address>>8,addl=address&0x00ff,i;

	  
    IICStart();
    IICWrite_ONE_BYTE(0xA0);	//写控制字
    IICWrite_ONE_BYTE(addh);    //写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);	
	for(i=0;i<8;i++)			//自检结果
	{
		IICWrite_ONE_BYTE(Diaglog[diaglogs].diagresult[i]);
	}
	
	for(i=0;i<3;i++)			//日期参数
	{
		IICWrite_ONE_BYTE(Diaglog[diaglogs].date[i]);
	}	
	
	for(i=0;i<2;i++)			//时间参数
	{
		IICWrite_ONE_BYTE(Diaglog[diaglogs].time[i]);
	}
	IICStop(); 	
   	delay_ms(10);
}

//*********************************************************************/
/*功能；自检日志的读取
入口参数：Diagresulttype类型指针，需读取自检日志数组的位置
		  char类型，需存储自检日志数组的位置
出口参数：无*/
/**********************************************************************/
void Eprom_Diaglog_Read(Diagresulttype *temp,char diaglogs);
void Eprom_Diaglog_Read(Diagresulttype *temp,char diaglogs)
{
	word address=DIAGRESULT+(word)diaglogs*64;
	unsigned char addh=address>>8,addl=address&0x00ff,data,i;
	  
    IICStart();
    IICWrite_ONE_BYTE(0xA0);    //写控制字
    IICWrite_ONE_BYTE(addh);	//写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 	//读取所需数据
	for(i=0;i<8;i++)			//自检结果
	{
    	Diaglog[diaglogs].diagresult[i]=IICRead_ONE_BYTE();
   		InI2C_OutputACK(0x00);
	}
	
	for(i=0;i<3;i++)			//日期参数
	{			 
    	Diaglog[diaglogs].date[i]=IICRead_ONE_BYTE();
	   	InI2C_OutputACK(0x00);
	}	
	
	for(i=0;i<1;i++)			//时间参数
	{
    	Diaglog[diaglogs].time[i]=IICRead_ONE_BYTE();
	   	InI2C_OutputACK(0x00);
	}	
  Diaglog[diaglogs].time[1]=IICRead_ONE_BYTE();	 
	InI2C_OutputACK(0x80);	

	IICStop();
	
}
//*********************************************************************/
/*功能；Eprom芯片检测程序
入口参数：无
出口参数：char型，若返回1则Eprom出现故障，0则Eprom正常*/
/**********************************************************************/
char Eprom_Check(void);
char Eprom_Check(void)
{
	char datacheck[8]=
	{
		0x12,0x34,0x56,0x78,0x89,0xab,0xcd,0xef
	};
	char i,data[8],result=0;
	IICStart();
    IICWrite_ONE_BYTE(0xA0);      	//写控制字
    IICWrite_ONE_BYTE(0x77);       	//写测试数据起始存放位置
    IICWrite_ONE_BYTE(0x77);
    for(i=0;i<8;i++)
    IICWrite_ONE_BYTE(datacheck[i]);
    IICStop();
  	delay_ms(6);  
  	
    IICStart();
    IICWrite_ONE_BYTE(0xA0);      	//写控制字
    IICWrite_ONE_BYTE(0x77);      	//写测试数据起始存放位置
    IICWrite_ONE_BYTE(0x77);
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 
    for(i=0;i<7;i++)
    {
	    data[i]=IICRead_ONE_BYTE();  	
    	InI2C_OutputACK(0x00);
    }
	    data[7]=IICRead_ONE_BYTE();  	
    	InI2C_OutputACK(0x80);
    
    IICStop(); 
    
    for(i=0;i<8;i++)
    {
    	if(data[i]!=datacheck[i])  result=1;
    }
    
    return result;
    
}



/*************************************************************/
  /*功能；写一个消息头的程序
入口参数：position int型，所需存储信息在信息头文件数组的位置
出口参数：无
/*************************************************************/
void Save_A_Message_Eprom(sword position)
{   
  	u16 address;
  	address=position*MESSTYPELENGTH;
    IICWrite_ONE_MEHE(&Messagesavetop[position],address);
}



//*****************************************************************
	/*功能:锁定一条信息，完成需锁定信息lock位的修改以及信息在锁定
	       块的写入锁定一条消息后,需要改变存储的情况,输入该消息
	       ADD[600]中的地址锁定一条信息，需要修改该信息的地址，使
	       其指向flash中锁定区域锁定该信息的存储位置
 入口参数：position表示需锁定信息在Messagesavetop[]中的位置
		   num表示锁定信息在Messagelocktop[]中的位置			
//*****************************************************************/
void LockAMessageHeader(sword position)
{
    u16 address,inaddress;
    inaddress=position*MESSTYPELENGTH;	//获取需锁定信息的存储地址   
    address=inaddress+10;      			//当前消息的LOCK所在字节
  	Write_Char_Eprm(address,1);   	//写入琐定标记1

}


/*************************************************************/
  /*功能；解锁一条信息，修改其对应存储信息的lock位
入口参数：position int型，存储信息头文件所在数组的条数
出口参数：无
/*************************************************************/
void UnlockAMessageHeader(sword position)
{
    u16 address=0,inaddress=0;
    inaddress=position*MESSTYPELENGTH;	//获取需锁定信息的存储地址
    address=inaddress+10;       		//当前消息的LOCK所在字节
   	Write_Char_Eprm(address,0);  		//写入琐定标记0
}






//*************************************************/
/*功能；总信息结构体Messinfo的写入
入口参数：无
出口参数：无*/
/**************************************************/
void WriteMesinfo();
void WriteMesinfo()
{
	sword i,j;
	byte addh,addl,datah,datal,a[30];
	addh=MESSAGEINFO>>8;
	addl=MESSAGEINFO;
	IICStart();
    IICWrite_ONE_BYTE(0xa0);      		//写控制字
    IICWrite_ONE_BYTE(addh);           	//写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);    
    for(i=0;i<2;i++)					//nownumber[2]数组参数写入，int型，高前低后			
    {
    	datah=Messageinfo.nownumber[i]>>8;
    	datal=Messageinfo.nownumber[i];
        IICWrite_ONE_BYTE(datah);           
    	IICWrite_ONE_BYTE(datal);	
    }
    
    for(i=0;i<4;i++)					//savenumber[4]数组参数写入，int型，高前低后
    {
    	datah=Messageinfo.savenumber[i]>>8;
    	datal=Messageinfo.savenumber[i];
        IICWrite_ONE_BYTE(datah);           
    	IICWrite_ONE_BYTE(datal);	
    }    
    
     for(i=0;i<4;i++)					//locknumber[4]数组参数写入，int型，高前低后
    {
    	datah=Messageinfo.locknumber[i]>>8;
    	datal=Messageinfo.locknumber[i];
        IICWrite_ONE_BYTE(datah);           
    	IICWrite_ONE_BYTE(datal); 	
    }   


   	
    IICWrite_ONE_BYTE(Messageinfo.rankmode);
    IICStop();
    
   	delay_ms(10);  
		
}


/*************************************************************/
  /*功能；把当前TOD模块中的天，小时，分钟保存
入口参数：无
出口参数：无
/*************************************************************/
void SaveTime();
void SaveTime()
{
// 	word yea,mon,day,hr,min;
// 	TODCS|=TODCS_TOD_LOCK_MASK;		//开启TOD_Lock位，读取TOD模块中时间的寄存器
// 	day=TODDAY;
// 	hr=TODHR;
// 	min=TODMIN;
//	TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位 
	timestruct=GetTime();     //@wu

	if(timestruct.day!=0||timestruct.hour!=0||timestruct.minute!=0)
	{
	 	Write_Int_Eprm(YEAR,timestruct.year);
	  Write_Int_Eprm(MONTH,timestruct.month);
	 	Write_Int_Eprm(DAY,timestruct.day);
	 	Write_Int_Eprm(HOUR,timestruct.hour);
	 	Write_Int_Eprm(MINUTE,timestruct.minute);	
	}

	

}

/*************************************************************/
  /*功能；读取之前保存在Eprom中的时间
入口参数：无
出口参数：无
/*************************************************************/
void ReadTime();
void ReadTime()
{
  sword i;
// 	u16 day;
	iyear=Read_Int_Eprm(YEAR);
	imonth=Read_Int_Eprm(MONTH);
 	iday=Read_Int_Eprm(DAY);			//读取时间--天数
 	ihour=Read_Int_Eprm(HOUR);		//读取时间--小时
 	iminute=Read_Int_Eprm(MINUTE);	//读取时间--分钟
//	DaysToDates(day,&iday,&imonth,&iyear);
	if((iyear>40)||(iyear<14)||(imonth>12)||(imonth<1)||(iday>31)||(iday<1)||(ihour>23)||(ihour<0)||(iminute>59)||(iminute<0))
	{
		iyear=14;
		imonth=8;
		iday=8;
		ihour=0;
		iminute=0;
	}
 	for(i=0;i<Messageinfo.savenumber[0];i++)
 	{
 		if((iyear<Messagesavetop[Messagetoprank[i]].date[0])
 		  ||((iyear==Messagesavetop[Messagetoprank[i]].date[0])&&(imonth<Messagesavetop[Messagetoprank[i]].date[1]))
 		  ||((iyear==Messagesavetop[Messagetoprank[i]].date[0])&&(imonth==Messagesavetop[Messagetoprank[i]].date[1])&&(iday<Messagesavetop[Messagetoprank[i]].date[2]))
 		  ||((iyear==Messagesavetop[Messagetoprank[i]].date[0])&&(imonth==Messagesavetop[Messagetoprank[i]].date[1])&&(iday==Messagesavetop[Messagetoprank[i]].date[2])
 		    &&(ihour<Messagesavetop[Messagetoprank[i]].time[0]))
 		  ||((iyear==Messagesavetop[Messagetoprank[i]].date[0])&&(imonth==Messagesavetop[Messagetoprank[i]].date[1])&&(iday==Messagesavetop[Messagetoprank[i]].date[2])
 		    &&(ihour==Messagesavetop[Messagetoprank[i]].time[0])&&(iminute<Messagesavetop[Messagetoprank[i]].time[1])))
 		  
 		{
 			iyear=Messagesavetop[Messagetoprank[i]].date[0];
 			imonth=Messagesavetop[Messagetoprank[i]].date[1];
 			iday=Messagesavetop[Messagetoprank[i]].date[2];
 			ihour=Messagesavetop[Messagetoprank[i]].time[0];
 			iminute=Messagesavetop[Messagetoprank[i]].time[1];					 			 			 			 			 			
 		}		
 	}

}

//*********************************************************************/
/*功能；正常加载接收机配置信息
入口参数：无
出口参数：
/**********************************************************************/
void Intial_Normal_Receiver();
void Intial_Normal_Receiver()
{
	unsigned char i,j,addh,addl,t;
	u16 address=DIAGLOGS; 
	addh=address>>8;
	addl=address&0x00ff;
	IICStart();
    IICWrite_ONE_BYTE(0xA0);    //写控制字
    IICWrite_ONE_BYTE(addh);	//写当前消息头存放的位置
    IICWrite_ONE_BYTE(addl);
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 	//读取所需数据

    
/*************自检日志参数的读取*******************/
	
	Diaglogn=IICRead_ONE_BYTE();//自检日志的数量
   	InI2C_OutputACK(0x00);
	Diaglogs=IICRead_ONE_BYTE();//当前可写自检日志指向数组
   	InI2C_OutputACK(0x00);	
	
/*************蜂鸣器参数的读取*******************/

	for(i=0;i<4;i++)			//蜂鸣选项设置参数
	{
		Buzzer[i]=IICRead_ONE_BYTE();
   		InI2C_OutputACK(0x00);	
	}

/*************打印格式配置参数的读取*******************/
	
	for(i=0;i<5;i++)	//依次读取误码显示，数据输出模式，数据格式模式，波特率模式,打印方向
	{
		Receiverset[i]=IICRead_ONE_BYTE();
	   	InI2C_OutputACK(0x00);
	}
	
/*************接收机模式配置参数的读取*******************/
	Mode=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);
/*************接收机工作频率配置参数的读取*******************/
	Workfre=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);	
/*************接收机本地时间配置参数的读取*******************/

	number=IICRead_ONE_BYTE(); 		//初始化时差调整量
   	InI2C_OutputACK(0x00);	

	sign=IICRead_ONE_BYTE();		//初始化时差
   	InI2C_OutputACK(0x00);
   	
	lcontrol=IICRead_ONE_BYTE();	//初始化本地时间
   	InI2C_OutputACK(0x00);	
/*************接收机语言配置参数的读取*******************/

	LANGUAGE=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);	
/*************接收机未读信息数的读取*******************/
    
 	Unread=(word)IICRead_ONE_BYTE()<<8;	//先读取高8位，再读取低8位
   	InI2C_OutputACK(0x00); 
   	
 	Unread|=(word)IICRead_ONE_BYTE();
    InI2C_OutputACK(0x00);
    
/*************接收机对比度配置参数的读取*******************/

	Contrast=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);    
    
/*************接收机语言配置参数的读取*******************/

	Operated=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x00);   
   	
/*************接收机背光配置参数的读取*******************/

	Backlight=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x80);      
    
    	
	IICStop();


/*************Diaglog[]的读取*******************/
	j=(Diaglogs-Diaglogn+10)%10;
	for(i=0;i<Diaglogn;i++)
	{
		t=(i+j)%10;
		Eprom_Diaglog_Read(&Diaglog[t],t);		
	}
	
/*************自动模式发射台配置参数的读取*******************/
	Eprom_AutoMode_Read();

/*************手动模式发射台配置参数的读取*******************/
	Eprom_ManualMsgMode_Read(RXSTATION_MANUAL);

/*************接收信息类别配置参数的读取*******************/
	Eprom_ManualMsgMode_Read(RX_MSGTYPE);
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			
			Autotemp[i][j]=Auto[i][j]; 			//自动配置参数，0表示接收
			Manualtemp[i][j]=Manual[i][j];		//手动配置参数，0表示接收
			MSGTYPETEMP[i][j]=MSGTYPE[i][j];		//信息类别配置参数，0表示接收
		}
		
	}
	MSGTYPE[0][14]=0;
	manual_area_temp=manual_area;
	flag_auto_iec=iec_mode_read(IEC_MODE);
	TransBacklight();
	TransContrast();
	ReadTime();
}

/**********eeprom中数据读取，测试用************@吴贤为*/

/*id readalleeprom();
void readalleeprom()
{
	unsigned int i;
	IICStart();
    IICWrite_ONE_BYTE(0xA0);    //写控制字
    IICWrite_ONE_BYTE(0x00);	//写当前消息头存放的位置
    IICWrite_ONE_BYTE(0x00);
    IICStart();
	IICWrite_ONE_BYTE(0xA1); 	//读取所需数据
	for(i=0;i<32768;i++)
	{
	    eepromdata[i]=IICRead_ONE_BYTE();
	    InI2C_OutputACK(0x00);
	}
	eepromdata[i]=IICRead_ONE_BYTE();
   	InI2C_OutputACK(0x80);
	IICStop();   	
}

void cleareeprom();
void cleareeprom()
{
	unsigned int i,j,add=0;
	byte addh,addl,data=0x00;
	for(i=0;i<512;i++)
	{
	     addh=add>>8;
	     addl=add&0x00ff;
	     IICStart();	
	     IICWrite_ONE_BYTE(0xA0);       	
         IICWrite_ONE_BYTE(addh);       		
         IICWrite_ONE_BYTE(addl);
	     for(j=0;j<64;j++)
	     {
             IICWrite_ONE_BYTE(data);
	     }
	     IICStop();	
	     add=add+0x0040;
	   	Delay_10_Milli_Seconds();  
	}
}           */
