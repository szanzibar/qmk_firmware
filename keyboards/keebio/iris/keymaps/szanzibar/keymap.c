#include QMK_KEYBOARD_H

// Reminder to run `qmk generate-compilation-database` if squiggles come back
// More context here: https://ptb.discord.com/channels/440868230475677696/440868230475677698/945364866800156723

enum my_layers { _DVORAK, _QWERTY, _SYMBOLS, _MEDIA, _GAMING };

// Tap Dance keycodes
enum td_keycodes {
    TD_ALTQ_DEL // DEL on tap, WIN + QWERTY on hold
};

enum combo_events { DASH_ARROW, EQUALS_ARROW, LEFT_DASH_ARROW, LEFT_EQUALS_ARROW, SHIFTS_CAPS, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;

#define SYMBOLS TT(_SYMBOLS)
#define MEDIA TT(_MEDIA)
#define GAMING TG(_GAMING)
#define LCTL_Q LM(_QWERTY, MOD_LCTL)
#define LALT_Q LM(_QWERTY, MOD_LALT)
#define LWIN_Q LM(_QWERTY, MOD_LGUI)
#define LCAG_Q LM(_QWERTY, MOD_LCTL | MOD_LALT | MOD_LGUI)
#define DASH_SYM LT(_SYMBOLS, KC_MINS)
#define Z_MEDIA LT(_MEDIA, KC_Z)
#define SCLN_MED LT(_MEDIA, KC_SCLN)
#define ALTQ_DEL TD(TD_ALTQ_DEL)

// Combos
const uint16_t PROGMEM dash_arrow_combo[]        = {DASH_SYM, KC_DOT, COMBO_END};
const uint16_t PROGMEM equals_arrow_combo[]      = {DASH_SYM, KC_DOT, KC_COMMA, COMBO_END};
const uint16_t PROGMEM left_dash_arrow_combo[]   = {DASH_SYM, KC_COMMA, COMBO_END};
const uint16_t PROGMEM left_equals_arrow_combo[] = {DASH_SYM, KC_QUOT, KC_COMMA, COMBO_END};
const uint16_t PROGMEM shifts_caps_combo[]       = {KC_LSFT, KC_RSFT, COMBO_END};

combo_t key_combos[] = {
    [DASH_ARROW] = COMBO_ACTION(dash_arrow_combo), [EQUALS_ARROW] = COMBO_ACTION(equals_arrow_combo), [LEFT_DASH_ARROW] = COMBO_ACTION(left_dash_arrow_combo), [LEFT_EQUALS_ARROW] = COMBO_ACTION(left_equals_arrow_combo), [SHIFTS_CAPS] = COMBO_ACTION(shifts_caps_combo),
};
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case DASH_ARROW:
            if (pressed) {
                SEND_STRING("->");
            }
            break;
        case EQUALS_ARROW:
            if (pressed) {
                SEND_STRING("=>");
            }
            break;
        case LEFT_DASH_ARROW:
            if (pressed) {
                SEND_STRING("<-");
            }
            break;
        case LEFT_EQUALS_ARROW:
            if (pressed) {
                SEND_STRING("<=");
            }
            break;
        case SHIFTS_CAPS:
            if (pressed) {
                tap_code(KC_CAPS);
            }
            break;
    }
}

// Tap dance states
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_SINGLE_TAP, // a third key is tapped after the double tap, "interrupting" the double tap
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_SINGLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

// Global tap dance state
static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for TD_ALTQ_DEL
void altqdel_finished(qk_tap_dance_state_t *state, void *user_data);
void altqdel_reset(qk_tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    DASH_SYM,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL_Q,  SCLN_MED, KC_Q,   KC_J,    KC_K,    KC_X,    MEDIA,            SYMBOLS, KC_B,    KC_M,    KC_W,    KC_V,    Z_MEDIA, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    LWIN_Q,  ALTQ_DEL, KC_BSPC,                  KC_SPC,  KC_ENT,  LCAG_Q
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

    [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,          _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYMBOLS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_GRV,  KC_EQL,  KC_LCBR, KC_RCBR, _______,                            KC_QUOT, KC_DQUO, KC_UP,   KC_LT,   KC_GT,   KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_TILD, KC_PLUS, KC_LPRN, KC_RPRN, _______,                            KC_PSCR, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_COLN, KC_SCLN, KC_LBRC, KC_RBRC, _______, _______,          _______, KC_APP,  KC_HOME, KC_END,  _______, KC_PGDN, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                    _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MEDIA] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, RESET,                              RESET,   KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, RGB_MOD, RGB_TOG,                            _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_MPRV, KC_MNXT, _______,                            _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, _______,          _______, KC_PDOT, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    GAMING,  _______, _______,                   _______, _______, KC_KP_0
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_GAMING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,          _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    GAMING,  _______, KC_SPC,                    _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
};
// clang-format on

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // a third key is tapped after the double tap, "interrupting" the double tap
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    } else if (state->count == 3) {
        if (state->interrupted)
            return TD_TRIPLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_TRIPLE_HOLD;
        else
            return TD_TRIPLE_TAP;
    } else
        return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void altqdel_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            layer_on(_QWERTY);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(LCTL(KC_DEL));
            break;
        default:
            for (uint8_t i = 0; i < state->count; i++) {
                tap_code(KC_DEL);
            }
            break;
    }
}

void altqdel_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_HOLD:
            layer_off(_QWERTY);
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {[TD_ALTQ_DEL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altqdel_finished, altqdel_reset)};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Converting hsv to rgb so that current brightness is respected
    // otherwise keyboard crashes from pulling too much power.
    // Some bug with WS2812 I guess? (https://docs.qmk.fm/#/feature_rgb_matrix?id=indicator-examples-1)
    uint8_t v   = rgb_matrix_get_val();
    HSV     hsv = {0, 255, v};

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    if (host_keyboard_led_state().caps_lock || (get_mods() & MOD_MASK_SHIFT)) {
        hsv.h = 0; // red
    } else {
        switch (layer) {
            case _QWERTY:
                hsv.h = 85;
                break; // green
            case _SYMBOLS:
                hsv.h = 170;
                break; // blue
            case _MEDIA:
                hsv.h = 43;
                break; // yellow
            case _GAMING:
                hsv.h = 128;
                break; // cyan
            default:
                hsv.v = 0;
                break;
        }
    }

    RGB rgb = hsv_to_rgb(hsv);
    if (hsv.v == 0) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], 0x02)) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
    } else {
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    }
}
