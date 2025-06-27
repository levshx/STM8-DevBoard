/**************************************
 * 
 *       stm8s sdcc beep demo
 * 
 * MCU: STM8S003
 * FREQ: 16MHz
 * 
 **************************************
*/

#include "stm8s.h"
#include "stm8s_uart1.h"

#define BAUDRATE 9600


void UART1_SendChar(char c) {
    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    UART1_SendData8(c);
}

void UART1_SendString(char *str) {
    while (*str) {
        UART1_SendChar(*str++);
    }
}

char UART1_ReceiveChar(void) {
    while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
    return UART1_ReceiveData8();
}

void main(void) {
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    UART1_DeInit();
    UART1_Init(BAUDRATE, 
               UART1_WORDLENGTH_8D, 
               UART1_STOPBITS_1, 
               UART1_PARITY_NO, 
               UART1_SYNCMODE_CLOCK_DISABLE, 
               UART1_MODE_TXRX_ENABLE);
    UART1_Cmd(ENABLE);
    
    UART1_SendString("STM8S UART1 Example\r\n");
    UART1_SendString("Echo mode: type something...\r\n");
    
    while (1) {
        char c = UART1_ReceiveChar();
        UART1_SendChar(c);
    }
}
