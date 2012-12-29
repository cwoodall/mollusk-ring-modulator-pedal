#include <avr/io.h>
#include <avr/interrupt.h>
#include "wave_lutsmas.h"
#include "cw_ringbuf_u8.h"

#define AUDIO_INPUT_PIN PA1
#define AUDIO_INPUT_ADC 1
#define AUDIO_OUTPUT_PIN PA6

static ringbuf_u8_t input_buffer;
//static ringbuf_u8_t output_buffer;

inline void setAudioOutput( uint8_t audio_lvl ) { OCR0B = audio_lvl; }
inline void stopAudioOutput( ) { TCCR0B &= ~0x01; }
inline void startAudioOutput( ) { TCCR0B |= 0x01; }

/**
 * setupADC() get ADC input.
 *
 * @todo make so that 8 MSB can be read out.
 */
inline void setupADC() {
    ADMUX = 1;
//    ADCSRB = (1<<ADLAR);
    ADCSRA = (1<<ADEN) | (1<< ADSC) | (1<<ADPS2) | (1<<ADPS1);    
}

/**
 * Setup audio DAC which is a PWM output on Output A on Timer/Counter 1
 */
inline void setupPWM() {
    /** 
     * Setup PWM outputs 
     * 
     *
     * PWM Frequency is F_CPU/1024 = 7.8 kHz. Lowpass filter for 3kHz should 
     * be fine.
     **/
    OCR1A = 0;
    OCR1B = 0xFF>>1; // Compare halfway to TOP
    // Set to FAST PWM with OCR1A in noninverting mode (set until compare,
    // then set again at bottom). Also, set to 10-bit output.
    TCCR1A = (1<<COM1A1) | (0<<COM1A0) | (0<< WGM11) | (1<<WGM10);
    TCCR1B =  (0<<WGM13) | (1<<WGM12) | (1<<CS10);
    TIMSK1 |= (1<<2);

}

/**
 * Sets up interrupts, and input output pins
 */
void setup() {
    cli();

    clear(&input_buffer);
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

/**
 * Main loop starts here
 */
int main() {
    // Setup
    setup();

    // Loop
    while(1) {
    }
    return 0;
}

/* INTERRUPTS */

/**
 * 
 */
ISR(TIM1_COMPB_vect) {
    static uint8_t toss = 0;
//    static uint8_t LFO_counter;
//    const static uint16_t *waveform = SIN_LUT; 
    OCR1A = (get_value(&input_buffer, 0)/2)+(get_value(&input_buffer, 1)/2);    
    toss = ADCL;
    push_back(&input_buffer, ADCH);

    ADCSRA |= (1<<ADSC);  
}
