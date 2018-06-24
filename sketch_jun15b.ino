// Low power NeoPixel goggles example.  Makes a nice blinky display
// with just a few LEDs on at any time.

#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
 #include <avr/power.h>
#endif

#define PIN 0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, PIN);

uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of spinny eyes
uint32_t black  = pixels.Color(0, 0, 0); // black
uint32_t magenta = pixels.Color(255, 0, 255);
uint32_t prevTime;
int pos = 0;
int posMode = 0;
int r = 0;
int g = 0;
int b = 0;
int delayTime = 25;
int rmode = 0;
int gmode = 0;
int bmode = 0;
// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
}
// Return color, dimmed by 75% (used by scanner)
uint32_t DimColor(uint32_t color)
{
    uint32_t dimColor = pixels.Color(map(Red(color), 0, 255, 0, 240), map(Green(color), 0, 255, 0, 240), map(Blue(color), 0, 255, 0, 240));
    return dimColor;
}

void setup() {
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
  if(F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  pixels.setBrightness(120); // 1/3 brightness
  prevTime = millis();
}

void loop() {
  int i;
  uint32_t t;

  switch(mode) {

    case 0:
      if(posMode == 0) {
        for(i=0; i<16; i++) {
         uint32_t c = 0;
         pixels.setPixelColor(i, DimColor(pixels.getPixelColor(i)));
         pixels.setPixelColor(i+16, DimColor(pixels.getPixelColor(i+16)));
         if(i == pos){
           c = pixels.getPixelColor(i);
           pixels.setPixelColor(i, r, g, b);
           pixels.setPixelColor(31 - i, r, g, b);
           delayTime = 25;
         }
        }
        if(pos == 40) {
          pos = 0;
        } else {
          pos++;
        }
      }

      if(rmode == 0){
        r+=5;
      } else {
        r-=5;
      }
      if(gmode == 0){
        g+=7;
      } else {
        g-=7;
      }
      if(bmode == 0){
        b+=9;
      } else {
        b-=9;
      }

      if(r>=255){
        r = 255;
        rmode = 1;
      } else if(r<=0) {
        rmode = 0;
        r = 0;
      }
      if(g>=254){
        g = 255;
        gmode = 1;
      } else if(g<=0) {
        gmode = 0;
        g = 0;
        }
      if(b>=253){
        b = 255;
        bmode = 1;
      } else if(b<=0){
        bmode = 0;
        b = 0;
       }

      pixels.show();
      offset++;
      delay(delayTime);
      break;
  }

  t = millis();
  if((t - prevTime) > 8000) {      // Every 8 seconds...
    // for(i=0; i<32; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}

