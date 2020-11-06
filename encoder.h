#ifndef _Encoder_H__
#define _Encoder_H__

#include "stm32f10x_gpio.h"
#include "usart.h"
#include "delay.h"

#define Encoder_GetCLK  PAin(7)		//��ȡʱ������
#define Encoder_GetDT   PAin(6)		//��ȡ�ź�����
#define Encoder_GetSW   PAin(5)		//��������������
#define Delta_Temp			0.5				//ÿ���¶���ֵ�ĸı�ֵ


extern float Goal_Temp,Actual_Temp;
extern uint8_t CLK_debounce,CLK_debounce_LAST,DT_debounce;

void Encoder_Init(void);
void Encoder_GPIO_Init(void);
void Encoder_CLK_EXTI_Init(void);
void Encoder_SW_EXTI_Init(void);
void Encoder_NVIC_Config(void);
void Encoder_Read_dir(void);

#endif

