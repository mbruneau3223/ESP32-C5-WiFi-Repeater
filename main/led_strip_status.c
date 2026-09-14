/* Addressable LED strip status indicator.
 *
 * Uses the Espressif led_strip component with the RMT backend.
 *
 * SPDX-License-Identifier: MIT
 */

#include "led_strip_status.h"
#include "router_config.h"
#include "wifi_config.h"
#include "esp_log.h"

static const char *TAG = "led_strip";

/* ---- Global ---- */
int led_strip_gpio = -1;

/* ---- Private state (common) ---- */
static volatile bool traffic_flag = false;
static volatile bool factory_reset_flag = false;

/* ======================================================================
 * * WS2812 status LED using Espressif led_strip RMT backend
 * ====================================================================== */

#include "led_strip.h"

static led_strip_handle_t strip_handle = NULL;

static void strip_set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    if (strip_handle) {
        led_strip_set_pixel(strip_handle, 0, r, g, b);
        led_strip_refresh(strip_handle);
    }
}

static void strip_off(void)
{
    if (strip_handle) {
        led_strip_clear(strip_handle);
        led_strip_refresh(strip_handle);
    }
}

void led_strip_status_init(void)
{
    if (led_strip_gpio < 0) {
        ESP_LOGI(TAG, "LED strip disabled (no GPIO configured)");
        return;
    }

    led_strip_config_t strip_config = {
        .strip_gpio_num = led_strip_gpio,
        .max_leds = 1,
        .led_model = LED_MODEL_WS2812,
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
        .flags.invert_out = 0,
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000,
        .mem_block_symbols = 64,
        .flags.with_dma = false,
    };

    esp_err_t err = led_strip_new_rmt_device(&strip_config, &rmt_config, &strip_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create LED strip on GPIO %d: %s",
                 led_strip_gpio, esp_err_to_name(err));
        strip_handle = NULL;
        return;
    }

    strip_off();
    ESP_LOGI(TAG, "LED strip on GPIO %d", led_strip_gpio);
}

bool led_strip_is_active(void)
{
    return strip_handle != NULL;
}

void led_strip_status_update(void)
{
    if (strip_handle == NULL)
        return;

    static uint8_t tick = 0;
    tick++;

    if (factory_reset_flag) {
        if (tick & 1)
            strip_set_rgb(60, 0, 0);
        else
            strip_set_rgb(0, 0, 60);
        return;
    }

    if (traffic_flag) {
    traffic_flag = false;
}

    if (!ap_connect) {
        uint8_t phase = tick % 40;
        uint8_t brightness = (phase < 20) ? (5 + phase * 2) : (5 + (40 - phase) * 2);
        strip_set_rgb(brightness, 0, 0);
        return;
    }

    // Connected: slowly breathe green
uint8_t phase = tick % 80;

uint8_t brightness;

if (phase < 40) {
    brightness = 5 + phase;
} else {
    brightness = 5 + (80 - phase);
}

strip_set_rgb(0, brightness, 0);
}

/* ---- Public API ---- */

void led_strip_notify_traffic(void)
{
    traffic_flag = true;
}

void led_strip_set_factory_reset(bool active)
{
    factory_reset_flag = active;
}
