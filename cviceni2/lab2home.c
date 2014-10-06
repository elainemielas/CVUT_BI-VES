#define _ADDED_C_LIB 1
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include <math.h>
#include <string.h>


void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}

void line(int x1, int y1, int x2, int y2) {
     
     disp_init();
     if (abs(y2 - y1) > abs(x2 - x1)) {
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
         if (abs(y2 - y1) > abs(x2 - x1)) put_pixel(y,x,0); 
             else put_pixel(x,y,0);
         error = error - deltay;
         if (error < 0) {
             y = y + ystep;
             error = error + deltax; }}
}


void poly(int n, int* coord) {

     // coord je pole souradnic bodu x0, y0, x1, y1...
     disp_init();
     int i;
     for (i=0; i<2n-1; i++) {
         line(coord[i], coord[i+1], coord[i+2], coord[i+3]);
         i+=2;
     }
}


void printchar(char c, int x, int y){
     disp_init();
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     i = atoi(c);
     char buffer[4];
     int cx;
     cx = snprintf (buffer, 4, "%d", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}


void printint(int i, int row, int col){
     disp_init();
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[7];
     int cx;
     cx = snprintf (buffer, 7, "%d", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void printinthex(int i, int row, int col){
     disp_init();
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char str[7]; 
     char *p;
     p=itoa(i, str, 16); 
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(p)) printf("chyba");
        else disp_line(p);
}

void printlong(long i, int row, int col){
     disp_init();
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[12];
     int cx;
     cx = snprintf (buffer, 12, "%l", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void printlonghex(long i, int row, int col){
     disp_init();
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[10];
     int cx;
     cx = snprintf (buffer, 10, "0x%lX", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

void printfloat(float i, int row, int col){
     disp_init();
     disp_clear();
     if (row<=TERM_HEIGHT && col<=TERM_WIDTH) disp_at(row, col);
        else printf("chyba"); 
     char buffer[50];
     int cx;
     cx = snprintf (buffer, 50, "%f", i);
     if (row==TERM_HEIGHT && (TERM_WIDTH-col)<strlen(buffer)) printf("chyba");
        else disp_line(buffer);
}

int main() {
int row, col;
printf("zadejte stred balonku");
scanf("%d, %d" &row, &col);
if (row>128 || col>64) printf ("chyba");
else {
     disp_init();
     disp_clear();
     draw_elipse(row,col,10,24);
     draw_rect (0,0,8,8);
     draw_line(4,8,(row-12), col);
     int i;
     for (i=0; i<15; i++) {
         m=rand()%128; 
         n=rand()%64; 
         put_pixel(m,n,1);
	     }
     disp_at(8,0);
     char str[10];
     str = "CHEERS!"
     disp_str(str);
     }
}