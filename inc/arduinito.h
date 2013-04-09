/*
 * arduinito.h
 *
 *  Created on: Apr 3, 2013
 *      Author: Zach Supalla
 */

#ifndef ARDUINITO_H_
#define ARDUINITO_H_

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

typedef struct stm32_pin_info {
  GPIO_TypeDef *gpio_peripheral;
  uint8_t gpio_pin;
};

extern const stm32_pin_info PIN_MAP[];


/*
 * Basic variables
 */

#define HIGH 0x1
#define LOW 0x0

/*
 * GPIO
 */

typedef enum PinMode {
  OUTPUT,
  INPUT,
  INPUT_PULLUP,
  INPUT_PULLDOWN
} PinMode;

void pinMode(uint8_t pin, PinMode mode);

void digitalWrite(uint8_t pin, uint8_t value);

uint32 digitalRead(uint8_t pin);

uint16 analogRead(uint8_t pin);

#endif /* ARDUINITO_H_ */
