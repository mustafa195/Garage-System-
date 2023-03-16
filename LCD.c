
#include "StdTypes.h"
#include "Utils1.h"
#include "DIO_interface.h"
#include "LCD.h"
#define  F_CPU 8000000
#include <util/delay.h>

#if LCD_MODE==_4_bit
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 ins)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(ins,7));
	DIO_WritePin(D6,READ_BIT(ins,6));
	DIO_WritePin(D5,READ_BIT(ins,5));
	DIO_WritePin(D4,READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(ins,3));
	DIO_WritePin(D6,READ_BIT(ins,2));
	DIO_WritePin(D5,READ_BIT(ins,1));
	DIO_WritePin(D4,READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X02); //4 bit
	WriteIns(0X28);
	WriteIns(0X0c); //0x0e,0x0f cursor
	WriteIns(0X01); //clear screen
	_delay_ms(1);
	WriteIns(0X06);
	
}

#elif LCD_MODE==_8_bit
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X38); //8 bit
	WriteIns(0X0c); //0x0e,0x0f cursor
	WriteIns(0X01); //clear screen
	_delay_ms(1);
	WriteIns(0X06);
	
}
#endif


void LCD_Clear(void)
{
	WriteIns(0X01); //clear screen
	_delay_ms(1);
}

void LCD_ClearCell(u8 line,u8 cell,u8 num)
{
	LCD_SetCursor(line,cell);
	for(u8 i=0;i<num;i++)
	{
		LCD_WriteChar(' ');
	}
}

void LCD_WriteNumber(s32 num)
{
	u8 i=0,str[16];
	s8 j;
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if(num<0)
	{
		LCD_WriteChar('-');
		num*=-1;
	}
	while(num)
	{
		str[i]=(num%10)+'0';
		num/=10;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}

void LCD_WriteString(c8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}

void LCD_WriteBinary(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		if((num>>i)&1)
		{
			LCD_WriteChar('1');
		}
		else
		{
			LCD_WriteChar('0');
		}
	}
}

void LCD_WriteHex(u8 num) //0x35
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN-10+'A');
	}
	if (LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN-10+'A');
	}
}

void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_SetCursor(u8 line,u8 cell)
{
	if(line==0)
	{
		WriteIns(0x80+cell);
	}
	else if(line==1)
	{
		WriteIns(0x80+0x40+cell);
	}
}

void LCD_SetCursorString(u8 line,u8 cell,u8* str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}

void LCD_CreateChar(u8* pattern,u8 location)
{
	u8 i=0;
	WriteIns(0x40+(location*8)); // send the address of CGRAM
	for(i=0;i<8;i++)
	{
		WriteData(pattern[i]); // pass the bytes of pattern on LCD
	}
	WriteIns(0x80);
}