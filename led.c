#include "led.h"
#include "config.h"
#include "bits.h"
#include <pic18f4520.h>

int bit = 0;

void configuraLed() { //func config
    TRISB = 0x00;
    PORTB = 0xF0;
}

int converteChar(char num) { //func converte p int
    switch (num) {
        case '0':
            bit = 0;
            return bit;
            break;

        case '1':
            bit = 1;
            return bit;
            break;

        case '2':
            bit = 2;
            return bit;
            break;

        case '3':
            bit = 3;
            return bit;
            break;

        case '4':
            bit = 4;
            return bit;
            break;

        case '5':
            bit = 5;
            return bit;
            break;

        case '6':
            bit = 6;
            return bit;
            break;

        case '7':
            bit = 7;
            return bit;
            break;
    }
}

void ligaLed(char num) { //func liga led
    converteChar(num);
    bitSet(PORTB, bit);
}

void desligaLed(char num) { //func liga led
    converteChar(num);
    bitClr(PORTB, bit);
}


