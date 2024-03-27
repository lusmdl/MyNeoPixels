#ifndef MYNEOPIXELS_HPP
#define MYNEOPIXELS_HPP

// AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// MACROS

#define TIME_RESET 50 // WS2812 and clones only need 50 µs


// ENUMS

/**
 * 
 * @note 
    RED,
    BLUE,
    YELLOW,
    GREEN,
    ORANGE,
    PURPLE,
    PINK,
    BROWN,
    BLACK,
    WHITE,   
    WARM_WHITE
 * 
 * 
 * 
*/
enum enum_colormodes {
    
    RED,
    BLUE,
    YELLOW,
    GREEN,
    ORANGE,
    PURPLE,
    PINK,
    BROWN,
    BLACK,
    WHITE,   
    WARM_WHITE

};


/**
 * 
 * 
 * 
 * @note
    RGB,
    RBG,
    GRB,
    GBR,
    BGR,
    BRG
 * 
 * 
 * 
 * 
 * 
*/
enum enum_colormapping {
    RGB,
    RBG,
    GRB,
    GBR,
    BGR,
    BRG
};


// Plain Old Data
//
// Für Datenübertragung zwischen Softwarekomponenten
// 
// Regeln:
// - Einfache Datenstrukturen
// - Nur Daten, keine Methoden
// - kompakt und leichtgewichtig
// - portabel
// - unveränderlich

/*
 *  Structure of the LED array
 *
 * pod_rgb:     RGB  for WS2812S/B/C/D, SK6812, SK6812Mini, SK6812WWA, APA104, APA106
 */
struct pod_rgb  { 

    uint8_t g; 
    uint8_t r; 
    uint8_t b; 
};

/*
 *  Structure of the LED array
 *
 * pod_rgbw:    RGBW for SK6812RGBW
 */
struct pod_rgbw { 
    
    uint8_t g; 
    uint8_t r; 
    uint8_t b; 
    uint8_t w;
};



// CLASSES 

// BASIC CLASS

/**
 * 
 * 
 * 
 * 
*/
class MyNeoPixels {

    protected:

        // MEMBER

        // CONSTANTS

        static const uint8_t dimCurve[256]; // Brightness values, adapted to the actual brightness curve from 0 to 255
};

class MyWS2812B : public MyNeoPixels {


    private:

        // MEMBER

        // Registers

        // Data pin Data Direction Register 
        volatile uint8_t* ptrDataDirectionRegister_; 

        // Data pin PORT register
        volatile uint8_t* ptrPortRegister_;

        // here comes the information for the poiter
        uint8_t* ptrPortRegisterMemAddr_;

        // Data pin Number (register bit)
        uint8_t pin_;

        // LED data

        enum_colormapping colorMapping_;
        pod_rgb* colorMapped_;

        uint8_t maxNumberOfLeds_;
        pod_rgb* color_;
        uint8_t* brightness_;


        // SETTER

        void inline setLedsPin(pod_rgb *led_array, uint16_t leds, uint8_t pin_mask);
        void sendArray(uint8_t *data, uint16_t data_len);
        void inline sendArrayMask(uint8_t *data, uint16_t data_len, uint8_t maskhi);
        void inline setLeds (pod_rgb  *led_array, uint16_t number_of_leds);
        double calculateBrightness (uint8_t bright, uint8_t led);


    protected:


    public:

        // CONSTRUCTOR

        MyWS2812B(volatile uint8_t& ddrx, volatile uint8_t& portx, uint8_t* sfr_mem_addr_portx, uint8_t pin_number, uint8_t max_number_of_leds = 255, enum_colormapping color_mapping = GRB);


        // DESTRUCTOR

        ~MyWS2812B();


        // SETTER

        // FOR ALL LEDS

        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setColor(enum_colormodes mode);
        void setBrightness(uint8_t n);
        void clearColor();

        // FOR ONE SPECIFIC LED

        void setColor(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
        void setColor(uint8_t led, enum_colormodes mode);
        void setBrightness(uint8_t n, uint8_t led);
        void clearColor(uint8_t led);

        // EXECUTE

        void show();

        // GETTER

        pod_rgb getColor(uint8_t led);
        uint8_t getMaxNumPixels();
};
#endif