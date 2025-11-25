/* Copyright 2025 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"
#include "TGPSKI.h"

enum layers {
    BASE,
    L1,
    L2,
    FN,
};

enum custom_keycodes {
    MV_D_1 = SAFE_RANGE, // num/clear
    MV_D_2, // /
    MV_D_3, // *
    MV_D_4, // -
    TASK_SWITCHER_FW, // enter
    ACTIVE_MAXIMIZE_TOGGLE, // 0
    ACTIVE_MINIMIZE_TOGGLE, // .
    ACTIVE_CURRENT_DESKTOP, // +
    WINDOW_ZOOM_IN, // encoder right
    WINDOW_ZOOM_OUT, // encoder left
    WINDOW_ZOOM_RESET, // encoder press
    DESKTOP_ZOOM_IN, // mod + encoder right
    DESKTOP_ZOOM_OUT, // mod + encoder left
    DESKTOP_ZOOM_RESET, // mod + encoder press
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

// Prefix: Meta + Ctrl + Alt + 
// Key / Mod Key
// ONE:  D / F
// TWO:  B / N
// THREE: H / J
// FOUR: E / R
// FIVE: C / V
// SIX: T / Y
// SEVEN: M / ,
// EIGHT: . / /
// NINE: K / L

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        WINDOW_ZOOM_RESET,     _______,                TO(L1),                   TO(L2),                 TO(FN),
        KC_LALT,               MV_D_1,                 MV_D_2,                   MV_D_3,                 MV_D_4,
        KC_LALT,               SEVEN,                  EIGHT,                    NINE,                   ACTIVE_CURRENT_DESKTOP,
        KC_LALT,               FOUR,                   FIVE,                     SIX,
        KC_LALT,               ONE,                    TWO,                      THREE,                  
        KC_LALT,               ACTIVE_MAXIMIZE_TOGGLE,                           ACTIVE_MINIMIZE_TOGGLE, TASK_SWITCHER_FW                           ),

    [L1] = LAYOUT_tenkey_27(
        QK_BOOTLOADER,         TO(BASE),               _______,                   TO(L2),                 TO(FN),
        KC_LALT,               MV_D_1,                 MV_D_2,                    MV_D_3,                 MV_D_4,
        _______,               _______,                _______,                   _______,                _______,
        _______,               _______,                _______,                   _______,
        _______,               _______,                _______,                   _______,                
        _______,               _______,                                           _______,                _______                          ),
 
    [L2] = LAYOUT_tenkey_27(
        KC_MUTE,               TO(BASE),               TO(L1),                    _______,                TO(FN),
        KC_LALT,               MV_D_1,                 MV_D_2,                    MV_D_3,                 MV_D_4,
        _______,               _______,                _______,                   _______,                _______,
        _______,               _______,                _______,                   _______,
        _______,               _______,                _______,                   _______,                
        _______,               _______,                                           _______,                _______                         ),

    [FN] = LAYOUT_tenkey_27(
        RGB_TOG,               TO(BASE),               TO(L1),                    TO(L2),                 _______,
        BT_HST1,               RGB_MOD,                RGB_VAI,                   RGB_HUI,                _______,
        BT_HST2,               RGB_RMOD,               RGB_VAD,                   RGB_HUD,                _______,
        BT_HST3,               RGB_SAI,                RGB_SPI,                   KC_MPRV,
        P2P4G,                 RGB_SAD,                RGB_SPD,                   KC_MPLY,                
        _______,               RGB_TOG,                                           KC_MNXT,                _______                        )
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(WINDOW_ZOOM_OUT, WINDOW_ZOOM_IN)},
    [L1]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [L2]   = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    // printf("Mods: %d, Oneshot mods: %d\n", mods, oneshot_mods);
    // printf("Layer state in process_record_user(): %d\n", get_highest_layer(layer_state));
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    switch (keycode) {
        // VIRTUAL DESKTOPS
        case MV_D_1:
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LSFT(SS_TAP(X_F1)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_F1)));
                }
            return false;
            }
        case MV_D_2:
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LSFT(SS_TAP(X_F2)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_F2)));
                }
                return false;
            }
        case MV_D_3:
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LSFT(SS_TAP(X_F3)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_F3)));
                }
                return false;
            }
        case MV_D_4:
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LSFT(SS_TAP(X_F4)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_TAP(X_F4)));
                }
                return false;
            }
        case ONE:
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_F)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_D)))));
                }                
                return false;
            }
        case TWO:
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_N)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_B)))));
                }
                return false;
            }
        case THREE: 
            if (record->event.pressed) {
                if (( mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_J)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_H)))));
                }
                return false;
            }
        case FOUR:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_R)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_E)))));
                }
                return false;
            }
        case FIVE:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_V)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_C)))));
                }
                return false;
            }
        case SIX:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_Y)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_T)))));
                }
                return false;
            }
        case SEVEN:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_COMMA)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_M)))));
                }
                return false;
            }
        case EIGHT:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_SLASH)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_DOT)))));
                }
                return false;
            }
        case NINE:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_L)))));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_K)))));
                }
                return false;
            }
        // ACTIVE_WINDOWS_AND_UW_2x1_1x2_1U
        case ACTIVE_MAXIMIZE_TOGGLE: // 0
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LWIN(SS_TAP(X_LEFT)));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LWIN(SS_TAP(X_W)));
                }
                return false;
            }
        case ACTIVE_MINIMIZE_TOGGLE: // .
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LWIN(SS_TAP(X_RIGHT)));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LWIN(SS_LCTL(SS_TAP(X_DOWN))));
                }
                return false;
            }
        case TASK_SWITCHER_FW: // enter
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LWIN(SS_TAP(X_DOWN)));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_LALT(SS_LSFT(SS_TAP(X_F4))));
                }
                return false;
            }
        case ACTIVE_CURRENT_DESKTOP: // +
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LWIN(SS_TAP(X_UP)));
                    register_mods(mods);
                } else {
                    SEND_STRING(SS_TAP(X_F3));
                }
                return false;
            }
        // ZOOM
        case WINDOW_ZOOM_IN: 
            if (record->event.pressed) { // DESKTOP
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_Q)))));
                    register_mods(mods);
                } else { // WINDOW
                    SEND_STRING(SS_LALT(SS_TAP(X_EQUAL)));
                }
                return false;
            }
        case WINDOW_ZOOM_OUT:
            if (record->event.pressed) { // DESKTOP
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_TAP(X_W)))));
                    register_mods(mods);
                } else { // WINDOW
                    SEND_STRING(SS_LALT(SS_TAP(X_MINUS)));
                }
                return false;
            }
        case WINDOW_ZOOM_RESET:
            if (record->event.pressed) { // DESKTOP
                if ((mods | oneshot_mods) & MOD_MASK_ALT) {
                    del_oneshot_mods(MOD_MASK_ALT);
                    unregister_mods(MOD_MASK_ALT);
                    SEND_STRING(SS_LALT(SS_LWIN(SS_LCTL(SS_LSFT(SS_TAP(X_R))))));
                    register_mods(mods);
                } else { // WINDOW
                    SEND_STRING(SS_LALT(SS_TAP(X_0)));
                }
                return false;
            }
    }
    return true;
}

bool set_layer_indicators(void) {
    switch (get_highest_layer(layer_state)) {
        case BASE:
            // printf("Matched base, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  212, 0, 255); // purp  // circle
            rgb_matrix_set_color(L1_LED_INDEX, 0, 0, 0);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  0, 0, 0);  // square
            rgb_matrix_set_color(FN_LED_INDEX,  0, 0, 0);  // cross
            break;
        case L1:
            // printf("Matched L1, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  0, 0, 0);  // circle
            rgb_matrix_set_color(L1_LED_INDEX,  212, 0, 255);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  0, 0, 0);  // square
            rgb_matrix_set_color(FN_LED_INDEX,  0, 0, 0);  // cross
            break;
        case L2:
            // printf("Matched L2, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  0, 0, 0);  // circle
            rgb_matrix_set_color(L1_LED_INDEX,  0, 0, 0);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  212, 0, 255);  // square
            rgb_matrix_set_color(FN_LED_INDEX,  0, 0, 0);  // cross
            break;
        case FN:
            // printf("Matched FN, rgb_matrix_indicators_user\n");
            rgb_matrix_set_color(BASE_LED_INDEX,  0, 0, 0);  // circle
            rgb_matrix_set_color(L1_LED_INDEX,  0, 0, 0);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX,  0, 0, 0);  // square
             rgb_matrix_set_color(FN_LED_INDEX,  212, 0, 255);  // cross 
            break;
   }
   return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // TRANSITION M KEYS FROM PURPLE TO RED
    RGB_MATRIX_INDICATOR_SET_COLOR(M1_LED_INDEX, 221, 0, 204);
    RGB_MATRIX_INDICATOR_SET_COLOR(M2_LED_INDEX, 230, 0, 153);
    RGB_MATRIX_INDICATOR_SET_COLOR(M3_LED_INDEX, 239, 0, 102);
    RGB_MATRIX_INDICATOR_SET_COLOR(M4_LED_INDEX, 248, 0, 51);

    // KEEP M5 GLOWING RED
    RGB_MATRIX_INDICATOR_SET_COLOR(M5_LED_INDEX, 255, 0, 0);

    // SET PLAYSTATION KEYs LAYER INDICATOR
    if (led_min <= BASE_LED_INDEX && led_max >= FN_LED_INDEX) {
        return set_layer_indicators();
    }

    return false;
}