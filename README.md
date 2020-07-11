# CSE 316 Project - January 2018
# Project Name: Delivery Bot

## Brief Description: 
This is a robotic car made with the ATmega32 microcontroller. This microcontroller based car can be controlled with any bluetooth application. Upon taking specific coordinate as input,
this bot considers itself to be in the relative origin and moves to that specific coordinate given as input. Proper user prompt will be displayed on the bluetooth console that is being
used to control the robot. Also the car detects an obstacle and stops by itself unless the obstacle is removed. Once removed, it resumes it's journey to the desired coordinate.

### Core components
* motors - For controlling the wheels rotation and direction. 
* motor drivers - For using the motors with the microcontroller
* blue-tooth sensor - For communicating messages via the USART protocol between the microcontroller and the phone being used.
* sonar sensor - For detecting obstacles
* hall effect sensor - For control of speed and rotation of the wheels.

The entry point to the code is **main.c** in the folder with path: \ACTUAL CODE V 4.0\ACTUAL_CODE_V_2.0\ACTUAL_CODE_V_2.0.


The necessary custom header files we used are:
* new_UART.h - collected from github
* pwm_generation.h - authored by Abdur Rahman Tushar(CSE - 16, BUET) 


If you want to see it live in action here is the link: [Delivery Bot](https://www.youtube.com/watch?v=-LcZ2hp7MaI&t=2s)


Group members:
Mohib Hossain Rafi
Ajwad Akil
Raihan Rasheed

Under the supervision of,
Tareq Mahmood
Lecturer, CSE, BUET

Md. Masum Mushfiq
Lecturer, CSE, BUET
