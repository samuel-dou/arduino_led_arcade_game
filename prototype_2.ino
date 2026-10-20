#include <FastLED.h>

#define NUM_LEDS 144
#define LED_PIN 4
#define BRIGHTNESS 25 // 0-255
#define LOWER_BOUND 69
#define HIGHER_BOUND 71
#define TOLERANCE 1
#define desiredIteration 8

CRGB leds[NUM_LEDS];
int counter = 0;
int center = NUM_LEDS / 2;
bool playing = true;

void setup() {

  Serial.begin(9600);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = LOWER_BOUND; i <= HIGHER_BOUND; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

void loop() {
  while (playing) {
    counter++;
  for (int i = 0; i < NUM_LEDS; i++) {
    // iterate through upwards

    if (i >= LOWER_BOUND && i <= HIGHER_BOUND) {
      // if it's in the target range
      Serial.println("IN TARGET RANGE FOR " + String(counter));
      if(counter == desiredIteration) {
        // if it's the iteration we want, blink green and break the loop
        // blink
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        playing = false;
        break;
      }
    } else if(i < LOWER_BOUND || i > HIGHER_BOUND) {
      leds[i] = CRGB::White;
      FastLED.show();
      leds[i] = CRGB::Black;
      FastLED.show();
  }
  }
  if (counter == desiredIteration) {
    break;
  }
  for (int i = NUM_LEDS - 1; i > 0; i--) {
    if (i >= LOWER_BOUND && i <= HIGHER_BOUND) {
      Serial.println("IN TARGET RANGE FOR " + String(counter));
      if(counter == desiredIteration) {
        // if it's the iteration we want, blink green and break the loop
        // blink
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Green);
        FastLED.show();
        delay(100);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(100);
        playing = false;
        break;
      }
    } else if(i < LOWER_BOUND || i > HIGHER_BOUND) {
      leds[i] = CRGB::White;
      FastLED.show();
      leds[i] = CRGB::Black;
      FastLED.show();
  }
  }
  Serial.println();
  }
}