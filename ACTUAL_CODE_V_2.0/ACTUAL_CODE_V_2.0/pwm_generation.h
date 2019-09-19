#include <avr/io.h>

void init_pwm0_fast_mode_non_inverted(){
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00);
    DDRB |= (1 << PB3); //0C0 PIN as output
}

void init_pwm0_fast_mode_inverted(){
    TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << COM00) | (1 << CS00);
    DDRB |= (1 << PB3); //0C0 PIN as output
}

void init_pwm0_phase_mode_non_inverted(){
    TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << CS00);
    DDRB |= (1 << PB3); //0C0 PIN as output
}

void init_pwm0_phase_mode_inverted(){
    TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00) | (1 << CS00) | (1 << CS02);
    DDRB |= (1 << PB3); //0C0 PIN as output   
}

void set_duty0_inverted(unsigned char c){
    OCR0 = 255*(1 - c/100);
}

void set_duty0_non_inverted(unsigned char c){
    OCR0 = (255*c/100);
}

void init_pwm2_fast_mode_non_inverted(){
    TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << CS20);
    DDRD |= (1 << PD7); // OC2 PIN as output
}

void init_pwm2_fast_mode_inverted(){
    TCCR2 = (1 << WGM20) | (1 << WGM21) | (1 << COM21) | (1 << COM20) | (1 << CS20);
    DDRD |= (1 << PD7); // OC2 PIN as output
}

void init_pwm2_phase_mode_non_inverted(){
    TCCR2 = (1 << WGM20) | (1 << COM21) | (1 << CS20);
    DDRD |= (1 << PD7); // OC2 PIN as output
}

void init_pwm2_phase_mode_inverted(){
    TCCR2 = (1 << WGM20) | (1 << COM21) | (1 << COM20) | (1 << CS20) | (1 << CS22);
    DDRD |= (1 << PD7); // OC2 PIN as output   
}

void set_duty2_non_inverted(unsigned char c){
    OCR2 = (255*c/100);
}
void set_duty2_inverted(unsigned char c){
    OCR2 = 255*(1 - c/100);
}
