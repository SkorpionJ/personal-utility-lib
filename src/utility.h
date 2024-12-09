#pragma once
#include <Arduino.h>

class Button
{
private:
    unsigned long button_last_change;
    unsigned long debounce_time;

    short button_pin;
    bool button_changed;
    bool button_base_value;
    bool button_last_state;
    bool current_stable_state;
    bool pullup;

    Button(short pin = -1, unsigned long time = 50, bool base_value = HIGH)
        : button_pin(pin),
          debounce_time(time),
          button_base_value(base_value),
          button_last_state(base_value),
          current_stable_state(base_value) {}

public:
    void setup(short button_pin, unsigned long debounce_time, bool button_base_value)
    {
        pullup ? pinMode(button_pin, INPUT_PULLUP) : pinMode(button_pin, INPUT);
        this->button_pin = button_pin;
        this->debounce_time = debounce_time;
        this->button_base_value = button_base_value;
        this->button_last_state = button_base_value;
    }

    void begin(bool pullup = true)
    {
        pinMode(button_pin, pullup ? INPUT_PULLUP : INPUT);
        this->pullup = pullup;
    }

    bool wasPressed()
{
    bool current_state = digitalRead(button_pin);
    unsigned long now = millis();

    // Check for state change
    if (current_state != button_last_state) {
        button_last_change = now;
        button_changed = true;
    }

    // Debounce check
    if (button_changed && (now - button_last_change >= debounce_time)) {
        button_changed = false;
        
        // Check if stable state is different
        if (current_state != current_stable_state) {
            current_stable_state = current_state;
            
            // Return true if pressed (opposite of base value)
            return (current_state != button_base_value);
        }
    }

    return false;
}

    bool isPressed()
    {
        return digitalRead(button_pin) != button_base_value;
    }
};
class Pause
{
private:
    unsigned long milliSec = 0;

public:
    bool wait(unsigned long milliSec)
    {
        if (millis() - this->milliSec >= milliSec)
        {
            this->milliSec = millis();
            return true;
        }
    }
};
