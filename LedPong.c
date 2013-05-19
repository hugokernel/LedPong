
//#define FCPU 16000000UL

#include "LedPong.h"



ISR(TIMER0_OVF_vect)
{
/*
    char x, y = 0;

    for (x = 2; x < 6; x++) {
        for (y = 0; y < 8; y++) {
            setPixel(x, y);
        }
    }

    TCNT0 = 0;
*/
    cli();
//    DBUGON;
    drawScreen();
    sei();
    //_delay_ms(10);
//    DBUGOFF;

//TCNT0 = 210;
    //TCNT0 = 200;
}

ISR(TIMER1_OVF_vect)
{
//    TCNT1H = speed_table[scroll_speed];
//    TCNT1L = 0;
    DBUGON;
    drawScreen();
    //TCNT1H = 238;
    //TCNT1L = 250;
    //delay_us(1000);

    DBUGOFF;
}

ISR(TIMER2_OVF_vect)
{

}

ISR(ADC_vect)
{

}

inline void clearScreen() {
    
    PORTA = 0;
    
    // TODO : mettre un AND
    PORTC = PORTD = 0;
}

inline void setPixel(unsigned char x, unsigned char y) {

    volatile uint8_t *port;

    clearScreen();

    port = map_x[x][0];
    *port = map_x[x][1];

    // TODO : mettre un AND
    port = map_y[y][0];
    *port = map_y[y][1];
}

inline void setLine(unsigned char y, char value) {

    volatile uint8_t *port;
    unsigned char out = 0;

    clearScreen();

    // TODO : mettre un AND
    port = map_y[y][0];
    *port = map_y[y][1];

    for (char x = 0; x < 8; x++) {
        if (value & (1 << x)) {
            out |= map_x[x][1];
        }
    }

    PORTA = out;
}

inline void drawScreen() {

    unsigned char x, y, value = 0;

    for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
            
            value = buffer[x][y];

            if (value) {
            /*
                switch (value) {
                    case 0: PORTB = 1; break;
                    case 1: PORTB = 2; break;
                    case 2: PORTB = 4; break;
                    case 3: PORTB = 8; break;
                }
*/
                PORTB = value;
                setPixel(x, y);
            } else {
                __asm("nop");
                __asm("nop");
                __asm("nop");
                __asm("nop");
                __asm("nop");
                __asm("nop");
                clearScreen();
            }

            _delay_us(400);
            PORTB = 0;
        }
    }
}



int main(void) {

    char a, t, x, y = 0;

/*
    // Timer 0 configuration : Print message
    TIMSK |= (1<<TOIE0);
    TCCR0 = ((1<<CS02) | (0<<CS01) | (1<<CS00));
    TCCR0 = 0;
    TCNT0 = 0;
*/
    // Timer 1 configuration : Scroll message
    TIMSK |= (1<<TOIE1);
    TCCR1A = 0;
    TCCR1B |= ((0<<CS12) | (1<<CS11) | (0<<CS10));
//    TCCR1C  = 0;
    TCNT1 = 0;
/*
    // Timer 2 configuration
    TIMSK2 |= 0;
    TCCR2A = 0;
    TCCR2B |= ((1<<CS22) | (1<<CS21) | (1<<CS20));
    TCNT2 = 0;
*/

//    USART_Init();
//    stdout = &mystdout;


    DDRA = 255;
    DDRB = 255;
    DDRC = 255;
    DDRD = 255;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;

    cli();

/*
    while(1) {
        DBUGON;
        _delay_ms(1);
        DBUGOFF;
        _delay_ms(1);
    }
*/


    t = 0;
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            buffer[y][x] = 255;
            continue;
            buffer[x][y] = rand() / (RAND_MAX / 254 + 1);
            //buffer[y][x] = t;
            //t = t + 1;
            continue;
            if (t % 2) {
                buffer[y][x] = 0;
            } else {
                buffer[y][x] = 200;
            }
            t++;
        }
    }

/*
    POWER_MAX;
    //POWER_MIN;
    while (1) {
        for (y = 0; y < 8; y++) {
            setLine(y, 0b111111111);
            _delay_ms(200);
            //_delay_us(250);
        }
    }
*/
    POWER_MAX;
    sei();
    while (1);

    while (1) {
        drawScreen();
        continue;
        for (x = 0; x < 8; x++) {
            clearScreen();
            //_delay_us(50);
            //DBUGON;
            setPixel(x, 0);
            PORTB = 255;
            _delay_us(300);
            //DBUGOFF;
        }
    }

/*
    while (1) {
        PORTA = 0;
        PORTB = a;
        setPixel(2, 0);
        for (t = 0; t < 200; t++) {
            _delay_ms(255);
        }

        a++;
        if (a > 8) {
            a = 0;
        }
    }
    */
/*
PORTB = 0;
    while (1) {
        setLine(a, 255);
        _delay_ms(20);
    
        a++;
        if (a > 7)
            a = 0;
    }
*/
    //goto paf;

    sei();
    //goto line;
    //while(1);
    //PORTB = 8;
    //setPixel(2, 0);
    while (1);

    while (1) {

        //cli();
        for (y = 0; y < 8; y++) {
            for (x = 0; x < 8; x++) {
                buffer[y][x] = a;
            }
        }

        //sei();
        a++;
        if (a > 8) {
            a = 0;
        }

        for (t = 0; t < 15; t++) {
            _delay_ms(255);
        }
    }

paf:
    cli();

//    PORTB = 0;

    //PB1 = 0;
    //PD6 = 0;

/*
    DDRA = 128;
    DDRD = 128;
    PORTA = 128;
    PORTD = 128;
*/
    //DDRA = 0;
    PORTB = 254;
    setLine(0, 255);
    //PORTB = 255;
    //setPixel(5, 0);
    //setPixel(6, 0);
//    while(1);
    
    //setLine(0, 255);
    //setPixel(5, 0);
//    PORTB = 255;
//    PORTA = 255;
    
//    while (1);

    while (1) {
        for (y = 0; y < 7; y++) {
            if (y == 0) {
                clearScreen();
                for (t = 0; t < 100; t++) {
                    _delay_ms(255);
                }
                continue;
            }

            setPixel(2, 0);
            PORTB = y;
            for (t = 0; t < 30; t++) {
                _delay_ms(255);
            }
        }
    }

line:
    cli();
    while (1) {
        for (y = 0; y < 8; y++) {
            setLine(y, 255);

            for (t = 0; t < 255; t++) {
                _delay_ms(200);
            }
        }
    }
}

