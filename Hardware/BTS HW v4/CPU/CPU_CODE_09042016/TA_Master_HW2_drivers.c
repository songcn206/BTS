#include <stdio.h>
#include <math.h>
#include "GPIO_STM32F10x.h"
#include "TA_Master_HW2_drivers.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
//extern volatile uint16_t ADC_values[2];
//const float hesoK[5]={0,26908.9,27028.5,129800.5,140537.1};
//const float Vdrop[5]={0,1.25,1.20,1.25,1.25};
//Aux Relay Board
//#define AUX_RL1(state) GPIO_PinWrite(GPIOC, 12, state)
//#define AUX_RL2(state) GPIO_PinWrite(GPIOC, 11, state)
//#define AUX_RL3(state) GPIO_PinWrite(GPIOC, 10, state)
//#define AUX_RL4(state) GPIO_PinWrite(GPIOA, 12, state)
//#define AUX_RL5(state) GPIO_PinWrite(GPIOA, 8, state)
//#define AUX_RL6(state) GPIO_PinWrite(GPIOC, 9, state)
//#define AUX_RL7(state) GPIO_PinWrite(GPIOC, 8, state)


#define         KEY4X4_COL1          GPIO_PinRead(GPIOB,1)    
#define         KEY4X4_COL2          GPIO_PinRead(GPIOB,0)    
#define         KEY4X4_COL3          GPIO_PinRead(GPIOC,5)    
#define         KEY4X4_COL4          GPIO_PinRead(GPIOC,4)    
#define         KEY4X4_ROW1_UP         GPIO_PinWrite(GPIOB,14,1)//   
#define         KEY4X4_ROW2_UP         GPIO_PinWrite(GPIOB,13,1)//   
#define         KEY4X4_ROW3_UP         GPIO_PinWrite(GPIOB,12,1)//   
#define         KEY4X4_ROW4_UP         GPIO_PinWrite(GPIOB,2,1)//
#define         KEY4X4_ROW1_DOWN         GPIO_PinWrite(GPIOB,14,0)//   
#define         KEY4X4_ROW2_DOWN         GPIO_PinWrite(GPIOB,13,0)//   
#define         KEY4X4_ROW3_DOWN         GPIO_PinWrite(GPIOB,12,0)//   
#define         KEY4X4_ROW4_DOWN         GPIO_PinWrite(GPIOB,2,0)//
const uint8_t  KEY_4X4[4][4]={'D','C','B','A',
								 '#','9','6','3',
								 '0','8','5','2',
								 '*','7','4','1'};	


void TIM_Config(void)
{
  //GPIO_InitTypeDef GPIO_InitStructure;
	//TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  
  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);


  
	
/* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  TIM_DeInit(TIM2);
	
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period=35999;
	TIM_TimeBaseStructure.TIM_Prescaler=1; 
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure); 
	

	
/* TIM enable counter */
  TIM_Cmd(TIM2, ENABLE);
  /* Enable the CC Interrupt Request */
  //TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4, ENABLE);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}

void KeyPad4x4_Init(void)
{
  // Keypad
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
}

uint8_t  KEY4X4_IsPush(void)
{
    if((KEY4X4_COL1==0)||(KEY4X4_COL2==0)||(KEY4X4_COL3==0)||(KEY4X4_COL4==0))
       return 1;
    else 
       return 0;
}
 /*******************************************************************************
Noi Dung    :   Keo hang thu i xuong muc logic 0, de kiem tra co nut duoc an tai 
                hang thu i hay khong.
Tham Bien   :   i: vi tri hang can kiem tra.
Tra Ve      :   Khong.
********************************************************************************/
void KEY4X4_CheckRow(uint8_t i)
{
KEY4X4_ROW1_UP;
KEY4X4_ROW2_UP;
KEY4X4_ROW3_UP;
KEY4X4_ROW4_UP;
	
if(i==0)
 KEY4X4_ROW1_DOWN;
else if(i==1)
 KEY4X4_ROW2_DOWN;
else if(i==2)
 KEY4X4_ROW3_DOWN;
else
 KEY4X4_ROW4_DOWN;
}
 /*******************************************************************************
Noi Dung    :   Lay gia tri nut nhan duoc an.
Tham Bien   :   Khong.
Tra Ve      :   0:     Neu khong co nut duoc an.
				khac 0: Gia tri cua nut an.
********************************************************************************/
uint8_t  KEY4X4_GetKey(void)
{
	uint8_t  i;
	
 KEY4X4_ROW1_DOWN;
 KEY4X4_ROW2_DOWN;
 KEY4X4_ROW3_DOWN;
 KEY4X4_ROW4_DOWN;

	if(KEY4X4_IsPush())
	{		
			for(i=0;i<4;i++)
			{				
				KEY4X4_CheckRow(i);
				if(!KEY4X4_COL1) return KEY_4X4[i][0];
				if(!KEY4X4_COL2) return KEY_4X4[i][1];
				if(!KEY4X4_COL3) return KEY_4X4[i][2];
				if(!KEY4X4_COL4) return KEY_4X4[i][3];
			}

	}
	return 0;
}

/*******************************************************************************
* Function Name  : 
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
static void delay_ms(uint16_t nms)    
{ 
	uint16_t i,j; 
	for( i = 0; i < nms; i++ )
	{ 
		for( j = 0; j < 1141; j++ );
	}
} 

static void delay_us(__IO uint32_t num)
{
	__IO uint32_t index = 0;
	
	/* Default system clock is 72MHz */
	for(index = (6 * num); index != 0; index--);
}

