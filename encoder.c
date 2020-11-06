#include "encoder.h"

void Encoder_Init(void)
{		
		Encoder_GPIO_Init();
		Encoder_CLK_EXTI_Init();
		Encoder_SW_EXTI_Init();
		Encoder_NVIC_Config();
}

void Encoder_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;		//����������
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��ʹ������IO PORTCʱ�� 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//ע��Ҫ�򿪸��ù���ʱ��
	
		//��ת���������Ŷ��壬PA7ΪCLK,PA6ΪDT
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;	 // �˿�����		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO 
		
		//��ת���������Ŷ��壬PA5���ڱ���������SW
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	 // �˿�����	����SW
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
}

void Encoder_CLK_EXTI_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;		//����������
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7); //ѡ��EXTI�ź�Դ
		EXTI_InitStructure.EXTI_Line = EXTI_Line7;               //�ж���ѡ��
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //˫���ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStructure);
}

void Encoder_SW_EXTI_Init(void)
{
		EXTI_InitTypeDef EXTI_InitStructure;		//����������
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5); //ѡ��EXTI�ź�Դ
		EXTI_InitStructure.EXTI_Line = EXTI_Line5;               //�ж���ѡ��
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;      //EXTIΪ�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  //�½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                //ʹ���ж�
    EXTI_Init(&EXTI_InitStructure);
}

void Encoder_NVIC_Config(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);           //����NVIC���ȼ�����Ϊ1

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;        //�ж�Դ��[9:5]��λ�ڡ�stm32f10x.h����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ���1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //�����ȼ���1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
}

void Encoder_Read_dir(void)
{
			char encoder_dir;
					
			encoder_dir = Encoder_GetCLK ^ Encoder_GetDT;		//ʹ����򣬼��ٸ�ֵ����
			if(encoder_dir && Goal_Temp < 30)								//������ֵ����Ϊ30���϶�
			{
					Goal_Temp += Delta_Temp;										//Goal_TempΪ���õ��¶���ֵ����
			}
			else if (!encoder_dir && Goal_Temp > -10)				//������ֵ����Ϊ-10���϶�
			{
					Goal_Temp -= Delta_Temp;
			}
				
}
	