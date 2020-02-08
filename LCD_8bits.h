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

#ifndef RB0 
#define D0 RB0
#endif

#ifndef RB1
#define D1 RB1
#endif

#ifndef RB2 
#define D2 RB2
#endif

#ifndef RB3 
#define D3 RB3
#endif

#ifndef RB4 
#define D4 RB4
#endif

#ifndef RB5 
#define D5 RB5
#endif

#ifndef RB6 
#define D6 RB6
#endif

#ifndef RB7
#define D7 RB7
#endif

#ifndef RD7 
#define RS RD7
#endif

#ifndef RD6 
#define RW RD6
#endif

#endif	/* XC_HEADER_TEMPLATE_H */

