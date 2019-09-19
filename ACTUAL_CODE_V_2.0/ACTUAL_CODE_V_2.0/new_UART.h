#include <stdlib.h>

//void UART_init();
//void UART_send(unsigned char data);
//unsigned char UART_receive();
//void UART_send_string(unsigned char* string);
//void UART_receive_string(unsigned char* string, int length);


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


unsigned char UART_receive() {
	unsigned char data;
	
	if((UCSRA&(1<<RXC))==0)
	{
		data='\0';
	}
	else
	{
		data = UDR ;
	}       
	
	
	return data;
}

/*unsigned char UART_receive() {
	unsigned char data;
	
	while((UCSRA&(1<<RXC))==0) ;      //waiting for the data to be received
	data = UDR ;
	
	return data;
}*/

void UART_send_string(unsigned char* string)
{
	int i = 0;
	while(string[i] != '\0') {				//loop until NULL character
		UART_send(string[i]);				//sending a character
		i++;
	}
}

void UART_receive_string(unsigned char* string, int length)
{
	unsigned char data;                   //character data for receiving a single character
	int i = 0;                            //loop control variable
	for(i=0;i<length;i++)                 //This loop receives a string of certain length from the user
	{
		while((UCSRA&(1<<RXC))==0) ;      //waiting for the data to be received
		data = UDR ;                      //data received
		string[i]=data;
	}
	
	string[i]='\0';
}
