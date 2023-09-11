#pragma once

#include "driver/gpio.h"
#include <freertos/queue.h>
#include <freertos/task.h>

extern TaskHandle_t tx;
extern TaskHandle_t rx;
void uartInit();
void txTask(void *pvParam);
void rxTask(void *pvParam);
