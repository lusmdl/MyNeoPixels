
/* HEADER */

#include "MyNeoPixels.hpp"

const uint8_t MyWS2812B ::dimCurve[256] = {
  0,    1,    1,    2,    2,    2,    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,
  3,    3,    3,    3,    3,    3,    3,    4,    4,    4,    4,    4,    4,    4,    4,    4,
  4,    4,    4,    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,    6,    6,    6,
  6,    6,    6,    6,    6,    7,    7,    7,    7,    7,    7,    7,    8,    8,    8,    8,
  8,    8,    9,    9,    9,    9,    9,    9,    10,   10,   10,   10,   10,   11,   11,   11,
  11,   11,   12,   12,   12,   12,   12,   13,   13,   13,   13,   14,   14,   14,   14,   15,
  15,   15,   16,   16,   16,   16,   17,   17,   17,   18,   18,   18,   19,   19,   19,   20,
  20,   20,   21,   21,   22,   22,   22,   23,   23,   24,   24,   25,   25,   25,   26,   26,
  27,   27,   28,   28,   29,   29,   30,   30,   31,   32,   32,   33,   33,   34,   35,   35,
  36,   36,   37,   38,   38,   39,   40,   40,   41,   42,   43,   43,   44,   45,   46,   47,
  48,   48,   49,   50,   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,   62,
  63,   64,   65,   66,   68,   69,   70,   71,   73,   74,   75,   76,   78,   79,   81,   82,
  83,   85,   86,   88,   90,   91,   93,   94,   96,   98,   99,   101,  103,  105,  107,  109,
  110,  112,  114,  116,  118,  121,  123,  125,  127,  129,  132,  134,  136,  139,  141,  144,
  146,  149,  151,  154,  157,  159,  162,  165,  168,  171,  174,  177,  180,  183,  186,  190,
  193,  196,  200,  203,  207,  211,  214,  218,  222,  226,  230,  234,  238,  242,  248,  255,
}; 









/**
 * @brief Constructor for the MyWS2812B class.
 *        Initializes the MyWS2812B object with the given parameters.
 *        Initializes the data port, data port memory address, data direction register,
 *        data out pin, and the color array with the maximum number of LEDs.
 * 
 * @param PORTx The data port for the LEDs.
 * @param sfrMemAddrPORTx The memory address of the data port.
 * @param DDRx The data direction register for the LEDs.
 * @param numberPin The data out pin for the LEDs.
 * @param maxNumberLeds The maximum number of LEDs that can be controlled. (Default: 255)
 * 
 * @warning This method may not handle unexpected errors and could be potentially unsafe in some scenarios.
 * 
 * @note Ensure that the correct memory addresses and port settings are provided to avoid unexpected behavior.
 * 
 * @example 
 * MyWS2812B leds(PORTA, &PORTA, DDRB, 3);
 */

MyWS2812B ::MyWS2812B(volatile uint8_t& DDRx, volatile uint8_t& PORTx, uint8_t* sfrMemAddrPORTx, uint8_t numberPin, uint8_t maxNumberLeds = 255, rgbCode code = GRB) : registerPtrPORT {&PORTx}, registerPtrMemAddrPort(sfrMemAddrPORTx), registerPtrDDR {&DDRx}, pin {numberPin}, maxNumberOfLeds {maxNumberLeds}, pixelCode {code} {

  color = new cRGB[maxNumberOfLeds]; // Initialisiere das Array mit der maximalen Anzahl von LEDs.
  correctColor = new cRGB[maxNumberOfLeds]; // Initialisiere das Array mit der maximalen Anzahl von LEDs.

  brightness = new uint8_t[maxNumberLeds];
  for (uint16_t i = 0; i < maxNumberLeds; i++)
  {
    brightness[i] = 255;
  }
}



/**
 * @brief Destructor for MyWS2812B class.
 * 
 * @warning This method may cause unexpected behavior and should be used with caution.
 * 
 * @note Frees the memory allocated for the color array when the object is deleted.
 * 
 * @example
 * MyWS2812B myLEDs;
 * // ...
 * delete &myLEDs; 
 */
MyWS2812B ::~MyWS2812B() {

  delete [] color; // Gib das Array-Speicherplatz beim Löschen des Objekts frei.
}



///////////////////////////////////////////////////////////////////////
/* BELOW THIS SECTION IS THE MAGIC */
///////////////////////////////////////////////////////////////////////



