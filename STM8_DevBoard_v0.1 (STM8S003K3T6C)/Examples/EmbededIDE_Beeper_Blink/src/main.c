/**************************************
 * 
 *       stm8s sdcc beep demo
 * 
 * MCU: STM8S003
 * FREQ: 16MHz
 * PIN: PD4 (BUZZER ON)
 * 
 **************************************
*/

#include "stm8s.h"
#include "stm8s_beep.h"


void DelayInit(void);
void DelayMs(uint16_t ms);

void main(void)
{
    // set system clock to 16Mhz
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    // init delay timer
    DelayInit();

    // Beeper Init
    BEEP_Init(BEEP_FREQUENCY_2KHZ);

    while (1)
    {
        BEEP_Cmd(DISABLE);
        DelayMs(500);
        BEEP_Cmd(ENABLE);
        DelayMs(500);
    }
}

void DelayInit(void)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
    TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249); // 1ms
    TIM4_SelectOnePulseMode(TIM4_OPMODE_SINGLE);
}

void DelayMs(uint16_t ms)
{
    while (ms--)
    {
        TIM4->SR1 = (uint8_t)(~TIM4_FLAG_UPDATE);
        TIM4->CR1 |= TIM4_CR1_CEN;
        while ((TIM4->SR1 & (uint8_t)TIM4_FLAG_UPDATE) == 0)
            ;
    }
}

/**
 * =========================================================
 *                     interrupt functions
 * =========================================================
*/

/**
  * @brief  TRAP interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    while (1)
    {
        nop();
    }
}

/**
  * @brief  this is a example for interrupt function define
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(_this_is_a_example, EXTI_PORTA_IRQn)
{
    // TODO
}
