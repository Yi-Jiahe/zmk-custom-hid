#pragma once

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include <zmk/hid.h>

#define HID_USAGE_PAGE_VENDOR_DEFINED 0xFF
#define ZMK_HID_REPORT_ID_TENTATWO 0x02

static const uint_8_t zmk_hid_tentatwo_report_desc[] = {
  HID_USAGE_PAGE(HID_USAGE_PAGE_VENDOR_DEFINED),
  HID_COLLECTION(HID_COLLECTION_APPLICATION),
    // 8 2-state buttons, one bit each
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX8(0x01),
    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(0x08),
    HID_INPUT(ZMK_HID_MAIN_VAL_DATA | ZMK_HID_MAIN_VAL_VAR | ZMK_HID_MAIN_VAL_ABS),
  HID_END_COLLECTION,
};

struct zmk_hid_tentatwo_report_body {
  uint8_t buttons;
} __packed;

struct zmk_hid_tentatwo_report {
  struct zmk_hid_tentatwo_report_body body;
} __packed;

int toggle_button(uint8_t button);

struct zmk_hid_tentatwo_report *get_tentatwo_report(void);
