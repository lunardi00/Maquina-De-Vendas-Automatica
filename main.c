#include <pic18f4520.h>
#include "pic18f4520.h"
#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "keypad.h"
#include "ssd.h"
#include "io.h"
#include "led.h"
#include "atraso.h"
#include "pwm.h"

#define L0 0x80
#define L1 0xC0
#define CLR 0x01
#define ON 0x0F

void selecionaProduto(int *produto);
void mostraPreco(int produto);
void produtoLed(int produto);

void main(void) {
    int produto = 0;
    //config inicial:
    configuraLed();
    for (;;) {

        // liga todos os 4 ultimos leds de PORTB
        for (int i = 4; i < 8; i++) {
            bitSet(PORTB, i);
        }

        // reseta valor de produto
        produto = 0;

        //menu inicial e opções
        lcdInit();
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint("Menu Inicial    ");
        atraso_ms(3000);
        char p1[16] = "1 - Doritos";
        char p2[16] = "2 - Kit Kat";
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint(p1);
        lcdCommand(L1);
        lcdPrint(p2);
        atraso_ms(2000);
        char p3[16] = "3 - Fanta";
        char p4[16] = "4 - Mentos";
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint(p3);
        lcdCommand(L1);
        lcdPrint(p4);
        atraso_ms(2000);
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint("Digite o codigo");
        lcdCommand(L1);
        lcdPrint("Do produto     ");

        while (produto == 0) {
            //permite selecao e mostra os preços nos displays
            selecionaProduto(&produto);
        }

        //apaga todos os displays
        bitClr(PORTA, 5);
        bitClr(PORTA, 4);
        bitClr(PORTA, 3);
        bitClr(PORTA, 2);

        //apaga o led referente ao produto selecionado
        produtoLed(produto);

        //processa o pedido e pede pra aguardar no LCD
        lcdInit();
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint("Aguarde...      ");
        atraso_ms(2000);

        // mostra mnsgm no lcd da remoção do produto da gondola
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint("Removendo       ");
        lcdCommand(L1);
        lcdPrint("O produto...    ");

        // liga o cooler, representando a maquina girando pra cair o produto
        pwmInit();
        pwmSet1(80);
        atraso_ms(5000);
        pwmSet1(0);

        //finaliza pedindo a retirada do produto no LCD
        lcdCommand(CLR);
        lcdCommand(L0);
        lcdPrint("Retire seu      ");
        lcdCommand(L1);
        lcdPrint("Produto!        ");
        atraso_ms(6000);
    }
}

void selecionaProduto(int *produto) {
    int aux;
    kpInit();
    int tecla;
    kpDebounce();
    if (kpRead() != tecla) {
        tecla = kpRead();
        if (bitTst(tecla, 3)) { //botao 1
            aux = 1;
            lcdInit();
            char p1[16] = "Doritos";
            char p2[16] = "Confirme com *";
            lcdCommand(CLR);
            lcdCommand(L0);
            lcdPrint(p1);
            lcdCommand(L1);
            lcdPrint(p2);
        } else if (bitTst(tecla, 7)) { //botao 2
            aux = 2;
            lcdInit();
            char p1[16] = "Kit Kat";
            char p2[16] = "Confirme com *";
            lcdCommand(CLR);
            lcdCommand(L0);
            lcdPrint(p1);
            lcdCommand(L1);
            lcdPrint(p2);
        } else if (bitTst(tecla, 11)) { //botao 3
            aux = 3;
            lcdInit();
            char p1[16] = "Fanta";
            char p2[16] = "Confirme com *";
            lcdCommand(CLR);
            lcdCommand(L0);
            lcdPrint(p1);
            lcdCommand(L1);
            lcdPrint(p2);
        } else if (bitTst(tecla, 2)) { //botao 4
            aux = 4;
            lcdInit();
            char p1[16] = "Mentos";
            char p2[16] = "Confirme com *";
            lcdCommand(CLR);
            lcdCommand(L0);
            lcdPrint(p1);
            lcdCommand(L1);
            lcdPrint(p2);
        } else if (bitTst(tecla, 1)) { //botao 1
            char p1[16] = "1 - Doritos";
            char p2[16] = "2 - Kit Kat";
            lcdInit();
            lcdCommand(CLR);
            lcdCommand(L0);
            lcdPrint(p1);
            lcdCommand(L1);
            lcdPrint(p2);
        } else if (bitTst(tecla, 5)) { //botao 8
            char p1[16] = "3 - Fanta";
            char p2[16] = "4 - Mentos";
            lcdInit();
            lcdCommand(CLR);
            lcdCommand(L0);
            lcdPrint(p1);
            lcdCommand(L1);
            lcdPrint(p2);
        }
        if (bitTst(tecla, 0)) { //botao *
            *produto = aux;
        }
    }
    mostraPreco(aux);
}

void mostraPreco(int aux) {
    ssdInit();
    int tempo;
    switch (aux) {
        case 0:
            ssdDigit(0, 0);
            ssdDigit(0, 1);
            ssdDigit(0, 2);
            ssdDigit(0, 3);
            break;
        case 1:
            ssdDigit(0, 0);
            ssdDigit(6, 1);
            ssdDigit(9, 2);
            ssdDigit(9, 3);
            break;
        case 2:
            ssdDigit(0, 0);
            ssdDigit(7, 1);
            ssdDigit(9, 2);
            ssdDigit(9, 3);
            break;
        case 3:
            ssdDigit(0, 0);
            ssdDigit(8, 1);
            ssdDigit(9, 2);
            ssdDigit(9, 3);
            break;
        case 4:
            ssdDigit(0, 0);
            ssdDigit(9, 1);
            ssdDigit(9, 2);
            ssdDigit(9, 3);
            break;
    }
    ssdUpdate();
    for (tempo = 0; tempo < 700; tempo++);
}

void produtoLed(int produto) {
    int led;
    if (produto == 1) led = '4';
    if (produto == 2) led = '5';
    if (produto == 3) led = '6';
    if (produto == 4) led = '7';
    desligaLed(led);
}
