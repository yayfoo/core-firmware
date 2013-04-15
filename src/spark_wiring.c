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
  /*
   * gpio_peripheral (GPIOA or GPIOB; not using GPIOC)
   * gpio_pin (0-15)
   * adc_channel (0-9 or NULL. Note we don't define the peripheral because our chip only has one)
   * timer_peripheral (TIM1 - TIM4, or NULL)
   * timer_ch (1-4, or NULL)
   * pin_mode (NULL by default, can be set to OUTPUT, INPUT, or other types)
   */
  {GPIOB, 7, NULL, TIM4, 2, NULL},
  {GPIOB, 6, NULL, TIM4, 1, NULL},
  {GPIOB, 5, NULL, NULL, NULL, NULL},
  {GPIOB, 4, NULL, NULL, NULL, NULL},
  {GPIOB, 3, NULL, NULL, NULL, NULL},
  {GPIOA, 15, NULL, NULL, NULL, NULL},
  {GPIOA, 14, NULL, NULL, NULL, NULL},
  {GPIOA, 13, NULL, NULL, NULL, NULL},
  {GPIOA, 8, NULL, NULL, NULL, NULL},
  {GPIOA, 9, NULL, NULL, NULL, NULL},
  {GPIOA, 0, 0, TIM2, 1, NULL},
  {GPIOA, 1, 1, TIM2, 2, NULL},
  {GPIOA, 4, 4, NULL, NULL, NULL},
  {GPIOA, 5, 5, NULL, NULL, NULL},
  {GPIOA, 6, 6, TIM3, 1, NULL},
  {GPIOA, 7, 7, TIM3, 2, NULL},
  {GPIOB, 0, 8, TIM3, 3, NULL},
  {GPIOB, 1, 9, TIM3, 4, NULL},
  {GPIOA, 3, 3, TIM2, 4, NULL},
  {GPIOA, 2, 2, TIM2, 3, NULL},
  {GPIOA, 10, NULL, NULL, NULL, NULL}
};

/*
 * Basic variables
 */

/*
 * @brief Set the mode of the pin to OUTPUT, INPUT, INPUT_PULLUP, or INPUT_PULLDOWN
 */
void pinMode(uint8_t pin, PinMode setMode) {

  GPIO_TypeDef *gpio_port = PIN_MAP[pin].gpio_peripheral;
  uint8_t gpio_pin = PIN_MAP[pin].gpio_pin;

  GPIO_InitTypeDef GPIO_InitStructure;

  switch(setMode) {
    case OUTPUT:

      if (gpio_port == GPIOA) {
    	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
      } else if (gpio_port == GPIOB) {
    	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
      }

      /* Configure the GPIO_LED pin */
      GPIO_InitStructure.GPIO_Pin = gpio_pin;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

      GPIO_Init(gpio_port, &GPIO_InitStructure);

      PIN_MAP[pin].pin_mode = OUTPUT;
      break;
    case INPUT:
      PIN_MAP[pin].pin_mode = INPUT;
      break;
    case INPUT_PULLUP:
      PIN_MAP[pin].pin_mode = INPUT_PULLUP;
      // TODO: Implement the pull-up resistor
      break;
    case INPUT_PULLDOWN:
      PIN_MAP[pin].pin_mode = INPUT_PULLDOWN;
      // TODO: Implement the pull-down resistor
      break;
    default:
      break;
  }
}

/*
 * @brief Initialize the ADC peripheral.
 */
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

/*
 * @brief Sets a GPIO pin to HIGH or LOW.
 */
void digitalWrite(uint8_t pin, uint8_t value) {
  if (pin >= TOTAL_PINS || PIN_MAP[pin].pin_mode != OUTPUT) {
    return;
  }

  if (value == HIGH) {
    PIN_MAP[pin].gpio_peripheral->BSRR = PIN_MAP[pin].gpio_pin;
  }
  else if (value == LOW) {
    PIN_MAP[pin].gpio_peripheral->BRR = PIN_MAP[pin].gpio_pin;
  }

}

/*
 * @brief Reads the value of a GPIO pin. Should return either 1 (HIGH) or 0 (LOW).
 */
uint32_t digitalRead(uint8_t pin) {
  if (pin >= TOTAL_PINS || PIN_MAP[pin].pin_mode == OUTPUT || PIN_MAP[pin].pin_mode == NULL) {
    return -1;
  }

  return GPIO_ReadInputDataBit(PIN_MAP[pin].gpio_peripheral, PIN_MAP[pin].gpio_pin);
}

/*
 * @brief Read the analog value of a pin. Should return a 16-bit value, 0-65536 (0 = LOW, 65536 = HIGH)
 */
uint16_t analogRead(uint8_t pin) {
  // Allow people to use 0-7 to define analog pins by checking to see if the values are too low.
  if (pin < FIRST_ANALOG_PIN) {
	pin = pin + FIRST_ANALOG_PIN;
  }

  if (pin >= TOTAL_PINS || PIN_MAP[pin].adc_channel == NULL)) {
    return -1;
  }

  if (adcFirstTime == true) {
    adcInit();
    adcFirstTime = false;
  }

  // TODO: Need to implement.
}
/*
 * @brief Should take an integer 0-255 and create a PWM signal with a duty cycle from 0-100%.
 */
void analogWrite(uint8_t pin, uint8_t value) {

  if (pin >= TOTAL_PINS || PIN_MAP[pin].timer_peripheral == NULL) {
	  return;
  }

  // TODO: Implement
}

/*
 * TIMING
 */

/*
 * @brief Should return the number of milliseconds since the processor started up.
 * 		  This is useful for measuring the passage of time.
 * 		  For now, let's not worry about what happens when this overflows (which should happen after 49 days).
 * 		  At some point we'll have to figure that out, though.
 */
uint32_t millis() {
	/*
	 * Basically, this should return the number of milliseconds since the processor started up.
	 * If we simply store it in a uint32_t, this will be accurate for roughly 49 days.
	 * At that point, it should reset gracefully.
	 */

	// TODO: Implement this.
}

/*
 * @brief This should block for a certain number of milliseconds.
 *        There are a million ways to implement this, but I borrowed the one that Wiring/Arduino use;
 *        Using the millis() function to check if a certain amount of time has passed.
 */
void delay(uint32_t ms) {
	uint32_t start = millis();
	while(millis() - start < ms);
}

/*
 * @brief This should block for a certain number of microseconds.
 *        This will only be used for small intervals of time, so it has different requirements than the above.
 *        It must be accurate at small intervals, but does not have to function properly
 *        with intervals more than a couple of seconds.
 *
 *        The below implementation is borrowed straight from Maple. I do not understand the code, nor do I
 *        understand the derivation of the multiplier.
 *
 *        This function is lower priority than the others.
 */
void delayMicroseconds(uint32_t us) {
	// We have to multiply this by something, but I'm not sure what.
	// Depends on how many clock cycles the below assembly code takes, I suppose.
	//
	us *= STM32_DELAY_US_MULT;

	/* fudge for function call overhead  */
	us--;
	asm volatile("   mov r0, %[us]          \n\t"
	             "1: subs r0, #1            \n\t"
	             "   bhi 1b                 \n\t"
	             :
	             : [us] "r" (us)
	             : "r0");
}
