#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(FN0,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS, EQL , GRV, BSPC, \
           TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC, RBRC,      BSPC, \
           FN3,  A,   S, FN2,   F,   G,   H,   J,   K,   L,SCLN,   QUOT,            ENT,  \
           LSFT,      Z,   X,   C,   V,   B,   N,   M,COMM, DOT,   SLSH,      RSFT,       \
                CAPS, LALT, LGUI,                 SPC, FN1,LGUI,         LALT),


    /* 1: FN 1 */
    KEYMAP(TRNS,   F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,  F13, DEL, \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGUP,   UP, PGDN, TRNS,   UP, TRNS,      BSLS, \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, HOME, LEFT, DOWN, RGHT, LEFT, RGHT,            TRNS, \
           TRNS,       TRNS, TRNS, TRNS, TRNS, MRWD, MFFD, MUTE, VOLD, VOLU, DOWN,       TRNS,      \
                 TRNS, TRNS, TRNS,                         MPLY, TRNS, TRNS,       TRNS),
    
    
    /* 2: FN 2 */
    KEYMAP(TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, WH_U, MS_U, WH_D, TRNS, TRNS, TRNS,       TRNS, \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, WH_L, MS_L, MS_D, MS_R, WH_R, TRNS,             TRNS, \
           TRNS,       TRNS, TRNS, TRNS, BTN1, MPRV, BTN2, TRNS, TRNS, TRNS, TRNS,       TRNS,       \
                 TRNS, TRNS, TRNS,                         TRNS, TRNS, TRNS,       TRNS),
    
    /* 3: FN 3 */
    KEYMAP(TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, DEL, \
           TRNS, WH_D, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,   UP, TRNS, TRNS, WH_L, WH_R,      TRNS, \
           TRNS, WH_U, TRNS, TRNS, TRNS, TRNS, TRNS, LEFT, DOWN, RGHT, TRNS, TRNS,            TRNS, \
           TRNS,       TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS,      \
                 TRNS, TRNS, TRNS,                         TRNS, TRNS, TRNS,       TRNS),

};
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_TAP_KEY(1, KC_ESC),
  [1] = ACTION_LAYER_TAP_KEY(1, KC_BSLS),
  [2] = ACTION_LAYER_TAP_KEY(2, KC_D),
  [3] = ACTION_LAYER_MODS(3, MOD_LCTL),
};