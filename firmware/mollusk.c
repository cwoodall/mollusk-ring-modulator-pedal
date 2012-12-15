#include <avr/io.h>
#include <avr/interrupt.h>
#include "inst.h"

#define AUDIO_INPUT_PIN PA1
#define AUDIO_INPUT_ADC 1
#define AUDIO_OUTPUT_PIN PA6

#define IBUFFER_SIZE 16
#define OBUFFER_SIZE 16

uint8_t in_head = 0;
uint8_t in_buffer[IBUFFER_SIZE];
uint8_t out_head = 0;
uint8_t out_buffer[OBUFFER_SIZE];

inline void setAudioOutput( uint8_t audio_lvl ) { OCR0B = audio_lvl; }
inline void stopAudioOutput( ) { TCCR0B &= ~0x01; }
inline void startAudioOutput( ) { TCCR0B |= 0x01; }

inline void setupADC() {
    ADMUX = 1;
//    ADCSRB = (1<<ADLAR);
    ADCSRA = (1<<ADEN) | (1<< ADSC) | (1<<ADPS2) | (1<<ADPS1);    
}

inline void setupPWM() {
    /** 
     * Setup PWM outputs 
     * 
     *
     * PWM Frequency is F_CPU/1024 = 7.8 kHz. Lowpass filter for 3kHz should 
     * be fine.
     **/
    OCR1A = 0;
    
    // Set to FAST PWM with OCR1A in noninverting mode (set until compare,
    // then set again at bottom). Also, set to 10-bit output.
    TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (1<< WGM11) | (1<<WGM10);
    TCCR1B =  (0<<WGM13) | (1<<WGM12) | (1<<CS10);
    TIMSK1 |= (1);

}

void setup() {
    cli();

    /** Configure I/O Pins **/
    // Set all pins on PortA to inputs except for the audio output.
    DDRA = 0x00; 
    DDRA |= (1 << AUDIO_OUTPUT_PIN);
    PORTA = 0x00; // Turn off pullups (specifically do not want a pull
                  // up on AUDIO_INPUT
    
    /** Setup PWM **/
    setupPWM();

    /** Setup ADC input **/
    setupADC();


    sei();
}

ISR(TIM1_OVF_vect) {
    static uint8_t toss = 0;
    static uint8_t LFO_counter;
    const static uint16_t *waveform = SIN_LUT;
//    OCR1A = ADCL ;
//    OCR1AH = ADCH;
    /** @todo This needs to be better **/
    /** @todo instantiate a ring buffer of sorts **/
    toss = ADCL;
    OCR1A = (((((ADCH<<8) | toss))));// * (SIN_LUT[LFO_counter]);
    OCR1A = OCR1A;// * SIN_LUT[LFO_counter]>>2;
    LFO_counter = (LFO_counter+1) % 255;
//    toss = ADCH;

    ADCSRA |= (1<<ADSC);  
}

int main() {
    setup();


    while(1) {
//        setAudioOutput(0xFF);
    }
    return 0;
}
