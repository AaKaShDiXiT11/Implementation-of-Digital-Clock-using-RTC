	 #include"header.h"
	 #include"rtcHeader.h"
	 #pragma pack(1)
/*




*/
struct timer {
  u8 hr:7;
  u8 min;
  u8 sec;
  u8 amPm:1;
  u8 zone:1;
  u8 years;
  u8 Tyears;
  u8 month:5;
  u8 date:6;
  u8 day:3;
  }t;


u8 flg;

main(){

       uart0_init(9600);
	   lcd_init();
	   i2c_init();
	   config_vic_for_eint0();
	   config_eint0();
	// i2c_byt_wrt_frm(0xd0,0x0,0x54);
	// i2c_byt_wrt_frm(0xd0,0x1,0x59);
	 //i2c_byt_wrt_frm(0xd0,0x2,0x23);

	   uart0_tx_str("PROG: START \r\n");
	
		lcd_cmd(0x01);
    while(1){
		/*
		 if(flg){
		 while(1){
		 if(SW1==0){
		   while(SW1==0);
		   cmd++;
		   if(cmd==4)
		   cmd=1;
					  switch(cmd){
				 case 1: lcd_str("settings");break;
				 case 2: lcd_str("stopWatch");break;	//
				 case 3: lcd_str("alarm");break;
				 case 4: lcd_str("return");break;
				 }

				 if(SW2==0){
				 while(SW2==0);
				 break;		 
				 }
		      }
			 
		   }

		 
		 switch(cmd){
		 case 1: setting();break;
		 case 2: stopWatch();break;
		 case 3: alarm();break;
		 }
		 
		  flg=0;
		 
		 
		 }





*/





		if(flg){
			lcd_cmd(0x01);
	   set_sec();
	   set_min();
	   set_hr();
	   set_years();
	   set_months();
	   set_date();
	   set_day();
		  	lcd_cmd(0x01);
	   flg=0;
		}





       t.sec= i2c_byt_red_frm(0xd0,0x0);
	   t.min= i2c_byt_red_frm(0xd0,0x1);
	   t.hr= i2c_byt_red_frm(0xd0,0x2);
	   t.amPm= (t.hr>>5)&1;
	   t.zone= (t.hr>>6)&1;
	   if(t.zone){
	   t.hr=t.hr&0x1f;
	   }
	   t.years=i2c_byt_red_frm(0xd0,0x6);;
       //t.Tyears= t.years==0?t.Tyears++:20;
       t.month=i2c_byt_red_frm(0xd0,0x5);
       t.date=i2c_byt_red_frm(0xd0,0x4);
       t.day=i2c_byt_red_frm(0xd0,0x3);

        /*uart0_tx((h/0x10)+48);
	   uart0_tx((h%0x10)+48); 
	   uart0_tx(':');
	   uart0_tx((m/0x10)+48);
	   uart0_tx((m%0x10)+48);
	   uart0_tx(':');
	   uart0_tx((s/0x10)+48);
	   uart0_tx((s%0x10)+48);
	   	uart0_tx_str("\r\n");*/
	  
	  lcd_cmd(0x80);
	  
	   lcd_data((t.hr/0x10)+48);
	   lcd_data((t.hr%0x10)+48); 
	   lcd_data(':');
	   lcd_data((t.min/0x10)+48);
	   lcd_data((t.min%0x10)+48);
	   lcd_data(':');
	   lcd_data((t.sec/0x10)+48);
	   lcd_data((t.sec%0x10)+48); 
	   //////time zone
	   lcd_cmd(0x89);
	   if(t.zone){
	   if(t.amPm){
	   lcd_string("PM");
	   }else{
			lcd_string("AM");
	   }
	   lcd_cmd(0xc0);
	   lcd_data((t.date/0x10)+48);
	   lcd_data((t.date%0x10)+48);
	   lcd_data('/');
	    lcd_data((t.month/0x10)+48);
	   lcd_data((t.month%0x10)+48);
	   lcd_data('/');
	   lcd_string("20");
	    lcd_data((t.years/0x10)+48);
	   lcd_data((t.years%0x10)+48);
	   
		lcd_cmd(0xcb);
	   	switch(t.day){
		 case 1: lcd_string("SUN");break;
		 case 2: lcd_string("MON");break;
		 case 3: lcd_string("TUE");break;
		 case 4: lcd_string("WED");break;
		 case 5: lcd_string("THU");break;
		 case 6: lcd_string("FRI");break;
		 case 7: lcd_string("SAT");break;
		}
	}
 }
}
