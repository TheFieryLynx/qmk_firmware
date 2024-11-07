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

#include "eeconfig.h"

#define WD_LEFT     LCTL(KC_LEFT) // move window left
#define WD_RGHT     LCTL(KC_RIGHT) // move window right
#define SC_AREA     LGUI(KC_S) // take screenshot of the area
#define SC_WD       LGUI(KC_G) // take screenshot of the active window
#define LC_SC       LGUI(KC_L) // lock screen
#define OP_TM       LGUI(KC_T) // open terminal
#define CL_WD       LGUI(KC_W) // close window
#define CH_LG       LALT(KC_CAPS) // change language

// CM_ == Custom_ - layer language independent symbols

enum custom_keycodes {
    LG_ACTN = SAFE_RANGE, // change language and change flag
    LG_SYNC, // change flag if system language is out of sync
    CM_LCBR, // {
    CM_RCBR, // }
    CM_LBRC, // [
    CM_RBRC, // ]
};

typedef union {
  uint32_t raw;
  struct {
    bool language_state :1; // true - US, false - RU
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
}

void change_eeconfig(void) {
    user_config.language_state = !user_config.language_state;
    eeconfig_update_user(user_config.raw);
}

void tap_symbol(uint16_t symbol) {
    if (user_config.language_state) {
        tap_code16(symbol);
    } else {
        tap_code16(CH_LG);
        tap_code16(symbol);
        tap_code16(CH_LG);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case LG_ACTN:
                change_eeconfig();
                tap_code16(CH_LG);
                return false;
            case LG_SYNC:
                change_eeconfig();
                return false;
            case CM_LCBR:
                tap_symbol(KC_LCBR);
                return false;
            case CM_RCBR:
                tap_symbol(KC_RCBR);
                return false;
            case CM_LBRC:
                tap_symbol(KC_LBRC);
                return false;
            case CM_RBRC:
                tap_symbol(KC_RBRC);
                return false;
            default:
                break;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, XXXXXXX, XXXXXXX,   KC_UP, XXXXXXX, SC_AREA,                      LG_SYNC, KC_LPRN, KC_RPRN, XXXXXXX, KC_MINS, KC_LBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT,   SC_WD,                      XXXXXXX, CM_LCBR, CM_RCBR,   LC_SC,  KC_EQL, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, WD_LEFT, KC_CAPS, WD_RGHT, XXXXXXX,                      LG_ACTN, CM_LBRC, CM_RBRC, XXXXXXX, KC_BSLS, KC_RBRC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______, _______,    _______,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,   CL_WD, XXXXXXX, XXXXXXX,   OP_TM,                         KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_4,    KC_5,    KC_6, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         KC_1,    KC_2,    KC_3,  KC_DOT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3), _______,    _______, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,RGB_RMOD,                      RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};
