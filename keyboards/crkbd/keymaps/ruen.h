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
            default:
                break;
        }
    }
    return true;
}
