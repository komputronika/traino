#include "Traino.h" 
     
//-----------------------------------------------
// Fungsi-fungsi pada class
//-----------------------------------------------
 
// Constructor
Traino::Traino() {/**/}

// Destructor
Traino::~Traino() {/**/}

// Begin - Harus dipanggil di dalam setup()
Traino::begin(){

    // Inisialisasi variabel private
    _data_shift = 0;

    // Inisialisasi untuk rotary encoder
    int encoderPos = 0;
    pinMode(ENC_PINA, INPUT_PULLUP);
    pinMode(ENC_PINB, INPUT_PULLUP);
    pinMode(ENC_BUTTON, INPUT_PULLDOWN);
    attachInterrupt(0, __doEncoder, CHANGE);

    // Pin mode untuk shift register
    pinMode(PIN_SR_LATCH, OUTPUT);
    pinMode(PIN_SR_CLOCK, OUTPUT);
    pinMode(PIN_SR_DATA,  OUTPUT);

    // Pin mode untuk tombol
    pinMode(PIN_BUTTON1, INPUT_PULLDOWN);
    pinMode(PIN_BUTTON2, INPUT_PULLDOWN);
    pinMode(PIN_BUTTON3, INPUT_PULLDOWN);    
    pinMode(PIN_BUTTON4, INPUT_PULLDOWN);    

    /*
    // Pin mode untuk relay
    //pinMode(PIN_RELAY_1, OUTPUT);
    //pinMode(PIN_RELAY_2, OUTPUT);

    // Pin mode untuk buzzer
    //pinMode(PIN_BUZZER,  OUTPUT);

    // Pin mode untuk LED
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);
    pinMode(PIN_LED_3, OUTPUT);
    pinMode(PIN_LED_4, OUTPUT);
    */
    // dst.
}

// Cek apakah rotary encoder diputar maju 
bool Traino::encoderForward() {
    if (_encoderPos > _oldPos) {
        _oldPos = _encoderPos;
        return 1;   
    } 
    return -1; 
}

// Cek apakah rotary encoder diputar mundur
bool Traino::encoderBack() {
    if (_encoderPos < _oldPos) {
        _oldPos = _encoderPos;
        return 1;   
    } 
    return -1; 
}

// Cek apakah tombol rotary encoder ditekan
bool Traino::encoderButton() {
    if (digitalRead(ENC_BUTTON, HIGH)) {
        return 1;
        delay(250); // anti bouncing   
    } 
    return -1; 
}

// Nyalakan atau matikan LED 1-4 
void Traino::LED(byte num, byte state) {
    byte pin;
    if (num==1){ bit = BIT_LED1; }
    if (num==2){ bit = BIT_LED2; }
    if (num==3){ bit = BIT_LED3; }
    if (num==4){ bit = BIT_LED4; }

    _data_shift = 0xFF & (1 << bit);
    
    // Seharusnya pakai shift595
    // digitalWrite(pin, state);
    shift595(_data_shift);
}

// Nyalakan atau matikan relay 
void Traino::relay(byte num, byte state) {
    byte bit;
    if (num==1){ bit = BIT_RELAY1; }
    if (num==2){ bit = BIT_RELAY2; }

    _data_shift = 0xFF & (1 << bit);
    
    // Seharusnya pakai shift595
    // digitalWrite(pin, state);
    shift595(_data_shift);
}

// Nyalakan buzzer pada frekuensi dan durasi tertentu
void Traino::buzzer(unsigned int freq, unsigned int duration) {
    _data_shift = 0xFF & (1 << BIT_BUZZER);
    shift595(_data_shift);
    delay(duration);
}

// Kirim byte via shift register
void Traino::shift595(byte value) {
    // Mengirim 1 byte shift register
    digitalWrite(PIN_SR_LATCH, LOW);
    shiftOut(PIN_SR_DATA, PIN_SR_CLOCK, LSBFIRST, value);
    digitalWrite(latchPin, HIGH);
}
