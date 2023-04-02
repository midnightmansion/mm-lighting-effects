#include <FastLED.h>

#define NUM_LEDS 120    // Number of LEDs on the strip
#define DATA_PIN 6      // Pin where data is connected
#define BRIGHTNESS 255  // Brightness level

CRGB leds[NUM_LEDS];  // Declare the LED strip

float ballPosition = 0;  // Starting position of the ball
float ballSpeed = 3;     // Speed of the ball
float ballSize = 6;      // Size of the ball
float gravity = 0.2;     // Gravity applied to the ball
int bounces = 0;
float cycle = 0;

#define MAX_BOUNCES 15.0

void setup() {
  // Initialize LED strip
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop() {
  // Clear the LED strip
  FastLED.clear();

  // Update the ball position
  ballPosition += ballSpeed;
  ballSpeed += gravity;

  // Check if the ball hits the end of the strip
  if (ballPosition + ballSize > NUM_LEDS || ballPosition < 0) {
    // Reverse the ball's direction and reduce its speed
    ballSpeed = -ballSpeed * 0.75 * ((MAX_BOUNCES + 20 - bounces) / (MAX_BOUNCES + 20));
    ballPosition += ballSpeed;
    bounces++;
    Serial.println(String(ballSpeed) + " " + String(ballPosition));
    if (bounces >= MAX_BOUNCES) {
      delay(3000);
      bounces = 0;
      ballSpeed = -6.5;
    }
  }

  // Draw the ball on the LED strip
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i >= ballPosition && i < ballPosition + ballSize) {
      // Set the color of the ball
      leds[i] = CHSV(round(cycle),255,255);
      cycle = cycle + 0.005;
      if (cycle > 255) {
        cycle = 0;
      }
    } else {
      // Set the color of the background
      leds[i] = CRGB(0, 0, 0);
    }
  }


  // Reverse the LED strip
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    CRGB tmp = leds[i];
    leds[i] = leds[NUM_LEDS - 1 - i];
    leds[NUM_LEDS - 1 - i] = tmp;
  }

  // Show the updated LED strip
  FastLED.show();

  // Pause for a moment
  delay(10);
}
