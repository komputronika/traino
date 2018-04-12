#define PIN_SR_LATCH   8 // ST_CP 74HC595
#define PIN_SR_CLOCK  12 // SH_CP 74HC595
#define PIN_SR_DATA   11 // DS 74HC595

void setup() {
  pinMode(PIN_SR_LATCH, OUTPUT);
  pinMode(PIN_SR_CLOCK, OUTPUT);
  pinMode(PIN_SR_DATA,  OUTPUT);
}

void shift595(byte value) {
    // Mengirim 1 byte shift register
    digitalWrite(PIN_SR_LATCH, LOW);
    shiftOut(PIN_SR_DATA, PIN_SR_CLOCK, LSBFIRST, value);
    digitalWrite(latchPin, HIGH);
    
}