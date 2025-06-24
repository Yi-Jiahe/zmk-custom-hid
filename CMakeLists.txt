zephyr_library()

  if (CONFIG_ZMK_BLE)
    zephyr_library_sources_ifdef(CONFIG_ZMK_HID_IO src/hid-io/hog.c)
  endif()
