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

enum planck_layers {
  _QWERTY,
  _GAMING,
  _SYMBOLS,
  _NAV,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  GAMING,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD,
    TD_TRIPLE_SINGLE_TAP,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum tapdance {
  NAV_NUMPAD,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SYMBOLS MO(_SYMBOLS)
#define NAV MO(_NAV)
#define NUMPAD MO(_NUMPAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,---------------------------------------------------------------------------------------------.
 * |  Tab |   Q     |   W    |   E  |   R  |   T  |   Y  |   U  |   I  |    O   |    P    |      |
 * |------+---------+--------+------+------+------+------+------+------+--------+---------+------|
 * |      |   A     |   S    |   D  |   F  |   G  |   H  |   J  |   K  |    L   |    ;    |WIN(")|
 * |------+---------+--------+------+------+------+------+------+------+--------+---------+------|
 * | Shift| Ctrl(Z) | Alt(X) |   C  |   V  |   B  |   N  |   M  |   ,  | Alt(.) | Ctrl(/) | Shift|
 * |------+---------+--------+------+------+------+------+------+------+--------+---------+------|
 * | Esc  |         |        |  Nav |Lower | Space| Bksp |Raise |  Nav |        |         |Enter |
 * `---------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB, KC_Q,         KC_W,         KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,           KC_P,            XXXXXXX,
    XXXXXXX, KC_A,         KC_S,         KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,           KC_SCLN,         LGUI_T(KC_QUOT),
    KC_LSPO, LCTL_T(KC_Z), LALT_T(KC_X), KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, RALT_T(KC_DOT), RCTL_T(KC_SLSH), KC_RSPC,
    LT(_SYMBOLS,KC_ESC), XXXXXXX,      XXXXXXX,      TD(NAV_NUMPAD), LOWER,   KC_SPC,  KC_BSPC,  RAISE,   NAV, XXXXXXX,     XXXXXXX,   KC_ENT
),

/* Gaming
 * ,-----------------------------------------------------------------------------------.
 * |  Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | Alt   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Ctl  |  Win |  Alt |      |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMING] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LALT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LGUI_T(KC_QUOT),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |   =  |   !  |   @  |  {   |   }  |  |   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   -  |   #  |  $   |  (   |   )  |  `   |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   &  |   %  |   ^  |  [   |   ]  |   ~  |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_planck_grid(
    KC_EQL,  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______, _______, _______, _______,
    KC_MINS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  _______, _______, _______, _______, _______, _______,
    KC_AMPR, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,  _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______
),

/* Nav
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |  Up  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Left | Down | Right|      |      | Left | Down |  Up  | Right|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAV] = LAYOUT_planck_grid(
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______,  _______, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |   7  |  8   |  9   |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   4  |  5   |  6   |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   1  |  2   |  3   |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   0  |  .   |  /   |  =   |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______,  _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_ASTERISK,
    _______, _______, _______, _______, _______,  _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS,
    _______, _______, _______, _______, _______,  _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_PLUS,
    _______, _______, _______, _______, _______,  _______, _______, _______, KC_KP_0, KC_KP_DOT, KC_KP_SLASH, KC_KP_EQUAL
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  tab | enter|      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------+-----------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, KC_TAB, KC_ENT, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  del  |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------+-----------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, KC_DEL, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |    EEPROM Reset  | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |    |Aud on|Audoff|      |      |Qwerty|Gaming|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |       |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    EEP_RST, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, _______,  AU_ON,   AU_OFF,  _______, _______, QWERTY,  GAMING,   _______, _______, _______,
    _______, _______,  _______,  _______,   _______,  _______,   _______,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case GAMING:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAMING);
      }
      return false;
      break;
  }
  return true;
}

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->interrupted) return TD_TRIPLE_SINGLE_TAP;
        else if (state->pressed) return TD_TRIPLE_HOLD;
        else return TD_TRIPLE_TAP;
    } else return TD_UNKNOWN;
}

static td_tap_t nav_num_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void nav_num_finished(qk_tap_dance_state_t *state, void *user_data) {
    nav_num_tap_state.state = cur_dance(state);
    switch (nav_num_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_on(_NAV);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_NUMPAD);
            break;
        default:
            break;
    }
}

void nav_num_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (nav_num_tap_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(_NAV);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_NUMPAD);
            break;
        default:
            break;
    }
    nav_num_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [NAV_NUMPAD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, nav_num_finished, nav_num_reset, 200)
};
