/* 
 * Se utilizó como referencia
 * la librería modificada por Pablo Mazariegos
 * originalmente escrita por Ligo George
 * ubicada en: https://github.com/pdmazariegos-uvg/ie3027/blob/master/Ejemplos/LCD4Bits.X/LCD.c
 */

#include <pic16f887.h>
#include <stdint.h>
#include "LCD_8bits.h"

void LCD_PORT(uint8_t a)
{
	if(a & 1)
		D0 = 1;
	else
		D0 = 0;

	if(a & 2)
		D1 = 1;
	else
		D1 = 0;

	if(a & 4)
		D2 = 1;
	else
		D2 = 0;

	if(a & 8)
		D3 = 1;
	else
		D3 = 0;
    
    if(a & 16)
		D4 = 1;
	else
		D4 = 0;

	if(a & 32)
		D5 = 1;
	else
		D5 = 0;

	if(a & 64)
		D6 = 1;
	else
		D6 = 0;

	if(a & 128)
		D7 = 1;
	else
		D7 = 0;
}

void LCD_CMD (uint8_t a){
    RS = 0;
    LCD_PORT(a);
    EN = 1;
    __delay_ms(4);
    EN = 0;
}

void LCD_CLR (void){
    LCD_CMD(0);
    LCD_CMD(1);
}

void LCD_SET_CURSOR (uint8_t a, uint8_t b){
    uint8_t temporal, x, z;
    if (a == 1) {
        temporal = 0x80 + b - 1;
        x = temporal>>4;
        z = temporal & 0x0F;
        LCD_CMD(x);
        LCD_CMD(z);
    }
    else if (a == 2){
        temporal = 0xC0 + b - 1;
        x = temporal>>4;
        z = temporal & 0x0F;
        LCD_CMD(x);
        LCD_CMD(z);
    }
}

void LCD_INIT (void) {
    LCD_PORT(0x00);
    __delay_ms(20);
    LCD_CMD(0x033);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_ms(11);
    LCD_CMD(0x03);
    
    LCD_CMD(0x02);
    LCD_CMD(0x02);
    LCD_CMD(0x08);
    LCD_CMD(0x00);
    LCD_CMD(0x0C);
    LCD_CMD(0x00);
    LCD_CMD(0x06);
}

void LCD_WRITE_CHAR(uint8_t a){
    uint8_t temporal, x;
    temporal = a & 0x0F;
    x = a & 0xF0;
    RS = 1;
    LCD_PORT (x>>4);
    EN = 1;
    __delay_us(40);
    EN = 0;
    LCD_PORT(temporal);
    EN = 1;
    __delay_us(40);
    EN = 0;          
}

void LCD_WRITE_STRING (uint8_t *a){
    int i;
    for(i=0; a[i]!='\0'; i++)
        LCD_WRITE_CHAR(a[i]);
}

void LCD_SHIFT_RIGHT(void){
    LCD_CMD(0x01);
    LCD_CMD(0x0C);
}

void LCD_SHIFT_LEFT(void){
    LCD_CMD(0x01);
    LCD_CMD(0x08);
}