#include "llc_rxtx.h"
#include "llc_event.h"

#include <Adafruit_SSD1306.h>
#include <DallasTemperature.h>

namespace tno
{
    LLC_USING_TYPEINT();

    stxp    u0_c        WEMOS_PIN_LED_BUILTIN   = 2;
    stxp    llc::SRXTX  WEMOS_PIN_MAP_RXTX      = {3, 1};
    stxp    u0_c        WEMOS_PIN_MAP_DIGITAL[] = 
        { 16
        , 5
        , 4
        , 0
        , 2
        , 14
        , 12
        , 13
        , 15
        };

    uint32_t    UTC_TIME_OFFSET = 1746535244;

    struct SScheduledEvent {
        u2_t    Time        = {};
        u2_t    RetryCount  = {};
        u2_t    RetryWait   = {}; // in seconds?
    };

    struct SScheduledTask {
        u3_t    TimeStart   = {};
        u3_t    TimeStop    = {};
        u2_t    RetryCount  = {};
        u2_t    RetryWait   = {}; // in seconds?
    };

    struct SSensorEntry {
        u3_t    Sensor      = {};
        u2_t    Time        = {};
        u2_t    Value       = {};
    };

    struct STempApp {
#ifdef LLC_ESP8266
        u0_t                            I2CSCL              = WEMOS_PIN_MAP_DIGITAL[5];
        u0_t                            I2CSDA              = WEMOS_PIN_MAP_DIGITAL[4]; 
#else // !LLC_ESP8266
        u0_t                            I2CSCL              = 22;
        u0_t                            I2CSDA              = 21; 
#endif // LLC_ESP8266
        s0_t                            I2CAddressOLED      = 0x3C;     // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

        u1_t                            I2CDisplayWidth     = 128;      // OLED display width, in pixels
        u1_t                            I2CDisplayHeight    = 64 ;      // OLED display height, in pixels

        llc::pobj<Adafruit_SSD1306>     I2CDisplay          = {};

        s0_t                            PinDS18B20          = WEMOS_PIN_MAP_DIGITAL[1];      // Change to your chosen pin
        llc::pobj<OneWire          >    ApiOneWire          = {}; 
        llc::pobj<DallasTemperature>    ApiDS18B20          = {};
        llc::apod<u3_t>                 DS18B20Addresses    = {};

        llc::apod<SScheduledEvent>      EventSchedule       = {};
        llc::apod<SSensorEntry>         SensorLog           = {};
    };
} // namespace