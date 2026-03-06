/*
 * Copyright (c) 2026 wmrsouza@hotmail.com
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

#include <app_version.h>

int main(void)
{
	LOG_INF("Zephyr Example Application %s", APP_VERSION_STRING);
	LOG_WRN("Zephyr Example Application %s", APP_VERSION_STRING);
	LOG_ERR("Zephyr Example Application %s", APP_VERSION_STRING);
	LOG_DBG("Zephyr Example Application %s", APP_VERSION_STRING);

	while (1) {
		k_sleep(K_MSEC(100));
	}

	return 0;
}

