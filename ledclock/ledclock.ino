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
const uint8_t bckColor[3]  = { 0, 0, 1 };
// Set the color of the tip { red, green, blue} max values are 255
const uint8_t tipColor[3]  = { 255, 255, 255 };
// Set the brightness to use (the maximum is 31)
// note: you can only set the brightness for the entire strip (not separate leds).
const uint8_t brightness = 5;
// Set the number of leds that make the tip
const uint16_t tipWidth = 4;
// Set the number of leds to step (times 100)
const uint16_t stepSize = 464;
// Set color for visualizing the points of the steps (set to all zeros in case you dont want to see this)
const uint8_t stepsColor[3]  = { 1, 0, 0 };
// Set the number of seconds that should take a single roundtrip of the tip
const uint32_t cycleTime = 60;
// Set number of tips
const uint16_t noTips = 5;


/*
 * START PROGRAM
 */
// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];
uint16_t stepCount;
const uint32_t dtime = cycleTime*1000 / ledCount;
const uint32_t dtips = round(ledCount / noTips);

void setup() {
  // put your setup code here, to run once:
  
  stepCount = 0;
  
  initstrip(bckColor);
  ledStrip.write(colors, ledCount, brightness);
}

void loop() {  
  uint16_t index;
  // put your main code here, to run repeatedly:
  stepCount = stepCount % ledCount;

  // Update color
  if round((stepCount*100 % stepSize)/100 == 0 )
  {
    initstrip(bckColor);
    visualsteps(stepsColor);
    for(uint16_t i = 0; i < noTips; i++)
    {
      index = stepCount + ledCount - i*dtips;
      colortip(tipColor, index);
    }
  }
  
  ledStrip.write(colors, ledCount, brightness);
  ledStrip.write(colors, ledCount, brightness);

  stepCount += 1;
  delay(dtime);
  
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

void colortip(uint8_t color[3], uint16_t firstIndex){
/* 
 *  fill tip with predefined color, firstIndex gives index of tip
 */
 uint16_t index;
 for(uint16_t i = 0; i < tipWidth; i++)
  {
    index = (firstIndex+ledCount-i) % ledCount;
    colors[index].red = color[0];
    colors[index].green = color[1];
    colors[index].blue = color[2];
  }
}

void visualsteps(uint8_t color[3]){
for(uint16_t i = 0; i < ledCount; i++)
  {
    if round((i*100 % stepSize)/100 == 0 )
    {
      colors[i].red = color[0];
      colors[i].green = color[1];
      colors[i].blue = color[2];
    }
    
  }
}

