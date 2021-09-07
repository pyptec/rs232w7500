/**
 ******************************************************************************
 * @file    UART/UART_Interrupt/w7500x_it.c
 * @author  WIZnet
 * @brief   Main Interrupt Service Routines.
 *          This file provides template for all exceptions handler and
 *          peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2018 WIZnet</center></h2>
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "w7500x_it.h"

/** @addtogroup W7500x_StdPeriph_Examples
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t transfer_message[];
uint8_t transfer_count = 0;
extern uint32_t uart0_rx_cnt;
extern uint8_t RxBuffer_UART0[];
extern uint8_t buffer_ready_uart0;

extern uint32_t uart1_rx_cnt;
extern uint8_t RxBuffer_UART1[];
extern uint8_t buffer_ready_uart1;

extern uint32_t uart2_rx_cnt;
extern uint8_t RxBuffer_UART2[];
extern uint8_t buffer_ready_uart2;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles PendSV_Handler exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 W7500x Peripherals Interrupt Handlers                      */
/*    Add here the Interrupt Handler for the used peripherals                 */
/******************************************************************************/

/**
 * @brief  This function handles SSP0 Handler.
 * @param  None
 * @retval None
 */
void SSP0_Handler(void)
{
}

/**
 * @brief  This function handles SSP1 Handler.
 * @param  None
 * @retval None
 */
void SSP1_Handler(void)
{
}

/**
 * @brief  This function handles UART0 Handler.
 * @param  None
 * @retval None
 */
void UART0_Handler(void)
{
    if (UART_GetITStatus(UART0, UART_IT_TXIM) == SET) 
			{
        UART_ClearITPendingBit(UART0, UART_IT_TXIM);
    
			}
    if (UART_GetITStatus(UART0, UART_IT_RXIM) == SET) 
			{
        UART_ClearITPendingBit(UART0, UART_IT_RXIM);
				 RxBuffer_UART0[uart0_rx_cnt] = (UART_ReceiveData(UART0));
					if(RxBuffer_UART0[uart0_rx_cnt]==0x0a)
					{
						buffer_ready_uart0=1;
						RxBuffer_UART0[uart0_rx_cnt++] =0;
					}
					else
					{
					uart0_rx_cnt++;
					}
      
			}
}

/**
 * @brief  This function handles UART1 Handler.
 * @param  None
 * @retval None
 */
void UART1_Handler(void)
{
	 if (UART_GetITStatus(UART1, UART_IT_TXIM) == SET) 
			{
        UART_ClearITPendingBit(UART1, UART_IT_TXIM);
     
			}
    if (UART_GetITStatus(UART1, UART_IT_RXIM) == SET) 
			{
        UART_ClearITPendingBit(UART1, UART_IT_RXIM);
				 RxBuffer_UART1[uart1_rx_cnt] = (UART_ReceiveData(UART1));
					if(RxBuffer_UART1[uart1_rx_cnt]==0x0a)
					{
						buffer_ready_uart1=1;
						RxBuffer_UART1[uart1_rx_cnt++] =0;
					}
					else
					{
					uart1_rx_cnt++;
					}
       
			}
}

/**
 * @brief  This function handles UART2 Handler.
 * @param  None
 * @retval None
 */
void UART2_Handler(void)
{
	if (S_UART_GetITStatus(S_UART_IT_TXI) == SET) 
			{
        S_UART_ClearITPendingBit(S_UART_IT_TXI);
     
			}
	if (S_UART_GetITStatus(S_UART_IT_RXI) == SET) 
			{
        S_UART_ClearITPendingBit(S_UART_IT_RXI);
				RxBuffer_UART2[uart2_rx_cnt] = S_UART_ReceiveData();
					if(RxBuffer_UART2[uart2_rx_cnt]==0x0a)
					{
						buffer_ready_uart2=1;
						RxBuffer_UART2[uart2_rx_cnt++] =0;
					}
					else
					{
					uart2_rx_cnt++;
					}
       
			}
}

/**
 * @brief  This function handles PORT0 Handler.
 * @param  None
 * @retval None
 */
void PORT0_Handler(void)
{
}

/**
 * @brief  This function handles PORT1 Handler.
 * @param  None
 * @retval None
 */
void PORT1_Handler(void)
{
}

/**
 * @brief  This function handles PORT2 Handler.
 * @param  None
 * @retval None
 */
void PORT2_Handler(void)
{
}

/**
 * @brief  This function handles PORT3 Handler.
 * @param  None
 * @retval None
 */
void PORT3_Handler(void)
{
}

/**
 * @brief  This function handles DMA Handler.
 * @param  None
 * @retval None
 */
void DMA_Handler(void)
{
}

/**
 * @brief  This function handles DUALTIMER0 Handler.
 * @param  None
 * @retval None
 */
void DUALTIMER0_Handler(void)
{
}

/**
 * @brief  This function handles DUALTIMER1 Handler.
 * @param  None
 * @retval None
 */
void DUALTIMER1_Handler(void)
{
}

/**
 * @brief  This function handles PWM0 Handler.
 * @param  None
 * @retval None
 */
void PWM0_Handler(void)
{
}

/**
 * @brief  This function handles PWM1 Handler.
 * @param  None
 * @retval None
 */
void PWM1_Handler(void)
{
}

/**
 * @brief  This function handles PWM2 Handler.
 * @param  None
 * @retval None
 */
void PWM2_Handler(void)
{
}

/**
 * @brief  This function handles PWM3 Handler.
 * @param  None
 * @retval None
 */
void PWM3_Handler(void)
{
}

/**
 * @brief  This function handles PWM4 Handler.
 * @param  None
 * @retval None
 */
void PWM4_Handler(void)
{
}

/**
 * @brief  This function handles PWM5 Handler.
 * @param  None
 * @retval None
 */
void PWM5_Handler(void)
{
}

/**
 * @brief  This function handles PWM6 Handler.
 * @param  None
 * @retval None
 */
void PWM6_Handler(void)
{
}

/**
 * @brief  This function handles PWM7 Handler.
 * @param  None
 * @retval None
 */
void PWM7_Handler(void)
{
}

/**
 * @brief  This function handles RTC Handler.
 * @param  None
 * @retval None
 */
void RTC_Handler(void)
{
}

/**
 * @brief  This function handles ADC Handler.
 * @param  None
 * @retval None
 */
void ADC_Handler(void)
{
}

/**
 * @brief  This function handles WATOE Handler.
 * @param  None
 * @retval None
 */
void WZTOE_Handler(void)
{
}

/**
 * @brief  This function handles EXTI Handler.
 * @param  None
 * @retval None
 */
void EXTI_Handler(void)
{
}

/**
 * @}
 */

/******************** (C) COPYRIGHT WIZnet *****END OF FILE********************/
