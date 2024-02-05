/*
* Light_WS2812 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "light_ws2812.h"
//#include "light_ws2812.c"

#include <MyNeoPixels.hpp>

//#define PORTD _SFR_IO8(0x0B)
//#define _SFR_MEM_ADDR(sfr) ((uint16_t) &(sfr))

MyWS2812B leds(PORTD, _SFR_MEM_ADDR(PORTD), DDRD, PD6, 3);

struct cRGB led[2];

int main(void)
{
  /*
  TRASHBIN

    _delay_ms(500);                         // wait for 500ms.

    led[0].r=0;led[0].g=255;led[0].b=0;			// green
    ws2812_setleds(led,2);
    _delay_ms(500);

    led[0].r=0;led[0].g=00;led[0].b=255;		// blue
    ws2812_setleds(led,2);



  
  */
  leds.clearAll();
  leds.show();

  _delay_ms(2000);

  uint32_t counter;
  while(1)
  {


    uint8_t i_0 = counter % 3;
    uint8_t i_1 = (counter+1) % 3;
    uint8_t i_2 = (counter+2) % 3;

    leds.setColor(i_0, 255, 0 , 0);
    leds.setColor(i_1, 0, 255, 0);
    leds.setColor(i_2, 0, 0, 255);
    leds.show();
    _delay_ms(500);
    counter++;
  }
}
