#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "Eprom.h"
#include "printer.h"
#include "iec.h"
#include "code.h"
#include "MessageDeal.h"
#include "spi_flash.h"
#include "stm32f2xx_gpio.h"  
#include "stm32f2xx_spi.h"  
#include "stm32f2xx_rcc.h"  
#include "timedelay.h"

#define SECTOR_SIZE  	 0x1000		//2k字块大小的定义
#define BLOCK_SIZE   	 0x10000		//32k字块大小的定义
//#define SST_ID       	 0xBF    	/* SST Manufacturer‘s ID code   */
//#define SST_39VF1601 	 0x234b  	/* SST 39VF1601 device code    */
//#define System_base      0x200000 	//偏移的基地址

#define FlashmapSize_Word	 0x0400		//存储信息的块大小1K字
#define FlashmapSize_Byte	 0x0400		//存储信息的块大小1K字节

#define ReadRom(offset)   *((volatile u8 *)(0x8040000+(offset)))
//void Delay_150_Nano_Seconds();		//用于CFI,DI等待
//void Delay_10_Micro_Seconds();		//用于Programm_Word的时间等待
//void Delay_25_Milli_Seconds();		//用于Sector_erase,Block_erase擦除等待时间
//void Delay_50_Milli_Seconds();		//用于Chip_erase擦除等待时间

//*********************************/
/*功能；150ns的延迟
入口参数：无
出口参数：无
/**********************************/
/*void Delay_150_Nano_Seconds()		//120M的时钟，每条指令时间8.33ns.150ns需要18条指令
{

	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
	asm(nop);
}  */





//*********************************/
/*功能；FLASH芯片擦除函数
入口参数：无
出口参数：无
/**********************************/
/*void Erase_Entire_Chip();
void Erase_Entire_Chip()
{
	*sysAddress(0x5555) = 0x00AA;  	// write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  	// write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0080;  	// write data 0x0088 to device addr 0x5555
    *sysAddress(0x5555) = 0x00AA;
    *sysAddress(0x2AAA) = 0x0055;
    *sysAddress(0x5555) = 0x0010;
    Delay_50_Milli_Seconds();
}   */


//*****************************************/
/*功能；2k的块擦除
入口参数：SAX uint32类型 2k擦除块的起始地址
		  有效位为AMS-A11，2k的整数倍
出口参数：无
/******************************************/
void Erase_One_Sector(u32 SectorAddr)
{
  /*!< Send write enable instruction */
  sFLASH_WriteEnable();

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  /*!< Send Sector Erase instruction */
  sFLASH_SendByte(sFLASH_CMD_SE);
  /*!< Send SectorAddr high nibble address byte */
  sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /*!< Send SectorAddr medium nibble address byte */
  sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /*!< Send SectorAddr low nibble address byte */
  sFLASH_SendByte(SectorAddr & 0xFF);
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd();
	
  delay_ms(10);		//25ms的等待函数
}


//*****************************************/
/*功能；  32k的块擦除
入口参数：BAX uint32类型 32k擦除块的起始地址
		  有效位为BMS-A15，32k的整数倍
出口参数：无
/******************************************/
void Erase_One_Block(u32 SectorAddr)
{
  /*!< Send write enable instruction */
  sFLASH_WriteEnable();

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  /*!< Send Sector Erase instruction */
  sFLASH_SendByte(sFLASH_CMD_BE);
  /*!< Send SectorAddr high nibble address byte */
  sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /*!< Send SectorAddr medium nibble address byte */
  sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /*!< Send SectorAddr low nibble address byte */
  sFLASH_SendByte(SectorAddr & 0xFF);
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd();
	
	delay_ms(10);		//25ms的等待函数
}

void EraseChip(void)
{
  /*!< Send write enable instruction */
  sFLASH_WriteEnable();

  /*!< Bulk Erase */
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  /*!< Send Bulk Erase instruction  */
  sFLASH_SendByte(sFLASH_CMD_CE);
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd();
	
	delay_ms(10);		//25ms的等待函数
}

/**
  * @brief  Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
  * @note   The number of byte can't exceed the FLASH page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH, must be equal
  *         or less than "sFLASH_PAGESIZE" value.
  * @retval None
  */
