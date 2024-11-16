#include"header.h"

extern u8 tx;
u8 temp;
//extern u32 count2;

void UART0_handler(void) __irq{
int r =U0IIR;//iterrupt identification reg bit (123)
r=(r>>1)&7;
if(r==2){//recive data cheaking
 uart0_tx_str("\r\n state:");
//tx=uart0_rx(); //tx a data
temp=U0RBR;//recived data in rbr reg

  if((tx>>7)&1){
  uart0_tx_str("\r\n your device is on manual mode .");
  }else{
if(((temp>>1)&1)== (temp&1))//receiver logic 
  tx=temp;
  else
 tx=tx^temp;
  
//-------------------------------------

 
if(((tx)&1) ==1	){	//checking for the 1st bit
//IOCLR0=LED1;
  uart0_tx_str("\r\n LED 1:ON");
}
else{
//IOSET0=LED1;
    uart0_tx_str("\r\n LED 1:OFF");}


if(((tx>> 1 )&1) ==1){	  //checking for the 2nd bit
//OCLR0=LED2;
  uart0_tx_str("\r\n LED 2:ON");}
else	 {
//IOSET0=LED2;
  uart0_tx_str("\r\n LED 2:OFF");}
   




 }


//-------------------------------------
}

VICVectAddr=0;
}


void config_vic_for_uart0(void){
VICIntSelect=0;
VICVectCntl1= 6|(1<<5);//assign intr to virrq slots--> 5 bit => slot eneble 0-4 => int select
VICVectAddr1=(u32)UART0_handler;//typecast to 32bit (bus size)assigning addr to slot
VICIntEnable=(1<<6);//to enable uart intr
}


void config_uart0(void){
U0IER=1;//uart0 interrupt enable reg-->1=>enable RX intr
}
