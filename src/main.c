/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <logging/log.h>
#include <liblogz_example_rs.h>

LOG_MODULE_REGISTER(blinky, LOG_LEVEL_DBG);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS	DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN	0
#define FLAGS	0
#endif

static bool on = false;
static const struct device* led_dev = NULL;

static uint32_t acc = 0;
void flip_timer(struct k_timer* timer) {
	LOG_INF("LED: %d", (int) on);
	gpio_pin_set(led_dev, PIN, (int)on);
	on = !on;
	register uint32_t r0 __asm__("r0") = acc;
	register uint32_t r1 __asm__("r1") = 0x01020304;
	register uint32_t r2 __asm__("r2");
	__asm__ (
		"uqadd8 r2, r0, r1\n\t"
	);
	acc = r2;
	LOG_INF("A: %8x B: %8x, C: %8x", r0, r1, r2);
	example_foo();
}
static K_TIMER_DEFINE(flip, flip_timer, NULL);

void main(void)
{
	int ret;

	led_dev = device_get_binding(LED0);
	if (led_dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(led_dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	if (ret < 0) {
		return;
	}

	k_timer_start(&flip, K_NO_WAIT, K_MSEC(250));

	while (1) {
		k_sleep(K_FOREVER);
	}
}
