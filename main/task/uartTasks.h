#pragma once

#include "driver/gpio.h"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

extern TaskHandle_t tx;
extern TaskHandle_t rx;
void uartInit();
int uartSendData(const char *logName, const char *data);
void txTask(void *pvParam);
void rxTask(void *pvParam);
