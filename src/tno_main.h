#include "llc_ptr_obj.h"
#include "llc_array_pod.h"
//#include "llc_event.h"
#include "llc_rxtx.h"

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

    struct STempApp {
        s0_t                                PinDS18B20      = WEMOS_PIN_MAP_DIGITAL[4];      // Change to your chosen pin
        llc::pobj<OneWire          >        ApiOneWire;
        llc::pobj<DallasTemperature>        ApiDS18B20;
        llc::apod<u3_t>                     DS18B20Addresses;
    };
} // namespace