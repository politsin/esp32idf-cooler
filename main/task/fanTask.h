#pragma once

#include "driver/gpio.h"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

// Tacho. Тахометр
extern int last_rpm;
void initTacho(void);
void updateTacho(void);

// PWM fan.
int getPWMvalue();
void initPWMfan(void);
void incFanSpeed(void);
void decFanSpeed(void);

extern TaskHandle_t fan;
void fanTask(void *pvParam);
