/*
    Circuit Monkey

    Equinox(tm) - 0801-B - 64 Pixel Matrix - Demo Modes and Patterns
    This item is compatible with WS2812C and NeoPixel code

    Available on Tindie at: https://www.tindie.com/products/16462/

    Code originaly derived from AdaFruit Strand Test demo code and uses the AdaFruit NeoPixel library.

    License: GPL3


*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 7
#define N_LEDS 64
#define BRIGHTNESS 30

#define BLK 256


uint16_t pattern[][64] = {
  /* BOX */
  {
    128, 128, 128, 128, 128, 128, 128, 128,
    128, BLK, BLK, BLK, BLK, BLK, BLK, 128,
    128, BLK, BLK, BLK, BLK, BLK, BLK, 128,
    128, BLK, BLK, BLK, BLK, BLK, BLK, 128,
    128, BLK, BLK, BLK, BLK, BLK, BLK, 128,
    128, BLK, BLK, BLK, BLK, BLK, BLK, 128,
    128, BLK, BLK, BLK, BLK, BLK, BLK, 128,
    128, 128, 128, 128, 128, 128, 128, 128
  },
  /* CIRCLE */
  {
    BLK, BLK, BLK,  30,  30, BLK, BLK, BLK,
    BLK,  30,  30, BLK, BLK,  30,  30, BLK,
    BLK,  30, BLK, BLK, BLK, BLK,  30, BLK,
     30, BLK, BLK, BLK, BLK, BLK, BLK,  30,
     30, BLK, BLK, BLK, BLK, BLK, BLK,  30,
    BLK,  30, BLK, BLK, BLK, BLK,  30, BLK,
    BLK,  30,  30, BLK, BLK,  30,  30, BLK,
    BLK, BLK, BLK,  30,  30, BLK, BLK, BLK
  },
  /* PLUS */
  {
    BLK, BLK, BLK, 230, 230, BLK, BLK, BLK,
    BLK, BLK, BLK, 230, 230, BLK, BLK, BLK,
    BLK, BLK, BLK, 230, 230, BLK, BLK, BLK,
    230, 230, 230, 230, 230, 230, 230, 230,
    230, 230, 230, 230, 230, 230, 230, 230,
    BLK, BLK, BLK, 230, 230, BLK, BLK, BLK,
    BLK, BLK, BLK, 230, 230, BLK, BLK, BLK,
    BLK, BLK, BLK, 230, 230, BLK, BLK, BLK
  },
  /* LOVE */
  {
     80, BLK, BLK, BLK, BLK,  10,  10, BLK,
     80, BLK, BLK, BLK,  10, BLK, BLK,  10,
     80,  80,  80, BLK, BLK,  10,  10, BLK,
    BLK, BLK, BLK, BLK, BLK, 200, 200, 200,
    120, BLK, 120, BLK, BLK, 200, BLK, BLK,
    120, BLK, 120, BLK, BLK, 200, 200, 200,
    120, BLK, 120, BLK, BLK, 200, BLK, BLK,
    BLK, 120, BLK, BLK, BLK, 200, 200, 200
  },
  /* GHOST */
  {
    BLK, BLK, BLK, BLK, BLK, BLK, BLK, BLK,
    BLK, BLK, 128, 128, 128, 158, BLK, BLK,
    BLK, 128, 128, 128, 128, 128, 158, BLK,
    128, 128, 256, 510, 128, 256, 400, 158,
    128, 128, 510, 510, 128, 400, 400, 158,
    128, 128, 128, 128, 128, 128, 158, 158,
    128, 128, 128, 128, 128, 128, 158, 158,
    128, BLK, 128, 128, BLK, 128, 158, 158
  }
};




Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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

void loop() {
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127, 0, 0), 50); // Red
//  theaterChase(strip.Color(0, 0, 127), 50); // Blue

  rainbowCycle(20);
  loadPattern(0);
  delay(2000);
  loadPattern(1);
  delay(2000);
  loadPattern(2);
  delay(2000);
  loadPattern(3);
  delay(2000);
  loadPattern(4);
  delay(2000);
  
// theaterChaseRainbow(50);
}

void loadPattern(int n ) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(pattern[n][i]));
    }
    strip.show();
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    strip.show();
    delay(wait);
    }
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(uint16_t WheelPos) {
//  if ( WheelPos == 0 ) {
//    return strip.Color(0,0,0); // Black
//  }
  if ( WheelPos > 255 ) {
    WheelPos -= 255;
    return strip.Color( WheelPos,WheelPos,WheelPos );  // Grey Scale
  }
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
