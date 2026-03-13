/*
 * Copyright (c) 2026 wmrsouza@hotmail.com
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/input/input.h>
#include <zephyr/dt-bindings/input/input-event-codes.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#include <app_version.h>

#define KBD_NODE DT_NODELABEL(kbd)
#define KBD_DEV  DEVICE_DT_GET(KBD_NODE)

#define KEYMAP_NODE DT_NODELABEL(keymap)
#define KEYMAP_DEV  DEVICE_DT_GET(KEYMAP_NODE)

static const struct device *input_dev;

static void input_cb(struct input_event *evt, void *user_data)
{
	if (input_dev != NULL && evt->dev != input_dev) {
		return;
	}

	if (evt->type != INPUT_EV_KEY) {
		return;
	}

	LOG_INF("key 0x%x %s", evt->code, evt->value ? "pressed" : "released");
}

void register_input_cb(const struct device *dev)
{
	input_dev = dev;
}

INPUT_CALLBACK_DEFINE(NULL, input_cb, NULL);

int main(void)
{
	LOG_INF("Zephyr Example Application %s", APP_VERSION_STRING);
	LOG_WRN("Zephyr Example Application %s", APP_VERSION_STRING);
	LOG_ERR("Zephyr Example Application %s", APP_VERSION_STRING);
	LOG_DBG("Zephyr Example Application %s", APP_VERSION_STRING);

	if (!device_is_ready(KBD_DEV)) {
		LOG_ERR("%s: device not ready.", KBD_DEV->name);
		return 0;
	}

	if (device_is_ready(KEYMAP_DEV)) {
		register_input_cb(KEYMAP_DEV);
		LOG_INF("input callback registered");
	} else {
		LOG_WRN("keymap device not ready, input callback not registered");
	}

	while (1) {
		k_sleep(K_MSEC(100));
	}

	return 0;
}

