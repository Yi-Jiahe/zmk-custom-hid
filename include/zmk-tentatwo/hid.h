#pragma once

#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>

#include <zmk/hid.h>

#define HID_USAGE_PAGE_VENDOR_DEFINED 0xFF

static const uint8_t zmk_hid_tentatwo_report_desc[] = {
  // Usage Page (Vendor Defined)
  // Usage (0x01)
  // Collection (Application)
  //   Usage (0x02)
  //   Logical Minimum (0)
  //   Logical Maximum (1)
  //   Report Size (1)
  //   Report Count (12)
  //   Input (Data, Variable, Absolute)
  //   Usage (0x03)
  //   Logical Minimum (-1)
  //   Logical Maximum (1)
  //   Report Size (2)
  //   Report Count (1)
  //   Input (Data, Variable, Absolute)
  //   Report Size (1)
  //   Report Count (2)
  //   Input (Constant)
  // End Collection
  HID_USAGE_PAGE(HID_USAGE_PAGE_VENDOR_DEFINED),
  HID_USAGE(0x01),
  HID_COLLECTION(HID_COLLECTION_APPLICATION),
    // 12 2-state buttons, one bit each
    HID_USAGE(0x02),
    HID_LOGICAL_MIN8(0x00),
    HID_LOGICAL_MAX8(0x01),
    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(0x0C), // 12
    HID_INPUT(ZMK_HID_MAIN_VAL_DATA | ZMK_HID_MAIN_VAL_VAR | ZMK_HID_MAIN_VAL_ABS),

    // Encoder with 3 states
    HID_USAGE(0x03),
    HID_LOGICAL_MIN8(0xFF), // -1
    HID_LOGICAL_MAX8(0x01),
    HID_REPORT_SIZE(0x02),
    HID_REPORT_COUNT(0x01),
    HID_INPUT(ZMK_HID_MAIN_VAL_DATA | ZMK_HID_MAIN_VAL_VAR | ZMK_HID_MAIN_VAL_ABS),
    
    // Byte padding
    HID_REPORT_SIZE(0x01),
    HID_REPORT_COUNT(0x02),
    HID_INPUT(ZMK_HID_MAIN_VAL_CONST),
  HID_END_COLLECTION,
};

struct zmk_hid_tentatwo_report_body {
  uint16_t buttons: 12;
  uint8_t encoder: 2;
  uint8_t padding: 2;
} __packed;

struct zmk_hid_tentatwo_report {
  struct zmk_hid_tentatwo_report_body body;
} __packed;

int toggle_button(uint8_t button);

int set_encoder(int8_t val);

struct zmk_hid_tentatwo_report *zmk_hid_get_tentatwo_report(void);
