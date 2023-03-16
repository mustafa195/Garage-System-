


#ifndef LCD_H_
#define LCD_H_

#define _4_bit 1
#define _8_bit 2

/************************************** pin config **************************************/
#define LCD_MODE _4_bit

#define  RS  PINA1
#define  EN  PINA2

/* if 8 bit mode only */
#define  LCD_PORT   PA
/* if 4 bit mode only */
#define D7 PINA6
#define D6 PINA5
#define D5 PINA4
#define D4 PINA3


void LCD_Init(void);
void LCD_Clear(void);
void LCD_ClearCell(u8 line,u8 cell,u8 num);
void LCD_WriteNumber(s32 num);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(c8* str);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteNumber_4D(u16 num);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_SetCursorString(u8 line,u8 cell,u8* str);
void LCD_CreateChar(u8* pattern,u8 location);



#endif /* LCD_H_ */