// Normally ws2812_sendarray_mask() runs under disabled-interrupt condition,
// undefine if you want to accept interrupts in that function.
#define interrupt_is_disabled
 


/**
 * @brief Sets the given LED array with standard RGB values.
 * 
 * @param ledArray The array of cRGB values for the LEDs.
 * @param numberOfLeds The number of LEDs to control.
 * 
 * @warning This method may result in unexpected behavior and should be used with caution.
 * 
 * @note The function sets the LED array using ws2812_setleds_pin() with the data output pin for the LEDs.
 * 
 * @example 
 * MyWS2812B ws2812;
 * struct cRGB leds[2] = {{255, 0, 0}, {0, 255, 0}}; 
 * ws2812.ws2812_setleds(leds, 2);
 */
void inline MyWS2812B ::ws2812_setleds(struct cRGB  *ledArray, uint16_t numberOfLeds)
{
  ws2812_setleds_pin(ledArray,numberOfLeds, 1 << (pin));
}



/**
 * @brief Sets the LED array with a specified data out pin mask.
 * 
 * @param ledarray The array of cRGB values for the LEDs.
 * @param leds The number of LEDs to control.
 * @param pinmask The pin mask to specify the data out pin for the LEDs.
 * 
 * @warning This method may have unpredictable behavior and is considered unsafe in certain scenarios.
 * 
 * @note Calls ws2812_sendarray_mask() with the LED array, number of LEDs multiplied by 3 (for RGB values), and the pin mask.
 * Delays for a reset time after sending the data.
 * 
 * @example 
 * ws2812_setleds_pin(myLedArray, 8, 0xFF);
 */
void inline MyWS2812B ::ws2812_setleds_pin(struct cRGB *ledarray, uint16_t leds, uint8_t pinmask)
{
  ws2812_sendarray_mask((uint8_t*)ledarray,leds+leds+leds,pinmask);
  _delay_us(TIME_RESET);
}












/**
 * @brief This method sends an array of RGB values to WS2812B LEDs using the fast 800kHz clockless WS2811/2812 protocol.
 * 
 * @param data The array of RGB values to send to the LED.
 * @param datlen The length of the data array.
 * 
 * @warning This method may have unexpected behavior in certain situations and is considered unsafe in some cases.
 * 
 * @note Ensure that the data array and length are correctly formatted before calling this method.
 * 
 * @example 
 * MyWS2812B ws2812b;
 * uint8_t rgbData[] = {255, 0, 0}; // Red color
 * ws2812b.ws2812_sendarray(rgbData, sizeof(rgbData));
 */
void MyWS2812B ::ws2812_sendarray(uint8_t *data,uint16_t datlen)
{
  ws2812_sendarray_mask(data,datlen,1 << (pin));
}







// Timing in ns

#define w_zeropulse   350
#define w_onepulse    900
#define w_totalperiod 1250


// Fixed cycles used by the inner loop

#if defined(__LGT8F__)
#define w_fixedlow    4
#define w_fixedhigh   6
#define w_fixedtotal  10   
#else
#define w_fixedlow    3
#define w_fixedhigh   6
#define w_fixedtotal  10   
#endif


// Insert NOPs to match the timing, if possible

#define w_zerocycles    (((F_CPU/1000)*w_zeropulse          )/1000000)
#define w_onecycles     (((F_CPU/1000)*w_onepulse    +500000)/1000000)
#define w_totalcycles   (((F_CPU/1000)*w_totalperiod +500000)/1000000)


// w1 - nops between rising edge and falling edge - low

#define w1 (w_zerocycles-w_fixedlow)


// w2   nops between fe low and fe high

#define w2 (w_onecycles-w_fixedhigh-w1)


// w3   nops to complete loop

#define w3 (w_totalcycles-w_fixedtotal-w1-w2)


#if w1>0
  #define w1_nops w1
#else
  #define w1_nops  0
#endif


// The only critical timing parameter is the minimum pulse length of the "0"
// Warn or throw error if this timing can not be met with current F_CPU settings.

#define w_lowtime ((w1_nops+w_fixedlow)*1000000)/(F_CPU/1000)
#if w_lowtime>550
   #error "Light_ws2812: Sorry, the clock speed is too low. Did you set F_CPU correctly?"
#elif w_lowtime>450
   #warning "Light_ws2812: The timing is critical and may only work on WS2812B, not on WS2812(S)."
   #warning "Please consider a higher clockspeed, if possible"
