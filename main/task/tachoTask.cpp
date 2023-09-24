// PWM_PIN GPIO_NUM_19 #19.
// TACHO_PIN GPIO_NUM_23 #23.
// https://github.com/KlausMu/esp32-fan-controller/blob/main/src/fanTacho.cpp
// https://www.youtube.com/watch?v=v2OxZgyD0Bs

#define FAN_TACHO_TAG "TACHOMETR"
#define FAN_TACHO_PIN GPIO_NUM_23

#include "tachoTask.h"
#include "uartTasks.h"
TaskHandle_t tacho;
uint32_t counter = 0;
void tachoTask(void *pvParam) {
  gpio_install_isr_service(0);
  gpio_set_direction(FAN_TACHO_PIN, GPIO_MODE_INPUT);
  gpio_set_pull_mode(FAN_TACHO_PIN, GPIO_PULLUP_ONLY);
  gpio_set_intr_type(FAN_TACHO_PIN, GPIO_INTR_POSEDGE);
  gpio_isr_handler_add(FAN_TACHO_PIN, tacho_interrupt, NULL);
  const TickType_t xBlockTime = pdMS_TO_TICKS(1000);
  static const char *TX_TASK_TAG = "FAN:";
  while (true) {
    vTaskDelay(xBlockTime);
    ESP_LOGW(FAN_TACHO_TAG, "RPM= %ld", counter * 30);
    char str[80];
    sprintf(str, "RPM:%ld\n", counter * 30);
    uartSendData(TX_TASK_TAG, str);
    counter = 0;
  }
}

static void IRAM_ATTR tacho_interrupt(void *arg) { counter++; }
