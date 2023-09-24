#pragma once

#include "driver/gpio.h"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

extern TaskHandle_t tacho;
void tachoTask(void *pvParam);
static void IRAM_ATTR tacho_interrupt(void *ar);
