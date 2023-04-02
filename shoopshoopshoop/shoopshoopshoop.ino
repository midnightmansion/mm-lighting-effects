#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER RGB
#define CHIPSET     WS2812B
#define NUM_LEDS    120

#define BRIGHTNESS  200
#define SPEED 8

#define MAX_PARTICLES 200

CRGB leds[NUM_LEDS];
float particleTracker[MAX_PARTICLES];

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( BRIGHTNESS );

  particleTracker[0] = 1;
}

void loop() {

  for (int i = 0; i < NUM_LEDS; i ++) {
    leds[i] = CRGB(0, 0, 0);  
  }

  // advance particles
  for (int i = 0; i < MAX_PARTICLES; i ++) {
    if (particleTracker[i] != 0) {
      particleTracker[i] += 0.1;
    }
    if (particleTracker[i] != 0 && particleTracker[i] < NUM_LEDS) {
      leds[round(particleTracker[i])] = CRGB(100, 100, 255);
    }
  }

  FastLED.show();
  delay(5);
}
