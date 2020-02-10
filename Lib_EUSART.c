#include <stdint.h>
#include <xc.h>
#include "EUSARTheader.h"

void EUSART_Init (uint8_t a){
    BAUDCTLbits.BRG16 = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    if (a==1){
        PIE1bits.RCIE = 1;
        INTCONbits.GIE = 1;
        INTCONbits.PEIE = 1;
    }
    RCSTAbits.RX9D = 0;
    RCSTAbits.CREN = 1;
}

uint8_t CHECK_FOR_ERRORS (void){
    if (RCSTAbits.FERR == 1){
        return 1;
    }else if (RCSTAbits.OERR == 1){
        return 2;
    }else{
        return 0;
    }    
    
}