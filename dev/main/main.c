#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "wifi.h"

#define GPIO_LEVEL_HIGH 1
#define GPIO_LEVEL_LOW	0

static const char* TAG = "Main_event_loop";

volatile bool wifi_connected = false;

esp_err_t event_handler(void *ctx, system_event_t *event) {

    return ESP_OK;
}

static void setEvents() {

	ESP_ERROR_CHECK(esp_event_loop_create_default());
	ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, wifi_handler, NULL));
}

void app_main(void) {

	ESP_LOGI(TAG, "setting up-------------");

	setEvents();
    nvs_flash_init();
    tcpip_adapter_init();
    wifi_init();
    wifi_start();

    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_NUM_21, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_21, GPIO_LEVEL_LOW); //annoying orange led blinking

    int level = 0;

    while (true) {

    	if (!wifi_connected) {
			gpio_set_level(GPIO_NUM_25, level);
			level = !level;
    	} else {
    		gpio_set_level(GPIO_NUM_25, GPIO_LEVEL_LOW);
    	}

		vTaskDelay(300 / portTICK_PERIOD_MS);
    }

    ESP_ERROR_CHECK(esp_event_loop_delete_default());
}

