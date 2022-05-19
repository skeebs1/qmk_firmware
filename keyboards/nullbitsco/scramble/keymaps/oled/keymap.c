/*
Copyright 2021 Jay Greco

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pet.h"
#include "status.h"
#include QMK_KEYBOARD_H

#define _BASE 0

enum layers {
    _BASE = 0,
    _VIA1,
    _VIA2,
    _VIA3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_F13, KC_F14, KC_F15,
    KC_F16, KC_F17, KC_F18
)

[_VIA1] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______
),

[_VIA2] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______
),

[_VIA3] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______
)

};

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

bool oled_task_user(void) {
  status_render_wpm(0, 0);
  status_render_layer(0, 3);
  pet_render(0, 13);

  return false;
}

bool wpm_keycode_user(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
      (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
      (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
    keycode = keycode & 0xFF;
  } else if (keycode > 0xFF) {
    keycode = 0;
  }

  // Include keys in WPM calculation
  if ((keycode >= KC_TAB && keycode <= KC_SLASH) || // Tab - Slash (Symbols, Punctuation, Space)
      (keycode >= KC_KP_1 && keycode <= KC_KP_DOT) ||  // Keypad numbers - Keypad Dot
      (keycode >= KC_F1 && keycode <= KC_F12)) { // F1 - F12
    return true;
  }

  return false;
}

void matrix_init_user(void) {
  set_scramble_LED(LED_OFF);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