void USER_I2C_Init(void)
{
	uint16_t timeOut = 0xffff;
	I2C_InitTypeDef I2CInit;
// Init I2C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//SCL of I2C2
	GPIO_PinConfigure(GPIOB, 10,
                      GPIO_AF_OPENDRAIN, 
                      GPIO_MODE_OUT50MHZ);
	//SDA of I2C2
	GPIO_PinConfigure(GPIOB, 11,
                      GPIO_AF_OPENDRAIN, 
                      GPIO_MODE_OUT50MHZ);
	//I2C_InitTypeDef I2CInit;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE); // Enable I2C2 clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	I2C_DeInit(I2C2); // I2C reset to initial state
	I2CInit.I2C_Mode = I2C_Mode_I2C; // I2C mode is I2C ^_^
	I2CInit.I2C_DutyCycle = I2C_DutyCycle_2; // I2C fast mode duty cycle (WTF is this?)
	I2CInit.I2C_OwnAddress1 = 0; // This device address (7-bit or 10-bit)
	I2CInit.I2C_Ack = I2C_Ack_Enable; // Acknowledgement enable
	I2CInit.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // choose 7-bit address for acknowledgement
	I2CInit.I2C_ClockSpeed = 100000; // 400kHz ?
	I2C_Cmd(I2C2,ENABLE); // Enable I2C
	I2C_Init(I2C2,&I2CInit); // Configure I2C
	while (I2C_GetFlagStatus(I2C2,I2C_FLAG_BUSY)) // Wait until I2C free
	{
		if(timeOut-- == 0) break;//{printf("I2C ERR\r\n");break;}
	}
}


/*EEPROM_W_Regs*/
/** 
  * @Author Tuan - 12/12/2015
  * @brief  EEPROM_W_Regs
  * @param  EEPROM_W_Regs
  * @retval True if OK, False if something was wrong
  */
uint8_t EEPROM_W_Regs(uint16_t addr,uint16_t length,uint8_t* pdata)
{
	uint16_t timeOut = 0xffff;
	uint32_t temp;
	uint16_t i;
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_SB) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
	/* Gui address slave de ghi */
	I2C_SendData(I2C2, EEPROM_ADDRESS_WRITE);
	timeOut = 0xffff;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_ADDR) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
		/* clear addr flag */
	temp = I2C2->SR2;
	I2C_SendData(I2C2, addr>>8);//8 bit dau
		/* clear addr flag */
	temp = I2C2->SR2;
	//while ((I2C2->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C2, addr&0xff);//8 bit sau
	for(i=0;i<length;i++){
	temp = I2C2->SR2;
	while ((I2C2->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C2, *(pdata+i));
	}
	
	temp = I2C2->SR2;
	temp++;
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2C2->SR1 & 0x00004) != 0x000004);
	/* Gui Stop condition */
	I2C_GenerateSTOP(I2C2, ENABLE);
	return 1;
}
/*EEPROM_ReadReg*/
/** 
  * @Author Tuan - 12/12/2015 
  * @brief  EEPROM_ReadReg
  * @param  None
  * @retval None
  */
uint8_t EEPROM_ReadReg(uint16_t addReg)
{
	__IO uint16_t timeOut = 0xffff;
	uint32_t temp=0;
	uint8_t tempValue;
	/* Gui Start condition */
	I2C_GenerateSTART(I2C2, ENABLE);
	/* cho time out */
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_SB) == RESET)
	{
		if(timeOut-- == 0)
			return 0;
	}
	/* Gui address slave de ghi */
	I2C_SendData(I2C2, EEPROM_ADDRESS_WRITE);
	timeOut = 0xffff;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_ADDR) == RESET)
	{
		if(timeOut-- == 0)
			return 0;
	}
		/* clear addr flag */
	temp = I2C2->SR2;
	
	I2C_SendData(I2C2, addReg>>8);
	/* clear addr flag */
	temp = I2C2->SR2;
	while ((I2C2->SR1 & 0x00004) != 0x000004);
	temp++;
	I2C_SendData(I2C2, addReg&0xff);
	temp = I2C2->SR2;
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2C2->SR1 & 0x00004) != 0x000004);
	
	/* Gui Stop condition */
	I2C_GenerateSTOP(I2C2, ENABLE);
	
	/* Gui Start condition */
		I2C_GenerateSTART(I2C2, ENABLE);
		/* cho time out */
		while(I2C_GetFlagStatus(I2C2, I2C_FLAG_SB) == RESET)
		{
		if(timeOut-- == 0)
			return 0;
		}
		/* Gui address slave de doc */
		//I2C_Send7bitAddress(I2C2,EEPROM_ADDRESS_READ,I2C_Direction_Receiver);
		I2C_SendData(I2C2, EEPROM_ADDRESS_READ);
		timeOut = 0xffff;
		while(I2C_GetFlagStatus(I2C2, I2C_FLAG_ADDR) == RESET)
		{
			if(timeOut-- == 0)
				return 0;
		}
		/* clear ack */
		I2C_AcknowledgeConfig(I2C2, DISABLE);
		/* clear addr flag */
		temp = I2C2->SR2;
		/* stop */
		I2C_GenerateSTOP(I2C2, ENABLE);
		/* Cho den khi co du lieu den (RXNE = 1) EV7 */
		while (I2C_GetFlagStatus(I2C2, I2C_FLAG_RXNE) == RESET);
		tempValue = I2C_ReceiveData(I2C2);
		while ((I2C2->CR1&0x200) == 0x200);		
		/* Enable ACK cho luot nhan tiep theo */
		I2C_AcknowledgeConfig(I2C2, DISABLE);
		return tempValue;
}
/*EEPROM_WriteReg*/
/** 
  * @Author Tuan - 12/12/2015 
  * @brief  EEPROM_WriteReg
  * @param  None
  * @retval None
  */
