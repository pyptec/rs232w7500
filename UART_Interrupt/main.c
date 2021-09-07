/**
 ******************************************************************************
 * @file    UART/UART_Interrupt/main.c
 * @author  WIZnet
 * @brief   Main program body
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
#include "main.h"

/** @addtogroup W7500x_StdPeriph_Examples
 * @{
 */

/** @addtogroup UART_Interrupt
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t transfer_message[] = "Hello World~\0";
uint8_t RxBuffer_UART0[30];
uint8_t RxBuffer_UART1[30];
uint8_t RxBuffer_UART2[30];
uint32_t uart0_rx_cnt=0;
uint32_t uart1_rx_cnt=0;
uint32_t uart2_rx_cnt=0;
uint8_t buffer_ready_uart0;
uint8_t buffer_ready_uart1=0;
uint8_t buffer_ready_uart2=0;
extern uint32_t uart0_rx_cnt;
extern uint32_t uart1_rx_cnt;
extern uint32_t uart2_rx_cnt;
extern uint8_t transfer_count;
/* Private function prototypes -----------------------------------------------*/
static void UART_Config(void);
extern void UartPuts(UART_TypeDef* UARTx, uint8_t *str);
extern void S_UartPuts(uint8_t *str);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program.
 * @param  None
 * @retval None
 */
int main(void)
{
    SystemInit();

    UART_Config();

  // printf("W7500x Standard Peripheral Library version : %d.%d.%d\r\n", __W7500X_STDPERIPH_VERSION_MAIN, __W7500X_STDPERIPH_VERSION_SUB1, __W7500X_STDPERIPH_VERSION_SUB2);

 //   printf("SourceClock : %d\r\n", (int) GetSourceClock());
 //   printf("SystemClock : %d\r\n", (int) GetSystemClock());

 //   printf("System Loop Start\r\n");

    UART_SendData(UART0, transfer_message[0]);

    while (1) {
			
			if(buffer_ready_uart0== 1)
			{
				UartPuts(UART0,RxBuffer_UART0);
				uart0_rx_cnt=0;
				RxBuffer_UART0[0]=0;
				buffer_ready_uart0=0;
				transfer_count=0;
			}
			if (buffer_ready_uart1== 1)
			
			{
				UartPuts(UART1,RxBuffer_UART1);
				S_UartPuts(RxBuffer_UART1);
				uart1_rx_cnt=0;
				RxBuffer_UART1[0]=0;
				buffer_ready_uart1=0;
			}
				if (buffer_ready_uart2== 1)
			
			{
				S_UartPuts(RxBuffer_UART2);
				uart2_rx_cnt=0;
				RxBuffer_UART2[0]=0;
				buffer_ready_uart2=0;
			}

    }
	
	return 0;
		
}


/**
 * @brief  Configures the UART Peripheral.
 * @note
 * @param  None
 * @retval None
 */
static void UART_Config(void)
{
	/*definicion de estructuras*/
		//UART_InitTypeDef UART_InitStructure_uart0;
    UART_InitTypeDef UART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

	/*configura UART0*/
    UART_StructInit(&UART_InitStructure);
	  UART_Init(UART0, &UART_InitStructure);
	  UART_Cmd(UART0, ENABLE);
    UART_ITConfig(UART0, (UART_IT_TXIM | UART_IT_RXIM), ENABLE);
	/*configura interrupcion UART0*/
	  NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	/*configura UART1*/
	  UART_StructInit(&UART_InitStructure);
	  UART_Init(UART1, &UART_InitStructure);
	  UART_Cmd(UART1, ENABLE);
	  UART_ITConfig(UART1, (UART_IT_TXIM | UART_IT_RXIM), ENABLE);
		/*configura interrupcion UART1*/
	  NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	/*configura UART2*/
		S_UART_Init(115200);
    S_UART_Cmd(ENABLE);
		 /* Configure Uart2 Interrupt Enable*/
			
//		S_UART_ITConfig((S_UART_CTRL_FLAG_TXI|S_UART_CTRL_FLAG_RXI),ENABLE);
		 /* NVIC configuration */
//		NVIC_InitStructure.NVIC_IRQChannel = UART2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 //   NVIC_Init(&NVIC_InitStructure);
   
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/******************** (C) COPYRIGHT WIZnet *****END OF FILE********************/
