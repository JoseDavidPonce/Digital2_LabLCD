/* 
 * 
 * Autor: José David Ponce del Cid
 * UVG
 * Ingeniería electrónica
 * Se utilizó como referencia
 * la librería modificada por Pablo Mazariegos
 * originalmente escrita por Ligo George
 * ubicada en: https://github.com/pdmazariegos-uvg/ie3027/blob/master/Ejemplos/LCD4Bits.X/LCD.c
 */

#include <pic16f887.h>
#include <stdint.h>
#include "LCD_8bits.h"      //Se importan los headers correspondientes

void LCD_CMD (uint8_t a){   //Función para enviar comandos al puerto 
    RS = 0;                 //de datos de la LCD
    PUERTO = a;
    EN = 1;               //Después de enviar el comando, se activa el reloj
    __delay_us(5);          //Para que tenga efecto
    EN = 0;
    __delay_ms(5);          //Se espera por seguridad
}

void LCD_CLR (void){        //Comando preestablecido para limpiar la LCD
    LCD_CMD(0x01);
}

void LCD_SET_CURSOR (uint8_t a, uint8_t b){ //Función para ubicar el cursor
    uint8_t temporal;
    if (a == 1) {                   //a es la fila y b es la columna
        temporal = 0x80 + b - 1;        //De esta manera el comando ya incluye      
        LCD_CMD(temporal);      //la coordenada necesaria
    }
    else if (a == 2){           //En el caso de que se escoja la fila 2, se
        temporal = 0xC0 + b - 1;    //hace lo mismo
        LCD_CMD(temporal);      //Siempre se envía el comando
    }
}

void LCD_INIT (void) {          //Para inicializar la LCD, esta función envía
    PUERTO = 0;         //la rutina necesaria para su inicialización
    __delay_ms(15);
    LCD_CMD(0x30);
    __delay_ms(5);
    LCD_CMD(0x30);
    __delay_us(160);
    LCD_CMD(0x30);
    __delay_us(160);
    
    
    LCD_CMD(0x02);      //Los siguientes comandos son de configuración cuando ya
    LCD_CMD(0x38);      //inicializó la LCD
    LCD_CMD(0x08);
    LCD_CMD(0x01);
    LCD_CMD(0x06);
    LCD_CMD(0x0C);

}

void LCD_WRITE_CHAR(char a){    //Cuando en esta función entra una variable char
    RS = 1;
    PUERTO = a;             //Se envía el dato al puerto de la LCD y se 
    EN = 1;     //imprime con una señal de reloj
    __delay_us(40);
    EN = 0;       
    __delay_ms(5);
}

void LCD_WRITE_STRING (char *a){    //La función de STRING separa un arreglo
    int i;                  //de chars y lo envía uno por uno con un ciclo for
    for(i=0; a[i]!='\0'; i++)   //usando la función anterior
        LCD_WRITE_CHAR(a[i]);
}

void LCD_SHIFT_RIGHT(void){ //Si se acabó el espacio de LCD, esta función mueve
    LCD_CMD(0x1C);          //a la derecha todo el display
}

void LCD_SHIFT_LEFT(void){  //Si se acabó el espacio de LCD, esta función mueve
    LCD_CMD(0x18);          //a la izquierda todo el display
}