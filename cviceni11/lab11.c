#define _ADDED_C_LIB 1
#include <stdio.h>
#include <stdlib.h>
#include "pl2303.h"
#include "led.h"
#include "display.h"
#include "delay.h"
#include <p24fxxxx.h>
#include <math.h>
#include <string.h>
#define LED_R 1
#define LED_G 2
#define LED_B 3


int immediateValue = 0;

void configure(){
	OC1CON1.bits = 0x0007;
	OC1CON2.bits = 0x0001;
	OC2CON1.bits = 0x0007;
	OC2CON2.bits = 0x0002;	
	OC3CON1.bits = 0x0007;
	OC3CON2.bits = 0x0003;
	T2CON &= ~(1<<4);
	T2CON &= ~(1<<5);
	PR2 = 0x0FFF;
	OC1RS = 0x0FFF;
	OC2RS = 0x0FFF;
	OC3RS = 0x0FFF;
	OC1R = 0x0FFF;
	OC2R = 0x0FFF;
	OC3R = 0x0FFF;
	RPOR10bits.RP21R = 18; // assign to OC1
	RPOR9bits.RP19R = 19; // assign to OC2
	RPOR13bits.RP26R = 20; // assign to OC3
}

void conf_touch() {
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
	configure();
	conf_touch();    
	int led;
	while(1)
		{
		led = touch_wait();
		switch led
			case 1 // zvysit R
			case 2 // zvysit G
			case 3 // zvysit B
		}
	
    

return 0;
}