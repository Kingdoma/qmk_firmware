#include QMK_KEYBOARD_H
#include "quantum.h"
#include "raw_hid.h"

static uint8_t cpu_usage = 0;
static uint8_t ram_usage = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        TO(1),                     KC_MUTE,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                 KC_P0,   KC_PDOT
    ),

    [1] = LAYOUT(
        TO(2),                           KC_NUM,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,
                   _______,   _______
    ),

    [2] = LAYOUT(
        TO(0),                           RM_TOGG,
        _______,   RM_SPDD,   RM_VALD,   RM_PREV,
        _______,   RM_SPDU,   RM_VALU,   RM_NEXT,
        _______,   _______,   _______,   _______,
                   _______,   _______
    ),
};

#if defined(ENCODER_MAP_ENABLE)
oled_rotation_t oled_init_user(oled_rotation_t rotation){
    return OLED_ROTATION_180;
}

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
    [2] = { ENCODER_CCW_CW(RM_SATD, RM_SATU) }
};

#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    //oled_set_cursor(0, 0);
    oled_write_P(PSTR("     "), false);
    oled_write_P(PSTR("Layer:"), false);
    switch (get_highest_layer(layer_state))
    {
    case 0:
        oled_write_P(PSTR("Default"), false);
        break;
    case 1:
        oled_write_P(PSTR("Mouse"), false);
        break;
    case 2:
        oled_write_P(PSTR("RGB"), false);
        break;
    default:
        oled_write_P(PSTR("Unknow"), false);
        break;
    }

    oled_write_P(PSTR("\n\n    "), false);
    //oled_set_cursor(10, 0);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);
    oled_write_P(led_state.num_lock ? PSTR("   ") : PSTR("NUM"), false);

    char buffer[32];
    oled_write_P(PSTR("\n   "), false);
    //oled_set_cursor(3, 3);
    sprintf(buffer, "CPU:%d%%   ", cpu_usage);
    oled_write(buffer,false);

    sprintf(buffer, "RAM:%d%% ", ram_usage);
    oled_write(buffer,false);

    // oled_write_P(PSTR("MEM:"),false);
    // oled_write_P(PSTR("GPU:"),false);
    // oled_write_P(PSTR("TEMP:"),false);

    return false;
}
#endif

#ifdef RAW_ENABLE

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[length];
    memset(response, 0, length);

    if (data[0] == 0x01) {  // Custom command for metrics
        cpu_usage = data[1];
        ram_usage = data[2];

        //echo
        response[0] = 0xFF;  // Indicate successful receipt
        response[1] = data[1];
        response[2] = data[2];
    }

    raw_hid_send(response, length);
}
#endif
