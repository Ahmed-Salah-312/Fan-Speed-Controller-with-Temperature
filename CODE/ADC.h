#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"
#define ADC_MAXIMUM_VALUE 1023
#define ADC_REF_VOLT 2.56
typedef enum
{
   AREF,AVCC,Reserved,internal_voltage
}ADC_RefrenceVoltage;
typedef enum
{
Pre_2,Pres_2,Pre_4,Pre_8,Pre_16,Pre_32,Pre_64,Pre_128
}ADC_Prescaler;
typedef struct{
 ADC_RefrenceVoltage ref_volt;
 ADC_Prescaler prescaler;
}ADC_ConfigType;

void ADC_init(ADC_ConfigType *Config_ptr);
uint16 ADC_readChannel(uint8 ch_num);
#endif /* ADC_H_ */
