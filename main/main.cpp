#include <M5Core2.h>
#include "esp_log.h"

static const char *TAG = "main";

void setup()
{
    M5.begin();
}

void loop()
{
    // M5Core2
    M5.update();
    // esp-idf
    ESP_LOGI(TAG, "looping now.");
    // arduino-esp32
    delay(1000);
}
