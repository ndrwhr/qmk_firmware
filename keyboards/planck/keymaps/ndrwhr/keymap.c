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
    CK = SAFE_RANGE,

    // STRING keycodes.
    SS_00, SS_01, SS_02, SS_03,
};

const char* STRINGS[] = {
    ":thinking-sheep:",
    "Andrew's Flock",
    "Andrew's Flock 2",
    "Andrew's Flock 3",
};

#define CK_DKTP        C(KC_UP)
#define CK_SLEEP_DIS   RCS(KC_SLEP)
#define CK_LOCK        G(C(KC_Q))
#define CK_SCHT        G(S(KC_4))
#define CK_SPCH        MEH(KC_S)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_grid(
        //     NOTHING      CHROME        SLACK        VSCODE      ITERM2                FIGMA         ZOOM        FINDER        1PASSWORD.      NOTHING         SLEEP
        SS_00, HYPR(KC_1),  HYPR(KC_2),   HYPR(KC_3),  HYPR(KC_4), HYPR(KC_5),   /*/*/   HYPR(KC_6),   HYPR(KC_7), HYPR(KC_8),   HYPR(KC_9),     HYPR(KC_0),     CK_SLEEP_DIS,
        //     NOTHING      ALL           1/2L         1/3L        2/3R                  1/3C          2/3L        1/3R          1/2R            NOTHING         LOCK
        SS_01, HYPR(KC_A),  CK_DKTP,      HYPR(KC_C),  HYPR(KC_D), HYPR(KC_E),   /*/*/   HYPR(KC_F),   HYPR(KC_G), HYPR(KC_H),   HYPR(KC_I),     HYPR(KC_J),     CK_LOCK,
        //     NOTHING      CENTER        T1/2L        T1/3L       T2/3R                 T1/3C         T2/3L       T1/3R         T1/2R           NOTHING         SCREENSHOT
        SS_02, HYPR(KC_K),  HYPR(KC_L),   HYPR(KC_M),  HYPR(KC_N), HYPR(KC_O),   /*/*/   HYPR(KC_P),   MEH(KC_A),  HYPR(KC_R),   HYPR(KC_S),     HYPR(KC_T),     CK_SCHT,
        //     NOTHING      FULL          B1/2L        B1/3L       B2/3R                 B1/3C         B2/3L       B1/3R         B1/2R           NOTHING         SPEAK
        SS_03, HYPR(KC_U),  HYPR(KC_V),   HYPR(KC_W),  HYPR(KC_X), HYPR(KC_Y),   /*/*/   HYPR(KC_Z),   MEH(KC_O),  MEH(KC_E),    MEH(KC_I),      MEH(KC_SCLN),   CK_SPCH
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= SS_00 && keycode <= SS_03 && record->event.pressed) {
        SEND_STRING(STRINGS[keycode - SS_00]);
        tap_code(KC_ENTER);
    }
    return true;
};