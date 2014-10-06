#define _ADDED_C_LIB 1
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include <math.h>
#include <string.h>
#include "delay.h"


void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}

void line(int x1, int y1, int x2, int y2) {
     int perem = 0;
     if (abs(y2 - y1) > abs(x2 - x1)) {
         perem = 1;
         swap(&x1, &y1);
         swap(&x2, &y2);}
     if (x1 > x2) { 
         swap(&x1, &x2);
         swap(&y1, &y2);}
     int deltax = x2 - x1;
     int deltay = abs(y2 - y1);
     int error = deltax / 2;
     int ystep;
     int y = y1;
     if (y1 < y2) ystep = 1; 
         else ystep = -1;
     int x;
     for (x = x1; x < x2; x++){
         if (perem) put_pixel(y,x,1); 
             else put_pixel(x,y,1);
         error = error - deltay;
         if (error < 0) {
             y = y + ystep;
             error = error + deltax; }}
}


void poly(int n, int* coord) {

     // coord je pole souradnic bodu x0, y0, x1, y1...
     int i;
     for (i=0; i<(2*n-2); i++) {
         line(coord[i], coord[i+1], coord[i+2], coord[i+3]);
         i++;
     }
     line(coord[0],coord[1],coord[2*n-2],coord[2*n-1]);
}

void printchar(char c, int row, int col){

     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     //int i = atoi(c);
     char buffer[4];
     int cx;
     cx = snprintf (buffer, 4, "%c", c);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
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

void printinthex(int i, int row, int col){

     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[7]; 
     int cx;
     cx = snprintf (buffer, 7, "0x%dX", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void printlong(long i, int row, int col){

     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[12];
     int cx;
     cx = snprintf (buffer, 12, "%li", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void printlonghex(long i, int row, int col){

     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[10];
     int cx;
     cx = snprintf (buffer, 10, "0x%lX", i);
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

int main() {
    disp_init();
    disp_clear();

    int val=30;
    int co[val];
    int i;
    for (i=0; i<val-1; i+=2) {
         co[i] = rand() % 119;
         co[i+1]= rand() % 38; }
    //co[0]=0; co[1]=0; co[2]=56; co[3]=25; co[4]=28; co[5]=39; 
    poly(3, co);
    delay_loop_ms(100);
    disp_clear();
    for (i=0; i<val-1; i+=2) {
         co[i] = rand() % 120;
         co[i+1]= rand() % 54; }
    poly(7, co);
    //delay_loop_10us();
    //printchar('4', 1, 1);
    //printint(87, 9, 10);
    //printinthex(96, 15, 12);
    //printlong(456746854, 28, 15);
    //printlonghex(54654521, 58, 6);
    //printfloat(15.11, 76, 36);
    delay_loop_ms(100);
    disp_clear();
    for (i=0; i<val-1; i+=2) {
         co[i] = rand() % 112;
         co[i+1]= rand() % 48; }
    poly(8, co);
    delay_loop_ms(100);
    disp_clear();
    return 1;

}


