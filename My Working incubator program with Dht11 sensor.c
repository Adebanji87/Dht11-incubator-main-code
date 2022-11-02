/*
 * GccApplication1.c
 *
 * Created: 12/10/2020 11:26:57 AM
 *  Author: Asafe
 */ 


#define F_CPU 16348000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "dht.h"
#define RELAY_PIN1 2
#define RELAY_PIN2 3
int8_t temperature, humidity;

	void GetDHT()
	{
		if (dht_gettemperaturehumidity(&temperature, &humidity) != -1)
		{
			char printbuff[8];
			lcd_clear();
			dtostrf(humidity, 3, 2, printbuff);
			LCD_setCursor(0,0);
			lcd_print("H:");
			LCD_setCursor (2,0);
			lcd_print(printbuff);
			LCD_setCursor (6,0);
			lcd_print("%");
			dtostrf(temperature, 3, 2, printbuff);
			LCD_setCursor(8,0);
			lcd_print ("T: ");
			LCD_setCursor (10,0);
			lcd_print(printbuff);
			LCD_setCursor (14,0);
			lcddata (0xDF);
			LCD_setCursor(15,0);
			lcd_print ("C");
			_delay_ms(1000);
			
		}
		else
		{
			lcd_clear();
			LCD_setCursor(0,0);
			lcd_print("not connected");
		}

	}
	
	

		int main(void)
		{

			lcdinit();
			lcd_clear();
			lcd_print ("Welcome Banji");
			_delay_ms(100);
			

			DDRC |= (1 << RELAY_PIN1);
			DDRC |= (1 << RELAY_PIN2);
			PORTC &= ~(1 << RELAY_PIN1);
			PORTC &= ~(1 << RELAY_PIN2);
			lcdinit();
			lcd_clear();

			int8_t temperature = 0;
			int8_t humidity = 0;
			
			
			while (1)
			{
				
				GetDHT();
	if (humidity>=0x0000003C)
	{
		PORTC &= ~(1 << RELAY_PIN1);
	}
	else if(humidity<0x00000032)
	{
		PORTC |= (1 << RELAY_PIN1);
	}
	if (temperature>=0x00000025)
	{
		PORTC &= ~(1 << RELAY_PIN2);
	}
	else
	{
		PORTC |= (1 << RELAY_PIN2);
	}
		
}
		}

	
					



		
		
		
   