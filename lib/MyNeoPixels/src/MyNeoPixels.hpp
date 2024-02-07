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

















/* CLASSES */

class MyWS2812B {


    private:

        /* CONSTANTS */

        #define TIME_RESET 50 // WS2812 and clones only need 50 µs
        const uint8_t dimCurve[] = {
            0,    1,    1,    2,    2,    2,    2,    2,    2,    3,    3,    3,    3,    3,    3,    3,
        	3,    3,    3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        	4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6,
        	6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8,
        	8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11,
        	11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15,
        	15, 15, 16, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20,
        	20, 20, 21, 21, 22, 22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26,
        	27, 27, 28, 28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35,
        	36, 36, 37, 38, 38, 39, 40, 40, 41, 42, 43, 43, 44, 45, 46, 47,
        	48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
        	63, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 78, 79, 81, 82,
        	83, 85, 86, 88, 90, 91, 93, 94, 96, 98, 99, 101, 103, 105, 107, 109,
        	110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
        	146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
        	193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
        }; 


        /* DATA */

        volatile uint8_t* registerPtrPORT; // Data port 
        uint8_t* registerPtrMemAddrPort;
        volatile uint8_t* registerPtrDDR; // Data port 
        uint8_t pin;  // Data out pin
        uint8_t maxNumberOfLeds {255};
        cRGB* color;


        /* SETTER */

        void inline ws2812_setleds_pin(struct cRGB *ledarray, uint16_t leds, uint8_t pinmask);
        void ws2812_sendarray(uint8_t *data,uint16_t datlen);
        void inline ws2812_sendarray_mask(uint8_t *data,uint16_t datlen,uint8_t maskhi);
        void inline ws2812_setleds (struct cRGB  *ledArray, uint16_t numberOfLeds);


    protected:


    public:

        /* CONSTRUCTOR */

        MyWS2812B(volatile uint8_t& DDRx, volatile uint8_t& PORTx, uint8_t* sfrMemAddrPORTx, uint8_t numberPin, uint8_t maxNumberLeds);


        /* DESTRUCTOR */

        ~MyWS2812B();


        /* SETTER */

        void setColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
        void show();
        void clearAll();
        
};

#endif


