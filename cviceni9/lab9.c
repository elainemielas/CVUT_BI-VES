#define _ADDED_C_LIB 1
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "cpu.h"
#include "delay.h"
#include "pl2303.h"
#include <p24fxxxx.h>
#include <math.h>
#include <string.h>

int immediateValue = 0;

void init(){
	//setup CTMU
	 //CTMUCON
	CTMUCONbits.CTMUEN = 0; //make sure CTMU is disabled
	CTMUCONbits.CTMUSIDL = 0; //CTMU continues to run in idle mode
	CTMUCONbits.TGEN = 0; //disable edge delay generation mode of the CTMU
	CTMUCONbits.EDGEN = 0; //edges are blocked
	CTMUCONbits.EDGSEQEN = 0; //edge sequence not needed
	CTMUCONbits.IDISSEN = 0; //Do not ground the current source
	CTMUCONbits.CTTRIG = 0; //Trigger Output is disabled
	CTMUCONbits.EDG2POL = 0;
	CTMUCONbits.EDG2SEL = 0x3; //Edge2 Src = OC1 (don’t care)
	CTMUCONbits.EDG1POL = 1;
	CTMUCONbits.EDG1SEL = 0x3; //Edge1 Src = Timer1 (don’t care)
	//CTMUICON
	CTMUICON = 0x300; //55uA
	CTMUICONbits.ITRIM = 0; //Nominal - No Adjustment
	//setup A/D converter
	AD1PCFGL = 0x0000;
	AD1CON1 = 0x0000;
	AD1CHS = 0x0000; //select the analog channel 0
	AD1CSSL=0x0000;
	AD1CON1bits.FORM = 0x0; //Unsigned fractional format
	AD1CON3 = 0x0000; //bits.ADRC=0;
	AD1CON2 = 0x0000;
	AD1CON1bits.ADON = 1; //Turn On A/D
	CTMUCONbits.CTMUEN = 1; //Enable CTMU
}
 

int touch_getkey(int i, int loopCount){
	    int count; 
		//Read CTMU (Get the raw sensor reading)
		AD1PCFGL= 0xFFFF; //set all A/D channels to digital I/O pins
		TRISB = 0x0000;
		LATB = 0x0000;
		PORTB = 0x0000; //set all channels to logical 0 outputs
		Nop(); Nop(); Nop(); Nop();
		Nop(); Nop(); Nop(); Nop();
		//Wait for charge to drain
		TRISB |= (1<<i); //set selected channel to input
		AD1PCFGL &= ~(1<<i) ; //set selected channel to analog A/D input
		Nop(); Nop(); Nop(); Nop();
		Nop(); Nop(); Nop(); Nop();
		//wait for A/D to connect to channel
		AD1CHS = i; //select A/D channel
		CTMUCONbits.IDISSEN = 1; //Drain any charge on the A/D circuit
		Nop(); Nop(); Nop(); Nop(); Nop();
		//Wait for charge to drain
		CTMUCONbits.IDISSEN = 0; //Stop discharge of A/D circuit
		IFS0bits.AD1IF = 0; //Make sure A/D interrupt flag = 0
		AD1CON1bits.SAMP = 1; //Manually start sampling
		CTMUCONbits.EDG2STAT = 0; // Make sure edge2 is 0
		CTMUCONbits.EDG1STAT = 1; // Set edge1 - Start Charge
		for (count = 0; count < loopCount; count++); // Delay for CTMU charge time
		CTMUCONbits.EDG1STAT = 0; //Clear edge1 - Stop Charge
		IFS0bits.AD1IF = 0;
		AD1CON1bits.SAMP = 0; //Clear SAMP bit to begin manual A/D conversion
		while(!IFS0bits.AD1IF); //Wait for the A/D conversion to finish
		immediateValue = ADC1BUF0; //Read the value from the A/D conversion
		AD1CON1bits.SAMP = 0;
		IFS0bits.AD1IF = 0;
		AD1CON1bits.DONE = 0; //Make sure A/D bits are cleared
		//End of CTMU read
        return immediateValue;
}


void printint(int i, int row, int col){

     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[7];
     int cx;
     cx = snprintf (buffer, 7, "%d", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void printfloat(double i, int row, int col){

     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[50];
     int cx;
     cx = snprintf (buffer, 50, "%f", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
} 

int touch_readkey(){
	int i, count, loopCount = 3;
   		 for(i=8; i<=12; i++) {
            if( touch_getkey(i, loopCount) < 300 ) return i;
			
			}
	return 0;
}

int touch_wait(){
	int i, count, loopCount = 3;

	while(1) 
	{  		 
	for(i=8; i<=12; i++) {
            if( touch_getkey(i, loopCount) < 300 ) return i;
			
			}
	}	
}

int main(){
    init();
	disp_init();
    printint(0, 50, 0);
    disp_home();
	while(1)
		{
		printfloat(touch_wait(), 50, 0);
		disp_home();
		}
	
    

return 0;
}