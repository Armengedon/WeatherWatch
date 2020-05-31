/*
 * wifi.h
 *
 *  Created on: 31 may. 2020
 *      Author: Jordi
 */
#ifndef COMPONENTS_WIFI_WIFI_H_
#define COMPONENTS_WIFI_WIFI_H_

#include "esp_event.h"

extern volatile bool wifi_connected;

void wifi_init();
void wifi_start();
void wifi_handler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);


#endif /* COMPONENTS_WIFI_WIFI_H_ */
