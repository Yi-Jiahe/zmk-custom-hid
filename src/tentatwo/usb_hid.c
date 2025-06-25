#include <zephyr/device.h>
#include <zephyr/init.h>

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>
#include <zephyr/logging/log.h>

#include <zmk/usb.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <zmk/event_manager.h>

#include <zmk-tentatwo/hid.h>

LOG_MODULE_DECLARE(hid_io, CONFIG_ZMK_HID_IO_LOG_LEVEL);

static const struct device *hid_dev;

static K_SEM_DEFINE(hid_sem, 1, 1);

static void in_ready_cb(const struct device *dev) { k_sem_give(&hid_sem); }

#define HID_GET_REPORT_TYPE_MASK 0xff00
#define HID_GET_REPORT_ID_MASK 0x00ff

#define HID_REPORT_TYPE_INPUT 0x100
#define HID_REPORT_TYPE_OUTPUT 0x200
#define HID_REPORT_TYPE_FEATURE 0x300

static int get_report_cb(const struct device *dev, struct usb_setup_packet *setup, int32_t *len,
                         uint8_t **data)
{
    switch (setup->wValue & HID_GET_REPORT_TYPE_MASK)
    {
    case HID_REPORT_TYPE_INPUT:
        struct zmk_hid_tentatwo_report *report = zmk_hid_get_report();
        *data = (uint8_t *)report;
        *len = sizeof(*report);
        break;
    default:
        LOG_ERR("Unsupported report type %d requested", (setup->wValue & HID_GET_REPORT_TYPE_MASK)
                                                            << 8);
        return -ENOTSUP;
    }

    return 0;
}

static int set_report_cb(const struct device *dev, struct usb_setup_packet *setup, int32_t *len,
                         uint8_t **data)
{
    LOG_ERR("Unsupported report type %d requested", (setup->wValue & HID_GET_REPORT_TYPE_MASK) << 8);
    return -ENOTSUP;
}

static const struct hid_ops ops = {
    .int_in_ready = in_ready_cb,
    .get_report = get_report_cb,
    .set_report = set_report_cb,
};

static int zmk_usb_hid_send_report(const uint8_t *report, size_t len)
{
    switch (zmk_usb_get_status())
    {
    case USB_DC_SUSPEND:
        return usb_wakeup_request();
    case USB_DC_ERROR:
    case USB_DC_RESET:
    case USB_DC_DISCONNECTED:
    case USB_DC_UNKNOWN:
        return -ENODEV;
    default:
        k_sem_take(&hid_sem, K_MSEC(30));
        int err = hid_int_ep_write(hid_dev, report, len, NULL);

        if (err)
        {
            k_sem_give(&hid_sem);
        }

        return err;
    }
}

int zmk_usb_hid_send_tentatwo_report(void)
{
    size_t len;
    uint8_t *report = get_tentatwo_report(&len);
    return zmk_usb_hid_send_report(report, len);
}

static int zmk_usb_hid_init(void)
{
    hid_dev = device_get_binding("HID_1");
    if (hid_dev == NULL)
    {
        LOG_ERR("Unable to locate HID device");
        return -EINVAL;
    }

    usb_hid_register_device(hid_dev, zmk_hid_tentatwo_report_desc, sizeof(zmk_hid_tentatwo_report_desc), &ops);

    usb_hid_init(hid_dev);

    return 0;
}

SYS_INIT(zmk_usb_hid_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
