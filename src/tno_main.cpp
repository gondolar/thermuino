#include "tno_main.h"
#include "llc_arduino.h"

#include <Wire.h>

#include <LittleFS.h>


LLC_USING_TYPEINT();

sttc    tno::STempApp g_App  = {};

llc::err_t  initDisplay(tno::STempApp & app) {
    //Wire.begin(app.I2CSDA, app.I2CSCL);
    //Adafruit_SSD1306 & display = *app.I2CDisplay.create((u0_t)app.I2CDisplayWidth, (u0_t)app.I2CDisplayHeight, &Wire, (s0_t)-1);
    //if_zero_fe(display.begin(SSD1306_SWITCHCAPVCC, app.I2CAddressOLED));
    //display.display();  // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
    return 0;
}

llc::err_t  initSensors(tno::STempApp & app) {
    app.ApiOneWire.create((u0_t)app.PinDS18B20);
    app.ApiDS18B20.create(app.ApiOneWire);
    //llc::pobj<Adafruit_SSD1306>     ;
    DallasTemperature   & ds18b20   = *app.ApiDS18B20;
    ds18b20.begin();
    info_printf("Scanning for DS18B20 sensors...");
    uint8_t         deviceAddress[8]  = {};
    while (app.ApiOneWire->search(deviceAddress)) {
        if_fail_e(app.DS18B20Addresses.push_back(*(const u3_t*)deviceAddress));
        info_printf("Sensor %u address: 0x%X%X.", app.DS18B20Addresses.size(), *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]));
    }
    g_App.ApiOneWire->reset_search();
    info_printf("DS18B20 sensors connected: %u.", app.DS18B20Addresses.size());
    return 0;
}

void setup() {
    Serial.begin(115200);

    if_fail_e(initDisplay(g_App));
    if_fail_e(initSensors(g_App));
    if_zero_e(LittleFS.begin());
    info_printf("setup() end.");
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
