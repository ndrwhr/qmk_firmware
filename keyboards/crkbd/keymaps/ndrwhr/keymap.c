/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layer_names {
    _BASE,
    _PINKY,
    _LEFT,
    _RIGHT,
    _SPECIAL
};

#define LY_P  MO(_PINKY)
#define LY_L  MO(_LEFT)
#define LY_R MO(_RIGHT)
#define LY_S MO(_SPECIAL)

enum custom_keycodes {
    CK_EMJI = SAFE_RANGE,   // {KC_LGUI,KC_LCTL,KC_SPC}
    CK_TIME,                // /time -
    CK_SPKE,                // - [+] {KC_ESC}
    CK_TRGH,                // - [-] {KC_ESC}
    CK_CC,                  // 4242424242424242
    CK_TY,                  // :ty3:
    CK_DOT,                 // ..\n
    CK_LOR,                 // Lorem Ipsum
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(
     KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH,
       LY_P,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
    KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSLS,
                                  LY_L, KC_BSPC,  KC_ENT,                       KC_ENT,  KC_SPC,    LY_R
  ),

  [_PINKY] = LAYOUT_split_3x6_3(
    XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, CK_TIME, CK_SPKE,                      KC_PGUP, XXXXXXX,   KC_UP, XXXXXXX,   CK_CC, CK_LOR,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD, CK_EMJI,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  CK_DOT, XXXXXXX, XXXXXXX, CK_TRGH,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               KC_LBRC,  KC_GRV,  KC_ENT,                       KC_ENT,  KC_TAB, KC_RBRC
  ),

  [_LEFT] = LAYOUT_split_3x6_3(
      CK_TY, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD,  KC_EQL,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
    XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSLS,
                               XXXXXXX,  KC_MEH,  KC_ENT,                       KC_ENT,  KC_SPC,    LY_R
  ),

  [_RIGHT] = LAYOUT_split_3x6_3(
     KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_1,    KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX,
    XXXXXXX,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_PLUS, KC_LCMD, KC_LOPT, KC_LCTL, KC_LSFT, XXXXXXX,
    KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
                                  LY_L, KC_BSPC,  KC_ENT,                       KC_ENT,  KC_MEH, XXXXXXX
  ),

  [_SPECIAL] = LAYOUT_split_3x6_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_PLY1,                       DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, DM_REC1, DM_RSTP,                       DM_RSTP, DM_REC2, XXXXXXX
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  switch (keycode) {
    case CK_EMJI:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LCTL) SS_TAP(X_SPACE) SS_UP(X_LGUI) SS_UP(X_LCTL));
        }
        break;
    case CK_TIME:
        if (record->event.pressed){
            SEND_STRING("/time -");
        }
        break;
    case CK_SPKE:
        if (record->event.pressed){
            SEND_STRING("- [+]" SS_DELAY(250) SS_TAP(X_ESC));
        }
        break;
    case CK_TRGH:
        if (record->event.pressed){
            SEND_STRING("- [-]" SS_DELAY(250) SS_TAP(X_ESC));
        }
        break;
    case CK_CC:
        if (record->event.pressed){
            SEND_STRING("4242424242424242");
        }
        break;
    case CK_TY:
        if (record->event.pressed) {
            SEND_STRING(":ty3:");
        }
        break;
    case CK_DOT:
        if (record->event.pressed) {
            SEND_STRING(".." SS_TAP(X_ENT));
        }
        break;
    case CK_LOR:
        if (record->event.pressed) {
            SEND_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
        }
        break;
    }
  return true;
}
#endif // OLED_ENABLE
