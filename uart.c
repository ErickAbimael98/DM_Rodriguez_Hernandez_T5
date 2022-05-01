

#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_uart.h"
#include "uart.h"


static uint8_t volatile newMessage = 0;
static uint8_t volatile buffer[BUFFER_SIZE];
static float volatile messageValue=0;
static uint8_t volatile bufferPosition=0;




void initUART(void){
    uart_config_t config;

    BOARD_InitBootPins();
    BOARD_InitBootClocks();

    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = ACTIVE_UART_BAUDRATE;
    config.enableTx     = true;
    config.enableRx     = true;

    UART_Init(ACTIVE_UART, &config, ACTIVE_UART_CLK_FREQ);

    /* Enable RX interrupt. */
    UART_EnableInterrupts(ACTIVE_UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
    EnableIRQ(ACTIVE_UART_IRQn);
}



void ACTIVE_UART_IRQHandler(void)
{
    uint8_t data;

    /* If new data arrived. */
   if ((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & UART_GetStatusFlags(ACTIVE_UART))
    {
        data = UART_ReadByte(ACTIVE_UART);

        if(bufferPosition>=BUFFER_SIZE){
        	bufferPosition=0;
        }

        if(((data>='0') && (data<='9'))||data=='.'){
        	buffer[bufferPosition]=data;
        	UART_WriteByte(ACTIVE_UART, buffer[bufferPosition]);
        	bufferPosition++;
		}
        if(data=='\r'){
        	UART_WriteByte(ACTIVE_UART,'\n');
        	if (bufferPosition==0){
        		return;
        	}

        	messageValue=stof (buffer);

        	if (messageValue>=0 && messageValue<=3.3){
        		newMessage=1;
        	}
        	else{
        		uint8_t message[]=INVALID_DAC_VALUE;
        	    UART_WriteBlocking(ACTIVE_UART, message, sizeof(message) / sizeof(message[0]));
        	    clearBuffer();
        	    sendRequest();
        	}

        }

    }
    SDK_ISR_EXIT_BARRIER;

}



void sendRequest(void){
	uint8_t message[]=REQUEST_DATA;

	UART_WriteBlocking(ACTIVE_UART, message, sizeof(message) / sizeof(message[0]));
}





uint8_t newDACvalueArrived(void){
	return newMessage;
}

float getMessage(void){
	return messageValue;
}

void clearBuffer(void){
	for(uint8_t i=0;i<BUFFER_SIZE;i++){
		buffer[i]=0;
	}
	bufferPosition=0;
	messageValue=0;
	newMessage=0;
}





float stof(uint8_t* s){
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1;
      continue;
    };
    uint16_t d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
};







