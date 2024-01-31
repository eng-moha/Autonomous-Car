/*
 * LCD_interface.h
 *
 * Created: 10/1/2023 12:12:19 PM
 *  Author: Autonomous Car Team
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
void LCD_init(void);                    // init
void LCD_sendChar(u8 );				//sent char
void LCD_sendComand (u8) ;       //sent comment
void LCD_sendString(u8*);	
void LCD_clear(void);
void LCD_sendNumber         (s32 number);
/*

void LCD_shift               (u8 shifttingDirection);
void LCD_goToSpecificPosition(u8 LineNumber, u8 Position);
*/	





#endif /* LCD_INTERFACE_H_ */
