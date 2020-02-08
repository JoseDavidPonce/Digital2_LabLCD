/* 
 * File:  Header libreria 8bits LCD 
 * Author: José David Ponce
 * Carné: 18187
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __LCD_8BITS_H_
#define	__LCD_8BITS_H_

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#ifndef PORTBbits.RB0 
#define D0 PORTBbits.RB0
#endif

#ifndef PORTBbits.RB1
#define D1 PORTBbits.RB1
#endif

#ifndef PORTBbits.RB2 
#define D2 PORTBbits.RB2
#endif

#ifndef PORTBbits.RB3 
#define D3 PORTBbits.RB3
#endif

#ifndef PORTBbits.RB4 
#define D4 PORTBbits.RB4
#endif

#ifndef PORTBbits.RB5 
#define D5 PORTBbits.RB5
#endif

#ifndef PORTBbits.RB6 
#define D6 PORTBbits.RB6
#endif

#ifndef PORTBbits.RB7 
#define D7 PORTBbits.RB7
#endif

#ifndef PORTDbits.RD7 
#define RS PORTDbits.RD7
#endif

#ifndef PORTDbits.RD6 
#define RW PORTDbits.RD6
#endif

#endif	/* XC_HEADER_TEMPLATE_H */

