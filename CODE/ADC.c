#include "avr/io.h"
#include "common_macros.h"
#include "adc.h"


void ADC_init(ADC_ConfigType *Config_ptr)
{
ADMUX=(ADMUX & (0x00)) | ((Config_ptr->ref_volt)<<6);
ADCSRA=(1<<ADEN);
ADCSRA=(ADCSRA & (0xF8)) | (Config_ptr->prescaler);
}
uint16 ADC_readChannel(uint8 ch_num)
{
	ch_num&=0x07;
ADMUX = ADMUX & (0xE0);
ADMUX = ADMUX | ch_num;
SET_BIT(ADCSRA,ADSC);
while(BIT_IS_CLEAR(ADCSRA,ADIF))
{

}
SET_BIT(ADCSRA,ADIF);
return ADC;
}
