#include <Adafruit_NeoPixel.h>
#include <Keypad.h>

// LED strip
#define LED_PIN 10
#define LED_COUNT 400
#define LED_COUNT_TO_USE 212
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int red = 0;
int green = 0;
int blue = 255;
int curr_brightness = 255;


// 4x4 Membrane Keypad
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to your new office lighting!");  
  setup_strip();
  Serial.println(red);  
  Serial.println(green);  
  Serial.println(blue);  
  set_strip_to_solid_color(strip.Color(red, green, blue), 50);
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println("You pressed the " + String(customKey) + " key!");   
  }
}

void setup_strip() {
  strip.begin(); // INITIALIZE NeoPixel strip object
  clear_strip();
  strip.setBrightness(curr_brightness);
}

void clear_strip() {
  Serial.println("Clearing all LEDs on strip");
  for (int x = 0; x < LED_COUNT; x++) {
      strip.setPixelColor(x, strip.Color(0, 0, 0));
  }
  strip.show();
}

void set_strip_to_solid_color(uint32_t color, int brightness) {
  for (int led = 0; led < LED_COUNT_TO_USE ; led++) {
    strip.setPixelColor(led, color);
  }
  strip.setBrightness(brightness);
  strip.show();
}