#endif   

#if w2>0
#define w2_nops w2
#else
#define w2_nops  0
#endif

#if w3>0
#define w3_nops w3
#else
#define w3_nops  0
#endif

#define w_nop1  "nop      \n\t"
#ifdef interrupt_is_disabled
#define w_nop2  "brid .+0 \n\t"
#else
#define w_nop2  "brtc .+0 \n\t"
#endif
#define w_nop4  w_nop2 w_nop2
#define w_nop8  w_nop4 w_nop4
#define w_nop16 w_nop8 w_nop8








/**
 * @brief Sends an array of bytes with RGB values using the WS2811/2812 protocol with a specified pin mask.
 * 
 * @param data The array of data bytes.
 * @param datlen The length of the data array.
 * @param maskhi The pin mask for the data output pin.
 * 
 * @warning This method uses inline assembly code to control the timing and signal for each byte of data which can lead to unexpected behavior and potential vulnerabilities.
 * 
 * @note Ensure proper understanding of the WS2811/2812 protocol and the specific hardware before using this method.
 * 
 * @example 
 * MyWS2812B::ws2812_sendarray_mask(dataArray, dataLength, maskValue);
 */
void inline MyWS2812B ::ws2812_sendarray_mask(uint8_t *data,uint16_t datlen,uint8_t maskhi)
{
  uint8_t curbyte,ctr,masklo;
  uint8_t sreg_prev;

  uint8_t *port = registerPtrMemAddrPort;
  
  (*registerPtrDDR) |= maskhi; // Enable output
  
  masklo	= ~maskhi & (*registerPtrPORT);

  maskhi |= (*registerPtrPORT);
  
  sreg_prev=SREG;
#ifdef interrupt_is_disabled
  cli();  
#endif  

  while (datlen--) {
    curbyte=*data++;
    
    asm volatile(
    "       ldi   %0,8  \n\t"
#ifndef interrupt_is_disabled
    "       clt         \n\t"
#endif
    "loop%=:            \n\t"
    "       st    X,%3 \n\t"    //  '1' [02] '0' [02] - re

#if (w1_nops&1)
w_nop1
#endif
#if (w1_nops&2)
w_nop2
#endif
#if (w1_nops&4)
w_nop4
#endif
#if (w1_nops&8)
w_nop8
#endif
#if (w1_nops&16)
w_nop16
#endif
#if defined(__LGT8F__)
    "       bst   %1,7  \n\t"    //  '1' [02] '0' [02]
    "       brts  1f    \n\t"    //  '1' [04] '0' [03]
    "       st    X,%4  \n\t"    //  '1' [--] '0' [04] - fe-low
    "1:     lsl   %1    \n\t"    //  '1' [05] '0' [05]
#else
    "       sbrs  %1,7  \n\t"    //  '1' [04] '0' [03]
    "       st    X,%4 \n\t"     //  '1' [--] '0' [05] - fe-low
    "       lsl   %1    \n\t"    //  '1' [05] '0' [06]
#endif
#if (w2_nops&1)
  w_nop1
#endif
#if (w2_nops&2)
  w_nop2
#endif
#if (w2_nops&4)
  w_nop4
#endif
#if (w2_nops&8)
  w_nop8
#endif
#if (w2_nops&16)
  w_nop16 
#endif
    "       brcc skipone%= \n\t"    //  '1' [+1] '0' [+2] - 
    "       st   X,%4      \n\t"    //  '1' [+3] '0' [--] - fe-high
    "skipone%=:               "     //  '1' [+3] '0' [+2] - 
#if (w3_nops&1)
w_nop1
#endif
#if (w3_nops&2)
w_nop2
#endif
#if (w3_nops&4)
w_nop4
#endif
#if (w3_nops&8)
w_nop8
#endif
#if (w3_nops&16)
w_nop16
#endif

    "       dec   %0    \n\t"    //  '1' [+4] '0' [+3]
    "       brne  loop%=\n\t"    //  '1' [+5] '0' [+4]
    :	"=&d" (ctr)
    :	"r" (curbyte), "x" (port), "r" (maskhi), "r" (masklo)
    );
  }
  
  SREG=sreg_prev;
#ifdef interrupt_is_disabled
  sei();  // enable after the magic happend
#endif  
}



///////////////////////////////////////////////////////////////////////
/* ABOVE THIS SECTION IS THE MAGIC */
///////////////////////////////////////////////////////////////////////



