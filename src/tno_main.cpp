
#include "tno_main.h"
#include "display_test.h"

#include "llc_arduino.h"
#ifdef LLC_ESP32
#   include <esp_wifi.h>
#endif
#include <Wire.h>
#include <SPI.h>

#ifdef LLC_ESP32
#   include <SPIFFS.h>
#else
#   include <LittleFS.h>
#endif //LLC_ESP32

using tno::WEMOS_PIN_MAP_DIGITAL;

//#define FEEDBACK_LED_IS_ACTIVE_LOW // The LED on my board (D4) is active LOW
//#define IR_RECEIVE_PIN          14 // D5
//#define IR_SEND_PIN             12 // D6 - D4/pin 2 is internal LED
//#define _IR_TIMING_TEST_PIN      2 // D4
//#define APPLICATION_PIN         13 // D7

//#define IR_RECEIVE_PIN          15  // D15
//#define IR_SEND_PIN              4  // D4
//#define TONE_PIN                30  // D27 25 & 26 are DAC0 and 1
//#define APPLICATION_PIN         16  // RX2 pin
//
//#include "TinyIRReceiver.hpp" // include the code


LLC_USING_TYPEINT();

#ifdef LLC_ESP32
SPIClass SPI2(HSPI);
//SPIClass SPI3(VSPI);
#endif // LLC_ESP32

#ifdef TNO_USE_ST77XX
//llc::err_t  initDisplayST7735(tno::STempApp & app) {
//    if_null_fe(app.ST7735.create(&SPI2, (s0_t)app.ST7735CS, (s0_t)app.ST7735DC, (s0_t)app.ST7735Reset));
//    app.ST7735->initR(INITR_MINI160x80); 
//    ::testDisplayST77XX(*app.ST7735);
//    //display.display();  // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
//    return 0;
//}
llc::err_t  initDisplayST7789(tno::STempApp & app) {
#ifdef LLC_ESP32
    if_null_fe(app.ST7789.create(&SPI2, (s0_t)app.ST77XXCS, (s0_t)app.ST77XXDC, (s0_t)app.ST77XXReset));
#endif // LLC_ESP32
    app.ST7789->init(135, 240);           // Init ST7789 240x135
    app.ST7789->setRotation(3);
    ::testDisplayST77XX(*app.ST7789);
      //display.display();  // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
    return 0;
}
#endif // TNO_USE_ST77XX

#ifdef TNO_USE_SSD1306
llc::err_t  initDisplaySSD1306(tno::STempApp & app) {
    Adafruit_SSD1306 & display = *app.SSD1306.create((u0_t)app.SSD1306Width, (u0_t)app.SSD1306Height, &Wire, (s0_t)-1);
    if_zero_fe(display.begin(SSD1306_SWITCHCAPVCC, app.SSD1306Address));
    display.display();  // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
    return 0;
}
#endif // TNO_USE_SSD1306

llc::err_t  initDisplay(tno::STempApp & app) {
#ifdef TNO_USE_ST77XX
    //if_fail_fe(initDisplayST7735(app));
    if_fail_fe(initDisplayST7789(app));
#endif // TNO_USE_ST77XX
#ifdef TNO_USE_SSD1306
    if_fail_fe(initDisplaySSD1306(app));
#endif // TNO_USE_SSD1306
    return 0;
}

llc::err_t  initDS18B20(tno::STempApp & app) {
    app.ApiDS18B20.create(app.ApiOneWire);
    DallasTemperature   & ds18b20   = *app.ApiDS18B20;
    ds18b20.begin();
    info_printf("Scanning for DS18B20 sensors...");
    uint8_t         deviceAddress[8]  = {};
    while (app.ApiOneWire->search(deviceAddress)) {
        if_fail_e(app.DS18B20Addresses.push_back(*(const u3_t*)deviceAddress));
        info_printf("Sensor %u address: 0x%X%X.", app.DS18B20Addresses.size(), *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]));
    }
    app.ApiOneWire->reset_search();
    info_printf("DS18B20 sensors connected: %u.", app.DS18B20Addresses.size());
    return 0;
}
llc::err_t  initIRReceiver(tno::STempApp & /*app*/, bool /*useFast*/) {
    //info_printf("Using TiniIR library version %s", VERSION_TINYIR);
    //if_zero_fef(initPCIInterruptForTinyReceiver(), "No interrupt available for pin %i.", IR_RECEIVE_PIN);    // Enables the interrupt generation on change of IR input signal
    //info_printf("Ready to receive %s IR signals at pin %i.", useFast ? "Fast" : "NEC", IR_RECEIVE_PIN);
    return 0;
}
llc::err_t  initSensors(tno::STempApp & app) {
    if_fail_fe(initDS18B20(app));
    if_fail_fe(initIRReceiver(app, 
#ifdef USE_FAST_PROTOCOL
        true
#else
        false
#endif
    ));
    return 0;
}

