/* 
 * Se utilizó como referencia
 * la librería modificada por Pablo Mazariegos
 * originalmente escrita por Ligo George
 * ubicada en: https://github.com/pdmazariegos-uvg/ie3027/blob/master/Ejemplos/LCD4Bits.X/LCD.c
 */

#include <pic16f887.h>
#include <stdint.h>
#include "LCD_8bits.h"

void LCD_CMD (uint8_t a){
    RS = 0;
    PUERTO = a;
    EN = 1;
    __delay_us(5);
    EN = 0;
    __delay_ms(5);
}

void LCD_CLR (void){
    LCD_CMD(0x01);
}

void LCD_SET_CURSOR (uint8_t a, uint8_t b){
    uint8_t temporal;
    if (a == 1) {
        temporal = 0x80 + b - 1;
        LCD_CMD(temporal);
    }
    else if (a == 2){
        temporal = 0xC0 + b - 1;
        LCD_CMD(temporal);
    }
}

void LCD_INIT (void) {
    PUERTO = 0;
    __delay_ms(15);
    LCD_CMD(0x30);
    __delay_ms(5);
    LCD_CMD(0x30);
    __delay_us(160);
    LCD_CMD(0x30);
    __delay_us(160);
    
    
    LCD_CMD(0x02);
    LCD_CMD(0x38);
    LCD_CMD(0x08);
    LCD_CMD(0x01);
    LCD_CMD(0x06);
    LCD_CMD(0x0C);

}

void LCD_WRITE_CHAR(char a){
    RS = 1;
    PUERTO = a;
    EN = 1;
    __delay_us(40);
    EN = 0;       
    __delay_ms(5);
}

void LCD_WRITE_STRING (char *a){
    int i;
    for(i=0; a[i]!='\0'; i++)
        LCD_WRITE_CHAR(a[i]);
}

void LCD_SHIFT_RIGHT(void){
    LCD_CMD(0x1C);
}

void LCD_SHIFT_LEFT(void){
    LCD_CMD(0x18);
}