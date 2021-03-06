#ifndef _BSP_TIM_H_
#define _BSP_TIM_H_

#include "stm32f10x.h"

/**************************************
 * stm32f103ve的板级支持包 TIM相关
 * 定时器相关初始化和操作
 * TIM3 TIM4 TIM5 TIM8
 * Channel(0~15)依次对应每个定时器的OC
 * 50Hz16路舵机控制
 * 2021/5   作者:庞碧璋
**************************************/

#define PWM_GPIO_PORT1  GPIOA
#define PWM_GPIO_Pin1   GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |\
                        GPIO_Pin_6 | GPIO_Pin_7

#define PWM_GPIO_PORT2  GPIOB
#define PWM_GPIO_Pin2   GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7 |\
                        GPIO_Pin_8 | GPIO_Pin_9

#define PWM_GPIO_PORT3  GPIOC
#define PWM_GPIO_Pin3   GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9

//对应pwm通道寄存器的值
static __IO uint16_t* Target_CCR[16] = {&TIM5->CCR1,&TIM5->CCR2,&TIM5->CCR3,&TIM5->CCR4,
                                    &TIM4->CCR4,&TIM4->CCR3,&TIM4->CCR2,&TIM4->CCR1,
                                    &TIM3->CCR1,&TIM3->CCR2,&TIM3->CCR3,&TIM3->CCR4,
                                    &TIM8->CCR1,&TIM8->CCR2,&TIM8->CCR3,&TIM8->CCR4};

static TIM_TypeDef* Target_TIM[4] = {TIM3,TIM4,TIM5,TIM8};

void PWM_Init(void);
void PWM_GPIO_Init(void);
void TIMBase_Init(void);
void TIMOC_Init(void);
void TIM_Enable(void);

void PWM_Out(uint8_t Channel,uint16_t CCR);
uint16_t*Read_PWM_Out(uint8_t Channel);

#endif
