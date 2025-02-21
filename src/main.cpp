#include <Arduino.h>
#include <PCM.h>
#include <stdint.h>

#include "macros.h"
#include "sounds.h"

uint32_t last_detected = 0;
uint32_t last_sound_played = 0;
bool last_state = LOW;

void setup(void) {
    Serial.begin(BAUD_RATE);
    Serial.println("[program started]\n");
    startPlayback(sounds::meow, sizeof(sounds::meow));
    // Speaker setup is done in the PCM library
    pinMode(SENSOR, INPUT);
    pinMode(LED, OUTPUT);
}

void loop(void) {
    bool cur_state = digitalRead(SENSOR);

    if (cur_state == HIGH && last_state == LOW) {
        last_detected = millis();
        Serial.println("Motion detected at " + String(last_detected) + " ms");
        digitalWrite(LED, HIGH);
    } else if (cur_state == LOW) {
        digitalWrite(LED, LOW);
    }

    last_state = cur_state;
    uint32_t idle_time = millis() - last_detected;

    // Play sound if user is idle and enough time has passed since last sound
    if (idle_time > IDLE_MS && (millis() - last_sound_played) > IDLE_MS) {
        Serial.println("Cat is angry because user has been idle for " + String(idle_time) + " ms");
        startPlayback(sounds::hiss, sizeof(sounds::hiss));
        last_sound_played = millis();
    }

    delay(LOOP_DELAY_MS);  // debounce
}
