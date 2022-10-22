/* Copyright 2020 gtips
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
  [_BASE] = LAYOUT_reviung41(
     KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH,
       LY_P,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
    KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSLS,
                                           LY_L, KC_BSPC,       KC_ENT,         KC_SPC,    LY_R
  ),

  [_PINKY] = LAYOUT_reviung41(
    XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, CK_TIME, CK_SPKE,                      KC_PGUP, XXXXXXX,   KC_UP, XXXXXXX,   CK_CC, CK_LOR,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD, CK_EMJI,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX,  CK_DOT, XXXXXXX, XXXXXXX, CK_TRGH,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        KC_LBRC,  KC_GRV,       KC_ENT,         KC_TAB, KC_RBRC
  ),

  [_LEFT] = LAYOUT_reviung41(
      CK_TY, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_SLSH,
    XXXXXXX, KC_LSFT, KC_LCTL, KC_LOPT, KC_LCMD,  KC_EQL,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_MINS,
    XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_BSLS,
                                        XXXXXXX,  KC_MEH,        KC_ENT,        KC_SPC,    LY_R
  ),

  [_RIGHT] = LAYOUT_reviung41(
     KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_1,    KC_2,    KC_3,    KC_4,    KC_5, XXXXXXX,
    XXXXXXX,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_PLUS, KC_LCMD, KC_LOPT, KC_LCTL, KC_LSFT, XXXXXXX,
    KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,
                                           LY_L, KC_BSPC,        KC_ENT,        KC_MEH, XXXXXXX
  ),

  [_SPECIAL] = LAYOUT_reviung41(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DM_PLY1,                       DM_PLY2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX, DM_REC1,       DM_RSTP,        DM_REC2, XXXXXXX
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t new_state = update_tri_layer_state(state, _LEFT, _RIGHT, _SPECIAL);

    switch (get_highest_layer(new_state)) {
    case _PINKY:
        rgblight_setrgb(RGB_PINK);
        break;
    case _LEFT:
        rgblight_setrgb (RGB_BLUE);
        break;
    case _RIGHT:
        rgblight_setrgb (RGB_RED);
        break;
    case _SPECIAL:
        rgblight_setrgb (RGB_GOLDENROD);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_WHITE);
        break;
    }

    return new_state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

#ifdef RGBLIGHT_ENABLE

static uint16_t key_timer; // timer to track the last keyboard activity
static void refresh_rgb(void); // refreshes the activity timer and RGB, invoke whenever activity happens
static void check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool is_rgb_timeout = false; // store if RGB has timed out or not in a boolean

void refresh_rgb() {
  key_timer = timer_read(); // store time of last refresh
  if (is_rgb_timeout) { // only do something if rgb has timed out
    is_rgb_timeout = false;
    rgblight_wakeup();
  }
}

void check_rgb_timeout() {
  if (!is_rgb_timeout && timer_elapsed(key_timer) > RGBLIGHT_TIMEOUT) {
    rgblight_suspend();
    is_rgb_timeout = true;
  }
}

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_WHITE);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

/* Runs at the end of each scan loop, check if RGB timeout has occurred */
void housekeeping_task_user(void) {
  #ifdef RGBLIGHT_TIMEOUT
  check_rgb_timeout();
  #endif
}

/* Runs after each key press, check if activity occurred */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef RGBLIGHT_TIMEOUT
  if (record->event.pressed) refresh_rgb();
  #endif
}

/* Runs after each encoder tick, check if activity occurred */
void post_encoder_update_user(uint8_t index, bool clockwise) {
  #ifdef RGBLIGHT_TIMEOUT
  refresh_rgb();
  #endif
}

#endif
