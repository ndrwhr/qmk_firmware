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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_planck_grid(
        e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e0a, e0b,
        e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e1a, e1b,
        e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e2a, e2b,
        e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e3a, e3b
    ),
};

#define MISSION_ACCOMPLISHED ":mission_accomplished_1::mission_accomplished_2::mission_accomplished_3::mission_accomplished_4::mission_accomplished_5:"

const char* EMOJIS[] = {
    ":ohno:",                   ":chef:",           ":prettyprettyprettygood:",     ":chart_with_downwards_trend:",     ":chart_with_upwards_trend:",   ":airhorn:",    ":pay_respects:",   ":sadtrombone:",    ":pikashocked:",        ":eyes:",           ":expressionless:",     ":wave:",
    ":thumbsup_terminator:",    ":yougotitdude:",   ":sanic:",                      ":dropbox-logo:",                   ":beautiful:",                  ":nice:",       ":yikes:",          ":rip:",            ":pikadrool:",          ":muscle_boba:",    ":woozy:",              ":raised_hand:",
    ":themoreyouknow:",         ":whynotboth:",     ":monkey_look:",                ":cool::beans:",                    ":plus-one:",                   ":100:",        ":oof:",            ":ruhroh:",         ":dropboxsmile:",       ":man-shrugging:",  ":thinking_face:",      ":clap:",
    MISSION_ACCOMPLISHED,       ":facepalm:",       ":monkey_look_away:",           ":ty3:",                            ":stamp:",                      ":yes_2:",      ":no_2:",           ":tada:",           ":moneydropboxsmile:",  ":foot-pray:",      ":joy:",                ":thumbsup:",
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= e00 && keycode <= e3b && record->event.pressed) {
        SEND_STRING(EMOJIS[keycode - e00]);
    }
    return true;
};
