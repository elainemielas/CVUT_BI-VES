#define _ADDED_C_LIB 1
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "delay.h"
#include <p24fxxxx.h>
#include <math.h>
#include <string.h>

int sync = 0;
int hodni;
int x = 0;
  

// Konfigurace pro hodinový kmitoèet 16MHz
// a další nutná implicitní nastavení
_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF \
    & FWDTEN_OFF & ICS_PGx2)
_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF \
    & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)

void printfloat(double i, int row, int col){
     
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[50];
     int cx;
     cx = snprintf (buffer, 50, "%f", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void confAD() {
//AD1CON1bits.SSRC = 0; // program mode
//AD1CON1bits.SSRC = 7;
AD1CON1bits.SSRC = 2; // timer 3
AD1CON1bits.FORM = 0; // int
//AD1CON1bits.ASAM = 0;
AD1CON1bits.ASAM = 1;
AD1PCFGLbits.PCFG0 = 0; //AN0 analog
AD1CON2bits.VCFG = 0;
AD1CON2bits.CSCNA = 0;
AD1CON2bits.SMPI = 0;
AD1CON2bits.BUFM = 0;
AD1CON2bits.ALTS = 0;
AD1CON3bits.SAMC = 10; 
AD1CON3bits.ADCS = 1; // 62,5 * 2 > 75
AD1CHSbits.CH0SB = 0; // AN0
AD1CON1bits.ADON = 1;
PR3 = 2500;
T3CONbits.TCKPS = 0b10;
T3CONbits.TON = 1;

IPC3bits.AD1IP = 7;
IEC0bits.AD1IE = 1;
IFS0bits.AD1IF = 0;
}

extern void set_color(int c);

void test_sync() {
	
	while(sync == 1){
    
		double hodnf;
		int hodnd;
		hodnf = (3,3 * (double)hodni/ (double)1024);
		
		printfloat(hodnf,62,2);
		hodnd = ((int)3,3 * hodni/ 64);
        disp_home();
		put_pixel(x,hodnd,1);
        x++;
		if (x == 128) { x = 0; disp_clear(); }
        
		sync = 0;
		}
}

void __attribute__((interrupt, auto_psv)) _ADC1Interrupt() {
hodni = ADC1BUF0;
sync = 1;
IFS0bits.AD1IF = 0;
}

int main() 
{
  confAD();
  disp_init();
  while(1)
  test_sync();
  //while(1) {AD1CON1bits.SAMP = 1;}
  //while (1) {
   //   T3CONbits.TON = 1;
   //   AD1CON1bits.SAMP = 1;
   //   }
  //delay_loop_ms(1);
  //AD1CON1bits.SAMP = 0;
  //while (AD1CON1bits.DONE == 0);
	
  //while (1) {}
 return 0;
}