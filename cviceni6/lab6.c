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

unsigned static volatile int stary_cas, perioda;

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


void __attribute__((interrupt, auto_psv)) _INT1Interrupt() {
    T2CONbits.TON = 0;
    int novy_cas = TMR2;
	perioda = novy_cas - stary_cas;
	//stary_cas = novy_cas;	

    led_on(3);

    TMR2 = 0x0000;
    T2CONbits.TON = 1;
    IFS1bits.INT1IF = 0; 
}

void initial () {
    stary_cas = 0;
	perioda = 0;
    T2CON = 0b0000000000000000;
    RPINR0bits.INT1R =17;
    TMR2 = 0;
    PR2 = 0xFFFF;
	INTCON2bits.INT1EP = 0;
    IPC5bits.INT1IP = 7;
	IFS1bits.INT1IF = 0;	
	IEC1bits.INT1IE = 1;
}

int main() {
    float fr = 1200;
    led_init();
    disp_init();
    generator_init();
    generator_run(fr);
    initial();
    T2CONbits.TON = 1;
    
    while(1) {
       if (perioda>0) {
                printint(perioda, 8, 0);
       }
    }
    return 0;            
                  
}