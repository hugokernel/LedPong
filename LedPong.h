
//#include <avr/pgmspace.h>


#include <avr/signal.h>
#include <avr/interrupt.h>

//#define FCPU 16000000UL
#include <util/delay.h>

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/sleep.h>  
//#include <avr/eeprom.h> 
#include <string.h>
#include <stdlib.h>



unsigned char map_x[][2] = {
    { &PORTA, 128 }, { &PORTA, 64 }, { &PORTA, 32 }, { &PORTA, 16 }, { &PORTA, 8 }, { &PORTA, 4 }, { &PORTA, 1 }, { &PORTA, 2 }
};

unsigned char map_y[][2] = {
    { &PORTD, 2 }, { &PORTD, 4 }, { &PORTC, 16 }, { &PORTC, 8 }, { &PORTC, 4 }, { &PORTC, 2 }, { &PORTC, 1 }, { &PORTD, 128 }
};


unsigned char buffer[8][8];

#define SBI(port, bit) (port) |= (1 << (bit))
#define CBI(port, bit) (port) &= ~(1 << (bit))

#define DBUGON  SBI(PORTD, 6)
#define DBUGOFF CBI(PORTD, 6)

#define POWER_MAX SBI(PORTB, 0); SBI(PORTB, 1); SBI(PORTB, 2); SBI(PORTB, 3);
#define POWER_MIN SBI(PORTB, 0); CBI(PORTB, 1); CBI(PORTB, 2); CBI(PORTB, 3);
