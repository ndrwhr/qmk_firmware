/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_disable();
}
#endif

enum custom_keycodes {
    e00 = SAFE_RANGE,
         e01, e02, e03, e04, e05, e06, e07, e08, e09, e0a, e0b,
    e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e1a, e1b,
    e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e2a, e2b,
    e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e3a, e3b
};

// Custom Macro Keycodes:

// Random stuff:
#define CMK_SYS_PREF    LGUI(KC_COMMA)
#define CMK_SLEEP_DIS   RCS(KC_SLEP)

// Window manager stuff:
#define CMK_DESKTOP     KC_F11
#define CMK_MAXIMIZE    MEH(KC_F)
#define CMK_LEFT_H      MEH(KC_G)
#define CMK_RIGHT_H     MEH(KC_C)
#define CMK_CENTER      MEH(KC_D)
#define CMK_LEFT_T      MEH(KC_H)
#define CMK_CENTER_T    MEH(KC_T)
#define CMK_RIGHT_T     MEH(KC_N)
#define CMK_UPPER_L     MEH(KC_B)
#define CMK_UPPER_R     MEH(KC_M)
#define CMK_LOWER_L     MEH(KC_W)
#define CMK_LOWER_R     MEH(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_grid(
        e00, e01, e02, e03, e04, e05, e06, e07, e08,         e09,          CMK_SYS_PREF, CMK_SLEEP_DIS,
        e10, e11, e12, e13, e14, e15, e16, e17, CMK_DESKTOP, CMK_MAXIMIZE, CMK_LEFT_H,   CMK_RIGHT_H,
        e20, e21, e22, e23, e24, e25, e26, e27, CMK_CENTER,  CMK_LEFT_T,   CMK_CENTER_T, CMK_RIGHT_T,
        e30, e31, e32, e33, e34, e35, e36, e37, CMK_UPPER_L, CMK_UPPER_R,  CMK_LOWER_L,  CMK_LOWER_R
    ),
};

const char* EMOJIS[] = {
    ":thinking-sheep:",                             ":time-sheep:",         ":aaaa-sheep-intensifies:",                 ":party-sheep:",            ":galaxy-brain-sheep:", ":bowing-sheep:",                               ":100-sheep:",          ":detective-sheep:",    ":ty3:",        ":hey-sorry-my-previous-meeting-is-running-over:",  "XXXXX",    "XXXXX",
    ":mild-panic-sheep-intensifies:",               ":recursive-sheep:",    ":baaaah-sheep-intensifies:",               ":dumpster-fire-sheep:",    ":zoom-sheep:",         ":care-sheep:",                                 ":heart-sheep:",        ":spicy-sheep:",        "XXXXX",        "XXXXX",                                            "XXXXX",    "XXXXX",
    ":mild-panic-sheep-hyper-intensifies:",         ":thisisfine-sheep:",   ":c-o-l-l-u-s-i-o-n-sheep-intensifies:",    ":sheepit:",                ":dead-sheep:",         ":sheep-but-you-can-see-the-pain-in-its-eyes:", ":conspiracy-sheep:",   ":melting-sheep:",      "XXXXX",        "XXXXX",                                            "XXXXX",    "XXXXX",
    ":mild-panic-sheep-my-god-its-full-of-stars:",  ":ohno-sheep:",         ":collusion-sheep:",                        ":doit-sheep:",             ":righteous-sheep:",    ":joy-sheep:",                                  ":cool-sheep:",         ":plus-1-sheep:",       "XXXXX",        "XXXXX",                                            "XXXXX",    "XXXXX",
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= e00 && keycode <= e3b && record->event.pressed) {
        SEND_STRING(EMOJIS[keycode - e00]);
    }
    return true;
};
