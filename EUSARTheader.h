
#ifndef __EUSARTHEADER_H_
#define	__EUSARTHEADER_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void EUSART_Init(uint8_t a, uint8_t b);
uint8_t CHECK_FOR_ERRORS (void);
void SEND_STRING(char *a);

#endif	/* XC_HEADER_TEMPLATE_H */

