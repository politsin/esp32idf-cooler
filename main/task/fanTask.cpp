
#define BLINK_TAG "FAN"
// #define LED_PIN1 GPIO_NUM_12

#include "fanTask.h"
TaskHandle_t fan;
void fanTask(void *pvParam) {
  // esp_rom_gpio_pad_select_gpio(LED_PIN1);
  // gpio_set_direction(LED_PIN1, GPIO_MODE_OUTPUT);
  // int isOn = 0;
  while (true) {
    // gpio_set_level(LED_PIN1, isOn);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    if (true) {
      ESP_LOGW(BLINK_TAG, "FAN!");
    }
  }
}
