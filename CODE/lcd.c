#include"gpio.h"
#include"lcd.h"
#include <util/delay.h>
#include"common_macros.h"

void LCD_sendCommand(uint8 command){
	GPIO_writePin(RS_PIN_PORT, RS_PIN , 0);			//RS PIN initialized by 0 to send commands
	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN, 1);		//Enable PIN initalized by 1
	_delay_ms(1);

#if (LCD_DATA_BITS_MODE ==4)
	GPIO_writePin(DATA_PORT_ID, PIN3_ID , GET_BIT(command,4));		//PIN 3 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN4_ID , GET_BIT(command,5));		//PIN 4 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN5_ID , GET_BIT(command,6));		//PIN 5 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN6_ID , GET_BIT(command,7));		//PIN 6 for data & commands

	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN , 0);		//Disable The Enalbe
	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN, 1);		// PUT 1 ON THE ENABLE PIN
	_delay_ms(1);

	GPIO_writePin(DATA_PORT_ID, PIN3_ID , GET_BIT(command,0));		//PIN 3 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN4_ID , GET_BIT(command,1));		//PIN 4 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN5_ID , GET_BIT(command,2));		//PIN 5 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN6_ID , GET_BIT(command,3));		//PIN 6 for data & commands

	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN, 0);		//Disable The Enalbe
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE ==8)
	GPIO_writePort(DATA_PORT_ID, command);		//port  for command
	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN , 0);		//Disable The Enalbe
	_delay_ms(1);
#endif
}
void LCD_displayCharacter(uint8 character){
	GPIO_writePin(RS_PIN_PORT, RS_PIN , 1);		//RS PIN initialized by 0 to send data
	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN, 1);		//PUT 1 ON THE ENABLE PIN
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE ==4)
	GPIO_writePin(DATA_PORT_ID, PIN3_ID , GET_BIT(character,4));		//PIN 3 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN4_ID , GET_BIT(character,5));		//PIN 4 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN5_ID , GET_BIT(character,6));		//PIN 5 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN6_ID , GET_BIT(character,7));		//PIN 6 for data & commands

	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN , 0);		//Disable The Enalbe
	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN , 1);		//PUT 1 ON THE ENABLE PIN
	_delay_ms(1);

	GPIO_writePin(DATA_PORT_ID, PIN3_ID , GET_BIT(character,0));		//PIN 3 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN4_ID , GET_BIT(character,1));		//PIN 4 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN5_ID , GET_BIT(character,2));		//PIN 5 for data & commands
	GPIO_writePin(DATA_PORT_ID, PIN6_ID , GET_BIT(character,3));		//PIN 6 for data & commands

	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN , 0);		//Disable The Enalbe
	_delay_ms(1);

#elif (LCD_DATA_BITS_MODE ==8)
	GPIO_writePort(DATA_PORT_ID, character);			//port  for  data
	_delay_ms(1);
	GPIO_writePin(Enable_PIN_PORT, Enable_PIN, 0);		//Disable The Enalbe
	_delay_ms(1);
#endif

}
void LCD_init(void){
	GPIO_setupPinDirection(RS_PIN_PORT, RS_PIN, PIN_OUTPUT);	// Rs as output pin
	GPIO_setupPinDirection(Enable_PIN_PORT, Enable_PIN, PIN_OUTPUT);	// E as output pin
#if (LCD_DATA_BITS_MODE ==8)
	GPIO_setupPortDirection(DATA_PORT_ID, PORT_OUTPUT);	// DATA PORT
	_delay_ms(20);
	LCD_sendCommand(0x38);
#elif (LCD_DATA_BITS_MODE ==4)
	GPIO_setupPinDirection(DATA_PORT_ID, PIN3_ID, PIN_OUTPUT);		//PIN 3 for data & commands
	GPIO_setupPinDirection(DATA_PORT_ID, PIN4_ID, PIN_OUTPUT);		//PIN 4 for data & commands
	GPIO_setupPinDirection(DATA_PORT_ID, PIN5_ID, PIN_OUTPUT);		//PIN 5 for data & commands
	GPIO_setupPinDirection(DATA_PORT_ID, PIN6_ID, PIN_OUTPUT);		//PIN 6 for data & commands
	/* Send for 4 bit initialization of LCD  */
		LCD_sendCommand(0x33);
		LCD_sendCommand(0x32);

		/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
		LCD_sendCommand(0x28);
#endif
		LCD_sendCommand(0x0c);		//cursor off
		LCD_sendCommand(0x01);		//clear screen
}

void LCD_displayString(uint8 *str){
	for(uint8 i=0 ;str[i]!='\0';i++)
	LCD_displayCharacter( str[i]);


}

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0 :
		lcd_memory_address = col ;
		break ;
	case 1 :
			lcd_memory_address = col + 0x40 ;
			break ;
	case 2 :
			lcd_memory_address = col + 0x10 ;
			break ;
	case 3 :
			lcd_memory_address = col + 0x50 ;
			break ;

	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | 0x80);
}

void LCD_displayStringRowColumn(uint8 row, uint8 col,uint8 *str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);
}

void LCD_clearScreen(void){
	LCD_sendCommand(0x1);		//clear command
}

void LCD_intgerToString(int data){
	char temp [16];
	itoa(data,temp,10);
	LCD_displayString(temp);

}

