#ifndef LCD_H_
#define LCD_H_
#include"std_types.h"
#define LCD_DATA_BITS_MODE 8
#define DATA_PORT_ID PORTC_ID
#define Enable_PIN PIN2_ID
#define Enable_PIN_PORT PORTD_ID
#define RS_PIN PIN0_ID
#define RS_PIN_PORT PORTD_ID
#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 Character);
void LCD_init(void);
void LCD_displayString(uint8 *str);
void LCD_moveCursor(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row, uint8 col,uint8 *str);
void LCD_clearScreen(void);
void LCD_intgerToString(int data);
#endif /* LCD_H_ */
