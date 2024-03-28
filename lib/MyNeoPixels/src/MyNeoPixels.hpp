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

/**
 * 
 * 
*/
struct pod_leddata {

    uint8_t maxNumberOfLeds;
    uint8_t* brightness;
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

// NEO PIXEL TYPES

#include "MyWS2812B.hpp"

#endif