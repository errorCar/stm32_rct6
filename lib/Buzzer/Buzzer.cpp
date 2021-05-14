#include "buzzer.h"

Buzzer::Buzzer(uint8_t pinn)
{
    this->pin = pinn;
    pinMode(pin,OUTPUT);
}
void Buzzer::beep()
{
    // set voltage and duration
    // analogWrite(value,pin);
    tone(pin,200);
}
void Buzzer::stop()
{
    // set 0
    // analogWrite(0,pin);
    noTone(pin);
}