uint8_t EEPROM_WriteReg(uint16_t addr, uint8_t Data)
{
	__IO uint16_t timeOut = 0xffff;
	uint32_t temp;
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_SB) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
	/* Gui address slave de ghi */
	//I2C_Send7bitAddress(I2C2,EEPROM_ADDRESS_WRITE,I2C_Direction_Transmitter); // Send EEPROM_addr slave address
	I2C_SendData(I2C2, EEPROM_ADDRESS_WRITE);
	timeOut = 0xffff;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_ADDR) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
		/* clear addr flag */
	temp = I2C2->SR2;
	
	I2C_SendData(I2C2, addr>>8);//8 bit dau
		/* clear addr flag */
	temp = I2C2->SR2;
	//while ((I2C2->SR1 & 0x00004) != 0x000004);
	
	I2C_SendData(I2C2, addr&0xff);//8 bit sau
	temp = I2C2->SR2;
	while ((I2C2->SR1 & 0x00004) != 0x000004);
	
	I2C_SendData(I2C2, Data);
	temp = I2C2->SR2;
	temp++;
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2C2->SR1 & 0x00004) != 0x000004);
	/* Gui Stop condition */
	I2C_GenerateSTOP(I2C2, ENABLE);
	return 1;
}

void EEPROM_init(void)//AT24C32
{
	__IO uint16_t timeOut = 0xffff;
	// Check connection to EEPROM
	I2C_GenerateSTART(I2C2,ENABLE); // Send START condition
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT))// Wait for EV5
	{
		if(timeOut-- == 0) break;//{printf("I2C ERR1 ");break;}
	}
	I2C_Send7bitAddress(I2C2,EEPROM_addr,I2C_Direction_Transmitter); // Send EEPROM_addr slave address
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) // Wait for EV6
	{
		if(timeOut-- == 0) break;//{printf("EEPROM not respond ");break;}
	}
	I2C_GenerateSTOP(I2C2,ENABLE);
}
/* @brief: Giai ma so BCD thanh so thap phan
 * @input: data de giai nen
 * @output: gia tri thap phan
 */
uint8_t BCD2DEC(uint8_t dat)
{
	uint8_t low;
	uint8_t high;
	low = dat & 0x0F;
	high = (dat >> 4)*10;
	return high+low;
}
/* @brief: Giai ma so thap phan thanh so BCD
 * @input: data de giai nen o dang so thap phan
 * @output: gia tri BCD
 */
uint8_t DEC2BCD(uint8_t dat)
{
	uint8_t low;
	uint8_t high;
	low = dat%10;
	high =(dat/10)<<4;
	return high+low;
}

/*DS3231_ReadReg*/
/** 
  * @Author Tuan - 19/10/2014 
  * @brief  DS3231_ReadReg
  * @param  None
  * @retval None
  */
uint8_t DS3231_ReadReg(uint8_t addReg)
{
	uint16_t timeOut = 0xffff;
	uint32_t temp=0;
	uint8_t tempValue;
	/* Gui Start condition */
	I2C_GenerateSTART(I2C_DS3231, ENABLE);
	/* cho time out */
	while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_SB) == RESET)
	{
		if(timeOut-- == 0)
			return 0;
	}
	/* Gui address slave de ghi */
	I2C_SendData(I2C_DS3231, DS3231_ADDRESS_WRITE);
	timeOut = 0xffff;
	while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_ADDR) == RESET)
	{
		if(timeOut-- == 0)
			return 0;
	}
		/* clear addr flag */
	temp = I2C_DS3231->SR2;
	temp++;
	I2C_SendData(I2C_DS3231, addReg);
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	/* Gui Stop condition */
	I2C_GenerateSTOP(I2C_DS3231, ENABLE);
	
	/* Gui Start condition */
		I2C_GenerateSTART(I2C_DS3231, ENABLE);
		/* cho time out */
		while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_SB) == RESET)
		{
		if(timeOut-- == 0)
			return 0;
		}
		/* Gui address slave de doc */
		I2C_SendData(I2C_DS3231, DS3231_ADDRESS_READ);
		timeOut = 0xffff;
		while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_ADDR) == RESET)
		{
			if(timeOut-- == 0)
				return 0;
		}
		/* clear ack */
		I2C_AcknowledgeConfig(I2C_DS3231, DISABLE);
		/* clear addr flag */
		temp = I2C_DS3231->SR2;
		/* stop */
		I2C_GenerateSTOP(I2C_DS3231, ENABLE);
		/* Cho den khi co du lieu den (RXNE = 1) EV7 */
		while (I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_RXNE) == RESET);
		tempValue = I2C_ReceiveData(I2C_DS3231);
		while ((I2C_DS3231->CR1&0x200) == 0x200);		
		/* Enable ACK cho luot nhan tiep theo */
		I2C_AcknowledgeConfig(I2C_DS3231, DISABLE);
		return tempValue;
}

