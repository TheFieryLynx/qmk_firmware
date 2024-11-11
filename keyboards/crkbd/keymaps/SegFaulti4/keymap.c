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
#include "../ruen.h"

#define SFT_1   LSFT(KC_1)
#define SFT_5   LSFT(KC_5)
#define SFT_8   LSFT(KC_8)
#define SFT_9   LSFT(KC_9)
#define SFT_0   LSFT(KC_0)
#define SFT_EQL LSFT(KC_EQL)
#define SFT_MIN LSFT(KC_MINS)

#define VUP KC_KB_VOLUME_UP
#define VDN KC_KB_VOLUME_DOWN

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT,  KC_ESC, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,    KC_BSPC,   MO(2),  KC_ENT
                                      //`--------------------------'  `--------------------------'

  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       RN_GRV,   SFT_5, RN_LOAB, SFT_EQL, RN_ROAB,RN_QUOT1,                      RN_SMCL, RN_LCBR, SFT_MIN, RN_RCBR, KC_BSLS,  RN_TLD,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,RN_QUEST, RN_LBRC,  KC_EQL, RN_RBRC,RN_QUOT2,                        RN_CL,   SFT_9, KC_MINS,   SFT_0, RN_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   SFT_1, RN_AMSD,   SFT_8, RN_DLLR,  RN_CRT,                       RN_DOG, RN_HASH, RN_COMM,  RN_DOT, RN_VERT, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, LG_SYNC,    LG_ACTN,   MO(3), _______
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      MS_WHLU,MS_WHLL,    KC_UP, MS_WHLR, KC_PGUP, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      MS_WHLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_GRV, KC_QUOT, KC_LBRC, KC_RBRC, XXXXXXX,                      KC_PSCR,  KC_INS,  KC_DEL, KC_HOME,  KC_END, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   MO(3), LG_SYNC,    LG_ACTN, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      XXXXXXX,     VDN, KC_MUTE,     VUP, KC_CAPS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};
