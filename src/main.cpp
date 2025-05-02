#include "llc_ptr_obj.h"
#include "llc_array_pod.h"
#include "llc_rxtx.h"
#include <DallasTemperature.h>
#include <LittleFS.h>

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
    s0_t                                PinDS18B20      = WEMOS_PIN_MAP_DIGITAL[2];      // Change to your chosen pin
    llc::pobj<OneWire          >        ApiOneWire;
    llc::pobj<DallasTemperature>        ApiDS18B20;
    llc::apod<u3_t>                     DS18B20Addresses;
};

sttc    STempApp g_App  = {};

void setup() {
    Serial.begin(115200);
    if_zero_e(LittleFS.begin());
    g_App.ApiOneWire.create((u0_t)g_App.PinDS18B20);
    g_App.ApiDS18B20.create(g_App.ApiOneWire);
    DallasTemperature   & ds18b20   = *g_App.ApiDS18B20;
    ds18b20.begin();

    info_printf("Scanning for DS18B20 sensors...");
    DeviceAddress   addr;
    while (g_App.ApiOneWire->search(addr)) {
        g_App.DS18B20Addresses.push_back(*(u3_t*)addr);
        info_printf("Sensor %u address: 0xull.", g_App.DS18B20Addresses.size(), g_App.DS18B20Addresses[g_App.DS18B20Addresses.size()-1]);
    }
    g_App.ApiOneWire->reset_search();
}

void loop() { 
}