/*DS3231_WriteReg*/
/** 
  * @Author Tuan - 19/10/2014 
  * @brief  DS3231_WriteReg
  * @param  None
  * @retval None
  */
uint8_t DS3231_WriteReg(uint8_t addReg, uint8_t Data)
{
	uint16_t timeOut = 0xffff;
	uint32_t temp =0;
	temp = timeOut-timeOut;
	/* Gui Start condition */
	I2C_GenerateSTART(I2C_DS3231, ENABLE);
	/* cho time out */
	while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_SB) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
	/* Gui address slave de ghi */
	I2C_SendData(I2C_DS3231, DS3231_ADDRESS_WRITE);
	timeOut = 0xffff;
	while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_ADDR) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
		/* clear addr flag */
	temp = I2C_DS3231->SR2;
	I2C_SendData(I2C_DS3231, addReg);
		/* clear addr flag */
	temp = I2C_DS3231->SR2;
	temp++;
	I2C_SendData(I2C_DS3231, DEC2BCD(Data));
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	/* Gui Stop condition */
	I2C_GenerateSTOP(I2C_DS3231, ENABLE);
	return 1;
}

/*DS3231_Set_Time*/
/** 
  * @Author Tuan - 19/10/2014 
  * @brief  DS3231_Set_Time
  * @param  Set time for DS3231
  * @retval True if OK, False if something was wrong
  */
uint8_t DS3231_Set_Time(uint8_t sec,uint8_t min,uint8_t hr,uint8_t day,uint8_t date,uint8_t month, uint16_t year)
{
	uint16_t timeOut = 0xffff;
	uint32_t temp;
	
	I2C_GenerateSTART(I2C_DS3231, ENABLE);
	while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_SB) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
	/* Gui address slave de ghi */
	I2C_SendData(I2C_DS3231, DS3231_ADDRESS_WRITE);
	timeOut = 0xffff;
	while(I2C_GetFlagStatus(I2C_DS3231, I2C_FLAG_ADDR) == RESET)
	{
		if(timeOut-- == 0)
		return 0;
	}
		/* clear addr flag */
	temp = I2C_DS3231->SR2;
	I2C_SendData(I2C_DS3231, 0x00);
		/* clear addr flag */
	temp = I2C_DS3231->SR2;
	I2C_SendData(I2C_DS3231, DEC2BCD(sec));
	temp = I2C_DS3231->SR2;
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C_DS3231, DEC2BCD(min));
	temp = I2C_DS3231->SR2;
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C_DS3231, DEC2BCD(hr));
	temp = I2C_DS3231->SR2;
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C_DS3231, DEC2BCD(day));
	temp = I2C_DS3231->SR2;
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C_DS3231, DEC2BCD(date));
	temp = I2C_DS3231->SR2;
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C_DS3231, DEC2BCD(month));
	temp = I2C_DS3231->SR2;
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	I2C_SendData(I2C_DS3231, DEC2BCD(year));
	temp = I2C_DS3231->SR2;
	temp++;
	/* EV8_2: Wait until BTF is set before programming the STOP */
	while ((I2C_DS3231->SR1 & 0x00004) != 0x000004);
	/* Gui Stop condition */
	I2C_GenerateSTOP(I2C_DS3231, ENABLE);
	return 1;
}


void DS3231_init(void)
{
	uint16_t timeOut = 0xffff;
	// Check connection to DS3231
	I2C_GenerateSTART(I2C2,ENABLE); // Send START condition
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT))// Wait for EV5
	{
		if(timeOut-- == 0) {printf("I2C ERR");break;}
	}
	I2C_Send7bitAddress(I2C2,DS3231_addr,I2C_Direction_Transmitter); // Send DS3231 slave address
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) // Wait for EV6
	{
		if(timeOut-- == 0) {printf("DS3231 ERR");break;}
	}
	I2C_GenerateSTOP(I2C2,ENABLE);
	
	// Wait for 250ms for DS3231 startup
	//Delay(300);

	// DS3231 init
	I2C_GenerateSTART(I2C2,ENABLE);
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT))// Wait for EV5
		{
		if(timeOut-- == 0) {printf("I2C ERR");break;}
		}
	I2C_Send7bitAddress(I2C2,DS3231_addr,I2C_Direction_Transmitter); // Send DS3231 slave address
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))// Wait for EV6
		{
		if(timeOut-- == 0) {printf("I2C ERR");break;}
		}
	I2C_SendData(I2C2,DS3231_control); // Send DS3231 control register address
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)) // Wait for EV8
		{
		if(timeOut-- == 0) {printf("I2C ERR");break;}
		}
	I2C_SendData(I2C2,0x00); // DS3231 EOSC enabled, INTCN enabled, SQW set to 1Hz
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)) // Wait for EV8
		{
		if(timeOut-- == 0) {printf("I2C ERR");break;}
		}
	I2C_SendData(I2C2,0x00); // DS3231 clear alarm flags
	while (!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED))// Wait for EV8
		{
		if(timeOut-- == 0) {printf("I2C ERR");break;}
		}
	I2C_GenerateSTOP(I2C2,ENABLE);

}



