#include<reg51.h>
#define LCD_DATA P2

 
void delay(void);
unsigned char key_in(void);
void lcd_out(unsigned char,unsigned char);

sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;

sbit R1=P3^0;
sbit R2=P3^1;
sbit R3=P3^2;
sbit R4=P3^3;
sbit C1=P3^4;
sbit C2=P3^5;
sbit C3=P3^6;
sbit C4=P3^7;
sbit LED=P1^7;

int LED_c=0;
int LED_D=0;

int d10s=0;
bit df=0;

unsigned char KEY;

void isr(void)interrupt 1{
	if(LED_c==LED_D){
		LED=~LED;
		LED_c=0;
	}else{
	  LED_c++;
		TR0=0;
	  TH0=0xFC;
	  TL0=0x66;
	  TR0=1;
		
	}
	
}
void isr1(void)interrupt 3{
	if(d10s==200){
		d10s=0;
		df=1;
		TR0=0;
		TR1=0;
		LED_c=0;
    LED_D=0;
		lcd_out(0,0x01);
    delay();
	}else{
	d10s++;
	TR1=0;
	TH1=0x4B;
	TL1=0xFD;
	TR1=1;
	}
	
}


int main()
{
	 LED=0;
	 TMOD =0x11;
	 TH0=0xFC;
	 TL0=0x66;
   TH1=0x4B;
	 TL1=0xFD;
	 IE=0x8A;
	
	 
   lcd_out(0,0x38);
   delay();
   lcd_out(0,0x0E);
   delay();
   lcd_out(0,0x01);
   delay();
   lcd_out(0,0x06);
   delay();
	 C1=1;C2=1;C3=1;C4=1;
	 while(1){
		 df=0;
		 KEY=key_in();
		 if(KEY!='n'){
			 lcd_out(1,KEY);
       delay();
			 if(KEY=='S'){
				 LED=0;
				 TR0=1;
				 TR1=1;
				 while(df==0);
				 
			 }else
			 LED_D=LED_D*10+ (KEY-'0');
			 
			 
			 
			 
				 
		 } 		 
	 }
	

}

void lcd_out(unsigned char x,unsigned char y){
	RW=0;
	RS=x;
	LCD_DATA = y;
	EN=1;
	EN=0;
}

unsigned char key_in(void){
	R1=0;R2=1;R3=1;R4=1;
	if(C1==0){ delay();while(C1==0);delay();return('7');}
	if(C2==0){ delay();while(C2==0);delay();return('8');}
	if(C3==0){ delay();while(C3==0);delay();return('9');}
	if(C4==0){ delay();while(C4==0);delay();return('/');}

	R1=1;R2=0;R3=1;R4=1;
	if(C1==0){ delay();while(C1==0);delay();return('4');}
	if(C2==0){ delay();while(C2==0);delay();return('5');}
	if(C3==0){ delay();while(C3==0);delay();return('6');}
	if(C4==0){ delay();while(C4==0);delay();return('*');}

	R1=1;R2=1;R3=0;R4=1;
	if(C1==0){ delay();while(C1==0);delay();return('1');}
	if(C2==0){ delay();while(C2==0);delay();return('2');}
	if(C3==0){ delay();while(C3==0);delay();return('3');}
	if(C4==0){ delay();while(C4==0);delay();return('-');}

	R1=1;R2=1;R3=1;R4=0;
	if(C1==0){ delay();while(C1==0);delay();return('S');}
	if(C2==0){ delay();while(C2==0);delay();return('0');}
	if(C3==0){ delay();while(C3==0);delay();return('=');}
	if(C4==0){ delay();while(C4==0);delay();return('+');}

	return 'n';

}

void delay()
{
	unsigned int i=1000;
	while(i>0)i--;
}

