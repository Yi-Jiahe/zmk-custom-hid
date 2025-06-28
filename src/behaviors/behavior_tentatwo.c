#define DT_DRV_COMPAT zmk_behavior_tentatwo

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>

#include <zmk-tentatwo/hid.h>
#include <zmk-tentatwo/endpoints.h>

LOG_MODULE_DECLARE(tentatwo, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event)
{
  LOG_DBG("on_keymap_binding_pressed: button %d", binding->param1);
  uint8_t param1 = binding->param1;

  if (param1 >= 0 && param1 < 12)
  {
    toggle_button((uint16_t)param1);
  }
  else if (param1 == 12)
  {
    set_encoder(-1);
  }
  else if (param1 == 13)
  {
    set_encoder(1);
  }
  else
  {
    return -EINVAL;
  }

  zmk_endpoints_send_tentatwo_report();

  return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event)
{
  LOG_DBG("on_keymap_binding_released: button %d", binding->param1);
  uint8_t param1 = binding->param1;

  if (param1 >= 0 && param1 < 12)
  {
    toggle_button((uint16_t)param1);
  }
  else if (param1 < 14)
  {
    set_encoder(0);
  }
  else
  {
    return -EINVAL;
  }

  zmk_endpoints_send_tentatwo_report();

  return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_tentatwo_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

#define TENTATWO_INST(n)                                          \
  BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL, \
                          CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_tentatwo_driver_api);

DT_INST_FOREACH_STATUS_OKAY(TENTATWO_INST)

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */