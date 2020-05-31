/*
 * wifi.c
 *
 *  Created on: 31 may. 2020
 *      Author: Jordi
 */

#include "esp_wifi.h"
#include "esp_log.h"
#include "wifi.h"

static const char* TAG = "Wifi_loop";

void wifi_init() {

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
	ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
	ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
	wifi_config_t sta_config = {
		.sta = {
			.ssid = CONFIG_ESP_WIFI_SSID,
			.password = CONFIG_ESP_WIFI_PASSWORD,
			.bssid_set = false
		}
	};
	ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
}

void wifi_start() {

    ESP_ERROR_CHECK( esp_wifi_start() );
    ESP_ERROR_CHECK( esp_wifi_connect() );
}

void wifi_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {

	switch (id) {
		case WIFI_EVENT_WIFI_READY:              	/**< ESP32 WiFi ready */
		case WIFI_EVENT_SCAN_DONE:					/**< ESP32 finish scanning AP */
		case WIFI_EVENT_STA_START:					/**< ESP32 station start */
		case WIFI_EVENT_STA_STOP:					/**< ESP32 station stop */
			break;
		case WIFI_EVENT_STA_CONNECTED:				/**< ESP32 station connected to AP */
			ESP_LOGI(TAG, "wifi connected");
		    wifi_connected = true;
			break;
		case WIFI_EVENT_STA_DISCONNECTED:         	/**< ESP32 station disconnected from AP */
			ESP_LOGI(TAG, "wifi disconnected");
			wifi_connected = false;
			break;
		case WIFI_EVENT_STA_AUTHMODE_CHANGE:     	/**< the auth mode of AP connected by ESP32 station changed */

		case WIFI_EVENT_STA_WPS_ER_SUCCESS:       	/**< ESP32 station wps succeeds in enrollee mode */
		case WIFI_EVENT_STA_WPS_ER_FAILED:        	/**< ESP32 station wps fails in enrollee mode */
		case WIFI_EVENT_STA_WPS_ER_TIMEOUT:       	/**< ESP32 station wps timeout in enrollee mode */
		case WIFI_EVENT_STA_WPS_ER_PIN:           	/**< ESP32 station wps pin code in enrollee mode */
		case WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP:   	/**< ESP32 station wps overlap in enrollee mode */

		case WIFI_EVENT_AP_START:                 	/**< ESP32 soft-AP start */
		case WIFI_EVENT_AP_STOP:                  	/**< ESP32 soft-AP stop */
		case WIFI_EVENT_AP_STACONNECTED:          	/**< a station connected to ESP32 soft-AP */
		case WIFI_EVENT_AP_STADISCONNECTED:       	/**< a station disconnected from ESP32 soft-AP */

		case WIFI_EVENT_AP_PROBEREQRECVED:        	/**< Receive probe request packet in soft-AP interface */

		default:
			break;
	}
}
