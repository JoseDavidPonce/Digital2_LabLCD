/* 
 * 
 * Autor: Jos� David Ponce del Cid
 * UVG
 * Ingenier�a electr�nica
 * Se utiliz� como referencia
 * la librer�a modificada por Pablo Mazariegos
 * originalmente escrita por Ligo George
 * ubicada en: https://github.com/pdmazariegos-uvg/ie3027/blob/master/Ejemplos/LCD4Bits.X/LCD.c
 */

#include <pic16f887.h>
#include <stdint.h>
#include "LCD_8bits.h"      //Se importan los headers correspondientes

void LCD_CMD (uint8_t a){   //Funci�n para enviar comandos al puerto 
    RS = 0;                 //de datos de la LCD
    PUERTO = a;
    EN = 1;               //Despu�s de enviar el comando, se activa el reloj
    __delay_us(5);          //Para que tenga efecto
    EN = 0;
    __delay_ms(5);          //Se espera por seguridad
}

void LCD_CLR (void){        //Comando preestablecido para limpiar la LCD
    LCD_CMD(0x01);
}

void LCD_SET_CURSOR (uint8_t a, uint8_t b){ //Funci�n para ubicar el cursor
    uint8_t temporal;
    if (a == 1) {                   //a es la fila y b es la columna
        temporal = 0x80 + b - 1;        //De esta manera el comando ya incluye      
        LCD_CMD(temporal);      //la coordenada necesaria
    }
    else if (a == 2){           //En el caso de que se escoja la fila 2, se
        temporal = 0xC0 + b - 1;    //hace lo mismo
        LCD_CMD(temporal);      //Siempre se env�a el comando
    }
}

void LCD_INIT (void) {          //Para inicializar la LCD, esta funci�n env�a
    PUERTO = 0;         //la rutina necesaria para su inicializaci�n
    __delay_ms(15);
    LCD_CMD(0x30);
    __delay_ms(5);
    LCD_CMD(0x30);
    __delay_us(160);
    LCD_CMD(0x30);
    __delay_us(160);
    
    
    LCD_CMD(0x02);      //Los siguientes comandos son de configuraci�n cuando ya
    LCD_CMD(0x38);      //inicializ� la LCD
    LCD_CMD(0x08);
    LCD_CMD(0x01);
    LCD_CMD(0x06);
    LCD_CMD(0x0C);

}

void LCD_WRITE_CHAR(char a){    //Cuando en esta funci�n entra una variable char
    RS = 1;
    PUERTO = a;             //Se env�a el dato al puerto de la LCD y se 
    EN = 1;     //imprime con una se�al de reloj
    __delay_us(40);
    EN = 0;       
    __delay_ms(5);
}

void LCD_WRITE_STRING (char *a){    //La funci�n de STRING separa un arreglo
    int i;                  //de chars y lo env�a uno por uno con un ciclo for
    for(i=0; a[i]!='\0'; i++)   //usando la funci�n anterior
        LCD_WRITE_CHAR(a[i]);
}

void LCD_SHIFT_RIGHT(void){ //Si se acab� el espacio de LCD, esta funci�n mueve
    LCD_CMD(0x1C);          //a la derecha todo el display
}

void LCD_SHIFT_LEFT(void){  //Si se acab� el espacio de LCD, esta funci�n mueve
    LCD_CMD(0x18);          //a la izquierda todo el display
}