/**
 * @file main_rc.cpp
 * @author Cassandra "ZZ Cat" Robinson (nicad.heli.flier@gmail.com)
 * @brief This file demonstrates the full capabilities of CRSF for Arduino.
 * @version 0.4.0
 * @date 2023-07-27
 *
 * @copyright Copyright (c) 2023, Cassandra "ZZ Cat" Robinson. All rights reserved.
 *
 * @section License GNU General Public License v3.0
 * This main file is a part of the CRSF for Arduino library.
 * CRSF for Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CRSF for Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CRSF for Arduino.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */

/* For some reason, main_rc.cpp is included in the Arduino IDE build as well as the PlatformIO build.
 * This causes the Arduino IDE to complain about setup() and loop() being defined in multiple files.
 * The following #if defined() block is used to prevent the Arduino IDE from complaining about setup() and loop()
 * being defined in multiple files.
 */
#if defined(ARDUINO) && !defined(PLATFORMIO)
#warning "This example sketch is not compatible with the Arduino IDE. Please use the rc_channels.ino example instead."
#elif defined(ARDUINO) && defined(PLATFORMIO)
#include "Arduino.h"

#include "CRSFforArduino.h"

/* Configuration Options. */
#define VIEW_RC_CHANNELS 1 // Set VIEW_RC_CHANNELS to 1 to view the RC channel data in the serial monitor.

void setup()
{
#if VIEW_RC_CHANNELS > 0 || defined(CRSF_DEBUG)
    // Initialize the serial port & wait for the port to open.
    Serial.begin(115200);
    while (!Serial)
    {
        ;
    }

    Serial.println("RC Channels Example");
#endif

    // Initialize the CRSFforArduino library.
    if (!crsf.begin())
    {
#if VIEW_RC_CHANNELS > 0 || defined(CRSF_DEBUG)
        Serial.println("CRSF for Arduino initialization failed!");
#endif
        while (1)
        {
            ;
        }
    }

#if VIEW_RC_CHANNELS > 0 || defined(CRSF_DEBUG)
    // Show the user that the sketch is ready.
    Serial.println("Ready");
    delay(3000);
#endif
}

void loop()
{
    crsf.update();

#if VIEW_RC_CHANNELS > 0 && !defined(CRSF_DEBUG)
    /* Print RC channels every 100 ms. Do this using the millis() function to avoid blocking the main loop. */
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint >= 100)
    {
        lastPrint = millis();
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
#endif
}
#endif // defined(ARDUINO) && defined(PLATFORMIO)
