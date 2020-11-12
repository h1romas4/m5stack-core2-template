#include <M5Core2.h>
#include "esp_log.h"

static const char *TAG = "main";

void setup()
{
    M5.begin();
}

void loop()
{
    M5.update();
    ESP_LOGI(TAG, "looping now.");
    delay(1000);
}
