#pragma once

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
#define MATRIX_ROWS 5
#define MATRIX_COLS 4


#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 3

#define LED_PIN_ON_STATE 1

#define RGB_MATRIX_LED_COUNT 15
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_KEYPRESSES

#define F_SCL 400000
#define OLED_SCROLL_TIMEOUT 120000
#define OLED_TIMEOUT 180000
#define OLED_UPDATE_INTERVAL 50

#define NO_USB_STARTUP_CHECK