void GLCD_CONST_RTCSEN (void)
{
	glcd_write_com(0x80);
	glcd_put_string("Thu x, xx/xx/xx ");
	glcd_write_com(0x90);
	glcd_put_string("    xx:xx       ");
	glcd_write_com(0x88);
	glcd_put_string("I xx.xoC xx.x%RH");
	glcd_write_com(0x98);
	glcd_put_string("O xx.xoC xx.x%RH");

}

void GLCD_CONST_Volt (void)
{
	glcd_write_com(0x80);
	glcd_put_string("DC:xx.xV I:xx.xA");
	glcd_write_com(0x90);
	glcd_put_string("P:xxxxW  i=xx.xA");
	glcd_write_com(0x88);
	glcd_put_string("AC: xxxV I:xx.xA");
	glcd_write_com(0x98);
	glcd_put_string("P:xxxxW pc=0.xx ");

}

void GLCD_CONST_Actor (void)
{
	glcd_write_com(0x80);
	glcd_put_string("F1  xx  F2  xx  ");
	glcd_write_com(0x90);
	glcd_put_string("F3  xx  F4  xx  ");
	glcd_write_com(0x88);
	glcd_put_string("A1  xx  A2  xx  ");
	glcd_write_com(0x98);
	glcd_put_string("                ");

}

void GLCD_CONST_Dry (void)
{
	glcd_write_com(0x80);
	glcd_put_string("D1  x   D2  x   ");
	glcd_write_com(0x90);
	glcd_put_string("D3  x   D4  x   ");
	glcd_write_com(0x88);
	glcd_put_string("D5  x   D6  x   ");
	glcd_write_com(0x98);
	glcd_put_string("D7  x   D8  x   ");
}

void GLCD_CONST_DATA_4 (void)
{
	glcd_write_com(0x80);
	glcd_put_string("Gate  OK        ");
	glcd_write_com(0x90);
	glcd_put_string("Smoke OK        ");
	glcd_write_com(0x88);
	glcd_put_string("Water OK        ");
	glcd_write_com(0x98);
	glcd_put_string("Fire  OK        ");

}

void GLCD_CONST_DATA_3 (void)
{
	glcd_write_com(0x80);
	glcd_put_string("Thu a, dd/mm/yy ");
	glcd_write_com(0x90);
	glcd_put_string("    hr:mm       ");
	glcd_write_com(0x88);
	glcd_put_string("AC IN:  xxxV    ");
	glcd_write_com(0x98);
	glcd_put_string("DC IN:  yy.yV   ");

}

void GLCD_CONST_DATA_2 (void)
{
	glcd_write_com(0x80);
	glcd_put_string("F1 OFF  F2 OFF  ");
	glcd_write_com(0x90);
	glcd_put_string("F3 OFF  F4 OFF  ");
	glcd_write_com(0x88);
	glcd_put_string("AiR1 OFF        ");
	glcd_write_com(0x98);
	glcd_put_string("AiR2 OFF        ");
}


void GLCD_CONST_DATA (void)
{
	glcd_write_com(0x80);
	glcd_put_string("Do am:    60.5% ");
	glcd_write_com(0x90);
	glcd_put_string("Nhiet do: 25.5oC");
	glcd_write_com(0x88);
	glcd_put_string("RL: No Data     ");
	glcd_write_com(0x98);
	glcd_put_string("BT: No Data     ");
}
void	GLCD_GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//GLCD IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//TRD_RS485//Chua su dung
	GPIO_PinConfigure(GPIOA, 11,
										GPIO_OUT_PUSH_PULL,
										GPIO_MODE_OUT50MHZ);
	//Gate Dry => Cam bien water dang noi voi PC0, phan cung sai het
	GPIO_PinConfigure(GPIOC, 0,
										GPIO_IN_FLOATING,
										GPIO_MODE_INPUT);
	//Smoke Dry => Cam bien water dang noi voi PC1, phan cung sai het
	GPIO_PinConfigure(GPIOC, 1,
										GPIO_IN_FLOATING,
										GPIO_MODE_INPUT);
	//Smoke Power
	GPIO_PinConfigure(GPIOC, 10,
										GPIO_OUT_PUSH_PULL,
										GPIO_MODE_OUT50MHZ);
	//Water => Cam bien water dang noi voi PC2, phan cung sai het
	GPIO_PinConfigure(GPIOC, 2,
										GPIO_IN_FLOATING,
										GPIO_MODE_INPUT);
	//PIR Dry => Cam bien water dang noi voi PC3, phan cung chua noi
	GPIO_PinConfigure(GPIOC, 3,
										GPIO_IN_FLOATING,
										GPIO_MODE_INPUT);
	//RS485_TxD
	GPIO_PinConfigure(GPIOA, 8,
										GPIO_OUT_PUSH_PULL,
										GPIO_MODE_OUT50MHZ);
	
}


void glcd_delay(uint8_t time)
{
	uint32_t i=0;
	for(i=0;i<120*time;i++);
}
void glcd_sendbyte(uint8_t zdata)
{
	unsigned int i;
	GLCD_RS(1);
	for(i=0; i<8; i++)
	{
		if((zdata << i) & 0x80)
		{
			GLCD_RW(1);
		}
		else 
		{
			GLCD_RW(0);
		}
		GLCD_EN(1);
		GLCD_EN(0);
	}
	delay_us(80);
}
void glcd_write_com(uint8_t cmdcode)
{
	GLCD_RS(1);
	glcd_sendbyte(0xf8);
	glcd_sendbyte(cmdcode & 0xf0);
	glcd_sendbyte((cmdcode << 4) & 0xf0);
	glcd_delay(80);
	//GLCD_RS(0);	
}
void glcd_write_data(uint8_t Dispdata)
{
	GLCD_RS(1);
	glcd_sendbyte(0xfa);
	glcd_sendbyte(Dispdata & 0xf0);
	glcd_sendbyte((Dispdata << 4) & 0xf0);
	delay_us(80);
}

