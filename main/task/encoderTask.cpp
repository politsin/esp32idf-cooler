
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//.
#include <iostream>
using std::string;

#include "fanTask.h"
#include "encoderTask.h"
#include "rotary_encoder.h"
#define ENC_TAG "ENCODER"
#define CONFIG_REPORT_MODE_CALLBACK true
#define CONFIG_ENCODER_DEBUG true

// ENCODER.
static const gpio_num_t encoderS1 = GPIO_NUM_0;
static const gpio_num_t encoderS2 = GPIO_NUM_36;
static const gpio_num_t encoderBtn = GPIO_NUM_34;
static const uint32_t debouncsEnc = 100;
static const uint32_t debouncsBtn = 100;
rotenc_handle_t handle = {};

// RMT.
uint32_t frequency = 10;

TaskHandle_t encoder;
void encoderTask(void *pvParam) {
  uint32_t tiks = 0;
  configureEncoderPins();
  const TickType_t xBlockTime = pdMS_TO_TICKS(50);
  while (true) {
    tiks++;
    // ESP_LOGE(ENC_TAG, "encoder= %d ticks", frequency);
    vTaskDelay(xBlockTime);
  }
}

/**
 * Coficure D39 Analog Input (vRef).
 */
void loopEsamples() {
#if CONFIG_REPORT_MODE_QUEUE
  rotenc_event_t event = {};
  if (rotenc_wait_event(&handle, &event) == ESP_OK) {
    event_callback(event);
  }
#elif CONFIG_REPORT_MODE_CALLBACK
  vTaskDelay(1000 / portTICK_PERIOD_MS);
#elif CONFIG_REPORT_MODE_POLLING
  vTaskDelay(100 / portTICK_PERIOD_MS);
  rotenc_event_t event = {0};
  ESP_ERROR_CHECK(rotenc_polling(&handle, &event));
  event_callback(event);
#endif
}

/**
 * Coficure D39 Analog Input (vRef).
 */
void configureEncoderPins() {
  // Verify that the GPIO ISR service is installed
  gpio_install_isr_service(0);
  // Initialize the handle instance of the rotary device,
  // by default it uses 1 mS for the debounce time.
  rotenc_init(&handle, encoderS1, encoderS2, debouncsEnc);
  // Flip direction.
  ESP_ERROR_CHECK(rotenc_flip_direction(&handle));
  rotenc_init_button(&handle, encoderBtn, debouncsBtn, button_callback);

#if CONFIG_REPORT_MODE_QUEUE
  ESP_LOGI(ENC_TAG, "Report mode by freertos queue");
  ESP_ERROR_CHECK(rotenc_set_event_queue(&handle, 1000));
#elif CONFIG_REPORT_MODE_CALLBACK
  ESP_LOGI(ENC_TAG, "Report mode by function callback");
  ESP_ERROR_CHECK(rotenc_set_event_callback(&handle, event_callback));
#elif CONFIG_REPORT_MODE_POLLING
  ESP_LOGI(ENC_TAG, "Report mode by polling");
#endif
}

static void button_callback(void *arg) {
  // rotenc_handle_t *handle = (rotenc_handle_t *)arg;
  frequency = 0;
  ESP_LOGI(ENC_TAG, "Push button");
}
static void event_callback(rotenc_event_t event) {
  frequency = event.position * 10;
  if (event.position < 0) {
    frequency = 0;
  }
  if (event.position > 10) {
    frequency = 100;
  }
  xTaskNotify(fan, frequency, eSetValueWithOverwrite);

#if CONFIG_ENCODER_DEBUG
  ESP_LOGI(ENC_TAG, "Event: position %ld, direction %s", event.position,
           event.direction ? (event.direction == ROTENC_CW ? "CW" : "CCW")
                           : "NOT_SET");
#endif
}
