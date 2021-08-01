#include "stdio.h"
#include "lcd.h"

void print(char ch[16]) {
    int i;
    for(i=0;i<15;i++) {
        if(ch[i]=='\n') {
            ch[i] = ' ';
            lcdCommand(0xC0);
        }
        lcdData(ch[i]);
    }
}
