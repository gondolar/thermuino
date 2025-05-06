#include "tno_main.h"
#include "llc_arduino.h"

#include <LittleFS.h>

#include <user_interface.h>

LLC_USING_TYPEINT();

sttc    tno::STempApp g_App  = {};

void setup() {
    Serial.begin(115200);
    g_App.ApiOneWire.create((u0_t)g_App.PinDS18B20);
    g_App.ApiDS18B20.create(g_App.ApiOneWire);
    DallasTemperature   & ds18b20   = *g_App.ApiDS18B20;
    ds18b20.begin();
    if_zero_e(LittleFS.begin());
    uint8 currentFrequency = system_get_cpu_freq();  // returns 80 or 160
    info_printf("System frequency: %u MHz.", currentFrequency);

    info_printf("Scanning for DS18B20 sensors...");
    uint8_t         deviceAddress[8]  = {};
    while (g_App.ApiOneWire->search(deviceAddress)) {
        if_fail_e(g_App.DS18B20Addresses.push_back(*(const u3_t*)deviceAddress));
        info_printf("Sensor %u address: 0x%X%X.", g_App.DS18B20Addresses.size(), *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]));
    }
    g_App.ApiOneWire->reset_search();
    info_printf("DS18B20 sensors connected: %u.", g_App.DS18B20Addresses.size());
}

void loop() { 
    DallasTemperature   & ds18b20   = *g_App.ApiDS18B20;
    ds18b20.requestTemperatures();
    for(u2_t i=0; i < g_App.DS18B20Addresses.size(); ++i) {
        u0_c                * deviceAddress         = (u0_c*)&g_App.DS18B20Addresses[i];
        f2_c tempC          = ds18b20.getTempC(deviceAddress);  // 
        info_printf("DS18B20 with id 0x%X%X measured temperature: %f.", *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]), tempC);
    }
}
