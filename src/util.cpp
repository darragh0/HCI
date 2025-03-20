#include "util.h"

#include <Arduino.h>
#include <PCM.h>

void log_motion(uint32_t last_motion_t) {
    Serial.println("Motion detected at " + String(last_motion_t) + " ms");
}

void log_button_press(uint32_t last_bp_t) {
    Serial.println("User petted the cat at " + String(last_bp_t) + " ms");
}

void log_idle(uint32_t time_since_motion) {
    Serial.println("Cat is angry because user has been idle for " + String(time_since_motion) + " ms");
}

void play_sound(const uint8_t* sound, size_t size) {
    startPlayback(sound, size);
}
