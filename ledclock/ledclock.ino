/* Programma voor het aansturen van de APA102 ledstrip
 *  
 *  Bovenaan het programma staan de in te stellen variabelen
 */



#include <FastGPIO.h>
#define APA102_USE_FAST_GPIO

#include <APA102.h>

// Define which pins to use.
const uint8_t dataPin = 11;
const uint8_t clockPin = 12;

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

/*
 * SET VARIABLES
 */
 
// Set the number of LEDs to control.
const uint16_t ledCount = 167;
// Set the background color { red, green, blue} max values are 255
const uint8_t bckColor[3]  = { 255, 0, 0 };
// Set the color of the tip { red, green, blue} max values are 255
//const uint8_t tipColor[3]  = { 0, 0, 255 };
// Set the brightness to use (the maximum is 31).

const uint8_t brightness = 5;
// Set the colors for the strip { red, green, blue} max values are 255
const uint8_t numColors = 3; // Current setting is three different colors
const uint8_t tipColors[numColors][3]  = {{ 0, 0, 255 } , { 255, 0, 0 } , { 0, 255, 0 } };


/*
 * START PROGRAM
 */
// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];
uint16_t stepCount;
uint16_t colorCount;

void setup() {
  // put your setup code here, to run once:
  uint8_t* tipColor = tipColors[0]; // initialize with first color
  initstrip(tipColor);
  
  ledStrip.write(colors, ledCount, brightness);
  stepCount = 0;
  colorCount = 0;
}

void loop() {
  
  // put your main code here, to run repeatedly:
  stepCount = stepCount % ledCount;
  if (stepCount == 0)
  {
    colorCount += 1;
  }
  colorCount = colorCount % numColors;
  uint8_t* tipColor = tipColors[colorCount];

  // Update color
  colors[stepCount].red = tipColor[0];
  colors[stepCount].green = tipColor[1];
  colors[stepCount].blue = tipColor[2];
  ledStrip.write(colors, ledCount, brightness);

  stepCount += 1;
  delay(40);
}

void initstrip(uint8_t color[3]){
/* 
 *  fill entire colorarray with predefined color
 */
 for(uint16_t i = 0; i < ledCount; i++)
  {
    colors[i].red = color[0];
    colors[i].green = color[1];
    colors[i].blue = color[2];
  }
}

