#ifndef TRAINO_H
#define TRAINO_H
 
#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
    #include "pins_arduino.h"
    #include "WConstants.h"
#endif
 
// Defines

// Rotary encoder
#define ENC_PINA        2
#define ENC_PINB        3
#define ENC_BUTTON      4

// Shift register 74HC595
#define PIN_SR_LATCH    8 // ST_CP 74HC595
#define PIN_SR_CLOCK   12 // SH_CP 74HC595
#define PIN_SR_DATA    11 // DS 74HC595

// Tombol
#define PIN_BUTTON1     8 
#define PIN_BUTTON2    12 
#define PIN_BUTTON3    11 
#define PIN_BUTTON4    11 

// LED
#define BIT_LED1        0
#define BIT_LED2        1
#define BIT_LED3        2
#define BIT_LED4        3

// Relay
#define BIT_RELAY1      4
#define BIT_RELAY2      5

// Buzzer
#define BIT_BUZZER      6



// Variabel global
volatile unsigned int _encoderPos, _oldPos = -1;

// Header class 
class Traino {
    public:
        Traino();
        ~Traino();
        void begin();
        bool encoderForward();
        bool encoderBack();
        bool encoderButton();
        void LED(byte num, byte state);
        void relay(byte num, byte state);
        void buzzer(byte freq, byte delay);
    private:
        byte _data_shift;
        void shift595(byte value);
};


//-----------------------------------------------
// Fungsi non class
//-----------------------------------------------

// Fungsi interrupt untuk rotary encoder
void _doEncoder() {
    if (digitalRead(ENC_PINA) == digitalRead(ENC_PINB)) {
        _encoderPos++;
    } else {
        _encoderPos--;
    }
}

#endif
