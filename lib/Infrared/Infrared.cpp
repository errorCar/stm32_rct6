#include "Infrared.h"
Infrared::Infrared(uint8_t pinn):pin(pinn)
{
}
uint8_t Infrared::get_val()
{
    digitalRead(pin);
    return val;
}