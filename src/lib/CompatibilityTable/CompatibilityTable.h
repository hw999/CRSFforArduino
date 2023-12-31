/**
 * @file CompatibilityTable.h
 * @author Cassandra "ZZ Cat" Robinson (nicad.heli.flier@gmail.com)
 * @brief This compatibility table is used to determine if the target development boat is compatible with CRSF for Arduino.
 * @version 0.4.0
 * @date 2023-07-27
 *
 * @copyright Copyright (c) 2023, Cassandra "ZZ Cat" Robinson. All rights reserved.
 *
 * @section License GNU General Public License v3.0
 * This header file is a part of the CRSF for Arduino library.
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

#pragma once

#include "Arduino.h"

class CompatibilityTable
{
  public:
    CompatibilityTable();

    bool isDevboardCompatible(const char *name);
    const char *getDevboardName();

  protected:
    typedef enum __ct_devboards_e
    {
        // Unknown device.
        DEVBOARD_IS_INCOMPATIBLE = 0,

        // Adafruit SAMD21 boards.
        DEVBOARD_ADAFRUIT_FEATHER_M0,
        DEVBOARD_ADAFRUIT_FEATHER_M0_EXPRESS,
        DEVBOARD_ADAFRUIT_ITSYBITSY_M0_EXPRESS,
        DEVBOARD_ADAFRUIT_METRO_M0_EXPRESS,
        DEVBOARD_ADAFRUIT_QTPY_M0,
        DEVBOARD_ADAFRUIT_TRINKET_M0,

        // Adafruit SAMD51 boards.
        DEVBOARD_ADAFRUIT_FEATHER_M4_EXPRESS,
        DEVBOARD_ADAFRUIT_GRAND_CENTRAL_M4,
        DEVBOARD_ADAFRUIT_ITSYBITSY_M4_EXPRESS,
        DEVBOARD_ADAFRUIT_METRO_M4_AIRLIFT_LITE,
        DEVBOARD_ADAFRUIT_METRO_M4_EXPRESS,

        // Adafruit SAME51 boards.
        DEVBOARD_ADAFRUIT_FEATHER_M4_CAN,

        // Arduino AVR boards.
        DEVBOARD_ARDUINO_MEGA2560,
        DEVBOARD_ARDUINO_MICRO,
        DEVBOARD_ARDUINO_UNO,

        // Arduino SAMD21 boards.
        DEVBOARD_ARDUINO_MKR1000,
        DEVBOARD_ARDUINO_MKRFOX1200,
        DEVBOARD_ARDUINO_MKRGSM1400,
        DEVBOARD_ARDUINO_MKRNB1500,
        DEVBOARD_ARDUINO_MKRVIDOR4000,
        DEVBOARD_ARDUINO_MKRWAN1300,
        DEVBOARD_ARDUINO_MKRWAN1310,
        DEVBOARD_ARDUINO_MKRWIFI1010,
        DEVBOARD_ARDUINO_MKRZERO,
        DEVBOARD_ARDUINO_NANO_33_IOT,
        DEVBOARD_ARDUINO_ZERO,

        // Seeed Studio boards.
        DEVBOARD_SEEEDSTUDIO_XIAO_M0,

        DEVBOARD_COUNT
    } __ct_devboards_t;

    typedef struct __ct_devicetypes_s
    {
        __ct_devboards_t devboard;
    } __ct_devicetypes_t;

    typedef struct __ct_devices_s
    {
        __ct_devicetypes_t type;
    } __ct_devices_t;

    __ct_devices_t device;

    const char *deviceNames[DEVBOARD_COUNT] = {
        "Incompatible device",
        "Adafruit Feather M0",
        "Adafruit Feather M0 Express",
        "Adafruit ItsyBitsy M0 Express",
        "Adafruit Metro M0 Express",
        "Adafruit QT Py M0",
        "Adafruit Trinket M0",
        "Adafruit Feather M4 Express",
        "Adafruit Grand Central M4",
        "Adafruit ItsyBitsy M4 Express",
        "Adafruit Metro M4 AirLift Lite",
        "Adafruit Metro M4 Express",
        "Adafruit Feather M4 CAN",
        "Arduino Mega 2560",
        "Arduino Micro",
        "Arduino Uno",
        "Arduino MKR1000",
        "Arduino MKRFOX1200",
        "Arduino MKRGSM1400",
        "Arduino MKRNB1500",
        "Arduino MKRVIDOR4000",
        "Arduino MKRWAN1300",
        "Arduino MKRWAN1310",
        "Arduino MKRWIFI1010",
        "Arduino MKRZERO",
        "Arduino Nano 33 IoT",
        "Arduino Zero",
        "Seeed Studio Xiao SAMD21"};
};

// CompatibilityTable CT = CompatibilityTable();
