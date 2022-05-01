
#include "board.h"
#include "uart.h"
#include "dac.h"

int main(void)
{

	initUART();
	initDAC();
	sendRequest();


    while (1)
    {
    	if (newDACvalueArrived()){

    		setDACvoltage(getMessage());

    		clearBuffer();
    		sendRequest();
    	}
    }
}
