/*
    Circuit Monkey

    Equinox(tm) - 0811-B - 37 Pixel Demo Modes and Patterns
    This item is compatible with WS2812B and NeoPixel code

    Available on Tindie at: https://www.tindie.com/products/16429/

    Code originaly derived from AdaFruit Strand Test demo code and uses the AdaFruit NeoPixel library.

    License: GPL3


*/

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 7

// Panel #0811 has 37 LEDs on it.
#define N_LEDS 37

// Brightness range is 0-255
#define BRIGHTNESS 20

// Color definitions for the Wheel() function.
#define BLK 256
#define RED 0
#define AMB 10
#define ORG 18
#define YEL 30
#define GRN 40
#define EMG 45

#define G25 320
#define G50 395

#define BLU 140


// Patterns for the 37 pixel disk.
// First ring is a single pixel, center
// Seconde ring is 6 pixels
// Third ring is 12 pixels
// Fourth ring is 18 pixels
uint16_t pattern[][37] = {
  /* Border with center decoration */
  {
    RED,   // Ring 0
    BLK, GRN, BLK, GRN, BLK, GRN,  // Ring 1
    BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK,        // Ring 2
    BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU,          // Ring 3a
    BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU, BLU,   // Ring 3b
  },
  /* Biohazard */
  {
    AMB,   // Ring 0

    AMB, BLK,
    AMB, BLK,
    AMB, BLK,  // Ring 1

    BLK, ORG, ORG, BLK,
    BLK, ORG, ORG, BLK,
    BLK, ORG, ORG, BLK,
    // Ring 2   - 18
    YEL, BLK, BLK, ORG, YEL, BLK,
    YEL, BLK, BLK, ORG, YEL, BLK,
    YEL, BLK, BLK, ORG, YEL, BLK
  },
  /* Galaxy */
  {
    BLU,   // Ring 0

    YEL, BLK,
    YEL, BLK,
    YEL, BLK,  // Ring 1

    BLK, YEL, YEL, BLK,
    BLK, YEL, YEL, BLK,
    BLK, YEL, YEL, BLK,
    // Ring 2   - 18
    BLK, BLK, YEL, GRN, EMG, BLK,
    BLK, BLK, YEL, GRN, EMG, BLK,
    BLK, BLK, YEL, GRN, EMG, BLK

  },
  /* Creepy Face */
  {
    ORG,   // Ring 0
    ORG, ORG, ORG, ORG, ORG, ORG,   // Ring 1
    G50, ORG, G25, G50, G50, G50, G25, ORG, G50, ORG, ORG, ORG,     // Ring 2
    ORG, ORG, ORG, ORG, ORG, ORG, ORG, ORG, ORG,      // Ring 3a
    ORG, ORG, ORG, ORG, ORG, ORG, ORG, ORG, ORG,      // Ring 3b
  },

};


Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Arduino Setup routine
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'
}

// Arduino Loop
void loop() {
  rainbowCycle(20);
  loadPattern(0);
  delay(3000);
  loadPattern(1);
  delay(3000);
  loadPattern(2);
  delay(3000);
  loadPattern(3);
  delay(3000);
  //  loadPattern(4);
  //  delay(2000);

}

// Load one of our pre-defined patterns.
void loadPattern(int n ) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(pattern[n][i]));
  }
  strip.show();
}

// Original AdaFruit Code
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Original AdaFruit Code
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// AdaFruit color wheel generator
// enhanced by Circuit Monkey
// Input a value 0 to 255 to get a color value.
// Greyscale 256-511     Black to white
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(uint16_t WheelPos) {
  if ( WheelPos > 255 ) {
    WheelPos -= 255;
    return strip.Color( WheelPos, WheelPos, WheelPos ); // Grey Scale
  }
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
