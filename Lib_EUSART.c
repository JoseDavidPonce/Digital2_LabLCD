#include <stdint.h>
#include <xc.h>
#include "EUSARTheader.h"

void EUSART_Init (uint8_t a, uint8_t b){
    //Configuracion para recepcion
    BAUDCTLbits.BRG16 = 0;
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    if (a==1){
        PIE1bits.RCIE = 1;
        PIR1bits.RCIF = 0;
        INTCONbits.GIE = 1;
        INTCONbits.PEIE = 1;
    }
    RCSTAbits.RX9D = 0;
    RCSTAbits.CREN = 1;
    
    //Configuracion para envio
    TXSTAbits.TXEN = 1;
    if(b==1){
        PIE1bits.TXIE = 1;
        PIR1bits.TXIF = 0;
        INTCONbits.GIE = 1;
        INTCONbits.PEIE = 1;
        
    }
    
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

