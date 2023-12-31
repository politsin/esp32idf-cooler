#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Tasks
#include "config.h"
#include "task/fanTask.h"
#include "task/uartTasks.h"
#include "task/blinkTask.h"
#include "task/tachoTask.h"
#include "task/encoderTask.h"

#define MAINTAG "MAIN"

extern "C" void app_main(void) {
  uint32_t min = 768 + configSTACK_OVERHEAD_TOTAL;
  uartInit();
  xTaskCreate(txTask, "rx", min * 4, NULL, configMAX_PRIORITIES, &tx);
  xTaskCreate(rxTask, "tx", min * 4, NULL, configMAX_PRIORITIES - 1, &rx);
  xTaskCreate(fanTask, "fan", min * 4, NULL, 1, &fan);
  xTaskCreate(tachoTask, "tacho", min * 4, NULL, 1, &tacho);
  xTaskCreate(blinkTask, "blink", min * 2, NULL, 1, &blink);
  xTaskCreate(encoderTask, "encoder", min * 4, NULL, 1, &encoder);
}
