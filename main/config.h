#include <driver/gpio.h>
// #include <esp32-hal-gpio.h>
// fanPWM
const int pwmPin = GPIO_NUM_17;
const int pwmFreq = 25000;
const int pwmChannel = 0;
const int pwmResolution = 8;
// only used for showing at how many percent fan is running
const int fanMaxRPM = 1500;

// fanTacho
const int tachoPin = GPIO_NUM_16;
// how often tacho speed shall be determined, in milliseconds
const int tachoUpdateCycle = 1000;
// Number of interrupts ESP32 sees on tacho signal on a single fan
// rotation. All the fans I've seen trigger two interrups.
const int numberOfInterrupsInOneSingleRotation = 2;

// Config.
const int pwmMinimumValue = 120;
const int pwmStep = 10;
// initial pwm fan speed on startup (0 <= value <= 255)
const int initialPwmValue = 120;
