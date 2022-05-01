#define DAC_BASEADDR DAC0
#define MAX_DAC_VALUE 4096
#define VOLTAGE_REFERENCE 3.3

void initDAC(void);
void setDACvoltage(float voltage);
