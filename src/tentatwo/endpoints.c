
#include <zmk/endpoints.h>
#include <zmk/hid.h>
#include <zmk/usb_hid.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(tentatwo, CONFIG_ZMK_LOG_LEVEL);

#include <zmk-tentatwo/endpoints.h>
#include <zmk-tentatwo/hid.h>
#include <zmk-tentatwo/usb_hid.h>

int zmk_endpoints_send_tentatwo_report() {
    struct zmk_endpoint_instance current_instance = zmk_endpoints_selected();

    switch (current_instance.transport) {
#if IS_ENABLED(CONFIG_ZMK_USB)
    case ZMK_TRANSPORT_USB: {
        int err = zmk_usb_hid_send_tentatwo_report();
        if (err) {
            LOG_ERR("FAILED TO SEND OVER USB: %d", err);
        }
        return err;
    }
#else
    case ZMK_TRANSPORT_USB: break;
#endif /* IS_ENABLED(CONFIG_ZMK_USB) */

    case ZMK_TRANSPORT_BLE: break; // TODO: Implement BLE support

    LOG_ERR("Unsupported endpoint transport %d", current_instance.transport);
    return -ENOTSUP;
    }
    
    LOG_ERR("Unhandled endpoint transport %d", current_instance.transport);
    return -ENOTSUP;
}
