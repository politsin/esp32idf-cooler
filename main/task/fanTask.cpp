
#define FAN_TAG "FAN"
#define FAN_PWM_PIN GPIO_NUM_19
#define FAN_TACHO_PIN GPIO_NUM_23

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
      .gpio_num = GPIO_NUM_19,
      .speed_mode = LEDC_MODE,
      .channel = LEDC_CHANNEL,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = LEDC_TIMER,
      .duty = 70, // Set duty to 0%
      .hpoint = 0,
  };
  ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
  while (true) {
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    // Set duty to 50%
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    if (true) {
      ESP_LOGW(FAN_TAG, "FAN!");
    }
  }
}