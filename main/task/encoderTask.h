#pragma once

#include "driver/gpio.h"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include <iostream>
using std::string;
#include "rotary_encoder.h"

extern TaskHandle_t encoder;
void encoderTask(void *pvParam);

void configureRmt(uint32_t freq, bool init);
void configureEncoderPins();
static void button_callback(void *arg);
static void event_callback(rotenc_event_t event);

/**
 * typedef enum {
 ADC1_CHANNEL_0 = 0, !< ADC1 channel 0 is GPIO36
 ADC1_CHANNEL_1,     !< ADC1 channel 1 is GPIO37
 ADC1_CHANNEL_2,     !< ADC1 channel 2 is GPIO38
 ADC1_CHANNEL_3,     !< ADC1 channel 3 is GPIO39
 ADC1_CHANNEL_4,     !< ADC1 channel 4 is GPIO32
 ADC1_CHANNEL_5,     !< ADC1 channel 5 is GPIO33
 ADC1_CHANNEL_6,     !< ADC1 channel 6 sis GPIO34
 ADC1_CHANNEL_7,     !< ADC1 channel 7 is GPIO35
 ADC1_CHANNEL_MAX,
 } adc1_channel_t;
 typedef enum {
 ADC2_CHANNEL_0 = 0, !< ADC2 channel 0 is GPIO4
 ADC2_CHANNEL_1,     !< ADC2 channel 1 is GPIO0
 ADC2_CHANNEL_2,     !< ADC2 channel 2 is GPIO2
 ADC2_CHANNEL_3,     !< ADC2 channel 3 is GPIO15
 ADC2_CHANNEL_4,     !< ADC2 channel 4 is GPIO13
 ADC2_CHANNEL_5,     !< ADC2 channel 5 is GPIO12
 ADC2_CHANNEL_6,     !< ADC2 channel 6 is GPIO14
 ADC2_CHANNEL_7,     !< ADC2 channel 7 is GPIO27
 ADC2_CHANNEL_8,     !< ADC2 channel 8 is GPIO25
 ADC2_CHANNEL_9,     !< ADC2 channel 9 is GPIO26
 ADC2_CHANNEL_MAX,
 } adc2_channel_t;
 */