void glcd_write_cmd(uint8_t cmd)
{
		uint8_t i;
		uint8_t temp;
	
	GLCD_RS(1);//CS
	GLCD_RW(1);//SID
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_RW(0);//SID
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	GLCD_EN(1);//SCLK
	GLCD_EN(0);//SCLK
	
		
	temp=cmd&0xf0;
	for(i=0; i<8; i++)
	{
		if((temp << i) & 0x80)
		{
			GLCD_RW(1);
		}
		else 
		{
			GLCD_RW(0);
		}
		GLCD_EN(1);
		GLCD_EN(0);
	}
	temp=(cmd << 4) & 0xf0;
		for(i=0; i<8; i++)
	{
		if((temp << i) & 0x80)
		{
			GLCD_RW(1);
		}
		else 
		{
			GLCD_RW(0);
		}
		GLCD_EN(1);
		GLCD_EN(0);
	}
	delay_us(80);
	GLCD_RS(0);
}
void GLCD_INIT_(void)
{
	GLCD_RS(1);
	delay_us(150);
	glcd_write_cmd(0x30);//Function Set
	delay_us(100);
	glcd_write_cmd(0x0d);//Display Control
	delay_us(100);
}
void glcd_init(void)
{
	GLCD_RS(0);
	delay_us(150);
	GLCD_RS(1);
	delay_us(150);
	glcd_write_com(0xf8);//sync
	glcd_write_com(0x30);
	delay_us(100);
	glcd_write_com(0xc);
	delay_us(50);
	//GLCD_RS(0);
}

void GLCD_Clear(void)
{
	glcd_write_cmd(1);
	delay_ms(2);
	glcd_write_com(0x8f);
}

void glcd_put_string(char *s)
{
	while(*s > 0)
	{ 
		glcd_write_data(*s);
		s++;
		delay_us(5);
	}
}
void glcd_test(void)
{
	glcd_write_cmd(0x03);//Return Home
	delay_us(80);    
	//glcd_write_com(0x80);//Set DDRAM Address--Address of first character of line 1
	glcd_put_string("0123456789ABCDEF");
	glcd_write_cmd(0x90);//Address of first character of line 2
	glcd_put_string("LCD TEST!    ^^ ");
	glcd_write_cmd(0x88);//Address of first character of line 3
	glcd_put_string("qwertyuiopasdfgh");
	glcd_write_cmd(0x98);////Address of first character of line 4
	glcd_put_string("BTS SYSTEM      ");
}

//----------------------------------------------------------------------------------------
void calc_sth1x(float *p_humidity ,float *p_temperature)
//----------------------------------------------------------------------------------------
// calculates temperature [�C] and humidity [%RH] 
// input :  humi [Ticks] (12 bit) 
//          temp [Ticks] (14 bit)
// output:  humi [%RH]
//          temp [�C]
{ const float C1=-2.0468;           // for 12 Bit RH
  const float C2=+0.0367;           // for 12 Bit RH
  const float C3=-0.0000015955;     // for 12 Bit RH
  const float T1=+0.01;             // for 12 Bit RH
  const float T2=+0.00008;          // for 12 Bit RH	

  float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit 
  float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit
  float rh_lin;                     // rh_lin:  Humidity linear
  float rh_true;                    // rh_true: Temperature compensated humidity
  float t_C;                        // t_C   :  Temperature [�C]

  t_C=t*0.01 - 39.7;                //calc. temperature [�C] from 14 bit temp. ticks @ 3V3
  rh_lin=C3*rh*rh + C2*rh + C1;     //calc. humidity from ticks to [%RH]
  rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   //calc. temperature compensated humidity [%RH]
  if(rh_true>100)rh_true=100;       //cut if the value is outside of
  if(rh_true<0.1)rh_true=0.1;       //the physical possible range

  *p_temperature=t_C;               //return temperature [�C]
  *p_humidity=rh_true;              //return humidity[%RH]
}

//--------------------------------------------------------------------
float calc_dewpoint(float h,float t)
//--------------------------------------------------------------------
// calculates dew point
// input:   humidity [%RH], temperature [�C]
// output:  dew point [�C]
{ float k,dew_point ;
  
  k = (log10(h)-2)/0.4343 + (17.62*t)/(243.12+t);
  dew_point = 243.12*k/(17.62-k);
  return dew_point;
}

/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention       : None
*******************************************************************************/
static void SDA_H(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* PC.7 ( DATA out ) */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   GPIO_SetBits(GPIOC , GPIO_Pin_7);

}


/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention       : None
*******************************************************************************/
static void SDA_L(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* PC.7 ( DATA out ) */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   GPIO_ResetBits(GPIOC , GPIO_Pin_7);
}


