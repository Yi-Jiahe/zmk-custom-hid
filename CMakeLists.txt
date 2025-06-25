zephyr_library()

if ((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  zephyr_library_sources_ifdef(CONFIG_ZMK_TENTATWO src/behaviors/behavior_tentatwo.c)

  zephyr_library_sources_ifdef(CONFIG_ZMK_TENTATWO src/tentatwo/tentatwo.c)
  zephyr_library_sources_ifdef(CONFIG_ZMK_TENTATWO src/tentatwo/endpoints.c)
  zephyr_library_sources_ifdef(CONFIG_ZMK_TENTATWO src/tentatwo/hid.c)
  zephyr_library_sources_ifdef(CONFIG_ZMK_TENTATWO src/tentatwo/usb_hid.c)
  if (CONFIG_ZMK_BLE)
  endif()
  zephyr_include_directories(include)

  zephyr_include_directories(${APPLICATION_SOURCE_DIR}/include)
endif()