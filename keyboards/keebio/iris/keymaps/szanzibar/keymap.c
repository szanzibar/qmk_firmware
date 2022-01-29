#include QMK_KEYBOARD_H
enum my_layers {
    _DVORAK,
    _QWERTY,
    _SYMBOLS,
    _MEDIA
};

#define SYMBOLS TT(_SYMBOLS)
#define MEDIA TT(_MEDIA)
#define LCTL_Q LM(_QWERTY, MOD_LCTL)
#define LALT_Q LM(_QWERTY, MOD_LALT)
#define LWIN_Q LM(_QWERTY, MOD_LGUI)
#define SHF_CAP MT(MOD_LSFT, KC_CAPS)
#define DASH_SYM LT(_SYMBOLS, KC_MINS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_DVORAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                               KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     LCTL_Q,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                               KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    DASH_SYM,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     SHF_CAP, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_DEL,           MEDIA,   KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    LWIN_Q,  LALT_Q,  KC_BSPC,                   KC_SPC,  KC_ENT,  SYMBOLS
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
     _______, KC_GRV,  KC_EQL,  KC_LCBR, KC_RCBR, _______,                            _______, KC_HOME, _______, KC_PGUP, _______, KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_TILD, KC_PLUS, KC_LPRN, KC_RPRN, _______,                            _______, KC_END,  KC_UP,   KC_PGDN, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,          _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                    _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_MEDIA] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, RESET,                              _______, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______,                            _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_MOD, KC_MPRV, KC_MNXT, KC_VOLU, _______, _______,                            _______, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, _______, _______, _______,          _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t v = rgb_matrix_get_val();

    HSV blue_hsv = {170, 255, v};
    RGB blue = hsv_to_rgb(blue_hsv);

    HSV yellow_hsv = {43, 255, v};
    RGB yellow = hsv_to_rgb(yellow_hsv);

    uint8_t layer = get_highest_layer(layer_state|default_layer_state);

    switch(layer) {
        case _SYMBOLS:
            rgb_matrix_set_color(0, blue.r, blue.g, blue.b);
            break;
        case _MEDIA:
            rgb_matrix_set_color(0, yellow.r, yellow.g, yellow.b);
            break;
        default:
            break;
    }
}

// void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     HSV hsv = {0, 0, 0};
//     RGB rgb = {0, 0, 0};
//     hsv.v = rgb_matrix_get_val();

//     switch(get_highest_layer(layer_state|default_layer_state)) {
//         case _SYMBOLS:
//             // blue
//             hsv.h = 170;
//             hsv.s = 255;
//             rgb = hsv_to_rgb(hsv);
//             rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
//             break;
//         case _MEDIA:
//             // yellow
//             hsv.h = 43;
//             hsv.s = 255;
//             rgb = hsv_to_rgb(hsv);
//             rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
//             break;
//         default:
//             break;
//     }
// }

// void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     uint8_t val = rgb_matrix_get_val();

//     switch(get_highest_layer(layer_state|default_layer_state)) {
//         case _SYMBOLS:
//             // blue
//             rgb_matrix_sethsv_noeeprom(170, 255, val);
//             break;
//         case _MEDIA:
//             // yellow
//             rgb_matrix_sethsv_noeeprom(43, 255, val);
//             break;
//         default:
//             rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
//             break;
//     }
// }

