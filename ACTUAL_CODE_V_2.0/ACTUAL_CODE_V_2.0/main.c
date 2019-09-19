/************************************************************************/
/* Code for operating delivery bot
   Author: Rafi, Apurbo, Akil                                                                     */
/************************************************************************/


/************************************************************************/
/*two user defined headers are made, one is "new_UART.h" that communicates with blue tooth via the UART protocol        
  And the other is "pwm_generation.h" authored by Abdur Rahman Tushar, that controls the speed of the motor and sets the speed of the motor                                                            */
/************************************************************************/
#ifndef F_CPU
#define F_CPU 1000000
#endif
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)

#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include "new_UART.h"
#include "pwm_generation.h"

/************************************************************************/
/* Defining necessary global variables                                                                     */
/************************************************************************/
volatile unsigned char a;					//for choosing user input
volatile int global_count;					//for keeping track of the rotation of left wheel
volatile int left_global_count = 0;			//for keeping track of the rotation of left wheel
volatile char rotation[5];					//a character array for displaying number of rotations
volatile int total_left_rotate = 0;		    // keeps track of total left rotation	
volatile int total_right_rotate = 0;		//// keeps track of total right rotation

/************************************************************************/
/* Interrupt for left rotation                                                                     */
/************************************************************************/
ISR(INT1_vect)
{
	global_count++;
	itoa(global_count, rotation, 10);
	UART_send_string("Left Rotations: ");
	UART_send_string(rotation);
	UART_send_string("\n");

}

/************************************************************************/
/* Interrupt for right rotation                                                                     */
/************************************************************************/
ISR(INT0_vect)
{
	left_global_count++;
	itoa(left_global_count, rotation, 10);
	UART_send_string("Right Rotations: ");
	UART_send_string(rotation);
	UART_send_string("\n");
}

/************************************************************************/
/* Function to rotate to a certain degree to the left according to the received input from blue tooth                                                                     */
/************************************************************************/
void leftRotate()
{
	global_count = 0;
	char buffer[15];
	UART_send_string("Input rotation degree as multiple of 18\n");
	UART_send_string("For 36 degree input 002\n");
	UART_send_string("For 90 degree input 005\n");
	UART_send_string("Your Input: ");
	UART_receive_string(buffer,3);
	buffer[3]='\0';

	int leftTurnRequiredRotation=atoi(buffer);


	/************************************************************************/
	/* car starts to rotate                                                                     */
	/************************************************************************/

	PORTB = PORTB | (1<<1);
	PORTB = PORTB | (1<<5);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<4);
	
	/************************************************************************/
	/* polling till the global count is equal to the required rotation                                                                     */
	/************************************************************************/
	while(global_count<leftTurnRequiredRotation){}

	/************************************************************************/
	/* car stopped here                                                                     */
	/************************************************************************/
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<4);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<5);
	global_count = 0;

}

/************************************************************************/
/* Function to rotate to a certain degree to the right according to the received input from blue tooth                                                                      */
/************************************************************************/
void rightRotate()
{
	left_global_count = 0;

	char buffer[15];
	UART_send_string("Input rotation degree as multiple of 18\n");
	UART_send_string("For 36 degree input 002\n");
	UART_send_string("For 90 degree input 005\n");
	UART_send_string("Your Input: ");
	UART_receive_string(buffer,3);
	buffer[3]='\0';

	int rightTurnRequiredRotation=atoi(buffer);
	
	/************************************************************************/
	/* car starts to rotate                                                                     */
	/************************************************************************/

	PORTB = PORTB | (1<<4);
	PORTB = PORTB | (1<<2);
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<5);


	/************************************************************************/
	/* polling till the global count is equal to the required rotation                                                                     */
	/************************************************************************/
	while(left_global_count<rightTurnRequiredRotation){}
		

	/************************************************************************/
	/* car stopped here                                                                     */
	/************************************************************************/
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<4);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<5);

	left_global_count = 0;


}

