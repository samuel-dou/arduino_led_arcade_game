#include <FastLED.h>

#define NUM_LEDS 144

#define LED_PIN 4

#define BRIGHTNESS 25 // 0-255

#define LOWER_BOUND 50

#define HIGHER_BOUND 60

CRGB leds[NUM_LEDS];

void setup() {

  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);

  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 50; i <= 60; i++) {

    leds[i] = CRGB::Red;

    FastLED.show();

  }

}

void loop() {

  for (int i = 0; i < NUM_LEDS; i++) {

    if (i >= LOWER_BOUND && i <= HIGHER_BOUND) {

      Serial.println("IN TARGET RANGE");

    } else if(i < LOWER_BOUND || i > HIGHER_BOUND) {

      leds[i] = CRGB::White;

      FastLED.show();

      leds[i] = CRGB::Black;

      FastLED.show();

  }

}