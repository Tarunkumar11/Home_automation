/*
 * COMPLETE HOME AUTOMATION.c
 *
 * Created: 20-Jun-18 2:12:30 PM
 *  Author: effort
 */ 


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <string.h>
//defining the value globally
#define RS 0
#define RW 1
#define EN 2
void data(char);
void comm(char);
void ini(void);
void displayv(char s[]);
void display(char s[]);
void intprint(int);
int main(void)
{
	char x;
	int i=2,j=2,k=2;
	DDRA=0xFF;
	DDRB=0x03;
	UBRRL=51;
	UCSRB=0X18;
	UCSRC=0X86;
	displayv("PRESS T FOR ON OR OFF LCD\r"); 
	displayv("PRESS L FOR ON OR OFF LED\r");
	displayv("PRESS F FOR ON OR OFF FAN\r");
    while(1)
    {
		while((UCSRA &(1<<RXC))==0);
		x=UDR;
       if (x=='T' && i%2==0)
		   { 
			 ini();
			 displayv("\r");
			 displayv("LCD IS ON\r");
			 display(" WELCOME TO      ");
			 comm(0XC0);
			 display("CETPA INFOTECH");
			 i++;
		   }
		else if (x=='T' && i%2!=0)
		{
			comm(0x08);
			displayv("\r");
			displayv("LCD IS OFF\r");
			i++;
		}
      if (j%2==0 && x=='L')
      {
	      PORTB|=0x02;
	      displayv("\r");
	      displayv("LED IS ON\r");
	      j++;
      }
      else if (j%2!=0 && x=='L')
      {
	      PORTB&=~(1<<1);
	      displayv("\r");
	      displayv("LED IS OFF\r");
	      j++;
      }
	  else if (k%2==0 && x=='F')
	  {
		  PORTB|=0x01;
		  displayv("\r");
		  displayv("FAN IS ON\r");
		  k++;
	  }
	  else if (k%2!=0 && x=='F')
	  {
		  PORTB&=~(1<<0);
		  displayv("\r");
		  displayv("FAN IS OFF\r");
		  k++;
	  }
       
    }
}
void comm(char x)
{
	PORTA=x &0xF0;
	PORTA&=~(1<<RS);
	PORTA&=~(1<<RW);
	PORTA|=1<<EN;
	_delay_ms(10);
	PORTA&=~(1<<EN);
	
	
	PORTA=(x<<4)&0xF0;
	PORTA&=~(1<<RS);
	PORTA&=~(1<<RW);
	PORTA|=1<<EN;
	_delay_ms(10);
	PORTA&=~(1<<EN);		
}
void data(char x)
{

	PORTA=x &0xF0;
	PORTA|=(1<<RS);
	PORTA&=~(1<<RW);
	PORTA|=1<<EN;
	_delay_ms(10);
	PORTA&=~(1<<EN);


PORTA=(x<<4)&0xF0;
PORTA|=(1<<RS);
PORTA&=~(1<<RW);
PORTA|=1<<EN;
_delay_ms(10);
PORTA&=~(1<<EN);	
}

void ini(void)
{
	
	DDRA=0xFF;//rs and en
	comm(0x02);//return to home
	comm(0x28);// 8 bit
	comm(0x06);//for cursor l2r
	comm(0x0E);//display on cursur on
	comm(0x01);//clear screen
	comm(0x80);// 0th row and 0th colum
}

void display(char s[])
{
	
	int i,len=0;
	len=strlen(s);
	for(i=0;i<=len;i++)
	{
		
		data(s[i]);
		_delay_ms(5);
	}
	
}
void intprint(int x)
{
	data((x/10000)+48);
	x%=10000;
	data((x/1000)+48);
	x%=1000;
	data((x/100)+48);
	x%=100;
	data((x/10)+48);
	x%=10;
	data(x+48);
}
#display the test 
void displayv(char s[])
{
	
	int i,len=0;
	len=strlen(s);
	for(i=0;i<=len;i++)
	{
		
		UDR=s[i];
		while((UCSRA & (1<<TXC))==0);
		UCSRA|=1<<TXC;
	}
	
}
