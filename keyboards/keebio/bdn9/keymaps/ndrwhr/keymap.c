/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

enum layer_names {
    LAYER_BASE,
    LAYER_RESET_1,
    LAYER_RESET_2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT(
        MO(1)       , XXXXXXX   , XXXXXXX,
        LGUI(KC_GRV), LGUI(KC_T), LGUI(KC_TAB),
        RCS(KC_TAB) , LGUI(KC_W), RCTL(KC_TAB)
    ),
    [LAYER_RESET_1] = LAYOUT(
        XXXXXXX, MO(2)  , XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [LAYER_RESET_2] = LAYOUT(
        XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

void left_encoder(bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}

void middle_encoder(bool clockwise) {
    if (clockwise) {
        tap_code(KC_WH_L);
    } else {
        tap_code(KC_WH_R);
    }
}

void right_encoder(bool clockwise) {
    if (clockwise) {
        tap_code(KC_WH_U);
    } else {
        tap_code(KC_WH_D);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case _LEFT:
            left_encoder(clockwise);
            break;
        case _MIDDLE:
            middle_encoder(clockwise);
            break;
        case _RIGHT:
            right_encoder(clockwise);
            break;
    }
    return false;
}