void sFLASH_WritePage(char* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  /*!< Enable the write access to the FLASH */
  sFLASH_WriteEnable();

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();
  /*!< Send "Write to Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_WRITE);
  /*!< Send WriteAddr high nibble address byte to write to */
  sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /*!< Send WriteAddr medium nibble address byte to write to */
  sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /*!< Send WriteAddr low nibble address byte to write to */
  sFLASH_SendByte(WriteAddr & 0xFF);

  /*!< while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /*!< Send the current byte */
    sFLASH_SendByte(*pBuffer);
    /*!< Point on the next byte to be written */
    pBuffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd();
}

/**
  * @brief  Writes block of data to the FLASH. In this function, the number of
  *         WRITE cycles are reduced, using Page WRITE sequence.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH.
  * @retval None
  */
void sFLASH_WriteBuffer(char* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % sFLASH_SPI_PAGESIZE;
  count = sFLASH_SPI_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
  NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

  if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      while (NumOfPage--)
      {
        sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
      {
        temp = NumOfSingle - count;

        sFLASH_WritePage(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        sFLASH_WritePage(pBuffer, WriteAddr, temp);
      }
      else
      {
        sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
      NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

      sFLASH_WritePage(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      if (NumOfSingle != 0)
      {
        sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/**
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void sFLASH_ReadBuffer(char* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "Read from Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_READ);

  /*!< Send ReadAddr high nibble address byte to read from */
  sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte to read from */
  sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte to read from */
  sFLASH_SendByte(ReadAddr & 0xFF);

  while (NumByteToRead--) /*!< while there is data to be read */
  {
    /*!< Read a byte from the FLASH */
    *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    /*!< Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
}

/**
  * @brief  Reads FLASH identification.
  * @param  None
  * @retval FLASH identification
  */
uint32_t sFLASH_ReadID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "RDID " instruction */
  sFLASH_SendByte(0x9F);

  /*!< Read a byte from the FLASH */
  Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Read a byte from the FLASH */
  Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Read a byte from the FLASH */
  Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}


/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t sFLASH_SendByte(char byte)
{
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(sFLASH_SPI, byte);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(sFLASH_SPI);
}


/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void sFLASH_WriteEnable(void)
{
  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "Write Enable" instruction */
  sFLASH_SendByte(sFLASH_CMD_WREN);

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
}

/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
void sFLASH_WaitForWriteEnd(void)
{
  uint8_t flashstatus = 0;

  /*!< Select the FLASH: Chip Select low */
  sFLASH_CS_LOW();

  /*!< Send "Read Status Register" instruction */
  sFLASH_SendByte(sFLASH_CMD_RDSR);

  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  }
  while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Enable the SPI clock */
  sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, ENABLE);

  /*!< Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(sFLASH_SPI_SCK_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | 
                         sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_CS_GPIO_CLK, ENABLE);
  
  /*!< SPI pins configuration *************************************************/

  /*!< Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(sFLASH_SPI_SCK_GPIO_PORT, sFLASH_SPI_SCK_SOURCE, sFLASH_SPI_SCK_AF);
  GPIO_PinAFConfig(sFLASH_SPI_MISO_GPIO_PORT, sFLASH_SPI_MISO_SOURCE, sFLASH_SPI_MISO_AF);
  GPIO_PinAFConfig(sFLASH_SPI_MOSI_GPIO_PORT, sFLASH_SPI_MOSI_SOURCE, sFLASH_SPI_MOSI_AF);
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_SPI2);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
        
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN| sFLASH_SPI_MOSI_PIN|sFLASH_SPI_MISO_PIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /*!< Configure sFLASH Card CS pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

void sFLASH_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;

  sFLASH_LowLevel_Init();
    
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS_HIGH();

  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sFLASH_SPI, &SPI_InitStructure);

  /*!< Enable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, ENABLE);
}

//************************************************/
/*功能；  汉字字库点阵读取函数
入口参数：Isn word型:需读取汉字的机内码或者直接地址
		  neima char型:1Isn为机内码，0Isn为直接地址	 
出口参数：无
/*************************************************/
void Read_Chinese_Code(word Isn,char neima);
void Read_Chinese_Code(word Isn,char neima)
{
	byte a[2],i;
	word code;
	uint32 CAddress;
//	char* q;
//  char Rx_Buffer0[4];
	if(neima == 1) 	       	//输入的Isn为中文的机内码，由机内码转换得到直接地址
	{
		a[1] = (byte)(Isn & 0x00ff);    	//机内码的低位 
		a[0] = (byte)(Isn >>8 & 0x00ff);	//机内码的高位
		CAddress = ((a[0]-0xa1)*0x5e + (a[1]-0xa1))*(uint32)(0x20);
//		CAddress = CAddress / 2;
	}
	else CAddress = Isn;  //输入的直接是地址，表示数字，字符和符号，不需要转换
	if(CAddress>0x3FFE0)
	{
		CAddress=0;
	}
	for(i=0;i<16;i++)	      //把读取的点阵存入全局变量数组CGTAB[2][16]中
	{
//		q=Rx_Buffer0;
//		code =* sysAddress(CAddress+i+0xce400);
//    sFLASH_ReadBuffer(Rx_Buffer0,CAddress+i+0x19c800,2);
		CGTAB[0][i] =ReadRom(CAddress+2*i);
		CGTAB[1][i] =ReadRom(CAddress+2*i+1);
		
	}
}
//*********************************************************************/
  /*功能；FLASH芯片检测程序
入口参数：无
出口参数：char型，若返回1则FLASH出现故障，0则FALSH正常
/**********************************************************************/
char CFI_Query(void);
char CFI_Query(void)
{
  
/*  	int index,j=0;
  	char returnstate;
  	int cfiid[37]={0x51,0x52,0x59,0x01,0x07,0x00,0x00,0x00,
  	0x00,0x00,0x00,0x27,0x36,0x00,0x00,0x03,0x00,0x04,0x05,0x01,
  	0x00,0x01,0x01,0x15,0x01,0x00,0x00,0x00,0x02,0xff,0x01,0x10,
  	0x00,0x1f,0x00,0x00,0x01};		//正确的CFI序列
  	int a[37];
  	
  	*sysAddress(0x5555) = 0x00AA;  	// write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  	// write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x0098;  	// write data 0x0098 to device addr 0x5555
    asm(nop);
    asm(nop);
    asm(nop);
    asm(nop);  

    for (index = 0x0010; index <= 0x0034; index++)	//读取FLASH的CFI序列
    {
       a[j] = *sysAddress(index);
         j++;
    }

    *sysAddress(0x5555) = 0x00AA;  	// write data 0x00AA to device addr 0x5555
    *sysAddress(0x2AAA) = 0x0055;  	// write data 0x0055 to device addr 0x2AAA
    *sysAddress(0x5555) = 0x00F0;  	// write data 0x00F0 to device addr 0x5555
    asm(nop);
    asm(nop);
    asm(nop);
    asm(nop); 
    
    for(j=0;j<37;j++) 				//判断所读取的CFI序列是否正确   
    if(a[j]!=cfiid[j]) break;
    
    if(j==37) returnstate=0;		//0表示正确，FLASH正常
    else returnstate=1;				//1表示错误，FLASH出错   */
    
    return(0);
}

//*****************************************/
  /*功能；字库烧录程序
入口参数：无
出口参数：无
/******************************************/
/*void ZikuLoad(void);
void ZikuLoad(void)
{
	FILE *fp;							//定义文件指针
	int j=0,index;
	
	Erase_Entire_Chip();				//擦除整个芯片
	if((fp=fopen("hzk","rb"))==NULL)	
	printf("cannot open this file\n");	//文件打不开报错
	while(j<133801)						//字库烧录，FLASH起始地址0xce400
	{
		fread(&index,2,1,fp);
		Program_One_Word(index,j+0xce400);
		j++;		
	}	
}   */

//*********************************************************************/
/*功能；FLASH信息空间初始化
入口参数：无
出口参数：
/**********************************************************************/
void Reset_Flash();
void Reset_Flash()
{
    char i;
    for(i=0;i<19;i++)
    {
    	Erase_One_Block((uint32)0x10000*(uint32)i);	
      delay_ms(5);		
    }
	
}

//********************************************************/
  /*功能；flash空闲块的查找，同时修改状态块的状态包括Eprom
入口参数：messagepoint char*型，信息内容的头指针 
出口参数：无
/*********************************************************/
void FlashmapLook(sword savenum,char *messagepoint)
{
	word itemp,stemp,btemp,jtemp,mtemp,ltemp;//add code
	byte Flashmap_temp[300];//add code
	word mountbyte,mountword,i,l;	//存储信息的字节数和字数
	word startmap=0;		//起始的存储块，0~1199
	word blockmount,m,n=0;			
	word Flashmaptemp=0;					
	byte * message;
	byte t;
	message=(byte *)messagepoint;	
	mountbyte=(word)(*message);	//获取高8位
	mountbyte=mountbyte<<8;
	message++;					//指向下一个字符
	t=(word)(*message);
	mountbyte+=t;
	
	blockmount=mountbyte/(word)FlashmapSize_Byte+(mountbyte%(word)FlashmapSize_Byte?1:0);	//获取所需的块数
	for(i=0;i<300;i++)
	{
		for(m=0;m<4;m++)
		{
			Flashmaptemp=Flashmap[i]&(0x03<<(2*m));
			if(Flashmaptemp==0) n++;
			else n=0;
			if(n==blockmount) break;
		}
		
		if(n==blockmount) break;
	}
	while(m==4) //存储空间满处理
	{
        deleteoldmess();
       	for(i=0;i<300;i++)
    	{
	    	for(m=0;m<4;m++)
	    	{
		    	Flashmaptemp=Flashmap[i]&(0x03<<(2*m));
		    	if(Flashmaptemp==0) n++;
		    	else n=0;
		    	if(n==blockmount) break;
	    	}
			if(n==blockmount) break;
    	}
	}	
		startmap=i*4+m+1-n;
		//return startmap;
		Messagesavetop[savenum].flashadd=startmap;	//把起始块及所需块数存入头文件目录
		Messagesavetop[savenum].flashmount=(byte)blockmount;
		
		for(i=startmap;i<startmap+blockmount;i++)
		{
			m=i%4;		//所在字节的状态位位置
			l=i/4;		//所在字节
			Flashmap[l]|=0x03<<(2*m);	//对应使用状态位的位置置11
		}	
		m=blockmount/4;			//所需的块数
		l=startmap/4;	//所在字节
		for(i=l;i<m+3+l;i++)	//修改Eprom状态表的对应状态位
		{
			Write_Char_Eprm(FlashmapStart+i,Flashmap[i]);
		}			
}
/*************************************************************************/

//存储信息部分程序//
/*每条信息平均分配1024字节，即512字，600条信息所需占用的空间为
  512*600=307200=0x4b000,即300k字节，全局变量当前可写消息的地址COMFlashADD,
  当前可写锁定地址COMFlashLockADD
/************************************************************************/


/**********************************************************/
  /*功能；向存储块写入一条消息，在存储信息的时候若
          字节数刚好为偶数，则NULL位也存储，若字节数为奇数，
          则省略NULL位，在读取信息时再加上
入口参数：savenum int型，需存储信息在存储信息头文件数组位置
		  messagepoint char*型，信息内容的头指针  
出口参数：无
/**********************************************************/
void WriteAMessToFlash(sword savenum,char *messagepoint)
{
	word mountbyte,i;	//存储信息的字节数和字数
	word temp;					//从字节到字转换的临时变量
	uint32 comflashadd;			//当前信息的起始存储地址
	char *message;
	word t;
//	byte sucess=1;
//	word count_sucess=0;
	
//	while(sucess)
//	{
//		sucess=0;
//		count_sucess=0;
		message=(char *)messagepoint;
		FlashmapLook(savenum,messagepoint);
		mountbyte=(word)(*message);	//获取高8位
		mountbyte=mountbyte<<8;
		message++;					//指向下一个字符
		t=(word)(*message);
		mountbyte+=t;
		message=(char *)messagepoint;		//指针message重新指向头地址
//		mountword=mountbyte;		//偶字节完整存储，奇字节省略最后NULL位存储

		comflashadd=(uint32)FlashmapSize_Byte*(uint32)Messagesavetop[savenum].flashadd;  //若存储器满了，出错??
	  sFLASH_WriteBuffer(message,comflashadd,mountbyte);
	//	comflashadd=FlashmapSize_Word*Messagesavetop[savenum].flashadd+0x8000;	
/*		for(i=0;i<mountword;i++)	//信息内容存储
		{
			temp=(byte)(*message);	//获取高8位
			temp=temp<<8;
			message++;
			t=(byte)(*message);				//指向下一个字符 
			temp+=t;
			message++;
			Program_One_Word(temp, comflashadd);
			if(temp==*sysAddress(comflashadd++))
				count_sucess++;	
		}
		if(count_sucess!=mountword)
			sucess=1;	
	}    */
	for(i=0;i<mountbyte;i++)
	{
		*messagepoint++=NULL;	
	}
		
}
/***************************************************************/
  /*功能；从FLSAH读取一条消息(锁定块和存储块公用)，所有信息的读取
          都存放在以Block2为头指针的动态存储块中
入口参数：address uint32型，需读取消息在FLASH中的起始存储地址
出口参数：无
/***************************************************************/
void ReadMessFlash(uint32 address,char* dout);
void ReadMessFlash(uint32 address,char* dout)
{
	word mountbyte,mountword,temp,i;

//	address=address+0x8000;
	mountbyte=Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].amount;		//读取信息的字节数，包括正文，1个NULL位，2个字节总数存储位
//	mountword=mountbyte/2;						//从FLASH读取信息的正文
  sFLASH_ReadBuffer(dout,address,mountbyte);
/*	for(i=0;i<mountword;i++)
	{
		temp=*sysAddress(address++);
		*(dout++)=temp>>8;		
		*(dout++)=temp;				
	}
//	if(mountbyte%2) *dout=NULL;			//若信息数为奇字节，须在最后加上NULL位
	*dout=NULL;							//奇数字节的N自然要加，为了方便判断偶数字节的末尾多添加了一个NULL
										//方便信息在LCD显示的末尾判断				 */
}

//********************************************/
/*功能；完成三个英文字符到一个中文汉字的转换
入口参数：三个英文字符的首字母地址
出口参数：LCD机内码
/*********************************************/
unsigned int eng_to_lcd1(char *p);
unsigned int eng_to_lcd1(char *p)
{
	unsigned int lcd;
	unsigned int temp,temp1,temp2;
	temp=(*p-'A')*676+(*(p+1)-'A')*26+(*(p+2)-'A');	//计算总值
	temp1=temp/94+0xa1;								//计算区码+0xA0,temp/94为区码-1
	temp2=temp%94+0xa1;								//计算位码+0xA0,temp/94为位码-1
	lcd=(temp1<<8)+temp2;							//合成GB2312-1980机内码
	return lcd;
}
/***************************************************************/
  /*功能；从FLSAH读取一条消息(锁定块和存储块公用)，用作打印
入口参数：address uint32型，需读取消息在FLASH中的起始存储地址
出口参数：无
/***************************************************************/
void ReadPrtMsg();
void ReadPrtMsg()
{
	word mountbyte,mountword,temp,i;
	word mountbyte_lcd=1;
	char *l=PrtMsg;
	long address;
	PrtStart->nowprint=&PrtMsg[1];
//	PrtLink *p=PrtStart->next;
	address=(uint32)Messagesavetop[PrtStart->xulie].flashadd*(uint32)FlashmapSize_Byte;
	mountbyte=Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].amount;
  sFLASH_ReadBuffer(l,address,mountbyte);	
//	p->start=(char *)malloc(sizeof(mountbyte));	//指向新开辟内存空间首地址
//	l=p->start;
//	p->nowprint=p->start+2;			//前两位存的为总字节数
//	p->end=p->start+mountbyte-1;	//指向新开辟内存空间末地址
	
/*	mountword=mountbyte/2;
	for(i=0;i<mountword;i++)
	{
		temp=*sysAddress(address++);
		*(l++)=temp>>8;		
		*(l++)=temp;				
	}
	if(mountbyte%2) *l=NULL;			//若信息数为奇字节，须在最后加上NULL位  */
	PrtStart->end=&PrtMsg[mountbyte-1];
	if(Messagesavetop[PrtStart->xulie].frequency==2)
	{
		
		PrtStart->nowprint=&PrtMsgChn[0];
		for(i=2;i<8;i++)
			PrtMsgChn[mountbyte_lcd++]=PrtMsg[i];
		for(i=8;i<18;i++)
		{
			switch(PrtMsg[i])
			{
			
				case('0'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb0;
					break;
				}
				case('1'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb1;
					break;
				}
				case('2'):
				{
				    PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb2;
					break;
					
				}
				case('3'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb3;
					break;
				}
				case('4'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb4;
					break;
				}
				case('5'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb5;
					break;
				}
				case('6'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb6;
					break;
				}
				case('7'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb7;
					break;
				}
				case('8'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb8;
					break;
				}
				case('9'):
				{
					PrtMsgChn[mountbyte_lcd++]=0xa3;
					PrtMsgChn[mountbyte_lcd++]=0xb9;
					break;
				}
				default:break;
			}		
		}
		for(i=18;i<mountbyte-1;i++)
		{
		    if(PrtMsg[i]==0)continue;
		   	else if(PrtMsg[i]=='\r')
		   	{
		   			chinese[mountbyte_lcd++]='\r';
		   			continue;
		   	}
				
			else if(PrtMsg[i]=='\n')
			{
					chinese[mountbyte_lcd++]='\n';                       //\r,\n照常转化
					continue;
			}
			else
			{
				PrtMsgChn[mountbyte_lcd++]=eng_to_lcd1(&PrtMsg[i])>>8;
				PrtMsgChn[mountbyte_lcd++]=(char)eng_to_lcd1(&PrtMsg[i]);
				i=i+2;
				
			}
		}
		PrtStart->end=&PrtMsgChn[mountbyte_lcd-1];
	}
	BadurateSet(Receiverset[3]+1);		
		
}
/***************************************************************/
  /*功能；从FLSAH读取一条消息(锁定块和存储块公用)，用作IEC传送
入口参数：address uint32型，需读取消息在FLASH中的起始存储地址
出口参数：无
/***************************************************************/
void ReadIecMsg(void);
void ReadIecMsg()
{
	word mountbyte,mountword,temp,i;
	int length=0;
	char *l=PrtMsg;
	long address;
//	PrtStart->nowprint=&PrtMsg[1];
//	PrtLink *p=PrtStart->next;
	address=(uint32)Messagesavetop[PrtStart->xulie].flashadd*(uint32)FlashmapSize_Word;
	mountbyte=Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].amount;
//	p->start=(char *)malloc(sizeof(mountbyte));	//指向新开辟内存空间首地址
//	l=p->start;
//	p->nowprint=p->start+2;			//前两位存的为总字节数
//	p->end=p->start+mountbyte-1;	//指向新开辟内存空间末地址
  sFLASH_ReadBuffer(l,address,mountbyte);	
/*	mountword=mountbyte/2;
	for(i=0;i<mountword;i++)
	{
		temp=*sysAddress(address++);
		*(l++)=temp>>8;		
		*(l++)=temp;				
	}
	if(mountbyte%2) *l=NULL;			//若信息数为奇字节，须在最后加上NULL位    */
	length=iec_trans(&PrtMsg[2],mountbyte-2);
	PrtStart->nowprint=&bice[0][0]-1;
	PrtStart->end=&bice[0][0]+length-1;	
		
}
/**********************************************************/
  /*功能；删除一条消息，并进行块的处理
入口参数：savenum int型，需删除信息在信息头文件数组位置
出口参数：无
/**********************************************************/
void DelAMessFlash(sword savenum)
{

	sword flashadd,i,m,l;	
	char flashmount;
	char biaoji1[4]={0x02,0x08,0x20,0x80};	//块的高位状态置1
	char biaoji0[4]={0xfe,0xfb,0xef,0xbf};	//块的低位状态置0
	flashadd=Messagesavetop[savenum].flashadd;		//获取起始块的位置
	flashmount=Messagesavetop[savenum].flashmount;	//获取块的数量
	
	for(i=flashadd;i<flashadd+flashmount;i++)
	{
		m=i%4;		//所在字节的状态位位置
		l=i/4;		//所在字节
		Flashmap[l]|=biaoji1[m];	//对应使用状态位的高位置1
		Flashmap[l]&=biaoji0[m];	//对应使用状态位的低位置0
	}
	
	m=flashmount/4;	//所需的字节数
	l=flashadd/4;	//所在字节
	for(i=l;(i<m+3+l)&&(i<300);i++)	//修改Eprom状态表的对应状态位
	{
		if(((Flashmap[i]&0x03)!=0x03)&&((Flashmap[i]&0x0c)!=0x0c)&&((Flashmap[i]&0x30)!=0x30)&&((Flashmap[i]&0xc0)!=0xc0))	//2K字的状态为0xaa，说明可以收回此块(falsh的最小删除块2K字)
		{
			Erase_One_Sector((uint32)SECTOR_SIZE*(uint32)i);
			Flashmap[i]=0x00;	//状态位全部清零
		}
		Write_Char_Eprm(FlashmapStart+i,Flashmap[i]);	//Eprom的对应状态进行修改
	}

}
/*void readflash();
void readflash()
{
	word i,temp,j=0;
	for(i=0;i<20000;i++)
	{
    temp=*sysAddress(i);
    flashdata[j++]=temp>>8;
    flashdata[j++]=temp;
	}
}        */
