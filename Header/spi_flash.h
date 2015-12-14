/**
  ******************************************************************************
  * @file    spi_flash.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   This file contains all the functions prototypes for the spi_flash
  *          firmware driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* M25P SPI Flash supported commands */  
#define sFLASH_CMD_WRITE          0x02  /* Write to Memory instruction */
#define sFLASH_CMD_WRSR           0x01  /* Write Status Register instruction */
#define sFLASH_CMD_WREN           0x06  /* Write enable instruction */
#define sFLASH_CMD_READ           0x03  /* Read from Memory instruction */
#define sFLASH_CMD_RDSR           0x05  /* Read Status Register instruction  */
#define sFLASH_CMD_RDID           0x9F  /* Read identification */
#define sFLASH_CMD_SE             0x20  /* Sector Erase instruction */
#define sFLASH_CMD_CE             0xC7  /* Chip Erase instruction */
#define sFLASH_CMD_BE             0xD8  /* Chip Erase instruction */

#define sFLASH_WIP_FLAG           0x01  /* Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE         0xA5
#define sFLASH_SPI_PAGESIZE       0x100

  
/* M25P FLASH SPI Interface pins  */  
#define sFLASH_SPI                           SPI2
#define sFLASH_SPI_CLK                       RCC_APB1Periph_SPI2
#define sFLASH_SPI_CLK_INIT                  RCC_APB1PeriphClockCmd

#define sFLASH_SPI_SCK_PIN                   GPIO_Pin_13
#define sFLASH_SPI_SCK_GPIO_PORT             GPIOB
#define sFLASH_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOB
#define sFLASH_SPI_SCK_SOURCE                GPIO_PinSource13
#define sFLASH_SPI_SCK_AF                    GPIO_AF_SPI2

#define sFLASH_SPI_MISO_PIN                  GPIO_Pin_14
#define sFLASH_SPI_MISO_GPIO_PORT            GPIOB
#define sFLASH_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define sFLASH_SPI_MISO_SOURCE               GPIO_PinSource14
#define sFLASH_SPI_MISO_AF                   GPIO_AF_SPI2

#define sFLASH_SPI_MOSI_PIN                  GPIO_Pin_15
#define sFLASH_SPI_MOSI_GPIO_PORT            GPIOB
#define sFLASH_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define sFLASH_SPI_MOSI_SOURCE               GPIO_PinSource15
#define sFLASH_SPI_MOSI_AF                   GPIO_AF_SPI2

#define sFLASH_CS_PIN                        GPIO_Pin_12
#define sFLASH_CS_GPIO_PORT                  GPIOB
#define sFLASH_CS_GPIO_CLK                   RCC_AHB1Periph_GPIOB

/* Exported macro ------------------------------------------------------------*/
/* Select sFLASH: Chip Select pin low */
#define sFLASH_CS_LOW()       GPIO_ResetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)
/* Deselect sFLASH: Chip Select pin high */
#define sFLASH_CS_HIGH()      GPIO_SetBits(sFLASH_CS_GPIO_PORT, sFLASH_CS_PIN)   

/* Exported functions ------------------------------------------------------- */

/* High layer functions  */
void sFLASH_Init(void);
void sFLASH_EraseSector(uint32_t SectorAddr);
void sFLASH_EraseBlock(uint32_t SectorAddr);
void sFLASH_EraseChip(void);
void sFLASH_WritePage(char* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_WriteBuffer(char* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void sFLASH_ReadBuffer(char* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t sFLASH_ReadID(void);
//void SystemInit(void);
/* Low layer functions */
uint8_t sFLASH_SendByte(char byte);
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord);
void sFLASH_WriteEnable(void);
void sFLASH_WaitForWriteEnd(void);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_FLASH_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