/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention       : None
*******************************************************************************/
unsigned char SDA_read(void)
{
   unsigned int j;
   GPIO_InitTypeDef GPIO_InitStructure_I;

   /* PC.6 ( DATA in ) */
   GPIO_InitStructure_I.GPIO_Pin = GPIO_Pin_7;
   GPIO_InitStructure_I.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure_I.GPIO_Mode = GPIO_Mode_IPU; 
   GPIO_Init(GPIOC, &GPIO_InitStructure_I);

   GPIO_ResetBits(GPIOC , GPIO_Pin_7);
	


   j = GPIO_ReadInputDataBit(GPIOC , GPIO_Pin_7);

   return j;
}

//----------------------------------------------------------------------------------
char s_write_byte(unsigned char value)
//----------------------------------------------------------------------------------
// writes a byte on the Sensibus and checks the acknowledge 
{ 
  unsigned char i,error=0;  
  for (i=0x80;i>0;i/=2)             //shift bit for masking
  { if(i&value){ SDA_H();}          //masking value with i , write to SENSI-BUS
    else{ SDA_L(); }                        
    delay_us(1); //__nop();                        //observe setup time
    SCK_H;                          //clk for SENSI-BUS
    delay_us(5); //__nop();__nop();__nop();        //pulswith approx. 5 us  	
    SCK_L;
    delay_us(1); //__nop();                         //observe hold time
  }
  SDA_H();                          //release DATA-line
  delay_us(1); //__nop();                          //observe setup time
  SCK_H;                            //clk #9 for ack 
  error=SDA_read();                     //check ack (DATA will be pulled down by SHT11)
  SCK_L;        
  return error;                     //error=1 in case of no acknowledge
}

//----------------------------------------------------------------------------------
char s_read_byte(unsigned char ack)
//----------------------------------------------------------------------------------
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1" 
{ 
  unsigned char i,val=0;
  SDA_H();                           //release DATA-line
  for (i=0x80;i>0;i/=2)             //shift bit for masking
  { SCK_H;                          //clk for SENSI-BUS
    if (SDA_read()) val=(val | i);        //read bit  
    SCK_L;  					 
  }
  if(ack == 1) {SDA_L();}                       //in case of "ack==1" pull down DATA-Line
	else {SDA_H(); }
  delay_us(1);                          //observe setup time
  SCK_H;                            //clk #9 for ack
	delay_us(5); 
  //__nop();__nop();__nop();          //pulswith approx. 5 us 
  SCK_L;
  delay_us(1); 
	//__nop();                          //observe hold time						    
  SDA_H();                           //release DATA-line
  return val;
}
//----------------------------------------------------------------------------------
void s_connectionreset(void)
//----------------------------------------------------------------------------------
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{  
  GPIO_InitTypeDef GPIO_InitStructure;
	unsigned char i; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	SDA_H(); SCK_L;                   //Initial state
  for(i=0;i<9;i++)                  //9 SCK cycles
  {      
		SCK_H;
    SCK_L; 
  }
  s_transstart();                   //transmission start
}
//----------------------------------------------------------------------------------
void s_transstart(void)
//----------------------------------------------------------------------------------
// generates a transmission start 
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{  
   SDA_H(); SCK_L;                   //Initial state
   delay_us(1); //__nop();
   SCK_H;
   delay_us(1); //__nop();
   SDA_L();
   delay_us(1); //__nop();
   SCK_L;  
   delay_us(5); //__nop();__nop();__nop();
   SCK_H;
   delay_us(1); //__nop();
   SDA_H();		   
   delay_us(1); //__nop();
   SCK_L;		   
}
//----------------------------------------------------------------------------------
char s_softreset(void)
//----------------------------------------------------------------------------------
// resets the sensor by a softreset 
{ 
  unsigned char error=0;  
  s_connectionreset();              //reset communication
  error+=s_write_byte(SHT1x_RESET);       //send RESET-command to sensor
  return error;                     //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_read_statusreg(unsigned char *p_value, unsigned char *p_checksum)
//----------------------------------------------------------------------------------
// reads the status register with checksum (8-bit)
{ 
  unsigned char error=0;
  s_transstart();                   //transmission start
  error=s_write_byte(SHT1x_STATUS_REG_R); //send command to sensor
  *p_value=s_read_byte(ACK);        //read status register (8-bit)
  *p_checksum=s_read_byte(noACK);   //read checksum (8-bit)  
  return error;                     //error=1 in case of no response form the sensor
}

//----------------------------------------------------------------------------------
char s_write_statusreg(unsigned char *p_value)
//----------------------------------------------------------------------------------
// writes the status register with checksum (8-bit)
{ 
  unsigned char error=0;
  s_transstart();                   //transmission start
  error+=s_write_byte(SHT1x_STATUS_REG_W);//send command to sensor
  error+=s_write_byte(*p_value);    //send value of status register
  return error;                     //error>=1 in case of no response form the sensor
}
 							   
//----------------------------------------------------------------------------------
char s_measure(uint16_t *p_value, unsigned char *p_checksum, unsigned char mode)
//----------------------------------------------------------------------------------
// makes a measurement (humidity/temperature) with checksum
{ 
	
	unsigned char error_data;
  unsigned char error=0,SDA_r;
	unsigned char msb,lsb;
  unsigned int i;

  s_transstart();                   //transmission start
  switch(mode){                     //send command to sensor
    case TEMP	: error+=s_write_byte(SHT1x_MEASURE_TEMP); break;
    case HUMI	: error+=s_write_byte(SHT1x_MEASURE_HUMI); break;
    default     : break;	 
  }
  for (i=0;i<65535;i++)   {
		__nop();
    SDA_r = SDA_read();
    if(SDA_r ==0)  {i=0;   break; } // wait until sensor has finished
  }	   //wait until sensor has finished the measurement
  if(SDA_r)    { error_data += 1; }              // or timeout (~2 sec.) is reached
	
	msb=s_read_byte(ACK); //read the first byte (MSB)
  lsb=s_read_byte(ACK); //read the second byte (LSB)
	*p_value=(msb<<8)|(lsb);
  //checksum=s_read_byte(noACK);                //read checksum (8-bit)
	
  //*(p_value)  =s_read_byte(ACK);    //read the first byte (MSB)
  //*(p_value+1)=s_read_byte(ACK);    //read the second byte (LSB)
  *p_checksum =s_read_byte(noACK);  //read checksum
  return error;
}

void USER_ADC_Init(void){
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC, ENABLE);
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	/* ADCx configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);	
	/* ADC1 Regular Channel 2 Configuration */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_55Cycles5);	
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE); 
	//enable DMA for ADC
	ADC_DMACmd(ADC1, ENABLE);  

	/* Enable Vrefint channel enable temperature sensor for ADC module */
	ADC_TempSensorVrefintCmd(ENABLE);

	/* Enable ADC1 reset calibaration register */   
	ADC_ResetCalibration(ADC1);

	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibaration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));  
	/* Start ADC1 Software Conversion */ 
	//ADC_SoftwareStartConvCmd(ADC1, ENABLE);

}

void DMAInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//create DMA structure
	DMA_InitTypeDef  DMA_InitStructure;
	//enable DMA1 clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//reset DMA1 channe1 to default values;
	DMA_DeInit(DMA1_Channel1);
	//channel will be used for memory to memory transfer
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	//setting normal mode (non circular)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	//medium priority
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	//source and destination data size word=32bit
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	//automatic memory destination increment enable.
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//source address increment disable
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//Location assigned to peripheral register will be source
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	//chunk of data to be transfered
	DMA_InitStructure.DMA_BufferSize = 2; // Bao nhieu kenh ADC??????????????????????????????
	//source and destination start addresses
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	//////////////////////////////////////////////////////////DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_values;
	//send values to DMA registers
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	// Enable DMA1 Channel Transfer Complete interrupt
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE); //Enable the DMA1 - Channel1
	


  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
  /* 2 bit for pre-emption priority, 2 bits for subpriority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
 	//Enable DMA1 channel IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

}

void USART1_Init(void)
{
	USART_InitTypeDef USARTx_Init;
	
	USARTx_Init.USART_WordLength = USART_WordLength_8b;
	USARTx_Init.USART_StopBits = USART_StopBits_1;
	USARTx_Init.USART_Parity = USART_Parity_No;
	USARTx_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTx_Init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USARTx_Init.USART_BaudRate = 115200;
	
	/* Enable UART clock, if using USART2 or USART3 ... we must use RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE) */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	GPIO_PortClock   (GPIOA, true);
	GPIO_PinWrite    (GPIOA, 9, 0);
	GPIO_PinConfigure(GPIOA, 9,
										GPIO_AF_PUSHPULL, 
										GPIO_MODE_OUT50MHZ);
	
	/* Configure PA9 for USART Tx as alternate function push-pull */
	GPIO_PinConfigure(GPIOA, 10,
										GPIO_IN_FLOATING,
										GPIO_MODE_INPUT);
	/* Configure PA10 for USART Rx as input floating */
	
	
	
		/* USART configuration */
	USART_Init(USART1, &USARTx_Init);
	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
}

void USART2_Init(void)
{
	USART_InitTypeDef USARTx_Init;
	
	USARTx_Init.USART_WordLength = USART_WordLength_8b;
	USARTx_Init.USART_StopBits = USART_StopBits_1;
	USARTx_Init.USART_Parity = USART_Parity_No;
	USARTx_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTx_Init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USARTx_Init.USART_BaudRate = 115200;
	
	/* Enable UART clock, if using USART2 or USART3 ... we must use RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE) */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	GPIO_PortClock   (GPIOA, true);
	GPIO_PinWrite    (GPIOA, 2, 0);
	GPIO_PinConfigure(GPIOA, 2,
										GPIO_AF_PUSHPULL, 
										GPIO_MODE_OUT50MHZ);
	
	/* Configure PA2 for USART Tx as alternate function push-pull */
	GPIO_PinConfigure(GPIOA, 3,
										GPIO_IN_FLOATING,
										GPIO_MODE_INPUT);
	/* Configure PA3 for USART Rx as input floating */
		/* USART configuration */
	USART_Init(USART2, &USARTx_Init);
	/* Enable USART */
	USART_Cmd(USART2, ENABLE);
}

void USART1_SendChar_(char ch) {
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); // wait for "Transmission Complete" flag cleared
	USART_SendData(USART1,ch);
}
void USART1_SendStr_(char *str,uint8_t length) {
	while (length--) USART1_SendChar_(*str++);
}

void USART2_SendChar_(char ch) {
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); // wait for "Transmission Complete" flag cleared
	USART_SendData(USART2,ch);
}

void USER_UART_NVIC(void)
{
  NVIC_InitTypeDef  NVIC_InitStructure;
  
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}	



