
#ifndef __ADC_HEADER_H_
#define	__ADC_HEADER_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void ADC_init(uint8_t Fosc ,uint8_t channel, uint8_t int_on, uint8_t left_or_right);
void start_conversion (void);        //Obtiene el valor ADC del canal ya configurado
uint8_t done_conversion (void);

#endif	/* XC_HEADER_TEMPLATE_H */

