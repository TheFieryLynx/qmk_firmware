#pragma once

#include QMK_KEYBOARD_H
#include "eeconfig.h"

#define CH_LG LALT(KC_CAPS) // change language

enum custom_keycodes {
    LG_ACTN = SAFE_RANGE, // change language and change flag
    LG_SYNC, // change flag if system language is out of sync
    // RN == RUEN
    RN_LCBR, // {
    RN_RCBR, // }
    RN_LBRC, // [
    RN_RBRC, // ]
    RN_GRV,  // ~
    RN_LOAB, // <
    RN_ROAB, // >
    RN_QUOT1,// '
    RN_QUOT2,// "
    RN_QUEST,// ?
    RN_AMSD, // &
    RN_DLLR, // $
    RN_CRT,  // ^
    RN_SMCL, // ;
    RN_CL,   // :
    RN_DOG,  // @
    RN_HASH, // #
    RN_TLD,  // `
    RN_SLSH, // /
    RN_VERT, // |
    RN_DOT,  // .
    RN_COMM, // ,
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
            case RN_LCBR:
                tap_symbol(KC_LCBR);
                return false;
            case RN_RCBR:
                tap_symbol(KC_RCBR);
                return false;
            case RN_LBRC:
                tap_symbol(KC_LBRC);
                return false;
            case RN_RBRC:
                tap_symbol(KC_RBRC);
                return false;
            case RN_GRV:
                tap_symbol(LSFT(KC_GRV));
                return false;
            case RN_LOAB:
                tap_symbol(LSFT(KC_COMM));
                return false;
            case RN_ROAB:
                tap_symbol(LSFT(KC_DOT));
                return false;
            case RN_QUOT1:
                tap_symbol(KC_QUOT);
                return false;
            case RN_QUOT2:
                tap_symbol(LSFT(KC_QUOT));
                return false;
            case RN_QUEST:
                tap_symbol(LSFT(KC_SLSH));
                return false;
            case RN_AMSD:
                tap_symbol(LSFT(KC_7));
                return false;
            case RN_DLLR:
                tap_symbol(LSFT(KC_4));
                return false;
            case RN_CRT:
                tap_symbol(LSFT(KC_6));
                return false;
            case RN_SMCL:
                tap_symbol(KC_SCLN);
                return false;
            case RN_CL:
                tap_symbol(LSFT(KC_SCLN));
                return false;
            case RN_DOG:
                tap_symbol(LSFT(KC_2));
                return false;
            case RN_HASH:
                tap_symbol(LSFT(KC_3));
                return false;
            case RN_TLD:
                tap_symbol(KC_GRV);
                return false;
            case RN_SLSH:
                tap_symbol(KC_SLSH);
                return false;
            case RN_VERT:
                tap_symbol(LSFT(KC_BSLS));
                return false;
            case RN_DOT:
                tap_symbol(KC_DOT);
                return false;
            case RN_COMM:
                tap_symbol(KC_COMM);
                return false;
            default:
                break;
        }
    }
    return true;
}
