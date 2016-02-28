#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(FN0,  1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS, EQL, BSPC, \
           TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC, RBRC, ENT, \
           LCAP, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT, NUHS,      \
           LSFT, NUBS,Z,   X,   C,   V,   B,   N,   M,  COMM, DOT, SLSH, RSFT,  UP, \
           LCTL, LALT, LGUI,            SPC,                  RGUI,LEFT, RGHT, DOWN),


    /* 1: FN 1 */
    KEYMAP(TRNS,  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9, F10,  F11,  F12, DEL, \
           PWR , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,      \
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, MPRV, MNXT, MUTE, VOLD, VOLU, TRNS, TRNS, PGUP,\
           TRNS, TRNS, TRNS,                  MPLY,                  TRNS, HOME,  END, PGDN),
};
const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_LAYER_TAP_KEY(1, KC_ESC), 
};