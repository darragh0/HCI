#ifndef __UTIL_H__
#define __UTIL_H__

#include <stddef.h>
#include <stdint.h>

void log_motion(uint32_t last_motion_t);
void log_button_press(uint32_t last_bp_t);
void log_idle(uint32_t time_since_motion);
void play_sound(const uint8_t* sound, size_t size);

#endif
