#include <Arduino.h>
#include <PCM.h>
#include <stdint.h>

#include "macros.h"
#include "sounds.h"
#include "util.h"

uint32_t last_motion_t = 0;
uint32_t last_bp_t = 0;
uint32_t last_hiss_t = 0;
uint32_t last_encouragement_t = 0;
bool last_sensor_state = LOW;
bool last_button_state = LOW;

void setup(void) {
    Serial.begin(BAUD_RATE);
    Serial.println("[program started]\n");
    pinMode(SENSOR, INPUT);
    pinMode(BUTTON, INPUT_PULLUP);
}

void loop(void) {
    bool cur_sensor_state = digitalRead(SENSOR);
    bool cur_button_state = digitalRead(BUTTON);

    bool motion_detected = cur_sensor_state == HIGH && last_sensor_state == LOW;
    bool button_pressed = cur_button_state == LOW && last_button_state == HIGH;

    if (motion_detected) {
        log_motion(last_motion_t = millis());
    }

    if (button_pressed) {
        log_button_press(last_bp_t = millis());
        play_sound(sounds::meow, sizeof(sounds::meow));
    }

    last_button_state = cur_button_state;
    last_sensor_state = cur_sensor_state;

    uint32_t time_since_motion = millis() - last_motion_t;
    bool user_idle = time_since_motion > IDLE_MS && (millis() - last_hiss_t) > IDLE_MS;

    // Play sound if user is idle and enough time has passed since last hiss
    if (user_idle) {
        last_hiss_t = millis();
        log_idle(time_since_motion);
        play_sound(sounds::hiss, sizeof(sounds::hiss));
    } else if (time_since_motion > IDLE_MS && (millis() - last_encouragement_t) > IDLE_MS) {
        last_encouragement_t = millis();
        play_sound(sounds::meow, sizeof(sounds::meow));
    }

    delay(LOOP_DELAY_MS);
}
