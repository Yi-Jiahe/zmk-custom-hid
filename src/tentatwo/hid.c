
#include "zmk/keys.h"

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(tentatwo, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/hid.h>
#include <dt-bindings/zmk/modifiers.h>
#include <zmk/keymap.h>

#include <zmk-tentatwo/hid.h>

static struct zmk_hid_tentatwo_report tentatwo_report = {
    .body = {
        .buttons = 0,
    },
};

int toggle_button(uint8_t button) {
    if (button >= 8) {
        LOG_ERR("Invalid button index: %d", button);
        return -EINVAL;
    }

    // Toggle the specified button
    tentatwo_report.body.buttons ^= (1 << button);
    LOG_DBG("Toggled button %d, new state: 0x%02X", button, tentatwo_report.body.buttons);

    return 0;
}

struct zmk_hid_tentatwo_report *zmk_hid_get_tentatwo_report(void) {
    return &tentatwo_report;
}
