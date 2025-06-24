# ZMK TentaTwo Module

This module contains the following modules for the tentatwo:
- keyboard defining the tentatwo shield
- behavior for sending tentatwo HID reports 

# Notes

The (USB)HID report descriptor is described in `hid`.

ZMK supports two transport modes, USB and BLE.
`usb_hid` covers the USB transport and `hog` (HID over GATT) covers the BLE transport.

How I imagine this solution working is the behavior will trigger the appropriate tentatwo report to be sent using either the USB-HID or HoG implementation.
The software side reading the custom reports will handle things like modifiers.

# References

The custom HID report implementation as a module is based off https://github.com/badjeff/zmk-hid-io.