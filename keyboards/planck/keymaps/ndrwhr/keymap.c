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

// Custom macros that can't be written using the #define macro.
enum custom_keycodes {
    CK = SAFE_RANGE,
    CK_THINKING_SHEEP,
    CK_FLOCK_1,
    CK_FLOCK_2,
    CK_FLOCK_3,
    CK_FLOCK_4,
    CK_SHEEP_MINI_CLEAR,
    CK_SHEEP_CLEAR,
    CK_LOREM,
    CK_SYS_EMOJI,
    CK_SYS_SCREENSHOT,
};

// Zoom shortcuts
#define CK_ZOOM_MUTE SGUI(KC_A)
#define CK_ZOOM_VIDEO SGUI(KC_V)
#define CK_ZOOM_INVITE SGUI(KC_I)
#define CK_ZOOM_SHARE SGUI(KC_S)
#define CK_ZOOM_CHAT SGUI(KC_H)

// Dash shortcut
#define CK_DASH G(KC_E)

// MacOS shortcuts.
#define CK_SYS_SLEEP_DIS RCS(KC_SLEP)
#define CK_SYS_LOCK G(C(KC_Q))
#define CK_SYS_SPEECH MEH(KC_S)

// Window manager shortcuts.
// 1st column.
#define CK_WM_00 C(KC_UP) /* Show Desktop */
#define CK_WM_10 HYPR(KC_B)  /* Center the window */
#define CK_WM_20 HYPR(KC_C)  /* Fullscreen */

#define CK_WM_01 HYPR(KC_D) /* Top left, 1/3 width. */
#define CK_WM_11 HYPR(KC_E) /* Left, 1/3 width. */
#define CK_WM_21 HYPR(KC_F) /* Bottom left, 1/3 width. */

#define CK_WM_02 HYPR(KC_G) /* Top left, 1/2 width. */
#define CK_WM_12 HYPR(KC_H) /* Left, 1/2 width. */
#define CK_WM_22 HYPR(KC_I) /* Bottom left, 1/2 width. */

#define CK_WM_03 HYPR(KC_J) /* Top left, 2/3 width. */
#define CK_WM_13 HYPR(KC_K) /* Left, 2/3 width. */
#define CK_WM_23 HYPR(KC_L) /* Bottom left, 2/3 width. */

#define CK_WM_04 HYPR(KC_M) /* Center, 1/3 width. */
#define CK_WM_14 HYPR(KC_N) /* Center, 1/3 width. */
#define CK_WM_24 HYPR(KC_O) /* Center, 1/3 width. */

#define CK_WM_05 HYPR(KC_P) /* Top right, 2/3 width. */
#define CK_WM_15 HYPR(KC_A) /* Right, 2/3 width. NOTE: Q does not work. */
#define CK_WM_25 HYPR(KC_R) /* Bottom right, 2/3 width. */

#define CK_WM_06 HYPR(KC_S) /* Top right, 1/2 width. */
#define CK_WM_16 HYPR(KC_T) /* Right, 1/2 width. */
#define CK_WM_26 HYPR(KC_U) /* Bottom right, 1/2 width. */

#define CK_WM_07 HYPR(KC_V) /* Top right, 1/3 width. */
#define CK_WM_17 HYPR(KC_W) /* Right, 1/3 width. */
#define CK_WM_27 HYPR(KC_X) /* Bottom right, 1/3 width. */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_grid(
        CK_THINKING_SHEEP,   CK_FLOCK_1,    CK_ZOOM_MUTE,   CK_ZOOM_VIDEO,  CK_ZOOM_INVITE, CK_ZOOM_SHARE,  CK_ZOOM_CHAT,   CK_SYS_EMOJI,  CK_LOREM,      CK_DASH,       KC_NO,         CK_SYS_SLEEP_DIS,
        CK_SHEEP_MINI_CLEAR, CK_FLOCK_2,    CK_WM_00,       CK_WM_01,       CK_WM_02,       CK_WM_03,       CK_WM_04,       CK_WM_05,      CK_WM_06,      CK_WM_07,      KC_NO,         CK_SYS_LOCK,
        CK_SHEEP_CLEAR,      CK_FLOCK_3,    CK_WM_10,       CK_WM_11,       CK_WM_12,       CK_WM_13,       CK_WM_14,       CK_WM_15,      CK_WM_16,      CK_WM_17,      KC_NO,         CK_SYS_SPEECH,
        KC_NO,               CK_FLOCK_4,    CK_WM_20,       CK_WM_21,       CK_WM_22,       CK_WM_23,       CK_WM_24,       CK_WM_25,      CK_WM_26,      CK_WM_27,      KC_NO,         CK_SYS_SCREENSHOT
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_SYS_EMOJI:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LCTL) SS_TAP(X_SPACE) SS_UP(X_LGUI) SS_UP(X_LCTL));
        }
        break;
    case CK_SYS_SCREENSHOT:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LGUI) SS_DOWN(X_LSFT) SS_TAP(X_4) SS_UP(X_LSFT) SS_UP(X_LGUI) SS_DELAY(100) SS_TAP(X_SPACE) SS_DELAY(100) SS_TAP(X_MS_BTN1));
        }
        break;
    case CK_THINKING_SHEEP:
        if (record->event.pressed) {
            SEND_STRING(":thinking-Sheep:");
            tap_code(KC_ENTER);
        }
        break;
    case CK_FLOCK_1:
        if (record->event.pressed) {
            SEND_STRING("Andrew's Flock");
            tap_code(KC_ENTER);
        }
        break;
    case CK_FLOCK_2:
        if (record->event.pressed) {
            SEND_STRING("Andrew's Flock 2");
            tap_code(KC_ENTER);
        }
        break;
    case CK_FLOCK_3:
        if (record->event.pressed) {
            SEND_STRING("Andrew's Flock 3");
            tap_code(KC_ENTER);
        }
        break;
    case CK_FLOCK_4:
        if (record->event.pressed) {
            SEND_STRING("Andrew's Flock 4");
            tap_code(KC_ENTER);
        }
        break;
    case CK_SHEEP_MINI_CLEAR:
        if (record->event.pressed) {
            SEND_STRING("!minisheepclear");
            tap_code(KC_ENTER);
        }
        break;
    case CK_SHEEP_CLEAR:
        if (record->event.pressed) {
            SEND_STRING("!sheepclear");
            tap_code(KC_ENTER);
        }
        break;
    case CK_LOREM:
        if (record->event.pressed) {
            SEND_STRING("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
        }
        break;
    }

    return true;
};
