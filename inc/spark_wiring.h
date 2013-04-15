/*
 * spark_wiring.h
 *
 *  Created on: Apr 15, 2013
 *      Author: zsupalla
 */

#ifndef SPARK_WIRING_H_
#define SPARK_WIRING_H_

#include "stm32f10x.h"

/*
 * Basic variables
 */

#define HIGH 0x1
#define LOW 0x0

#define true 0x1
#define false 0x0

#define STM32_DELAY_US_MULT 12 // TODO: Fix this.

#define NULL ((void *)0)

/*
 * Pin mapping. Borrowed from Wiring
 */

#define TOTAL_PINS 21
#define TOTAL_ANALOG_PINS 8
#define FIRST_ANALOG_PIN 10

#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define LED1 8
#define LED2 9

#define A0 10
#define A1 11
#define A2 12
#define A3 13
#define A4 14
#define A5 15
#define A6 16
#define A7 17

#define RX 18
#define TX 19

#define BTN 20

// Timer pins

#define TIMER2_CH1 10
#define TIMER2_CH2 11
#define TIMER2_CH3 18
#define TIMER2_CH4 19

#define TIMER3_CH1 14
#define TIMER3_CH2 15
#define TIMER3_CH3 16
#define TIMER3_CH4 17

#define TIMER4_CH1 1
#define TIMER4_CH2 0

// SPI pins

#define SS 7
#define SCK 6
#define MISO 5
#define MOSI 4

typedef enum PinMode {
  OUTPUT,
  INPUT,
  INPUT_PULLUP,
  INPUT_PULLDOWN
} PinMode;

typedef struct stm32_pin_info {
  GPIO_TypeDef *gpio_peripheral;
  uint8_t gpio_pin;
  uint8_t adc_channel;
  TIM_TypeDef *timer_peripheral;
  uint8_t timer_ch;
  PinMode pin_mode;
} stm32_pin_info;


/*
 * GPIO
 */


void pinMode(uint8_t pin, PinMode mode);

void digitalWrite(uint8_t pin, uint8_t value);

uint32_t digitalRead(uint8_t pin);

void analogWrite(uint8_t value);

uint16_t analogRead(uint8_t pin);

/*
 * TIMING
 */

uint32_t millis();
void delay(uint32_t ms);
void delayMicroseconds(uint32_t us);

void

#endif /* SPARK_WIRING_H_ */
