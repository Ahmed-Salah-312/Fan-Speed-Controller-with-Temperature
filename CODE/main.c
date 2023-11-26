/*
 ======================================================================================
 Name        : miniproject3.c
 Author      : Ahmed Salah
 ======================================================================================
 */

#include "ADC.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "DC_MOTOR.h"
int main(void)
{
	uint16 motor_speed;
	uint8 temp ;
	ADC_ConfigType	ADC_Config={internal_voltage,Pre_8};
	LCD_init(); /* initialize LCD driver */
	ADC_init(&ADC_Config); /* initialize ADC driver */
	DcMotor_Init();	/* initialize DC_MOTOR driver */

	/* Display this string "ADC Value = " only once on LCD at the first row */
	LCD_displayString("Fan is  ");
	LCD_moveCursor(1,0);
	LCD_displayString("Temp =    C");

    while(1)
    {
    	/* Read ADC channel 0 where the potentiometer is connected */
    	temp = LM35_getTemperature();
    	LCD_moveCursor(1,6);
    	LCD_intgerToString(temp);
    	LCD_displayCharacter(' ');
		motor_speed = ADC_readChannel(2);
		LCD_moveCursor(0,8);
		if (temp < 30){
			LCD_displayString("OFF");
			/*TURN OFF THE MOTOR*/
			DcMotor_Rotate(STOP,0);
		}
		else {
			LCD_displayString("ON ");
			if((temp >=30)&&(temp <60)){
				/*turn on the fan with 25% of its maximum speed.*/
				DcMotor_Rotate(CW,0.25*max_speed);

			}
			else if((temp >=60)&&(temp <90)){
				/*turn on the fan with 50% of its maximum speed.*/
				DcMotor_Rotate(CW,0.5*max_speed);

			}
			else if((temp >=90)&&(temp <120)){
				/*turn on the fan with 75% of its maximum speed.*/
				DcMotor_Rotate(CW,0.75*max_speed);
						}
			else if(temp >=120){
				/*turn on the fan with 100% of its maximum speed.*/
				DcMotor_Rotate(CW,max_speed);

						}
		}



    }
}


