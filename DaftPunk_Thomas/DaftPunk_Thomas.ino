#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define EARS_PIN 6
#define VISOR_PIN 7

#define EARS_COUNT 16
#define VISOR_COUNT 48

Adafruit_NeoPixel earRings(EARS_COUNT, EARS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel visorStrip(VISOR_COUNT, VISOR_PIN, NEO_GRB + NEO_KHZ800);

long firstPixelHue = 0;

void setup() {
  
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  visorStrip.begin();
  visorStrip.show();
  earRings.begin();
  earRings.show();
}

void loop() {

  int selection = random(0, 4);
  if(selection == 0) {
      visorSequenceA(visorStrip);
  }
  else if (selection == 1) {
    visorSequenceB(visorStrip);
  }
  else if (selection == 2) {
      theaterChase(visorStrip, visorStrip.Color(255,10,0), 75);
  }
  else {
      visorSequenceC(visorStrip);
  }

}



void colorWipe(Adafruit_NeoPixel strip, uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
    strip.begin();
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(Adafruit_NeoPixel strip, uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
    strip.begin();
  }
}

//// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
//void rainbow(Adafruit_NeoPixel strip, int wait) {
//
//  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
//    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
//
//      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//
//      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//    }
//    strip.show(); // Update strip with new contents
//    delay(wait);  // Pause for a moment
//      strip.begin();
//  }
//}

void updateRainbow() {
  if(firstPixelHue < 5*65536) {
      firstPixelHue += 256;
  }
  else {
    firstPixelHue = 0;
  }
  
  for(int i=0; i<earRings.numPixels(); i++) { // For each pixel in strip...
    int pixelHue = firstPixelHue + (i * 65536L / earRings.numPixels());
    earRings.setPixelColor(i, earRings.gamma32(earRings.ColorHSV(pixelHue)));
  }
  earRings.show(); // Update strip with new contents
  earRings.begin();
}

void visorSequenceA(Adafruit_NeoPixel strip) {
  visorStrip.begin();
  for(int i = 0; i < strip.numPixels()/4; i++) {
    strip.setPixelColor(i, strip.Color(255,10,0)); //Q2
    strip.setPixelColor(strip.numPixels()-i-1, strip.Color(255,10,0)); //Q4
    strip.setPixelColor(strip.numPixels()/2-i-1, strip.Color(255,10,0)); //Q1
    strip.setPixelColor(strip.numPixels()/2+i, strip.Color(255,10,0)); //Q3 
    updateRainbow();
    strip.show();                          
    delay(20);                           
  }
  for(int i = 0; i < strip.numPixels()/4; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0)); //Q2
    strip.setPixelColor(strip.numPixels()-i-1, strip.Color(0,0,0)); //Q4
    strip.setPixelColor(strip.numPixels()/2-i-1, strip.Color(0,0,0)); //Q1
    strip.setPixelColor(strip.numPixels()/2+i, strip.Color(0,0,0)); //Q3  
    updateRainbow();             
    strip.show();                          
    delay(50);                           
  }
  delay(200);
}

void visorSequenceB(Adafruit_NeoPixel strip) {
  visorStrip.begin();
  for(int i = 0; i < strip.numPixels()/2; i++) {
    strip.setPixelColor(i, strip.Color(255,10,0)); 
    strip.setPixelColor(i + strip.numPixels()/2 , strip.Color(255,10,0)); 
    updateRainbow();
    strip.show();                          
    delay(30);                           
  }
  for(int i = 0; i < strip.numPixels()/2; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0)); 
    strip.setPixelColor(i + strip.numPixels()/2 , strip.Color(0,0,0)); 
    updateRainbow();             
    strip.show();                          
    delay(30);                           
  }
  for(int i = 0; i < strip.numPixels()/2; i++) {
    strip.setPixelColor(i, strip.Color(255,10,0)); 
    strip.setPixelColor(i + strip.numPixels()/2 , strip.Color(255,10,0)); 
    updateRainbow();             
    strip.show();                          
    delay(30);                           
  }
  for(int i = 0; i < strip.numPixels()/2; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0)); 
    strip.setPixelColor(i + strip.numPixels()/2 , strip.Color(0,0,0)); 
    updateRainbow();
    strip.show();                          
    delay(30);                           
  }
}

void visorSequenceC(Adafruit_NeoPixel strip) {
  int barSize = 6;
  int stripLength = strip.numPixels();
  int stripQuad = strip.numPixels()/4;
  visorStrip.begin();
  
  for(int i = 0; i < stripQuad * 2; i++) {
    strip.setPixelColor(i, strip.Color(255,10,0)); //Q2
    strip.setPixelColor(i - barSize, strip.Color(0,0,0)); //Q2

    strip.setPixelColor(stripLength - i - 1, strip.Color(255,10,0)); //Q3
    strip.setPixelColor(stripLength - i - 1 + barSize, strip.Color(0,0,0)); //Q3
    
    updateRainbow();
    strip.show();                          
    delay(40);                           
  }

  for(int i = stripQuad * 2; i > 0; i--) {
    strip.setPixelColor(i, strip.Color(0,0,0)); //Q2
    strip.setPixelColor(i - barSize, strip.Color(255,10,0)); //Q2

    strip.setPixelColor(stripLength - i - 1, strip.Color(0,0,0)); //Q3
    strip.setPixelColor(stripLength - i - 1 + barSize, strip.Color(255,10,0)); //Q3
    
    updateRainbow();
    strip.show();                          
    delay(40);                           
  }
}
