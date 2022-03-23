# Soldered Standalone AVR Programmer
 
Library originally made by [Adafruit](https://www.adafruit.com/). [Link](https://github.com/adafruit/Adafruit_AVRProg) to the original library. Thanks Adafruit!

This library is modified to be able to program UPDI devices using classic AVR MCUs (like ATMEGA328P or ATMEGA2560). It uses HW UART pins to program UPDI device and A2 pin (Arduino Analog In 2) as target PWR pin. You can modify pin in the example. It uses Arduino SoftwareSerial for debug messages on pons D2 and D3 (D2 = RXD, D3 = TXD). Not all debug messages are sent, because many of them are using printf() that is not supported by Arduino Core, so all these messages are commented out.

To program UPDI device, connect 470 Ohm resistor between HW UART TX and target MCU UPDI pin, HW UART RX is directly connected to target MCU UPDI pin.

~~~
    Programmer                                                Target MCU
       MCU                                              (ATTINY404 For example)
------------------                                      -------------  
              A2 |--------------------------------------| VCC
                 |                                      |
 HW UART TX (D1) |--------[470R]-------+----------------| UPDI
                 |                     |                |
 HW UART RX (D0) |---------------------+                |
                 |                                      |
             GND |--------------------------------------| GND
------------------                                      -------------
~~~

# NOTE!
The library is not maintained properly, so use it at your own risk! We do not provide any warranty!
