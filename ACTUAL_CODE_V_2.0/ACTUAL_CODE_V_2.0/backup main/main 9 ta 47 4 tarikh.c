#ifndef F_CPU
#define F_CPU 1000000
#endif
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)
#include<avr/io.h>
//#include<util/delay.h>
#include<util/delay.h>
#include "serial.h"
#include "MrLCDATmega32.h"
#include "pwm_generation.h"



/*#ifndef F_CPU
#define F_CPU 1000000UL // 16MHz clock speed
#endif
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)

#include <avr/io.h>
#include <util/delay.h>
#include "pwm_generation.h"*/

		/* make PORT as output port */
volatile unsigned char a;

int main()
{
	
	// bluetooth control code starts
	DDRB = 0xff;
	serial_init(9600);
	int k = 0;
	//char msg[10]="";
	char buffer[16];
	
	Initialise();
	DDRD = 0b11111011;
	_delay_ms(50);

	Initialise();//lcd initi
	
	
	//bluetooth control finishes
	
	
	// motor control starts from here
	int left_speed = 85; // init l_s
	int right_speed = 5; // init r_s
	int top_speed = 100; // init full speed library works using 100 actually
	init_pwm0_phase_mode_non_inverted();
	set_duty0_non_inverted(left_speed);
	init_pwm2_phase_mode_non_inverted();
	set_duty2_non_inverted(right_speed);
	
	// motor control finishes
	
	while(1)
	{
		
		if(serial_available()){
			
			a = serial_read();
			s_clearbuffer();
			urclear();
			serial_char(a);
			s_clearbuffer();
			urclear();
			int x= a;
			GoToMrLCDLocation(1,1);
			Send_A_String("Magnetometer");
			GoToMrLCDLocation(1,2);
			Send_A_String("Heading=");
			//itoa(Magneto_GetHeading(),buffer,10);
			itoa(x,buffer,10);
			Send_A_String(buffer);
			Send_A_String(" ");
			//GoToMrLCDLocation(13,2);
			//Send_A_String("cm");
			GoToMrLCDLocation(1,1);
			
			//GoToMrLCDLocation(13,2);
			//itoa(serial_char(a),buffer,10);
			//Send_A_String(buffer);
			//Send_A_String(" ");
			//GoToMrLCDLocation(1,1);
			
			//serial_num(x);
			//itoa(x,msg,10);
			//msg[0] = a;
			//msg[1] = '\0';
			//serial_string(msg);
			//msg= 
			//here a==161, b=162, c=163, ...,w=183,s=179,x=184,q=177,e=165
			// w for forwared  183
			// s for backward  243 179
			// a for lean left 161 
			// d for lean right 164
			// x for stopping 184
			// t for increase left motor 180
			// y for decrease left motor 185
			// u for increase right motor 181
			// i for decrease right motor 169
			// o for viewing speed status 175
			if(a>=161)
			{
				/*if(a<=162){
					if(k==0)
					{
						PORTB = 0xFF;
						k=5;
					}
					else
					{
						PORTB = 0x00;
						k=0;
					}
					//Send_A_String("Magnetometer");
					//GoToMrLCDLocation(1,2);
					//Send_A_String("Heading=");
					//itoa(Magneto_GetHeading(),buffer,10);
					x = a;
					itoa(x,buffer,10);
					GoToMrLCDLocation(1,1);
					Send_A_String(buffer);
					Send_A_String(" ");
					//Send_A_String("cm");
					//GoToMrLCDLocation(1,1);
					//_delay_ms(2000);
				}*/
				/*
				if(a==161)
				{
					if(k==0)
					{
						PORTB = 0xFF;
						k=5;
					}
					else
					{
						PORTB = 0x00;
						k=0;
					}
					//Send_A_String("Magnetometer");
					//GoToMrLCDLocation(1,2);
					//Send_A_String("Heading=");
					//itoa(Magneto_GetHeading(),buffer,10);
					x = a;
					itoa(x,buffer,10);
					GoToMrLCDLocation(1,1);
					Send_A_String(buffer);
					Send_A_String(" ");
					//Send_A_String("cm");
					//GoToMrLCDLocation(1,1);
					//_delay_ms(2000);
				}
				if(a==183)
				{
					GoToMrLCDLocation(1,1);
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					Send_A_String("in 183 branch");
					
				}
				if(a==179)
				{
					GoToMrLCDLocation(1,1);
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					Send_A_String("in 179 branch");
					
					
				}
				//PORTB=0xFF;
				*/
				if(a==183)// for w
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in w so will go forward");
					
				}
				if(a==179)// for s
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in s so will go backward");
					
				}
				
				if(a==164)// for d
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in d so will go right");
					
				}
				if(a==184)// for x
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in x so will stop");
					

				}
				if(a==180)// for t
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					//x = a;
					//itoa(x,buffer,10);
					//Send_A_String(buffer);
					
					Send_A_String("incre. leftwh.");
					left_speed = (left_speed + 1 ) % top_speed;
					GoToMrLCDLocation(1,2);
					Send_A_String("now: ")
					x = left_speed;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					
				}
				if(a==185)// for y
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					//x = a;
					//itoa(x,buffer,10);
					//Send_A_String(buffer);
					
					Send_A_String("decre. leftwh.");
					left_speed = (left_speed - 1 ) % top_speed;
					GoToMrLCDLocation(1,2);
					Send_A_String("now: ")
					x = left_speed;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
				}
				if(a==181)// for u
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in u increasing rightwheel");
					
				}
				if(a==169)// for i
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in i decreasing rightwheel");
					
				}
				if(a==175)// for o
				{
					lcdClear();
					GoToMrLCDLocation(1,1);
					
					x = a;
					itoa(x,buffer,10);
					Send_A_String(buffer);
					
					Send_A_String(" in o showing speed");
					
					GoToMrLCDLocation(1,2);
					Send_A_String("left: ");
					//speed code 
					Send_A_String("right: ");
					//speed code
				}
				
				if(a==161) // for a
				{
					if(k==0)
					{
						PORTB = 0xFF;
						k=5;
					}
					else
					{
						PORTB = 0x00;
						k=0;
					}
					//Send_A_String("Magnetometer");
					//GoToMrLCDLocation(1,2);
					//Send_A_String("Heading=");
					//itoa(Magneto_GetHeading(),buffer,10);
					x = a;
					itoa(x,buffer,10);
					GoToMrLCDLocation(1,1);
					Send_A_String(buffer);
					Send_A_String(" ");
					//Send_A_String("cm");
					//GoToMrLCDLocation(1,1);
					//_delay_ms(2000);
				}
				
				
			}
		}
		
	}
	
	
}