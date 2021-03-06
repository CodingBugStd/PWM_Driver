#include "bsp_tim.h"
#include <stdio.h>

void PWM_Init(void)
{
    PWM_GPIO_Init();
    TIMBase_Init();
    TIMOC_Init();
    TIM_Enable();
}

void PWM_GPIO_Init(void)
{
    GPIO_InitTypeDef    GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStruct.GPIO_Pin = PWM_GPIO_Pin1;
    GPIO_Init(PWM_GPIO_PORT1,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = PWM_GPIO_Pin2;
    GPIO_Init(PWM_GPIO_PORT2,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = PWM_GPIO_Pin3;
    GPIO_Init(PWM_GPIO_PORT3,&GPIO_InitStruct);
}

void TIMBase_Init(void)
{
    TIM_TimeBaseInitTypeDef TIMBase_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

    TIMBase_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIMBase_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIMBase_InitStruct.TIM_Period = 20000 - 1;
    TIMBase_InitStruct.TIM_Prescaler = 72 -1 ;
    TIMBase_InitStruct.TIM_RepetitionCounter = 0;

    for(uint8_t temp=0;temp<4;temp++)
        TIM_TimeBaseInit(Target_TIM[temp],&TIMBase_InitStruct);
}

void TIMOC_Init(void)
{
    TIM_OCInitTypeDef   TIM_OCInitStruct;

    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCIdleState_Reset;      //互补通道空闲电平
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;         //互补通道有效电平
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;          //有效电平
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;   //不开启互补通道
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0;

    uint8_t temp = 0;
    for(temp=0;temp<4;temp++)
    {
        TIM_OC1Init(Target_TIM[temp],&TIM_OCInitStruct);
        TIM_OC2Init(Target_TIM[temp],&TIM_OCInitStruct);
        TIM_OC3Init(Target_TIM[temp],&TIM_OCInitStruct);
        TIM_OC4Init(Target_TIM[temp],&TIM_OCInitStruct);

        TIM_OC1PreloadConfig(Target_TIM[temp],TIM_OCPreload_Enable);
        TIM_OC2PreloadConfig(Target_TIM[temp],TIM_OCPreload_Enable);
        TIM_OC3PreloadConfig(Target_TIM[temp],TIM_OCPreload_Enable);
        TIM_OC4PreloadConfig(Target_TIM[temp],TIM_OCPreload_Enable);
    }
}

void TIM_Enable(void)
{
    uint8_t temp;
    TIM_CtrlPWMOutputs(TIM8,ENABLE);
    for(temp=0;temp<4;temp++)
        TIM_Cmd(Target_TIM[temp],ENABLE);
}

void PWM_Out(uint8_t Channel,uint16_t CCR)
{
    if(Channel<16)
        *Target_CCR[Channel] = CCR;
}

uint16_t*Read_PWM_Out(uint8_t Channel)
{
    if(Channel<16)
        return (uint16_t*)Target_CCR[Channel];
    return NULL;
}

