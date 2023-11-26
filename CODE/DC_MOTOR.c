#include "DC_MOTOR.h"
#include "PWM.h"


void DcMotor_Init(void){

	GPIO_setupPinDirection(PORTD_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTD_ID,PIN7_ID,PIN_OUTPUT);
	GPIO_writePin(PORTD_ID,PIN7_ID,LOGIC_LOW);	//enable is zero
}

void DcMotor_Rotate(uint8 state,uint8 speed){
	GPIO_writePin(PORTD_ID,PIN7_ID,LOGIC_HIGH);	//enable is zero
	PWM_Timer0_Start(speed);
	switch(state){
	case  ACW :
		GPIO_writePin(PORTD_ID,PIN5_ID,LOGIC_LOW);
		GPIO_writePin(PORTD_ID,PIN6_ID,LOGIC_HIGH);
		break ;
	case CW :
		GPIO_writePin(PORTD_ID,PIN5_ID,LOGIC_HIGH);
		GPIO_writePin(PORTD_ID,PIN6_ID,LOGIC_LOW);
		break ;
	case STOP:
		GPIO_writePin(PORTD_ID,PIN5_ID,LOGIC_LOW);
		GPIO_writePin(PORTD_ID,PIN6_ID,LOGIC_LOW);
	    break;
	default :
		GPIO_writePin(PORTD_ID,PIN5_ID,LOGIC_LOW);
		GPIO_writePin(PORTD_ID,PIN6_ID,LOGIC_LOW);
	    break;
	}

}