sttc    tno::STempApp g_App  = {};

void setup() {
    tno::STempApp & app = g_App;
	llc::evalResetCause(app, app.BootInfo.ResetCause, app.BootInfo.AwakeCause, app.BootInfo.WakeupPins);

    Wire.begin(app.I2CSDA, app.I2CSCL);
#ifdef LLC_ESP32
    SPI2.begin(app.HSPISCL, app.HSPIMISO, app.HSPIMOSI);
#endif // LLC_ESP32
#ifdef RADIO_REMOTE_CONTROL
    pinMode(app.A, INPUT);
    pinMode(app.B, INPUT);
    pinMode(app.C, INPUT);
    pinMode(app.D, INPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
#else
   //SPI3.begin(app.VSPISCL, app.VSPIMISO, app.VSPIMOSI); 
#endif
    app.ApiOneWire.create((uint8_t)15);
	//g_App.Servos.Board1.begin();
	//g_App.Servos.Board1.setPWMFreq(60);


	es_if_failed(llc::setupNetwork(app, app.Filenames.WiFi, app.Filenames.HTTP, app.Folders.Setup));
    if_fail_e(initDisplay(app));
    if_fail_e(initSensors(app));
    info_printf("setup() end.");
}

llc::err_t tickIRReceiver   () {
//    if (false == TinyReceiverDecode()) 
//        return 0;
//    info_printf("Flags:0x%x.", (u2_t)TinyIRReceiverData.Flags);
//#ifndef USE_FAST_PROTOCOL
//    info_printf("Address:0x%x.", (u2_t)TinyIRReceiverData.Address); // We have no address at FAST protocol
//#endif
//    info_printf("Command:0x%x.", (u2_t)TinyIRReceiverData.Command);
//    if_true_i(TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT);
//    if_true_fe(TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED); //  Parity failed. Try defining USE_EXTENDED_NEC_PROTOCOL or USE_ONKYO_PROTOCOL.
//    return TinyIRReceiverData.Address | (TinyIRReceiverData.Command << (sizeof(TinyIRReceiverData.Address)*8));
    return 0;
}

llc::error_t drawTemperatures(tno::STempApp & app) {
#ifndef TNO_HEADLESS
    using namespace tno;

    Adafruit_GFX & tft = 
#   ifdef TNO_USE_ST77XX
        *app.ST7789;
#   else // !TNO_USE_ST77XX
        *app.SSD1306;
#   endif // TNO_USE_ST77XX
    for(u2_t i=0; i < app.DS18B20Addresses.size(); ++i) {
        f2_c celsius = app.DS18B20Values[i];
        u3_c address = app.DS18B20Addresses[i];
        if(celsius > 15) 
            tft.setTextColor(U1_RED);
        else if(celsius > 10) 
            tft.setTextColor(U1_ORANGE);
        else if(celsius > 4) 
            tft.setTextColor(U1_YELLOW);
        else if(celsius > 0) 
            tft.setTextColor(U1_BLUE);
        else if(celsius > -4) 
            tft.setTextColor(U1_CYAN);
         else 
            tft.setTextColor(U1_WHITE);
        char sensorText[64] = {};
        llc::sprintf_s(sensorText, "%llu: %.2f C", address, celsius);
        tft.println(sensorText);
    }
#endif // TNO_HEADLESS
    return 0;
}

void loop() { 
    tno::STempApp       & app       = g_App;
    DallasTemperature   & ds18b20   = *app.ApiDS18B20;
    ds18b20.requestTemperatures();
    if_fail_re(app.DS18B20Values.resize(app.DS18B20Addresses.size(), 0.0f));
    for(u2_t i=0; i < app.DS18B20Addresses.size(); ++i) {
        u0_c * deviceAddress    = (u0_c*)&app.DS18B20Addresses[i];
        f2_c tempC              = app.DS18B20Values[i]  = ds18b20.getTempC(deviceAddress);  // 
        info_printf("DS18B20 with id 0x%X%X measured temperature: %f.", *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]), tempC);
    }
    Adafruit_GFX & tft = 
#   ifdef TNO_USE_ST77XX
        *app.ST7789;
#   else // !TNO_USE_ST77XX
        *app.SSD1306;
#   endif // TNO_USE_ST77XX
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextWrap(true);
    tft.fillScreen(0);
    drawTemperatures(app);
    tickIRReceiver();
#ifdef RADIO_REMOTE_CONTROL
    if(digitalRead(app.A)) { digitalWrite(16, !digitalRead(16)); info_printf("%u", digitalRead(16)); }
    if(digitalRead(app.B)) { digitalWrite(17, !digitalRead(17)); info_printf("%u", digitalRead(17)); }
    if(digitalRead(app.C)) { digitalWrite(16, 0); info_printf("%u", digitalRead(16)); }
    if(digitalRead(app.D)) { digitalWrite(17, 0); info_printf("%u", digitalRead(17)); }
#endif
}
