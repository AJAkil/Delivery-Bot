#define CHECK(n,p) ( n &   (1<<p) )
#define   SET(n,p) ( n |=  (1<<p) )
#define RESET(n,p) ( n &= ~(1<<p) )
#define  FLIP(n,p) ( n ^=  (1<<p) )


#ifndef F_CPU
#define F_CPU 1000000UL // 1MHz clock speed
#endif


/*#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7*/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
//#include "lcd.h"
#include "MrLCDATmega32.h"


#include <avr/io.h>

void UART_init(){
	UCSRA = 0x02 ;
	UCSRB = 0x18 ;
	UCSRC = 0x86 ;
	UBRRL = 12 ;
	UBRRH = 0 ;
}

void UART_send(unsigned char data){
	while((UCSRA&(1<<UDRE))==0) ;
	UDR = data ;
}

/*unsigned char ADC_temp(){
	ADMUX  = 0b11100000;
	unsigned int result,resultLow;
	
	SET(ADCSRA,ADSC);//sets ADSC = 1,So begins conversion
	while(CHECK(ADCSRA,ADSC)){;}//waits ultil conversion is finisghed
	
	resultLow = ADCL;//
	result    = ADCH;
	
	float tem = result*(2.56/1024) ;
	tem  = (1.3*tem*50) ;
	result = (int) tem;
	char a[10] ;
	itoa(result,a,10) ;
	//Lcd4_Clear() ;
	//Lcd4_Set_Cursor(1,1) ;
	//Lcd4_Write_String("Temp : ") ;
	//Lcd4_Write_String(a) ;
	//Lcd4_Write_String(" C") ;
	_delay_ms(250);
	return result ;
}*/

/*unsigned char ADC_sound(){
	ADMUX  = 0b01000001;
	unsigned int result,resultLow ;
	SET(ADCSRA,ADSC);//sets ADSC = 1,So begins conversion
	while(CHECK(ADCSRA,ADSC)){;}//waits ultil conversion is finisghed
	resultLow = ADCL;//
	result    = ADCH;
	result = (result<<8) + resultLow ;
	result /= 2 ;
	float dV ;
	double a = 10 ;
	double b = 12 ;
	double c = 17 ;
	if(result<=13){
		dV = 20*log(result/a) ;
		result = 49.5 + dV ;
	}
	else if(result>13 && result<23){
		dV = 20*log(result/b) ;
		result = 65 + dV ;
	}
	else if(result>23){
		dV = 20*log(result/c) ;
		result = 70 + dV ;
	}

	char s[10] ;
	itoa(result,s,10) ;
	//Lcd4_Clear() ;
	//Lcd4_Set_Cursor(1,1) ;
	//Lcd4_Write_String("Sound : ") ;
	//Lcd4_Write_String(s) ;
	//Lcd4_Write_String(" dB") ;
	_delay_ms(250);
	return result ;
}*/

/*void showString(){
	Lcd4_Write_String("Hello World");
	for(int i = 0;i<15;i++){
		_delay_ms(500);
		Lcd4_Shift_Left();
	}
	for(int i = 0;i<15;i++){
		_delay_ms(500);
		Lcd4_Shift_Right();
	}
	_delay_ms(2000);
}*/

int main(void)
{
	UART_init() ;
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xFF;
	unsigned char data ;
	char string[300];
	int i=0;
	Initialise();
	Send_A_String("wtf:");
	
	for(i=0;i<5;i++)
	{
		while((UCSRA&(1<<RXC))==0) ;
		data = UDR ;
		string[i]=data;
	}
	
	string[i]='\0';
	Send_A_String(string);
	
	
	
	//ADCSRA = 0b10000111;
	//Lcd4_Init()
	
	//Lcd4_Set_Cursor(1,1) ;
	//Lcd4_Write_String("Welcome :-) ") ;
	while(1)
	{
		while((UCSRA&(1<<RXC))==0) ;
		data = UDR ;
		if(data=='1'){
			Send_A_String("working");
			//Lcd4_Clear() ;
			//Lcd4_Set_Cursor(1,1) ;
			//UART_send(ADC_temp()) ;
		}
		else if(data=='3'){
			//Lcd4_Clear() ;
			//Lcd4_Set_Cursor(1,1) ;
			//UART_send(ADC_sound()) ;
		}
		else if(data=='2'){
			//Lcd4_Clear() ;
			//Lcd4_Set_Cursor(1,1) ;
			//UART_send(1) ;
		}
		//ADC_sound() ;
		//ADC_temp() ;
		
	}
}