/**
 * @brief Sets the color of a specific LED.
 * 
 * @param led The index of the LED for which to set the color.
 * @param r The red value of the color (0-255).
 * @param g The green value of the color (0-255).
 * @param b The blue value of the color (0-255).
 * 
 * @warning This method may produce unexpected results in certain cases and is considered unsafe.
 * 
 * @note Make sure to properly handle input values within the 0-255 range for RGB color values.
 * 
 * @example 
 * MyWS2812B.setColor(2, 255, 0, 0);
 * // Sets the color of the 3rd LED to pure red.
 */
void MyWS2812B ::setColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {

  
  color[led] = {r, g, b};

  calculateBrightness(brightness[led], led);

}







/**
 * @brief Sets the color of a specific LED in a MyWS2812B strip based on the given mode.
 * 
 * @param led The index of the LED to set the color for
 * @param mode The color mode to apply (warm white or default)
 * 
 * @warning This method may produce unexpected results and is considered unsafe in certain scenarios.
 * @note If an unsupported mode is provided, the default color (255, 255, 255) will be used.
 * 
 * @example 
 * MyWS2812B strip;
 * strip.setColor(2, warmWhite);
 */
void MyWS2812B ::setColor(uint8_t led, colorModes mode) {

  switch (mode)
  {
  case warmWhite:
    color[led] = {255, 75, 15};
    break;
  
  default:
    color[led] = {255, 255, 255};
    break;
  }

  calculateBrightness(brightness[led], led);

}






/**
 * @brief Sets the color of all the WS2812B LEDs to the specified color mode.
 * 
 * @param mode The color mode to set for all LEDs
 * 
 * @warning This method might behave unexpectedly if the number of LEDs exceeds the maximum allowed.
 * 
 * @note This method sets the color of all LEDs in the strip to the specified color mode.
 * 
 * @example 
 * 
 * // Set all LEDs to red color
 * MyWS2812B.setColor(RED);
 */
void MyWS2812B ::setColor(colorModes mode) {

  for (int i = 0; i < maxNumberOfLeds; i++)
  {
    setColor(i, mode);
  }
  

}


/**
 * @brief Sets the color of all WS2812B LEDs to the specified RGB values.
 * 
 * @param r The red component value (0-255)
 * @param g The green component value (0-255)
 * @param b The blue component value (0-255)
 * 
 * @warning This method may be unsafe in certain cases where unexpected behavior could occur.
 * 
 * @note This method sets the same RGB color for all LEDs in the strip.
 * 
 * @example 
 * MyWS2812B.setColor(255, 0, 0);
 */
void MyWS2812B ::setColor(uint8_t r, uint8_t g, uint8_t b) {

  for (int i = 0; i < maxNumberOfLeds; i++)
  {
    setColor(i, r,g,b);
  }
  

}



/**
 * @brief Sends the color data for all LEDs to the WS2812B strip.
 * 
 * @warning This method may be insecure and unexpected behavior could occur.
 * 
 * @note This method uses the ws2812_setleds() function.
 * 
 * @example 
 * MyWS2812B strip;
 * strip.show();
 */
void MyWS2812B ::show() {

  ws2812_setleds(correctColor,maxNumberOfLeds);
}



/**
 * @brief Clears the color data for all LEDs.
 * 
 * @warning This method sets the color of all LEDs to black (RGB values set to 0), 
 * clearing all color data. It can potentially lead to unexpected behavior in certain situations.
 * 
 * @note Use with caution as it will clear all existing color data for the LEDs.
 * 
 * @example 
 * MyWS2812B.clearColor();
 */
void MyWS2812B ::clearColor() {

  for (uint8_t i = 0; i < maxNumberOfLeds; i++)
  {
    setColor(i, 0,0,0);
  }
}






/**
 * @brief Clears the color data for a specific LED by setting its RGB values to 0.
 * 
 * @param led The index of the LED in the array to clear the color data for.
 * 
 * @warning This method may behave unexpectedly if the LED index is out of bounds.
 * 
 * @note Calling this method will reset the RGB values of the specified LED to black.
 * 
 * @example
 * MyWS2812B myLED;
 * myLED.clearColor(2);
 */
void MyWS2812B ::clearColor(uint8_t led) {

  color[led].r = 0;
  color[led].g = 0;
  color[led].b = 0;
}




