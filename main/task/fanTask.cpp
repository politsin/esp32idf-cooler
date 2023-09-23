
#define FAN_TAG "FAN"
#define FAN_PWM_PIN GPIO_NUM_19
#define FAN_TACHO_PIN GPIO_NUM_23

#include <cmath>
#include "fanTask.h"
#include "driver/ledc.h"

#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_DUTY_RES LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY (4095)      // Set duty to 50%. ((2 ** 13) - 1) * 50% = 4095
#define LEDC_FREQUENCY (5000) // Frequency in Hertz. Set frequency at 5 kHz

TaskHandle_t fan;
void fanTask(void *pvParam) {
  // Prepare and then apply the LEDC PWM timer configuration
  ledc_timer_config_t ledc_timer = {
      .speed_mode = LEDC_MODE,
      .duty_resolution = LEDC_DUTY_RES,
      .timer_num = LEDC_TIMER,
      .freq_hz = LEDC_FREQUENCY, // Set output frequency at 5 kHz
      .clk_cfg = LEDC_AUTO_CLK,
  };
  ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

  // Prepare and then apply the LEDC PWM channel configuration
  ledc_channel_config_t ledc_channel = {
      .gpio_num = FAN_PWM_PIN,
      .speed_mode = LEDC_MODE,
      .channel = LEDC_CHANNEL,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = LEDC_TIMER,
      .duty = LEDC_DUTY,
      .hpoint = 0,
  };
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
  const TickType_t xBlockTime = pdMS_TO_TICKS(100);
  uint32_t notify;
  while (true) {
    vTaskDelay(xBlockTime);
    if (xTaskNotifyWait(0, 0, &notify, 0) == pdTRUE) {
      // Set duty.
      uint32_t duty = (pow(2, 13) - 1) * notify / 100;
      ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty));
      // Update duty to apply the new value
      ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
      if (true) {
        ESP_LOGW(FAN_TAG, "FAN! %lu", notify);
      }
    }
  }
}
