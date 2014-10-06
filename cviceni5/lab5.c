#define _ADDED_C_LIB 1
#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "led.h"
#include "display.h"
#include <p24fxxxx.h>
#include <math.h>
#include <string.h>
#define LED_R 1
#define LED_G 2
#define LED_B 3

int freq;

void printint(int i, int row, int col){
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[7];
     int cx;
     cx = snprintf (buffer, 7, "%d", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}


void __attribute__((interrupt, auto_psv)) _T3Interrupt() {
    T2CONbits.TON = 0;
    T3CONbits.TON = 0;
    freq = TMR2;

    led_on(3);

    TMR2 = 0x0000;
    TMR3 = 0x0000;
    T2CONbits.TON = 1;
    T3CONbits.TON = 1;
    IFS0bits.T3IF = 0; 
}

void initial () {
    freq = 0;
    T2CON = 0b0000000000000010;
    T3CON = 0b0000000000100000;    
    RPINR3bits.T2CKR =17;
    TMR2 = 0;
    TMR3 = 0;
    PR3 = 0x00FA;
    PR2 = 0xFFFF;
    IPC2bits.T3IP = 7;
	IFS0bits.T3IF = 0;	
	IEC0bits.T3IE = 1;
}

int main() {
    float fr = 156000;
    led_init();
    disp_init();
    generator_init();
    generator_run(fr);
    initial();
    T2CONbits.TON = 1;
    T3CONbits.TON = 1; 

    while(1) {
       if (freq>0) {
                printint(freq, 8, 0);
       }
    }
    return 0;            
                  
}