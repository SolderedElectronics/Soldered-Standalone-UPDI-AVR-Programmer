#include "Adafruit_AVRProg.h"
#include "SoftwareSerial.h"
#include "WS2812-SOLDERED.h"
#include "images2.cpp"

Adafruit_AVRProg avrprog = Adafruit_AVRProg();
#define AVR_POWER    6
#define WS_PIN       8
#define WS_NUMPIXELS 1

SoftwareSerial mySerial(4, 5);
WS2812 led(WS_NUMPIXELS, WS_PIN);
uint8_t fuses[10];

void setup()
{
    mySerial.begin(115200);                            /* Initialize serial for status msgs */
    avrprog.setUPDI(&Serial, 230400, AVR_POWER, true); // can also try 230400
    led.begin();
    led.setPixelColor(0, led.Color(0, 0, 0));
    led.show();
    startProgramming();
}


void loop()
{
}

void startProgramming()
{
    LEDProgramming();
    if (!avrprog.targetPower(true))
    {
        LEDError();
    }
    uint16_t signature = avrprog.readSignature();

    if (signature == 0 || signature == 0xFFFF)
    {
        LEDError();
    }
    const image_t *targetimage = &image_404;
    if (targetimage->image_chipsig != signature)
    {
        LEDError();
    }

    if (!avrprog.readFuses(fuses, 10))
    {
        LEDError();
    }

    if (!avrprog.eraseChip())
    {
        LEDError();
    }

    if (!avrprog.writeImage(targetimage->image_hexcode, pgm_read_byte(&targetimage->image_pagesize),
                            pgm_read_word(&targetimage->chipsize)))
    {
        LEDError();
    }
    LEDSucc();
}

void LEDProgramming()
{
    led.setPixelColor(0, led.Color(32, 32, 32));
    led.show();
}

void LEDError()
{
    led.setPixelColor(0, led.Color(32, 0, 0));
    led.show();
    while (true)
        ;
}

void LEDSucc()
{
    led.setPixelColor(0, led.Color(0, 32, 0));
    led.show();
    while (true)
        ;
}