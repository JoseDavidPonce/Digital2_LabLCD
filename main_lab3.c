/*
 * File:   main_lab3.c
 * Author: José Ponce
 * Ingeniería electrónica
 * Carné 18187
 * Created on 9 de febrero de 2020, 07:50 PM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD_8bits.h"
#include "ADCheader.h"
#include "EUSARTheader.h"

#define _XTAL_FREQ 4000000  //Configura una frecuencia para los delays

void Port_init(void);   //Prototipos de funciones
uint8_t pot1, pot2, start_another;
float volt1, volt2;     //Variables float para los voltajes
int valor = 0;
char Contador;
char string1[4];        //String para los valores de sprintf
char string2[4];
char string3[3];

void __interrupt() isr(void){   //Módulo de interrupciones con ADC, y RX
    if (PIR1bits.ADIF == 1){    //Si acabó una conversión ADC, apagar la bandera
        PIR1bits.ADIF = 0;
        start_another = 1;      //e indicar con una bandera para comenzar otra
        if (ADCON0bits.CHS0 == 0){  //Si el canal es el 0
            pot2 = ADRESH;      //Guardar el valor en pot2
            ADCON0bits.CHS0 = 1;    //Cambiar al canal 1
        }else{         //Si el canal no es 0, es 1. Y se guarda el valor en 
            pot1 = ADRESH;      //pot
            ADCON0bits.CHS0 = 0;        //se regresa al canal 0
        }
    }if (PIR1bits.RCIF == 1){       //Si se acaba de recibir un dato
        Contador = RCREG;           //hay que guardarlo en "contador"
        PIR1bits.RCIF = 0;      //Apagar la badera de interrupción
    }
}

void main(void) {       //Programa principal
    Port_init();        //Configuración de los puertos
    LCD_INIT();         //Inicialización de la LCD
    ADC_init(1,1,1,0);      //Inicialización de la conversión ADC
    EUSART_Init(1, 0);      //Inicialización de la comunicación serial y 9600 baudios
    while(1){               //Comienzo del loop
        if (start_another == 1){    //Si hay que iniciar otra conversión,
            start_conversion();     //Activar la bandera go_done
            start_another = 0;      //Y apagar el indicador
        }
        if (Contador == 0x2B){      //Si el contador es igual al signo +
            valor++;        //Sumar 1 al valor de la variable de valor
            Contador = 0;   //resetear variable contador para recibir otro dato
        }else if (Contador == 0x2D){    //si el signo es -, hay que restar 1 al valor
            valor--;
            Contador = 0;
        }
        volt1 = pot1*(5.0/255);     //Conversión de 0 - 255 a 0 - 5v 
        volt2 = pot2*(5.0/255);         //Para visualizar los voltajes
        sprintf(string1,"%1.1f", volt1);    //Se convierte el voltaje con 1 decimal
        sprintf(string2, "%1.1f", volt2);   //en variables de string
        sprintf(string3, "%d", valor);      //para ser enviadas con facilidad
        LCD_SET_CURSOR(1,1);        //Se coloca el cursor en la primera fila
        LCD_WRITE_STRING("V1   V2  Cont.");     //y primera columna
        LCD_SET_CURSOR(2,1);        //Se coloca en la segunda fila para escribir 
        LCD_WRITE_STRING(string1);      //los strings obtenidos
        LCD_SET_CURSOR(2,6);        //Se corre para la siguiente string
        LCD_WRITE_STRING(string2);      //Se imprime el segundo valor de voltaje
        LCD_SET_CURSOR(2, 11);
        LCD_WRITE_STRING(string3);      //por último se imprime el contador
        TXREG = 0x45;                   //Enviar un código de inicio de datos
        SEND_STRING(string1);       //Para comenzar la recepción del otro lado
        SEND_STRING(string2);       //de los tres valores, volt1, volt2 y contador
        SEND_STRING(string3);
    }
    return;
}

void Port_init(void){       //Inicialización de los puertos 
    TRISA = 0x03;
    ANSEL = 0;
    ANSEL = 0x03;
    ANSELH = 0;
    TRISB = 0;
    PORTB = 0;
    TRISD = 0;
    PORTD = 0;
    PORTA = 0;
}