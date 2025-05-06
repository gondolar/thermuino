#include "tno_main.h"

#include <LittleFS.h>

LLC_USING_TYPEINT();

sttc    tno::STempApp g_App  = {};

void setup() {
    Serial.begin(115200);
    g_App.ApiOneWire.create((u0_t)g_App.PinDS18B20);
    g_App.ApiDS18B20.create(g_App.ApiOneWire);
    DallasTemperature   & ds18b20   = *g_App.ApiDS18B20;
    ds18b20.begin();
    if_zero_e(LittleFS.begin());

    info_printf("Scanning for DS18B20 sensors...");
    //DeviceAddress     deviceAddress     = {};
    uint8_t         deviceAddress[8]  = {};
    while (g_App.ApiOneWire->search(deviceAddress)) {
        if_fail_e(g_App.DS18B20Addresses.push_back(*(u3_t*)deviceAddress));
        info_printf("Sensor %u address: 0x%Xll.", g_App.DS18B20Addresses.size(), g_App.DS18B20Addresses[g_App.DS18B20Addresses.size()-1]);
    }
    g_App.ApiOneWire->reset_search();
    info_printf("DS18B20 sensors connected: %u.", g_App.DS18B20Addresses.size());
}

void loop() { 
    DallasTemperature   & ds18b20   = *g_App.ApiDS18B20;
    ds18b20.requestTemperatures();
    for(u2_t i=0; i < g_App.DS18B20Addresses.size(); ++i) {
        cnst    float   tempC   = ds18b20.getTempCByIndex(i);  // 
        info_printf("DS18B20 measured temperatura: %f.", tempC);
    }
}
