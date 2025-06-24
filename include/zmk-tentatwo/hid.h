#pragma once

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include <zmk/hid.h>

#define HID_USAGE_PAGE_VENDOR_DEFINED 0xFF

static const uint_8_t zmk_hid_report_desc_tentatwo[] = {
  HID_USAGE_PAGE(HID_USAGE_PAGE_VENDOR_DEFINED),
  HID_COLLECTION(HID_COLLECTION_APPLICATION),
    // One button
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX8(0x01),
    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(0x01),
    HID_INPUT(ZMK_HID_MAIN_VAL_DATA | ZMK_HID_MAIN_VAL_VAR | ZMK_HID_MAIN_VAL_ABS),
  HID_END_COLLECTION,
};

