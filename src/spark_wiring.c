/*
 * spark_wiring.c
 *
 *  Created on: Apr 15, 2013
 *      Author: zsupalla
 */

#include "spark_wiring.h"

/*
 * Globals
 */

uint8_t adcFirstTime = true;

/*
 * Pin mapping
 */

extern struct stm32_pin_info PIN_MAP[TOTAL_PINS] = {
  {GPIOB, 7},
  {GPIOB, 6},
  {GPIOB, 5},
  {GPIOB, 4},
  {GPIOB, 3},
  {GPIOA, 15},
  {GPIOA, 14},
  {GPIOA, 13},
  {GPIOA, 8},
  {GPIOA, 9},
  {GPIOA, 0},
  {GPIOA, 1},
  {GPIOA, 4},
  {GPIOA, 5},
  {GPIOA, 6},
  {GPIOA, 7},
  {GPIOB, 0},
  {GPIOB, 1},
  {GPIOA, 3},
  {GPIOA, 2},
  {GPIOA, 10}
};

/*
 * Basic variables
 */

void pinMode(uint8_t pin, PinMode setMode) {

  GPIO_TypeDef *gpio = PIN_MAP[pin].gpio_peripheral;
  uint8_t gpio_pin = PIN_MAP[pin].gpio_pin;

  GPIO_InitTypeDef GPIO_InitStructure;

  switch(setMode) {
    case OUTPUT:

      if (gpio == GPIOA) {
    	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      } else if (gpio == GPIOB) {
    	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      }

      /* Configure the GPIO_LED pin */
      GPIO_InitStructure.GPIO_Pin = gpio_pin;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

      GPIO_Init(gpio, &GPIO_InitStructure);
      break;
    case INPUT:
      break;
    case INPUT_PULLUP:
      break;
    case INPUT_PULLDOWN:
      break;
    default:
      break;
  }
}

void adcInit() {
  ADC_InitTypeDef ADC_InitStructure;

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 9;

  ADC_Init(ADC1, &ADC_InitStructure);
}

void digitalWrite(uint8_t pin, uint8_t value) {
  if (pin >= TOTAL_PINS) {
    return;
  }

  if (value == HIGH) {
    PIN_MAP[pin].gpio_peripheral->BRR = PIN_MAP[pin].gpio_pin;
  }
  else if (value == LOW) {
    PIN_MAP[pin].gpio_peripheral->BSRR = PIN_MAP[pin].gpio_pin;
  }

}

uint32_t digitalRead(uint8_t pin) {
  if (pin >= TOTAL_PINS) {
    return -1;
  }

  return GPIO_ReadInputDataBit(PIN_MAP[pin].gpio_peripheral, PIN_MAP[pin].gpio_pin);
}

uint16_t analogRead(uint8_t pin) {
  pin = pin + FIRST_ANALOG_PIN;

  if (pin >= TOTAL_PINS) {
    return -1;
  }

  if (adcFirstTime == true) {
    adcInit();
    adcFirstTime = false;
  }

  return GPIO_ReadInputDataBit(PIN_MAP[pin].gpio_peripheral, PIN_MAP[pin].gpio_pin);


}
