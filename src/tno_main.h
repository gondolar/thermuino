
#include "nlc_app.h"

#include "llc_rxtx.h"
#include "llc_event.h"
#ifndef TNO_HEADLESS
#   ifdef TNO_USE_SSD1306
#   include <Adafruit_SSD1306.h>
#   endif // TNO_USE_SSD1306
#   ifdef TNO_USE_SH110X
#     include <Adafruit_SH110X.h>
#   endif // TNO_USE_SH110X
#   ifdef TNO_USE_ST77XX
#   include <Adafruit_ST77xx.h>
#   endif // TNO_USE_ST77XX
#endif // TNO_HEADLESS
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

    stxp    u2_c        UTC_TIME_OFFSET         = 1746535244;

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
        u2_t    Time        = {};
        u3_t    Event       = {};
        u3_t    Sensor      = {};
        u2_t    Value       = {};
    };
//#define RADIO_REMOTE_CONTROL
    struct STempApp : ::llc::SNLCApp {
#ifdef LLC_ESP8266
        u0_t                            I2CSCL              = WEMOS_PIN_MAP_DIGITAL[1];
        u0_t                            I2CSDA              = WEMOS_PIN_MAP_DIGITAL[2]; 

        u0_t                            HSPISCL              = WEMOS_PIN_MAP_DIGITAL[5];
        u0_t                            HSPIMOSI             = WEMOS_PIN_MAP_DIGITAL[7]; 
        u0_t                            HSPIMISO             = WEMOS_PIN_MAP_DIGITAL[6]; 
#else // !LLC_ESP8266
        u0_t                            I2CSCL              = 22;
        u0_t                            I2CSDA              = 21; 

        u0_t                            HSPISCL              = 13;
        u0_t                            HSPIMOSI             = 14; 
        u0_t                            HSPIMISO             = 12; 
#   ifdef RADIO_REMOTE_CONTROL
        u0_t                            A                   = 18;
        u0_t                            B                   = 19; 
        u0_t                            C                   = 22; 
        u0_t                            D                   = 23; 
        u0_t                            T                   = 12; 
#   else
        u0_t                            VSPISCL              = 23;
        u0_t                            VSPIMOSI             = 18; 
        u0_t                            VSPIMISO             = 19; 
#   endif // RADIO_REMOTE_CONTROL
#endif // LLC_ESP8266

#ifndef TNO_HEADLESS
#   ifdef TNO_USE_SSD1306
        s0_t                            SSD1306Address      = 0x3C; // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
        u1_t                            SSD1306Width        = 128;      // OLED display width, in pixels
        u1_t                            SSD1306Height       = 64 ;      // OLED display height, in pixels
        llc::pobj<Adafruit_SSD1306>     SSD1306             = {};
#   endif // TNO_USE_SSD1306

#   ifdef TNO_USE_SH110X
        u0_c                            SH1106Address       = 0x3D; 
        u1_t                            SH1106Width         = 128; // OLED display width, in pixels
        u1_t                            SH1106Height        = 64 ; // OLED display height, in pixels
        llc::pobj<Adafruit_SH1106G>     SH1106              = {};
#   endif // TNO_USE_SH110X

#   ifdef TNO_USE_ST77XX
        u0_t                            ST77XXCS            = 5;
        s0_t                            ST77XXReset         = 27;
        s0_t                            ST77XXDC            = 26;
        s0_t                            ST77XXBacklight     = 25;
        u1_t                            ST77XXWidth         = 240; // 160;
        u1_t                            ST77XXHeight        = 135; // 80;
        llc::pobj<Adafruit_ST7789>      ST7789              = {};
        //llc::pobj<Adafruit_ST7735>        ST7735              = {};
#   endif // TNO_USE_ST77XX
#endif // TNO_HEADLESS

#ifdef LLC_ESP8266
        s0_t                            PinDS18B20          = WEMOS_PIN_MAP_DIGITAL[1];      // Change to your chosen pin
#else
        s0_t                            PinDS18B20          = 15;      // Change to your chosen pin
#endif
    

        llc::pobj<OneWire          >    ApiOneWire          = {}; 
        llc::pobj<DallasTemperature>    ApiDS18B20          = {};
        llc::apod<u3_t>                 DS18B20Addresses    = {};
        llc::apod<f2_t>                 DS18B20Values       = {};
        llc::apod<SScheduledEvent>      ScheduledEvents     = {};
        llc::apod<SScheduledTask>       ScheduledTasks      = {};
        llc::apod<SSensorEntry>         SensorsLog          = {};
    };
    // Some ready-made 16-bit ('565') color settings:0
    static constexpr const uint16_t U1_BLACK   = 0x0000U;
    static constexpr const uint16_t U1_WHITE   = 0xFFFFU;
    static constexpr const uint16_t U1_RED     = 0xF800U;
    static constexpr const uint16_t U1_GREEN   = 0x07E0U;
    static constexpr const uint16_t U1_BLUE    = 0x001FU;
    static constexpr const uint16_t U1_CYAN    = 0x07FFU;
    static constexpr const uint16_t U1_MAGENTA = 0xF81FU;
    static constexpr const uint16_t U1_YELLOW  = 0xFFE0U;
    static constexpr const uint16_t U1_ORANGE  = 0xFC00U;

} // namespace