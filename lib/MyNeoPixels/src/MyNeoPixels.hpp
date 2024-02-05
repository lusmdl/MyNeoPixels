#ifndef MYNEOPIXELS_HPP
#define MYNEOPIXELS_HPP

/* AVR */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



/* MY */
#include "MyNeoPixelsUserConfigFile.h"




/* C/C++ */





/* MACROS */



/*
TRASHBIN:

// Define Reset time in µs.
#if !defined(ws2812_resettime)
#define ws2812_resettime    300
#endif

// Define I/O pin
#if !defined(ws2812_port)
#define ws2812_port B   // Data port
#endif
#if !defined(ws2812_pin)
#define ws2812_pin  0   // Data out pin
#endif
// Internal defines

#if !defined(CONCAT)
#define CONCAT(a, b)            a ## b
#endif

#if !defined(CONCAT_EXP)
#define CONCAT_EXP(a, b)   CONCAT(a, b)
#endif

#define ws2812_PORTREG  CONCAT_EXP(PORT,ws2812_port)
#define ws2812_DDRREG   CONCAT_EXP(DDR,ws2812_port)


*/



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

        #define TIME_RESET 300 // WS2812 and clones only need 50 µs

        /* DATA */

        volatile uint8_t* registerPtrPORT; // Data port 
        uint16_t* registerPtrMemAddrPort;
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
        MyWS2812B(volatile uint8_t& PORTx, uint16_t sfrMemAddrPORTx, volatile uint8_t& DDRx, uint8_t numberPin, uint8_t maxNumberLeds);


        /* DESTRUCTOR */
        ~MyWS2812B();


        /* set */

        void setColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
        void show();
        void clearAll();














};





#endif


