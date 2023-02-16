# CRSF for Arduino

[![GitHub release (latest by date)](https://img.shields.io/github/v/release/ZZ-Cat/CRSFforArduino)](https://github.com/ZZ-Cat/CRSFforArduino/releases/latest)
[![GitHub license](https://img.shields.io/github/license/ZZ-Cat/CRSFforArduino)](https://github.com/ZZ-Cat/CRSFforArduino/blob/Main-Trunk/LICENSE.md)
[![Build Status](https://github.com/ZZ-Cat/CRSFforArduino/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/ZZ-Cat/CRSFforArduino/actions)
[![Conventional Commits](https://img.shields.io/badge/Conventional%20Commits-1.0.0-%23FE5196?logo=conventionalcommits&logoColor=white)](https://conventionalcommits.org)

## Written & developed by

Cassandra "ZZ Cat" Robinson

## Discontinuation of Arduino IDE

Arduino IDE support in Visual Studio Code is being discontinued.
The Visual Studo Code extension that adds support for Arduino is discontinuing support for the Arduino IDE.
This means that I too am discontinuing support for the Arduino IDE in all of my projects - starting with CRSF for Arduino.
The good news is that my library is in its early stages of development, I have not yet made any official releases of my library, & it isn't being widely used yet. This makes it easier for me to adapt to the new changes.

Does this mean that I may need to rebrand my library? Yes.
I originally created my library for use within the Arduino IDE (assuming 1.8, here. Not 2.0) without being aware of the fact that the IDE itself had already reached the end of its life, & Arduino themselves had discontinued it.
If I kept the name "CRSF for Arduino" moving forward, this would imply that you can still use it in the (now discontinued) Arduino IDE. Thus, sending the wrong message about what my library is compatible with.

What of my two existing branches involving telemetry?
Well... for starters, I rebased Telemetry-Feedback & during that rebase, I somehow managed to completely obliterate my code for telemetry feedback. =</.>=
I don't know how I did that, but it happened. I was already planning on refactoring it anyway, so now I am having to rewrite it entirely.

So, where to, from here?
I am no longer using the Arduino IDE.
In fact, I haven't actually used the Arduino IDE itself in a _very_ long time. All of my development is done in Visual Studio Code, these days. For my Arduino-related projects, I have been using an extension in Visual Studio Code that adds support for the Arduino IDE. The developers of this extension are discontinuing support for the Arduino IDE altogether, & they have no plans to introduce support for version 2.0 of the Arduino IDE.

It _just so happens_ that over the last two days, I have been conducting preliminary tests with PlatformIO & learning how to develop with that. PlatformIO is 100% platform agnostic, has its own built-in debugging system, it even has its own Continuous Integration/Continuous Deployment (I have been chasing after decent CI/CD ever since I started my project), & it has everything that I need & nothing that I don't need.
At this point, I am like "Where has this been all my life & why am I not already using it?"
Using PlatformIO is a no-brainer, for me. So, there you go. From 2023-02-17 10:48 Hrs NZDT, I am using PlatformIO as my IDE of choice for developing my embedded systems projects.

## Warning

CRSFforArduino is undergoing active development & is not yet ready for prime time release.
If you choose to use CRSFforArduino in its current state, do so at your own risk.
Some features may be broken, bugged, untested, missing, or the code as a whole may resemble a pigeon flying by swinging its head around in circles.

Fear not! I am working on this library (aside from flying my helicopters & helping out with other heli-related projects) & I have every intention of making that stubborn pigeon fly by using its wings. No matter how much the basterd wants to insist on swinging its head around in circles to fly. =^/.~=

If you have spotted any bugs, something isn't working the way it should, or you have any suggestions on what you want to see in CRSFforArduino, don't hesitate to open an Issue. The Discussions tab is also open, so if you want to chat to me about my library, feel free to do so there.

## Description

Traditional PWM RC receivers are becoming a thing of the past & (by extension) are getting harder & harder to come by.
CRSF is _the_ de-facto standard for RC nowadays, & it is time to bring it to the world of Arduino!
This means that your development board is now compatible with any receiver that runs ExpressLRS firmware.

## Why ExpressLRS?

For starters, it's an open source radio control link that offers incredibly low latency, long range (EG [100 kilometers on 2.4GHz](https://youtu.be/IjQYLyvai6s) without failsafe), & it's incredibly robust in rough RF environments.

An ExpressLRS receiver communicates to your development board through one of the board's Serial/UART ports.
This provides you with up to 16 10-bit full resolution channels & telemetry without taking up unnecessary amounts of pin real estate.

## Installation

### Warning: These instructions are outdated & are no longer relevant

These installation instructions will be updated as soon as the transition to PlatformIO has been completed.

### Prerequisites

You need these before you can use CRSFforArduino.

- [Adafruit's SAMD Board Support package](https://github.com/adafruit/ArduinoCore-samd)
- [Adafruit's Zero DMA driver](https://github.com/adafruit/Adafruit_ZeroDMA)
- [Arduino's SAMD Board Support package](https://github.com/arduino/ArduinoCore-samd)
- [Arduino IDE](https://www.arduino.cc/en/software) If you are using the VSCode plugin, use the Arduino IDE version 1.8.19. Otherwise, use the very latest version of the Arduino IDE.

### Download CRSFforArduino

1. Click the green code button & hit "Download ZIP".
2. Extract that to your libraries' directory. EG ```C:\Users\..\Documents\Arduino\libraries```
3. Start up the Arduino IDE (or VSCode, if you're using that instead).

## How to use CRSFforArduino

### The API

1. Add my library to your sketch with ```#include "CRSFforArduino.h"```
2. Underneath that, you need to declare ```CRSFforArduino crsf = CRSFforArduino(&Serial1)```
3. In your ```setup()```, do ```crsf.begin()``` to start communicating with your connected ExpressLRS receiver.
4. In your ```loop()```, you need to call ```crsf.update()```, as this polls your receiver for new RC channels data.
5. Do ```crsf.getChannel(n)``` to get the raw value from your desired RC channel. Here, ```n``` refers to your channel number from 1 to 16.

If you want to convert the raw channel value to microseconds, do ```crsf.rcToUs(n)```, where ```n``` is the raw RC value you want to convert. ```rcToUs()``` will return the converted value in microseconds.

The example below demonstrates what your code should look like, using the instructions above:

```c++
/* Arduino is included here for shits & giggles. */
#include "Arduino.h"

/* 1. Add Cassie Robinson's CRSFforArduino.h library. */
#include "CRSFforArduino.h"

/* 2. Declare a CRSFforArduino object.
You can call it literally anything you want, as long as you tell CRSFforArduino what serial port your receiver is connected to. */
CRSFforArduino crsf = CRSFforArduino(&Serial1)

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        ;
    }

    /* 3. Start communicating with a connected ELRS receiver. */
    crsf.begin();

    /* Pro tip: Always show a little message in the Serial Monitor to let you know that your sketch is initialized successfully. */
    Serial.println("Channels Example");
    delay(1000);
    Serial.println("Ready");
    delay(1000);
}

void loop()
{
    /* 4. Update the main loop with new RC data. */
    if (crsf.update())
    {
        /* Pro tip: Read back your RC channels data inside an if() statement.
        
        5. Here, your RC channel values are converted to microseconds, & are sent to the Serial Monitor. */
        Serial.print("RC Channels <A: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(1)));
        Serial.print(", E: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(2)));
        Serial.print(", T: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(3)));
        Serial.print(", R: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(4)));
        Serial.print(", Aux1: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(5)));
        Serial.print(", Aux2: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(6)));
        Serial.print(", Aux3: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(7)));
        Serial.print(", Aux4: ");
        Serial.print(crsf.rcToUs(crsf.getChannel(8)));
        Serial.println(">");
    }
}
```

### Example Sketches

In the ```examples``` folder, there is a sketch called ```channels.ino``` that I used to test this library.
It contains instructions on how to set your hardware up & how to connect your receiver to your development board.
It also details binding procedures (if needed), & the channel ranges & channel order.
The example sketch also demonstrates how to read RC channels data from your connected ExpressLRS receiver.

### Flashing

1. Verify your sketch.
2. Select your com port that your development board is connected to.
3. Upload your sketch to your development board.

### Viewing RC data

1. Open up the Serial Monitor.
2. Your RC channel values will be there, & they will change as you move the sticks on your RC handset.

## Compatible development boards

Here is a list of target development boards CRSFforArduino is compatible with:

- SAMD21 based boards:
  - Adafruit Crickit M0
  - Adafruit Feather M0 & variants
  - Adafruit Gemma M0
  - Adafruit ItsyBitsy M0 Express
  - Adafruit QtPy M0
  - Adafruit Trinket M0
  - Arduino MKR series
  - Arduino Zero
- SAMD51 based boards:
  - Adafruit Feather M4 Express
  - Adafruit Feather M4 CAN Express
  - Adafruit ItsyBitsy M4 Express
  - Adafruit Metro M4 Express
  - Adafruit Metro M4 Express AirLift Lite
- SAME51 based boards:
  - Adafruit Grand Central M4

Compatibility with other microcontroller boards may be added in the future, if there is demand for it. Keep in mind that this will be subject to hardware limitations of the host microcontroller itself.

Generally speaking, if the host microcontroller's UART peripheral supports 420k bauds (or higher), it is a likely candidate for this library to support it.
If the host microcontroller also has DMA, this is an added bonus. DMA is no longer required (but it is still the preferred method).

## AVR based microcontrollers are not compatible

Development boards such as the Arduino UNO, Arduino Micro, Arduino Nano, Arduino Mega 2560 & any other development board that was built around the ATmega microcontrollers of yesteryear are incompatible with my library.
Their processing capabilities simply are not there, & they are far too slow for the constraints required by the CRSF protocol.
The AVR archtecture itself is a legacy architecture & I simply will not support it.

## Compatible receivers

Generally speaking, if your transmitter & receiver combo supports ExpressLRS or TBS Crossfire, it's automatically compatible.
Keep in mind that CRSF for Arduino is tested almost exclusively on ExpressLRS hardware.

## Telemetry

Currently, there is no telemetry feedback from the host microcontroller's side... _yet!_
This is coming soon.

At first, I wanted to focus primarily on the important part first: Being able to read the RC channels data.
This was my benchmark. Now, I know that this is working, I am now focusing on getting telemetry feedback up & running.

There is now a [development branch](https://github.com/ZZ-Cat/CRSFforArduino/tree/Telemetry-Feedback) where telemetry is being worked on & tested. Once this is working the way it's supposed to, it will be merged into the Main-Trunk & I will update this section to reflect this.

## Software license

As always, I believe in freedom & I want to pass that freedom onto you.
Which is why I am proud to license CRSFforArduino to you under the GNU GPL v3.

## Attributions

I give credit where credit is due. Because CRSFforArduino isn't entirely my own idea, but built on the shoulders of giants. Here is a list of credits to those what helped to make this possible:

- Inspiration for this library
  - [ExpressLRS](https://github.com/ExpressLRS)
    - [Development Team](https://github.com/orgs/ExpressLRS/people)
    - [License](https://github.com/ExpressLRS/ExpressLRS/blob/master/LICENSE)
    - [Source Code](https://github.com/ExpressLRS/ExpressLRS)
    - [Website](https://www.expresslrs.org/3.0/)
- References for CRSF implementation
  - [BetaFlight](https://github.com/betaflight)
    - [Development Team](https://github.com/orgs/betaflight/people)
    - [License](https://github.com/betaflight/betaflight/blob/master/LICENSE)
    - [Source Code](https://github.com/betaflight/betaflight)
    - [Website](https://betaflight.com/)
  - [RotorFlight](https://github.com/rotorflight)
    - [Development Team](https://github.com/rotorflight#credits)
    - [License](https://github.com/rotorflight/rotorflight-firmware/blob/master/LICENSE)
    - [Source Code](https://github.com/rotorflight/rotorflight-firmware)
- Third Party libraries
  - [Adafruit Industries](https://github.com/adafruit)
    - [Adafruit_ZeroDMA](https://github.com/adafruit/Adafruit_ZeroDMA)
      - [Author](https://github.com/PaintYourDragon)
      - [License](https://github.com/adafruit/Adafruit_ZeroDMA/blob/master/LICENSE)
    - [Website](https://www.adafruit.com/)