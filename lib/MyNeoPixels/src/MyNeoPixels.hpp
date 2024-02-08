#ifndef MYNEOPIXELS_HPP
#define MYNEOPIXELS_HPP

/* AVR */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



/* MY */




/* C/C++ */





/* MACROS */



/* USER DEFINED TYPES */

/*
 *  Structure of the LED array
 *
 * cRGB:     RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 * cRGBW:    RGBW for SK6812RGBW
 */
struct cRGB  { uint8_t g; uint8_t r; uint8_t b; }; // RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
struct cRGBW { uint8_t g; uint8_t r; uint8_t b; uint8_t w;}; // RGBW for SK6812RGBW






/* ENUMS */

enum colorModes {
    warmWhite

};

enum rgbCode {
    RGB,
    RBG,
    GRB,
    GBR,
    BGR,
    BRG
};















/* CLASSES */

class MyWS2812B {


    private:

        /* CONSTANTS */

        #define TIME_RESET 50 // WS2812 and clones only need 50 µs
        static const uint8_t dimCurve[256];

        /* DATA */

        volatile uint8_t* registerPtrPORT; // Data port 
        uint8_t* registerPtrMemAddrPort;
        volatile uint8_t* registerPtrDDR; // Data port 
        uint8_t pin;  // Data out pin
        uint8_t maxNumberOfLeds;
        rgbCode pixelCode;
        cRGB* color;
        cRGB* correctColor;
        uint8_t* brightness;


        /* SETTER */

        void inline ws2812_setleds_pin(struct cRGB *ledarray, uint16_t leds, uint8_t pinmask);
        void ws2812_sendarray(uint8_t *data,uint16_t datlen);
        void inline ws2812_sendarray_mask(uint8_t *data,uint16_t datlen,uint8_t maskhi);
        void inline ws2812_setleds (struct cRGB  *ledArray, uint16_t numberOfLeds);
        double calculateBrightness (uint8_t bright, uint8_t led);


    protected:


    public:

        /* CONSTRUCTOR */

        MyWS2812B(volatile uint8_t& DDRx, volatile uint8_t& PORTx, uint8_t* sfrMemAddrPORTx, uint8_t numberPin, uint8_t maxNumberLeds = 255, rgbCode code = GRB);


        /* DESTRUCTOR */

        ~MyWS2812B();


        /* SETTER */

        void setColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
        void setColor(uint8_t led, colorModes mode);
        void setBrightness(uint8_t n);
        void setBrightness(uint8_t n, uint8_t led);
        void show();
        void clearColor();
        void clearColor(uint8_t led);

        /* GETTER */
        cRGB getColor(uint8_t led);
        
};

#endif