/************************************************************************/
/* Function to rotate 90 degree to the left                                                                     */
/************************************************************************/
void leftRotate90()
{
	global_count = 0;  //resetting global count

	UART_send_string("\nRotating 90 degrees left\n");
	_delay_ms(1000);

	//int leftTurnRequiredRotation= 8;  //counts 8 magnet to rotate 90 degrees

	int leftTurnRequiredRotation= 5;

	total_left_rotate++;
	_delay_ms(1000);
	
	/************************************************************************/
	/* car starts to left rotate 90 degrees                                                                 */
	/************************************************************************/

	PORTB = PORTB | (1<<1);
	PORTB = PORTB | (1<<5);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<4);

	
	/************************************************************************/
	/* polling till the global count is equal to the required rotation                                                                     */
	/************************************************************************/
	while(global_count<leftTurnRequiredRotation){}
		

	/************************************************************************/
	/* car stopped here                                                                     */
	/************************************************************************/
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<4);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<5);

	global_count = 0;
	_delay_ms(1000);
}

/************************************************************************/
/* Function to rotate 90 to the right                                                                     */
/************************************************************************/
void rightRotate90()
{
	left_global_count = 0;   //resetting global count

	UART_send_string("\nRotating 90 degrees right\n");
	_delay_ms(1000);
	int rightTurnRequiredRotation = 5;   //counts 8 magnet to rotate 90 degrees

	total_right_rotate++;
	_delay_ms(1000);

	/************************************************************************/
	/* car starts to right rotate 90 degrees                                                                     */
	/************************************************************************/
	
	PORTB = PORTB | (1<<4);
	PORTB = PORTB | (1<<2);
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<5);

	
	/************************************************************************/
	/* polling till the global count is equal to the required rotation                                                                     */
	/************************************************************************/
	while(left_global_count<rightTurnRequiredRotation){}
		

	/************************************************************************/
	/* car stopped here                                                                     */
	/************************************************************************/
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<4);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<5);

	left_global_count = 0;
	_delay_ms(1000);
}



/************************************************************************/
/* This function checks for obstacles, if any, stops the car                                                                     */
/************************************************************************/
void checkObstacle()
{


	int obstacle = PINA & 0x01; // we take sonar value from pin0 of portA
	if(obstacle==1)
	{
		UART_send_string("clear the obstacle in-front\n");
		unsigned char state;
		state = PINB;			//saving the current state of PORTB

		PORTB = PORTB & ~(1<<1);
		PORTB = PORTB & ~(1<<4);
		PORTB = PORTB & ~(1<<2);
		PORTB = PORTB & ~(1<<5);

		while(obstacle==1)
		{
			obstacle = PINA & 0x01; // we take sonar value from pin0 of portA
		}

		PORTB = state;			//Returning to the Previous state of PORTB
	}
}


/************************************************************************/
/* This function moves the car ahead in a certain axis along the x or y axis                                                                     */
/************************************************************************/
void moveAhead(int unit)
{
	global_count = 0;
	left_global_count = 0;

	int requiredRotation = 0;
	char buffer[10];
	itoa(unit,buffer,10);
	UART_send_string("\nMoving ");
	UART_send_string(buffer);
	UART_send_string(" feet ahead\n");

	/************************************************************************/
	/* Converting the unit to rotation                                                                     */
	/************************************************************************/

	requiredRotation = unit*7;   //1 foot requires 7 rotation


	/************************************************************************/
	/* moving ahead                                                                     */
	/************************************************************************/
	PORTB = PORTB | (1<<1);
	PORTB = PORTB | (1<<4);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<5);
	

	/************************************************************************/
	/* polling till the global count is equal to the required rotation                                                                     */
	/************************************************************************/
	while(global_count<requiredRotation){checkObstacle();}
		

	/************************************************************************/
	/* stopped here                                                                     */
	/************************************************************************/
	PORTB = PORTB & ~(1<<1);
	PORTB = PORTB & ~(1<<4);
	PORTB = PORTB & ~(1<<2);
	PORTB = PORTB & ~(1<<5);
	
	/************************************************************************/
	/* resetting the values of global count                                                                     */
	/************************************************************************/
	global_count = 0;
	left_global_count = 0;


}


