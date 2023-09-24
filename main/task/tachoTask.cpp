// PWM_PIN GPIO_NUM_19 #19.
// TACHO_PIN GPIO_NUM_23 #23.
// https://github.com/KlausMu/esp32-fan-controller/blob/main/src/fanTacho.cpp

#define FAN_TACHO_TAG "TACHO"
#define FAN_TACHO_PIN GPIO_NUM_23

#include "tachoTask.h"
TaskHandle_t tacho;
void tachoTask(void *pvParam) {
  esp_rom_gpio_pad_select_gpio(FAN_TACHO_PIN);
  gpio_set_direction(FAN_TACHO_PIN, GPIO_MODE_INPUT);
  const TickType_t xBlockTime = pdMS_TO_TICKS(1000);
  while (true) {
    // gpio_set_level(LED_PIN2, !isOn);
    // gpio_set_level(LED_PIN1, isOn);
    // vTaskDelay(30 / portTICK_PERIOD_MS);
    // gpio_set_level(LED_PIN1, !isOn);
    vTaskDelay(xBlockTime);
    if (true) {
      ESP_LOGW(FAN_TACHO_TAG, "tachometr!");
    }
  }
}
