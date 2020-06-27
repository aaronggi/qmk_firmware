
#include QMK_KEYBOARD_H


#include "stdint.h"

//I was tired of seeing red squiggles, this is pretty much a noop
//since this gets defined in rules.mk
#ifndef INTELLISENSE_HELPER
    #include "lily58.h"
    #include "quantum.h"
    #include "quantum_keycodes.h"
    #include "../../rev1/rev1.h"
    #include "../../rev1/config.h"
#endif

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

typedef uint16_t u16;

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ULTRA,
};



#define _QWERTY 0
#define _LOWER  1
#define _RAISE  2
#define _ULTRA  3
#define _NUMPD  4

extern uint8_t is_master;
LEADER_EXTERNS();

//Layer Taps
const static u16 LT_LWR = LT(_LOWER, KC_SPC);
const static u16 LT_RSE = LT(_RAISE, KC_ENT);
const static u16 LT_TBNP = LT(_NUMPD, KC_TAB);

//Mod Taps
const static u16 MT_QUOT = MT(MOD_RCTL, KC_QUOT);
const static u16 MT_RCBR = MT(MOD_RCTL, KC_RCBR);
const static u16 MT_RA_K = MT(MOD_RALT, KC_K);
const static u16 MT_LA_D = MT(MOD_RALT, KC_D);


const u16 PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tab LNP|   Q  |   W  |  E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |LALT/D|   F  |   G  |-------.    ,-------|   H  |   J  |K/RALT|   L  |   ;  | '/ctl|
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LALT | LEAD | /Space  /       \Enter \  |BackSP| RALT | RGUI |
 *                   |      |      |      |/ LLWR  /         \LRAISE\ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
  LT_TBNP,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    MT_LA_D, KC_F,    KC_G,                      KC_H,    KC_J,    MT_RA_K, KC_L,    KC_SCLN, MT_QUOT, \
  KC_LSPO,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, \
                             KC_LGUI, KC_LALT, KC_LEAD, LT_LWR,  LT_RSE,  KC_BSPC, KC_RALT, KC_RGUI \
),
/* LOWER
 * This looks a little weird because it has down in both vim-style as well as emacs
 * hitting raise and 'N' would be awkward, so i'm putting it in this layer.
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |			          |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   1  |   2  |   3  |   4  |  5   |                    |   6  |  7   |   8  |  9   |  0   |   \
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| down |     |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LALT |LEAD  | /Space  /       \Enter \  |BackSP| RALT | RGUI |
 *                   |      |      |      |/Lower  /         \RAISE \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LOWER] = LAYOUT( \
  KC_F1,    KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_TILD,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,     KC_8,    KC_9,    KC_0,  KC_BSLS, \
  _______,  _______, _______,  _______, _______, _______,                    XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, \
  _______,  _______, _______,  _______, _______, _______, _______, _______,  KC_DOWN, _______, _______, _______, _______, _______, \
                               _______, _______, _______, _______, _______,  _______, _______, _______ \
),
/* RAISE
 * Emacs-style keyboard shortcuts so I can navigate like I'm in emacs anywhere
 * ,-----------------------------------------.                    ,------------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |       |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 * |  `   |      | C-x  | end  |      |      |                    |      |      |   +  |   =  |  up  |       |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+-------|
 * | LCTRL| home |      | del  | right|  esc |-------.    ,-------|      | entr |   _  |   -  |   {  | }/CTL |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+-------|
 * | LS/( |      |      | pgup | pgdn|  left |-------|    |-------| down |  [   |   |  |   \  |  ]   | RS/)  |
 * `-----------------------------------------/       /     \      \------------------------------------------'
 *                   | LAlt | LGUI | LEAD | /Space  /       \Enter \  |BackSP| RALT | RGUI |
 *                   |      |      |      |/       /         \Raise \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  KC_GRV,  _______, C(KC_X),  KC_END, _______, _______,                   _______, _______, KC_PLUS, KC_EQL,  KC_UP, _______, \
  _______, KC_HOME, _______,  KC_DEL, KC_RIGHT,KC_ESC,                    _______, KC_ENT,  KC_UNDS, KC_MINS, KC_LCBR, MT_RCBR, \
  _______, _______, _______, KC_PGUP, KC_PGDN, KC_LEFT, _______, _______, KC_DOWN, KC_LBRC, KC_PIPE, KC_BSLS, _______, _______,	\
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),
/* ULTRA
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | RESET|      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ULTRA] =  LAYOUT( \
  RESET,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),

/* NUMPD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |   /  |  *   |  -   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |   7  |  8   |  9   |  +   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      | LSHFT|      |-------.    ,-------|      |  4   |  5   |  6   | ENT  | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | LSFT |      |      |      |      |      |-------|    |-------|      |   1  |  2   | 3    | ENT | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_NUMPD] =  LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1,    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

int RGB_current_mode;

// Setting ULTRA layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {


  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      else
      return false;
      break;
    }
  return true;
}

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;

    SEQ_ONE_KEY(KC_E) {
      // Anything you can do in a macro.
      //SEND_STRING(SS_LCTL(SS_LSFT("t")));
      //did_leader_succeed = true;
    }
    SEQ_TWO_KEYS(KC_M, KC_F) {
        SEND_STRING("cd $QMK_HOME && make " KEYBRD ":" GITUSERN ":" UPLOADER "");
        tap_code(KC_ENT);
        wait_ms(3000);
      reset_keyboard();
      //SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
      //did_leader_succeed = true;
    }

    SEQ_THREE_KEYS(KC_U, KC_L, KC_T){
    }
    leader_end();
  }
}

