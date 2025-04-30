#include "Keyboard.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 32     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <Keypad.h>

#include "GuiManager.h"

const byte ROWS = 4;  //four rows
const byte COLS = 3;  //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { '0', '1', '2' },
  { '3', '4', '5' },
  { '6', '7', '8' },
  { '9', 'A', 'B' }
};
byte rowPins[ROWS] = { A0, A1, A2, A3 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 10, 16, 14 };      //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

GuiManager* gui;

void setup() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.display();
  delay(2000);  // Pause for 2 seconds
    // Clear the buffer
  display.clearDisplay();
  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

  Keyboard.begin();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Basladi..."));
  display.display();  // Show initial text
  delay(100);

  gui = new GuiManager(&display);
}

void loop() {
  char customKey = customKeypad.getKey();
  if (customKey){
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(customKey);
    display.display();      // Show initial text
  }
  if (customKey =='9') {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.releaseAll();
  }
  if (customKey =='A') {
    Keyboard.press(KEY_DOWN_ARROW);
    delay(100);
    Keyboard.releaseAll();
  }
  if (customKey =='B') {
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(100);
    Keyboard.releaseAll();
  }
  if (customKey =='7') {
    Keyboard.press(KEY_UP_ARROW);
    delay(100);
    Keyboard.releaseAll();
  }
  if (customKey =='0') {
    gui->previousPage();
  }
  if (customKey =='2') {
    gui->nextPage();
  }
  if (customKey =='1') {
    gui->doit();
  }
  if (customKey =='4') {
    Keyboard.press(0x26|0x80);
    delay(100);
    Keyboard.releaseAll();
  }
  if (customKey =='3') {
    Keyboard.press(KEY_HOME);
    delay(100);
    Keyboard.releaseAll();
  }
  if (customKey =='5') {
    Keyboard.press(KEY_END);
    delay(100);
    Keyboard.releaseAll();
  }
}
