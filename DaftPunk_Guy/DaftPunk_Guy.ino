#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define FACE_PIN 7
#define EAR_PIN 8

#define FACE_COUNT 64
#define EAR_COUNT 48

Adafruit_NeoPixel faceBars(FACE_COUNT, FACE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel earPulse(EAR_COUNT, EAR_PIN, NEO_GRB + NEO_KHZ800);

long firstPixelHue = 0;

int bottomBarPos = 0;
int earPulsePos = 0;

void setup() {
  
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  faceBars.begin();
  faceBars.show();
  faceBars.setBrightness(63);
  earPulse.begin();
  earPulse.show();
}

void loop() {
  int selection = random(0, 4);
  
  if(selection == 0) {
    faceSequencePulse(faceBars);
  }
  else if (selection == 1) {
    faceSequenceSweep(faceBars);
  }
  else if (selection == 2) {
    faceSequenceStack(faceBars);
  }
  else {
    faceSequenceIdle(faceBars);
    delay(2500);
  }
}

void faceSequenceStack(Adafruit_NeoPixel strip) {
  strip.begin();
  strip.clear();
  
  for(int i = 8; i > 0; i--) {
    for(int k = 8; k >= (8 - i); k--) {
      lightOneBar(k,255);
      lightOneBar(k+1,63);
      clearOneBar(k+2);
      delay(125);
      clearOneBar(k+1);
    }
  }
  delay(500);

  for(int i = 8; i >= 0; i--) {
    clearOneBar(i);
    for(int k = i; k < 8; k++) {
      clearOneBar(k);
      lightOneBar(k+1,62);
      lightOneBar(k+2,255);
      delay(125);
    }
  }
  delay(500);
  faceBars.clear();
  delay(1000);
}
void faceSequencePulse(Adafruit_NeoPixel strip) {
  delay(250);
  
  strip.begin();
  for(int i = 0; i < 250; i+= 10) {
    for(int k = 0; k < 8; k++){
      lightOneBar(k, i);
    }
  }

  delay(250);
  
  for(int i = 250; i >= 0; i-= 10) {
    for(int k = 0; k < 8; k++){
      lightOneBar(k, i);
    }
  }

  delay(250);
}
void faceSequenceSweep(Adafruit_NeoPixel strip) {
  strip.begin();
  
  for(int i = 0; i < 8; i++) {
    lightOneBar(i, 255);
    delay(50);
  }
  delay(500);
  
  for(int i = 0; i < 8; i++) {
    clearOneBar(i);
    delay(50);
  }
  delay(500);

  for(int i = 8; i >= 0; i--) {
    lightOneBar(i, 255);
    delay(50);
  }
  delay(500);
  
  for(int i = 8; i >= 0; i--) {
    clearOneBar(i);
    delay(50);
  }
  delay(500);
}

void faceSequenceIdle(Adafruit_NeoPixel strip) {
  strip.begin();
  for(int i = 0; i < 8; i++) {
    lightOneBar(i, 255);
  }

}

void lightOneBar(int pos, int brightness) {
  int kBright = constrain(brightness, 0, 255);
  if(pos == 0) {
    for(int i = 0; i < 8; i++) {
      faceBars.setPixelColor(i, faceBars.Color(kBright,kBright,kBright));
      faceBars.show();
    }  
  }
  else if(pos == 1) {
    for(int i = 8; i < 16; i++) {
      faceBars.setPixelColor(i, faceBars.Color(kBright,0,0));
      faceBars.show();
    }  
  }
  else if(pos == 2) {
    for(int i = 16; i < 24; i++) {
      faceBars.setPixelColor(i, faceBars.Color(kBright,kBright/8,0));
      faceBars.show();
    }
  }
  else if(pos == 3) {
    for(int i = 24; i < 32; i++) {
      faceBars.setPixelColor(i, faceBars.Color(kBright,kBright,0));
      faceBars.show();
    }
  }
  else if(pos == 4) {
    for(int i = 32; i < 40; i++) {
      faceBars.setPixelColor(i, faceBars.Color(0,kBright,0));
      faceBars.show();
    }  
  }
  else if(pos == 5) {
    for(int i = 40; i < 48; i++) {
      faceBars.setPixelColor(i, faceBars.Color(0,kBright,kBright/2));
      faceBars.show();
    }  
  }
  else if(pos == 6) {
    for(int i = 48; i < 56; i++) {
      faceBars.setPixelColor(i, faceBars.Color(kBright/8,0,kBright));
      faceBars.show();
    }  
  }
  else if(pos == 7) {
    for(int i = 56; i < 64; i++) {
      faceBars.setPixelColor(i, faceBars.Color(kBright,0,kBright));
      faceBars.show();
    }  
  }
}

void clearOneBar(int pos) {
  int start = 0;
  int fin = 0;
  
  if(pos == 0) {
    fin = 8; 
  }
  else if(pos == 1) {
    start = 8;
    fin = 16;
  }
  else if(pos == 2) {
    start = 16;
    fin = 24;
  }
  else if(pos == 3) {
    start = 24;
    fin = 32;
  }
  else if(pos == 4) {
    start = 32;
    fin = 40; 
  }
  else if(pos == 5) {
    start = 40;
    fin = 48;
  }
  else if(pos == 6) {
    start = 48;
    fin = 56;
  }
  else if(pos == 7) {
    start = 56;
    fin = 64; 
  }
  for(int i = start; i < fin; i++) {
    faceBars.setPixelColor(i, faceBars.Color(0,0,0));
    faceBars.show();
  }  
}
