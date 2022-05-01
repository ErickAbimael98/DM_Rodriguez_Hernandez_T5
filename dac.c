


#include "fsl_dac.h"
#include "fsl_common.h"
#include "dac.h"

void initDAC(void){
	dac_config_t dacConfigStruct;

	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(DAC_BASEADDR, true);
	DAC_SetBufferReadPointer(DAC_BASEADDR, 0U);

}


void setDACvoltage(float voltage){
	uint16_t dacValue= voltage*MAX_DAC_VALUE/VOLTAGE_REFERENCE;
    DAC_SetBufferValue(DAC_BASEADDR, 0U, dacValue);

}


