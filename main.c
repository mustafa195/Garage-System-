
//#include <avr/io.h>
#include "MemMap.h"
#include "Utils1.h"
#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOVE.h"
#include "LCD.h"
#include "KeyPad_InterFace.h"
#include "KeyPad_cfg.h"
#include "ADC.h"
#include "Timers.h"
#define F_CPU 8000000
#include <util/delay.h>



void SERVO_SetPosition(u8 angle)
{
	OCR1A=((angle*(u32)1000)/180)+999;
}

int main(void)
{
    
	DIO_Init();
	LCD_Init();
	//ADC_Init(VREF_AVCC,ADC_SCALER_64);
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_NON_INVERTING);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	ICR1=19999; //total time 20ms
	
	//LCD_WriteNumber(22);
	//LCD_SetCursor(1,0);
	//LCD_WriteString("Slots on the Garage");
	//ADC_Init(VREF_VCC,ADC_SCALER_64);
	
  //KEYPAD_Init();
	// LCD_WriteChar('A');
	//LCD_SetCursor(1,0);
	LCD_WriteString("There are 0 Cars");
	LCD_SetCursor(1,0);
	LCD_WriteString("garage has space");
	s8 flage1=0,flage2=0,IR1,IR2,Counter=0;
	//u8 k;
	
	/*LCD_WriteString("ADC TEST");
	u16 num=0;
	num= ADC_READ(CH_3);
	LCD_SetCursor(1,0);*/
	//u8 num=6;
	//LCD_WriteNumber(num);
    while (1) 
    {
		
		IR1=DIO_ReadPin(PIND0);
		if(IR1==1 && flage1==0 && Counter<3)
		{
			Counter++;
			LCD_SetCursor(0,10);
			LCD_WriteChar(Counter+48);
			flage1=1;
			if (Counter==3)
			{
				LCD_Clear();
				LCD_WriteString("There are 3 Cars");
				LCD_SetCursor(1,0);
				LCD_WriteString("Garage is Full");
			}
			OCR1B=999;
			_delay_ms(1000);
			OCR1B=1499;
			
		}
		else if (IR1==0)
		{
			flage1=0;
		}
		IR2=DIO_ReadPin(PIND1);
		if(IR2==1 && flage2==0 && Counter>0)
		{
			Counter--;
			LCD_SetCursor(0,11);
			LCD_WriteChar(Counter+48);
			flage2=1;
			LCD_Clear();
			LCD_WriteString("There are ");
			LCD_WriteChar(Counter+48);
			LCD_WriteString(" Cars");
			LCD_SetCursor(1,0);
			LCD_WriteString("garage has space");
			OCR1A=999; //-90 ==>>1ms
			_delay_ms(1000);
			OCR1A=1499; //0 ==>>1.5ms
		}
		
		else if(IR2==0)
		{
			flage2=0;
		}
    }
}

