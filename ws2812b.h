// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        1 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 60 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int DELAYVAL = 50; // Time (in milliseconds) to pause between pixels

//根据led数量算出彩虹的各led的颜色
uint32_t colors[NUMPIXELS];

//黑灯时的颜色值
uint32_t black=pixels.Color(0,0,0);

//流水线的每一步的显示类型
uint8_t flow[8];

//是否开启流水线
bool hasFlow=false;

uint32_t flowColor=pixels.Color(255,255,0);

void begin() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

//设置亮度
void setBrightness(int brightness){
  pixels.setBrightness(brightness+1);
  pixels.show();
}

//设置跑马灯的速度
void setSpeed(int speed){
  DELAYVAL=(101-speed)*10;
}

//设置颜色
void setColor(uint32_t color){
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i,color);
  }
  pixels.show();
}

//彩灯渐变
void colorfour(bool needDelay){
   for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i,pixels.Color(0,0,0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    if(needDelay){
      delay(DELAYVAL);
    } 
   }
}

////彩灯渐变
//void rainbow(int wait)
//{
//    // Hue of first pixel runs 5 complete loops through the color wheel.
//    // Color wheel has a range of 65536 but it's OK if we roll over, so
//    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
//    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
////    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
////    {
//        for (int i = 0; i < NUMPIXELS; i++)
//        { // For each pixel in strip...
//            // Offset pixel hue by an amount to make one full revolution of the
//            // color wheel (range of 65536) along the length of the strip
//            // (strip.numPixels() steps):
//            int pixelHue = 0 + (i * 65536L / NUMPIXELS);
//            // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
//            // optionally add saturation and value (brightness) (each 0 to 255).
//            // Here we're using just the single-argument hue variant. The result
//            // is passed through strip.gamma32() to provide 'truer' colors
//            // before assigning to each pixel:
//            pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
//        }
//        pixels.show(); // Update strip with new contents
//        delay(wait);  // Pause for a moment
////    }
//}

//彩灯渐变
void tRainbow(int wait)
{
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
    {
       uint32_t color = pixels.gamma32(pixels.ColorHSV(firstPixelHue));
    
        for (int i = 0; i < NUMPIXELS; i++)
        { // For each pixel in strip...
            // Offset pixel hue by an amount to make one full revolution of the
            // color wheel (range of 65536) along the length of the strip
            // (strip.numPixels() steps):
//            int pixelHue = 0 + (i * 65536L / NUMPIXELS);
            // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
            // optionally add saturation and value (brightness) (each 0 to 255).
            // Here we're using just the single-argument hue variant. The result
            // is passed through strip.gamma32() to provide 'truer' colors
            // before assigning to each pixel:
            pixels.setPixelColor(i,color);
             
        }
        pixels.show(); // Update strip with new contents
            delay(wait);  // Pause for a moment
       
    }
}

//彩灯渐变
void rainbow(int wait)
{
    // Hue of first pixel runs 5 complete loops through the color wheel.
    // Color wheel has a range of 65536 but it's OK if we roll over, so
    // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
    // means we'll make 5*65536/256 = 1280 passes through this outer loop:
//    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
//    {
        for (int i = 0; i < NUMPIXELS; i++)
        { // For each pixel in strip...
            // Offset pixel hue by an amount to make one full revolution of the
            // color wheel (range of 65536) along the length of the strip
            // (strip.numPixels() steps):
            int pixelHue = 0 + (i * 65536L / NUMPIXELS);
            // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
            // optionally add saturation and value (brightness) (each 0 to 255).
            // Here we're using just the single-argument hue variant. The result
            // is passed through strip.gamma32() to provide 'truer' colors
            // before assigning to each pixel:
            pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
             pixels.show(); // Update strip with new contents
            delay(wait);  // Pause for a moment
        }
       
//    }
}

//由暗转亮
void toLight(uint32_t color){
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, color);
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

//由亮转暗
void toBlack(uint32_t color){
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i,black);
    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
  }
}

uint32_t getGradientColors(){
  
}

uint32_t toColor(uint32_t colors[]){
  
  return pixels.Color(colors[0],colors[1],colors[2]);
}

void setFlowColor(uint32_t color){
  flowColor=color;
}

void setFlow(){
  
}

void runFlow(){
//   toLight(flowColor);
//   toBlack(flowColor);
   rainbow(DELAYVAL);
   toBlack(flowColor);
   tRainbow(DELAYVAL);
   toBlack(flowColor);
}