/**
 * @brief Calculates the corrected brightness of a specific LED color component based on the brightness level and LED configuration.
 * 
 * @param bright The brightness level of the LED (0-255)
 * @param led The index of the LED color component (0-2)
 * 
 * @return The calculated corrected brightness percentage for the LED color component
 * 
 * @warning This method may encounter unexpected behavior and is considered unsafe in certain scenarios.
 * 
 * @note The correct LED color component calculation is done based on the pixel code configuration.
 * 
 * @example 
 * double brightness = MyWS2812B.calculateBrightness(150, 1);
 * // Calculate corrected brightness for LED component 1 with brightness level 150
 */
double MyWS2812B ::calculateBrightness (uint8_t bright, uint8_t led) {

  double percent = static_cast<double>(dimCurve[bright]) / 255;

  switch (pixelCode)
  {
  case RGB:

    correctColor[led].r = color[led].r * percent;
    correctColor[led].g = color[led].g * percent;
    correctColor[led].b = color[led].b * percent;
    break;

  case RBG:

    correctColor[led].r = color[led].r * percent;
    correctColor[led].b = color[led].g * percent;
    correctColor[led].g = color[led].b * percent;
    break;
    
  case GRB:

    correctColor[led].g = color[led].r * percent;
    correctColor[led].r = color[led].g * percent;
    correctColor[led].b = color[led].b * percent;
    break;

  case GBR:

    correctColor[led].g = color[led].r * percent;
    correctColor[led].b = color[led].g * percent;
    correctColor[led].r = color[led].b * percent;
    break;

  case BGR:

    correctColor[led].b = color[led].r * percent;
    correctColor[led].g = color[led].g * percent;
    correctColor[led].r = color[led].b * percent;
    break;
    
  case BRG:

    correctColor[led].b = color[led].r * percent;
    correctColor[led].r = color[led].g * percent;
    correctColor[led].g = color[led].b * percent;
    break;
  
  default:
    correctColor[led].r = color[led].r * percent;
    correctColor[led].g = color[led].g * percent;
    correctColor[led].b = color[led].b * percent;
    break;
  }

  

  return percent;
}




/**
 * @brief Get the color of a specific LED in the WS2812B strip.
 * 
 * @param led The index of the LED whose color is to be retrieved
 * @return The color of the specified LED
 * 
 * @warning This method may lead to unexpected behavior if the LED index is out of bounds.
 * @note Ensure that the LED index provided is within the valid range of LEDs.
 * 
 * @example 
 * cRGB myColor = getColor(3);
 * displayColor(myColor); // Example output method
 */
cRGB MyWS2812B ::getColor(uint8_t led) {

  return color[led];

}






/**
 * @brief Sets the brightness value for all LEDs in the strip.
 * 
 * @param n The brightness value to be set for all LEDs (0-255).
 * 
 * @warning This method may not handle unexpected inputs and could lead to undefined behavior.
 * 
 * @note The brightness value is applied to all LEDs in the strip.
 * 
 * @example 
 * myStrip.setBrightness(100);
 */
void MyWS2812B ::setBrightness(uint8_t n) {

  for (uint16_t led = 0; led < maxNumberOfLeds; led++)
  {
    brightness[led] = n;
    calculateBrightness(n, led);
  }
}






/**
 * @brief Sets the brightness of a specific WS2812B LED.
 * 
 * @param n The brightness value to set (0-255).
 * @param led The index of the LED to set the brightness for.
 * 
 * @warning This method may behave unexpectedly and be unsafe in certain conditions.
 * 
 * @note Make sure to check the range of the brightness value before calling this method.
 * 
 * @example 
 * MyWS2812B ws2812b;
 * ws2812b.setBrightness(200, 1);
 */
void MyWS2812B ::setBrightness(uint8_t n, uint8_t led) {

  brightness[led] = n;
  calculateBrightness(n, led);
}








/**
 * @brief This method retrieves the maximum number of pixels supported by the WS2812B LED strip.
 * 
 * @return The maximum number of pixels supported
 * 
 * @warning This method may be unsafe in certain situations where the maximum number of pixels is exceeded.
 * 
 * @note Please ensure the maximum number of pixels is within the specified limit to avoid unexpected behavior.
 * 
 * @example
 * uint8_t maxPixels = myWS2812B.getMaxNumPixels();
 * Serial.print("Maximum number of pixels: ");
 * Serial.println(maxPixels);
 */
uint8_t MyWS2812B ::getMaxNumPixels() {
  return maxNumberOfLeds;
}