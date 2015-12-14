#include "stm32f2xx.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_fsmc.h"

void FSMC_GPIO_Config(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE); 

	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_FSMC);     //NADV配置
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //@WU 100MHZ?
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 	
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
                                  |GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
		
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource3,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
		GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
	  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10
                                  |GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Init(GPIOE,&GPIO_InitStructure);

}

void FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure; 
    FSMC_NORSRAMTimingInitTypeDef  p; 
    p.FSMC_AddressSetupTime = 10;
    p.FSMC_AddressHoldTime = 10;    /*ADDHOLD 地址保持时间*/
    p.FSMC_DataSetupTime =10;   /*DATAST 数据建立时间*/
    p.FSMC_BusTurnAroundDuration= 5;   /*BUSTURN 总线返转时间*/
    p.FSMC_CLKDivision = 0;   /*CLKDIV 时钟分频*/
    p.FSMC_DataLatency = 1;     /*DATLAT 数据保持时间*/ 
    p.FSMC_AccessMode = FSMC_AccessMode_B;   /*访问模式*/  
	
    FSMC_NORSRAMInitStructure.FSMC_Bank =  FSMC_Bank1_NORSRAM1; 
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Enable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;   
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p; 

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}