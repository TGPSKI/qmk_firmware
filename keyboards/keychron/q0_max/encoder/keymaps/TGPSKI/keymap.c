/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE, _______, TO(L1), TO(L2), TO(FN),
        MC_1,	 KC_NUM, KC_PSLS,KC_PAST,KC_PMNS,
        MC_2,	 KC_P7,	 KC_P8,	 KC_P9,	 KC_PPLS,
        MC_3,	 KC_P4,	 KC_P5,	 KC_P6,
        MC_4,	 KC_P1,	 KC_P2,	 KC_P3,	 KC_PENT,
        MO(FN),    KC_P0,          KC_PDOT         ),

    [L1] = LAYOUT_tenkey_27(
        _______, TO(BASE), _______, TO(L2), TO(FN),
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______          ),

    [L2] = LAYOUT_tenkey_27(
        _______, TO(BASE), TO(L1), _______, TO(FN),
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______          ),

    [FN] = LAYOUT_tenkey_27(
        RGB_TOG, TO(BASE), TO(L1), TO(L2), _______,
        BT_HST1, RGB_MOD, RGB_VAI, RGB_HUI, _______,
        BT_HST2, RGB_RMOD,RGB_VAD, RGB_HUD, _______,
        BT_HST3, RGB_SAI, RGB_SPI, KC_MPRV,
        P2P4G,   RGB_SAD, RGB_SPD, KC_MPLY, _______,
        _______, RGB_TOG,          KC_MNXT          )

};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [L1]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [L2]   = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BASE:
            rgb_matrix_set_color(BASE_LED_INDEX, RGB_RED);  // circle
            rgb_matrix_set_color(L1_LED_INDEX, RGB_OFF);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX, RGB_OFF);  // square
            rgb_matrix_set_color(FN_LED_INDEX, RGB_OFF);  // cross
            break;
        case L1:
            rgb_matrix_set_color(BASE_LED_INDEX, RGB_OFF);  // circle
            rgb_matrix_set_color(L1_LED_INDEX, RGB_RED);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX, RGB_OFF);  // square
            rgb_matrix_set_color(FN_LED_INDEX, RGB_OFF);  // cross
            break;
        case L2:
            rgb_matrix_set_color(BASE_LED_INDEX, RGB_OFF);  // circle
            rgb_matrix_set_color(L1_LED_INDEX, RGB_OFF);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX, RGB_RED);  // square
            rgb_matrix_set_color(FN_LED_INDEX, RGB_OFF);  // cross0
            break;
        case FN:
            rgb_matrix_set_color(BASE_LED_INDEX, RGB_OFF);  // circle
            rgb_matrix_set_color(L1_LED_INDEX, RGB_OFF);  // triangle
            rgb_matrix_set_color(L2_LED_INDEX, RGB_OFF);  // square
            rgb_matrix_set_color(FN_LED_INDEX, RGB_RED);  // cross 
            break;
    }
    return state;
}
