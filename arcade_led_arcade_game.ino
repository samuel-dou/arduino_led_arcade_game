#include <FastLED.h>

#define NUM_LEDS 72
#define TOTAL_LEDS 144
#define LED_PIN 4
#define FIRST_LED 72
#define BUTTON_PIN 5
#define BRIGHTNESS 40 // 0-255
#define NUM_FLASHES 3
#define STARTING_CENTER 108
#define LV1_TOL 5
#define LV2_TOL 3
#define LV3_TOL 1
#define LV4_TOL 0
#define LV5_TOL 20
#define CENTER_MOVE_DELAY 4
#define WRONG_THRESHOLD 5

CRGB leds[TOTAL_LEDS];
int LAST_LED = FIRST_LED + NUM_LEDS;
bool inRange = false;
bool pressed = false;
bool playing = true;
bool centerAscending = true;
int level = 1;
int LOWER_BOUND, HIGHER_BOUND, low_bound_center, high_bound_center;
int center = STARTING_CENTER;
int counter = 0;
int wrong_counter = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  updateBounds(level);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, TOTAL_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  setTarget();
}

void loop() {
  while (playing) {
    updateBounds(level);
    for (int i = FIRST_LED; i < LAST_LED; i++) {

    if (level == 5) {
      counter++;
      if (counter == CENTER_MOVE_DELAY) {
        counter = 0;
        moveCenter();
        updateBounds(level);
        setTarget();
      }
    }

    if (wrong_counter >= WRONG_THRESHOLD) {
      resetGame();
      updateBounds(level);
      setTarget();
    }
    inRange = (i >= LOWER_BOUND && i <= HIGHER_BOUND);
    pressed = (digitalRead(BUTTON_PIN) == HIGH);

    if (pressed) {
      if (inRange) {
        flashGreen(NUM_FLASHES);
        level = updateLevel(level);
        updateBounds(level);
        wrong_counter = 0;
      } else {
        flashRed(NUM_FLASHES);
        wrong_counter++;
      }
      setTarget();
      while (digitalRead(BUTTON_PIN) == HIGH) {
        delay(10);
      }
    } else {
      if (!inRange) {
      move(i);
      } else {
      moveRed(i);
      }
    }
  }
    for (int i = LAST_LED - 1; i >= FIRST_LED; i--) {
    
    if (level == 5) {
      counter++;
      if (counter == CENTER_MOVE_DELAY) {
        counter = 0;
        moveCenter();
        updateBounds(level);
        setTarget();
      }
    }

    if (wrong_counter >= WRONG_THRESHOLD) {
      resetGame();
      updateBounds(level);
      setTarget();
    }

    inRange = (i >= LOWER_BOUND && i <= HIGHER_BOUND);
    pressed = (digitalRead(BUTTON_PIN) == HIGH);

    if (pressed) {
      if (inRange) {
        flashGreen(NUM_FLASHES);
        level = updateLevel(level);
        updateBounds(level);
        wrong_counter = 0;
      } else {
        flashRed(NUM_FLASHES);
        wrong_counter++;
      }
      setTarget();

      while (digitalRead(BUTTON_PIN) == HIGH) {
        delay(10);
      }
    } else {
      if (!inRange) {
      move(i);
      } else {
      moveRed(i);
      }
    }
  
    }
    
  }
}

void resetGame () {
  level = 1;
  wrong_counter = 0;
}

void flashGreen(int t) {
  for (int i = 0; i < t; i++) { 
    fill_solid(leds + FIRST_LED, NUM_LEDS, CRGB::Green);
    FastLED.show();
    delay(100);
    fill_solid(leds + FIRST_LED, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(100);
  }
}

void flashRed(int t) {
  for (int i = 0; i < t; i ++) {
    fill_solid(leds + FIRST_LED, NUM_LEDS, CRGB::Red);
    FastLED.show();
    delay(100);
    fill_solid(leds + FIRST_LED, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(100);
  }
}

void setTarget() {

  fill_solid(leds + FIRST_LED, NUM_LEDS, CRGB::Black);

  for (int i = LOWER_BOUND; i <= HIGHER_BOUND; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

void move(int i) {
  leds[i] = CRGB::White;
  FastLED.show();
  leds[i] = CRGB::Black;
  FastLED.show();
}

void moveRed(int i) {
  leds[i] = CRGB::White;
  FastLED.show();
  leds[i] = CRGB::Red;
  FastLED.show();
}

void updateBounds(int level) {
  if (level >= 1 && level <= 4) {
    center = STARTING_CENTER;
  }
  if (level == 1) {
    LOWER_BOUND = center - LV1_TOL;
    HIGHER_BOUND = center + LV1_TOL;
  }
  else if (level == 2) {
    LOWER_BOUND = center - LV2_TOL;
    HIGHER_BOUND = center + LV2_TOL;
  }
  else if (level == 3) {
    LOWER_BOUND = center - LV3_TOL;
    HIGHER_BOUND = center + LV3_TOL;
  }
  else if (level == 4) {
    LOWER_BOUND = center - LV4_TOL;
    HIGHER_BOUND = center + LV4_TOL;
  }
  else if (level == 5) {
    LOWER_BOUND = center;
    HIGHER_BOUND = center;
  }
}

void moveCenter() {
  low_bound_center = STARTING_CENTER - LV5_TOL;
  high_bound_center = STARTING_CENTER + LV5_TOL;

  if (center == high_bound_center) {
    centerAscending = false;
  } else if (center == low_bound_center) {
    centerAscending = true;
  }
  if (centerAscending) {
    center++;
  } else {
    center--;
  }

}

int updateLevel(int level) {
  if (level != 5) {
    return level + 1;
  }
  else {
    return 1;
  }
}