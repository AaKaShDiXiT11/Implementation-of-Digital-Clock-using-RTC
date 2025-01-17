#include<LPC21XX.H>
#include "header.h"

void lcd_data(u8 data){
u32 temp;
//higher nibble
IOCLR1=0XFE<<16;
temp=(data & 0XF0)<<16;
IOSET1=temp;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

//LOWER NIBBLE
IOCLR1=0XFE<<16;
temp=(data & 0X0F)<<20;
IOSET1=temp;

IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_cmd(u8 cmd){
u32 temp;
IOCLR1=0XFE<<16;
temp=(cmd & 0XF0)<<16;
IOSET1=temp;

IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;

//LOWER NIBBLE

IOCLR1=0XFE<<16;
temp=(cmd & 0X0F)<<20;
IOSET1=temp;
 
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1 = 1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_init(){
IODIR1=0XFE <<16;
IOCLR1=1<<19;
PINSEL2=0X0;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0e);
lcd_cmd(0x01);
}

void lcd_string(char *ptr){
while(*ptr){
lcd_data(*ptr);
ptr++;
}
}
//unsigned char a[10]={0x0,0x06,0x0f,0x0f,0x0f,0x07,0x03,0x01};
unsigned char a[10]={0x07,0x05,0x07,0x16,0x1f,0x1e,0x0e,0x04};
void lcd_cgram(){
int i;
lcd_cmd(0x50);
for(i=0;i<=7;i++){
lcd_data(a[i]);
}
}

//unsigned char b[10]={0x0,0x0c,0x1e,0x1e,0x1e,0x1c,0x18,0x10};

void lcd_cgram1(unsigned char *b,unsigned char cmd){
int i;
lcd_cmd(cmd);
for(i=0;i<=7;i++){
lcd_data(b[i]);
}
}

void lcd_int(int num){
int n[10],i;
if(num==0){
lcd_data('0');
}
if(num<0){
lcd_data('-');
num=-num;			  
}
i=0;
while(num>0){
n[i]=num%10+48;
num=num/10;
i++;
}

for(i=i-1;i>=0;i--){
lcd_data(n[i]);
}
}
