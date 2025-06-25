#define DT_DRV_COMPAT zmk_behavior_tentatwo

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/behavior.h>

#include <zmk-tentatwo/hid.h>
#include <zmk-tentatwo/endpoints.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int on_behavior_tentatwo_binding_pressed(struct zmk_behavior_binding *binding,
                                                struct zmk_behavior_binding_event event)
{
  return toggle_binding(binding, event);
}

static int on_behavior_tentatwo_binding_released(struct zmk_behavior_binding *binding,
                                                 struct zmk_behavior_binding_event event)
{
  return toggle_binding(binding, event);
}

static int toggle_binding(struct zmk_behavior_binding *binding,
                             struct zmk_behavior_binding_event event)
{
  uint8_t button = binding->param1;
  toggle_button(button);
  zmk_endpoints_send_tentatwo_report();

  return ZMK_BEHAVIOR_OPAQUE;
}

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
