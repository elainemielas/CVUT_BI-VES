#include <p24fxxxx.h>
//#include "delay.h"
#include "delayy.h"
// Konfigurace pro hodinový kmitoèet 16MHz
// a další nutná implicitní nastavení
_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF \
     & FWDTEN_OFF & ICS_PGx2)
_CONFIG2( 0xF7FF & IESO_OFF & FCKSM_CSDCMD & OSCIOFNC_OFF \
     & POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV3 & IOL1WAY_ON)

#define LED_R 1
#define LED_G 2
#define LED_B 4

void led(int led_id, int on) {
   if (on) {
      if (led_id == 1) {LATF  &= 0b0000000000000000;}
      else if (led_id == 2) {LATG  &= 0b0000000000000000;}
      else if (led_id == 4) {LATG  &= 0b0000000000000000;}
   }
   else {
      if (led_id == 1) {LATF  |= 0b0000000000110000;}
      else if (led_id == 2) {LATG  |= 0b0000001100000000;}
      else if (led_id == 4) {LATG  |= 0b0000000011000000;}
   }
}

void nic() {
      LATF  |= 0b0000000000110000;
      LATG  |= 0b0000001111000000;
}

led_delay_100us() {
   int i=0;
   nic();
   led(1,1);
   led(2,0);
   led(4,0);
   for(i=0; i<100; i++) delay_loop();
   nic(); 
   for(i=0; i<100; i++) delay_loop();
   led(1,1);
   led(2,1);
   led(4,0);
   for(i=0; i<100; i++) delay_loop();
   nic();  
   for(i=0; i<100; i++) delay_loop();
   led(1,0);
   led(2,1);
   led(4,0);
   for(i=0; i<100; i++) delay_loop();
   nic(); 
   for(i=0; i<100; i++) delay_loop();
   led(1,1);
   led(2,1);
   led(4,0);
   for(i=0; i<100; i++) delay_loop();
   nic();  
   for(i=0; i<100; i++) delay_loop();
   led(1,1);
   led(2,0);
   led(4,0);
   for(i=0; i<100; i++) delay_loop();
   nic(); 
   for(i=0; i<100; i++) delay_loop();
}
/*
led_delay_100ms() {
   nic();
   led(1,1);
   led(2,0);
   led(4,0);
   delay_loop_ms(2000);
   nic(); 
   delay_loop_ms(2000);
   led(1,1);
   led(2,1);
   led(4,0);
   delay_loop_ms(2000);
   nic();  
   delay_loop_ms(2000);
   led(1,0);
   led(2,1);
   led(4,0);
   delay_loop_ms(2000);
   nic(); 
   delay_loop_ms(2000);
   led(1,1);
   led(2,1);
   led(4,0);
   delay_loop_ms(2000);
   nic();  
   delay_loop_ms(2000);
   led(1,1);
   led(2,0);
   led(4,0);
   delay_loop_ms(2000);
   nic(); 
   delay_loop_ms(2000);
}
*/
int main (void) {
   TRISF &= 0b1111111111001111;
   TRISG &= 0b1111110000111111;
   ODCF  |= 0b0000000000110000;
   ODCG  |= 0b0000001111000000;
 
   led_delay_100us();
   return 0;
}