int main()
{

	/************************************************************************/
	/* Initializing the blue tooth library for serial communication                                                                     */
	/************************************************************************/
	UART_init(); 


	DDRA = 0x00;			// Setting up a pin of A0 for receiving signal from sonar
	


	/************************************************************************/
	/* motor control starts from here
	PINB1, PINB2-->left motor control
	PINB4, PINB5-->right motor control                                                              */
	/************************************************************************/
	int left_speed = 82;   // initialize l_s
	int right_speed = 85; // initialize r_s
	int top_speed = 100; // initialize full speed library works using 100 actually
	init_pwm0_phase_mode_non_inverted();
	set_duty0_non_inverted(left_speed); //setting the left speed
	init_pwm2_phase_mode_non_inverted();
	set_duty2_non_inverted(right_speed);//setting the right speed

	DDRB = DDRB | 0x00110110;// bits are set to helps to drive motor
	/************************************************************************/
	/* motor control finishes                                                                     */
	/************************************************************************/


	/************************************************************************/
	/* interrupt initialization and enabling for Hall effect sensor                                                                     */
	/************************************************************************/
	GICR = (1<<INT1) |(1<<INT0);
	MCUCR = 0b00001111;  //both interrupt are set to rising edges of the clock

	sei();
	_delay_ms(1000);

	char buffer[16];   //a buffer for blue tooth communication
	int count;
	int x;


	while(1)
	{
		/************************************************************************/
		/* prompt to display on the console itself                                                                     */
		/************************************************************************/
		checkObstacle();
		UART_send_string("\n\nWelcome to prompt\n");
		UART_send_string("Enter t to change left wheel speed\n");
		UART_send_string("Enter y to change right wheel speed\n");
		UART_send_string("Enter o to view wheel speeds\n");
		UART_send_string("Enter r for rotate the car\n");
		UART_send_string("Enter w to move the car forward\n");
		UART_send_string("Enter s to move the car backward\n");
		UART_send_string("Enter x to stop the car\n");
		UART_send_string("Enter m to move the car forward for specific unit\n");
		UART_send_string("Enter j to start the delivery operation\n");
		UART_send_string("Your input: ");

		/************************************************************************/
		/* receiving menu choice                                                                     */
		/************************************************************************/
		UART_receive_string(buffer,1);
		buffer[1]='\0';

		a = buffer[0];
		UART_send(a);
		UART_send_string("\n");


				if(a=='w')
				{
					UART_send_string("In w\n");
					UART_send_string("the car will move forward\n");

					PORTB = PORTB | (1<<1);
					PORTB = PORTB | (1<<4);
					PORTB = PORTB & ~(1<<2);
					PORTB = PORTB & ~(1<<5);
				}
				if(a =='s')
				{

					UART_send_string("inside S so the car will move backward");

					PORTB = PORTB | (1<<2);
					PORTB = PORTB | (1<<5);
					PORTB = PORTB & ~(1<<1);
					PORTB = PORTB & ~(1<<4);

				}
				if(a =='x')
				{
					UART_send_string("inside X so the car will stop");

					PORTB = PORTB & ~(1<<1);
					PORTB = PORTB & ~(1<<4);
					PORTB = PORTB & ~(1<<2);
					PORTB = PORTB & ~(1<<5);

					global_count = 0;
					left_global_count = 0;

				}

				if(a =='a') // for 90 degrees left rotation
				{

					UART_send_string("The car will now turn left\n");
					leftRotate90();

				}

				if(a =='d')//for 90 degrees right rotation
				{
					UART_send_string("The car will now turn right\n");
					rightRotate90();
				}

				if(a =='t')//changing the left wheel speed
				{
					UART_send_string("\nGive the speed of left wheel:");
					UART_receive_string(buffer,3);
					buffer[3]='\0';
					left_speed = atoi(buffer);

					set_duty2_non_inverted(left_speed);

				}
				if(a =='y')//changing the right wheel speed
				{
					UART_send_string("Give the speed of right wheel:");
					UART_receive_string(buffer,3);
					buffer[3]='\0';
					right_speed = atoi(buffer);

					set_duty0_non_inverted(right_speed);

				}
				if(a =='o')//shows speed of both the wheels
				{
					UART_send_string("In O showing speed\n");

					x = left_speed;
					itoa(x,buffer,10);

					UART_send_string("left:");
					UART_send_string(buffer);


					x = right_speed;
					itoa(x,buffer,10);

					UART_send_string(" right:");
					UART_send_string(buffer);
					UART_send_string("\n");
					
				}

				if(a=='r') //rotating left or right by 90 degrees with this option
				{
					while(1)
					{
						UART_send_string("\nEnter l to rotate left and r to rotate right or e to exit\n");
						UART_receive_string(buffer,1);
						if(buffer[0]=='l')
						{
							leftRotate();
						}
						else if(buffer[0] == 'r')
						{
							rightRotate();
						}
						else if(buffer[0] =='e')
						{
							break;
						}
					}
				}

				if (a == 'j') //this mode is for the delivery operation mode
				{
					UART_send_string("\nWelcome to the operation mode\n");

					while(1)
					{
						UART_send_string("Give your coordinate in x, y format( ex. 002,003) in feet\n");
						UART_receive_string(buffer,7);
						UART_send_string("GAY BUFFER = ");
						UART_send_string(buffer);
						UART_send_string("\n");

						char xCoord[4];
						char yCoord[4];

						/************************************************************************/
						/* processing the input string to get x,y coordinates in feet                                                                     */
						/************************************************************************/

						xCoord[0] = buffer[0];
						xCoord[1] = buffer[1];
						xCoord[2] = buffer[2];

						yCoord[0] = buffer[4];
						yCoord[1] = buffer[5];
						yCoord[2] = buffer[6];

						xCoord[3] = '\0';
						yCoord[3] = '\0';

						UART_send_string("x = ");
						UART_send_string(xCoord);
						UART_send_string("\n");
						UART_send_string("y = ");
						UART_send_string(yCoord);


						/************************************************************************/
						/* Now we convert the string coordinates to integers                                                                     */
						/************************************************************************/
						int x;
						int y;

						x = atoi(xCoord);
						y = atoi(yCoord);
						
						/************************************************************************/
						/* conditionally we call the appropriate rotate functions to operate the car                                                                     */
						/************************************************************************/

						if(x>=0)
						{
							rightRotate90();
							moveAhead(x);

							if(y>=0)
							{
								leftRotate90();
								moveAhead(y);
							}
							else
							{
								rightRotate90();
								moveAhead(-y);
							}
						}
						else
						{
							leftRotate90();
							moveAhead(-x);

							if(y>=0)
							{
								rightRotate90();
								moveAhead(y);
							}
							else
							{
								leftRotate90();
								moveAhead(-y);
							}
						}

						UART_send_string("Do you want to continue operation?\n y/n\n");
						UART_receive_string(buffer,1);

						if (buffer[0] == 'n')
						{
							break;
						}
					}
				}

				if (a == 'm') //this option moves the car in forward direction to a certain coordinate
				{
					UART_send_string("Give unit in feet to move forward\n");
					UART_receive_string(buffer, 3);

					int unit = atoi(buffer);
					if (unit <= 0)
					{
						UART_send_string("Send positive unit\n");
					}
					else{
						moveAhead(unit);
					}
				}

		}
}
