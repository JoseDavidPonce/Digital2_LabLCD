/*
 * File:   main_lab3.c
 * Author: José P11
 *
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

#define _XTAL_FREQ 4000000

void Port_init(void);
uint8_t pot1, pot2, start_another;
float volt1, volt2;
char string1[5];
char string2[5];

void __interrupt() isr(void){
    if (PIR1bits.ADIF == 1){
        PIR1bits.ADIF = 0;
        start_another = 1;
        if (ADCON0bits.CHS0 == 0){
            pot2 = ADRESH;
            ADCON0bits.CHS0 = 1;
        }else{
            pot1 = ADRESH;
            ADCON0bits.CHS0 = 0;
        }
    }
}

void main(void) {    
    Port_init();
    LCD_INIT();
    ADC_init(1,1,1,0);
    EUSART_Init(1, 0);
    while(1){
        if (start_another == 1){
            start_conversion();
            start_another = 0;
        }
        
        
        volt1 = pot1*(5.0/255);
        volt2 = pot2*(5.0/255);  
        sprintf(string1,"%1.2f", volt1);
        sprintf(string2, "%1.2f", volt2);
        LCD_SET_CURSOR(1,1);
        LCD_WRITE_STRING("V1   V2  Cont.");
        LCD_SET_CURSOR(2,1);
        LCD_WRITE_STRING(string1);
        LCD_SET_CURSOR(2,6);
        LCD_WRITE_STRING(string2);
    }
    return;
}

void Port_init(void){
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