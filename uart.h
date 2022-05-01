/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define ACTIVE_UART            UART0
#define ACTIVE_UART_CLKSRC     UART0_CLK_SRC
#define ACTIVE_UART_CLK_FREQ   CLOCK_GetFreq(UART0_CLK_SRC)
#define ACTIVE_UART_IRQn       UART0_RX_TX_IRQn
#define ACTIVE_UART_IRQHandler UART0_RX_TX_IRQHandler
#define ACTIVE_UART_BAUDRATE   115200
#define BUFFER_SIZE 10

#define INVALID_DAC_VALUE "Error en valor de entrada \r\n"
#define REQUEST_DATA "Introducir voltaje de 0 a 3.3v expresado con 3 decimales \r\n"

void initUART(void);

void sendRequest(void);

uint8_t newDACvalueArrived(void);
float getMessage(void);
void clearBuffer(void);
float stof( uint8_t* s);

