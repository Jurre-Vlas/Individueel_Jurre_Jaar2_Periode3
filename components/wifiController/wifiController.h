#ifndef SMARTSPEAKER_WIFICONTROLLER_H
#define SMARTSPEAKER_WIFICONTROLLER_H

#include <stdbool.h>
#include "esp_peripherals.h"

void wifi_init(esp_periph_set_handle_t peripherals_pool);
bool getWifiStatus();

#endif //SMARTSPEAKER_WIFICONTROLLER_H
