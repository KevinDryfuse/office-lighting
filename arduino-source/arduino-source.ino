#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

// LED strip
#define LED_PIN 10
#define LED_COUNT 212
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int red = 0;
int green = 0;
int blue = 0;
uint32_t currentColor = strip.Color(red, green, blue);
int currentBrightness = 50;
boolean isStripOn = false;

// 4x4 Membrane Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
boolean action = false;

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to your new office lighting!");  
  setupStrip(); 
  rainbowCycle(1, 1);
  clearStrip();
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey){
    action = true;
    if (customKey == 'A') {
      Serial.println("Setting lights to solid color blue");
      isStripOn = true;
      red = 0;
      green = 0;
      blue = 255;
      currentColor = strip.Color(red, green, blue);
      }
    if (customKey == 'B') {
      Serial.println("Setting lights to solid color red");
      isStripOn = true;  
      blue = 0;
      green = 0;
      red = 255;
      currentColor = strip.Color(red, green, blue);
    }
    if (customKey == 'C') {
      Serial.println("Setting lights to solid color green");
      isStripOn = true;  
      red = 0;
      blue = 0;
      green = 255;
      currentColor = strip.Color(red, green, blue);
    }  
  }
  
  if (action) {
    if (isStripOn) {
      setStripToSolidColor(currentColor, currentBrightness);
    }
    else {
      clearStrip();
    }
    action = false;
  }
}


void rainbowCycle(uint8_t wait, int cycles) {
  
  for(int c = 0; c <= cycles; c++) {
    uint16_t i, j;
 
    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, wheel(((i * 256 / strip.numPixels()) + j) & 255));
        
      }
      strip.show();
      delay(wait);
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t wheel(byte wheelPosition) {
  if(wheelPosition < 85) {
   return strip.Color(wheelPosition * 3, 255 - wheelPosition * 3, 0);
  } else if(wheelPosition < 170) {
   wheelPosition -= 85;
   return strip.Color(255 - wheelPosition * 3, 0, wheelPosition * 3);
  } else {
   wheelPosition -= 170;
   return strip.Color(0, wheelPosition * 3, 255 - wheelPosition * 3);
  }
}

void setupStrip() {
  strip.begin(); // INITIALIZE NeoPixel strip object
  clearStrip();
  strip.setBrightness(currentBrightness);
}

void clearStrip() {
  Serial.println("Clearing all LEDs on strip");
  for (int x = 0; x < LED_COUNT; x++) {
      strip.setPixelColor(x, strip.Color(0, 0, 0));
  }
  strip.show();
}

void setStripToSolidColor(uint32_t color, int brightness) {
  for (int led = 0; led < LED_COUNT; led++) {
    strip.setPixelColor(led, color);
  }
  strip.setBrightness(brightness);
  strip.show();
}
