#include "tno_main.h"
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

#define IR_RECEIVE_PIN          15  // D15
#define IR_SEND_PIN              4  // D4
#define TONE_PIN                27  // D27 25 & 26 are DAC0 and 1
#define APPLICATION_PIN         16  // RX2 pin

#include "TinyIRReceiver.hpp" // include the code


LLC_USING_TYPEINT();

SPIClass SPI2(HSPI);
SPIClass SPI3(VSPI);

void testlines(Adafruit_ST7735 & tft, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(Adafruit_ST7735 & tft, char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(Adafruit_ST7735 & tft, uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(Adafruit_ST7735 & tft, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(Adafruit_ST7735 & tft, uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(Adafruit_ST7735 & tft, uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(Adafruit_ST7735 & tft, uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles(Adafruit_ST7735 & tft) {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects(Adafruit_ST7735 & tft) {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void tftPrintTest(Adafruit_ST7735 & tft) {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(3.14159, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons(Adafruit_ST7735 & tft) {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

llc::err_t  testDisplayST7735(Adafruit_ST7735 & tft) {
    uint16_t time = millis();
    tft.fillScreen(ST77XX_BLACK);
    time = millis() - time;

    Serial.println(time, DEC);
    delay(500);

    // large block of text
    tft.fillScreen(ST77XX_BLACK);
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ";
    testdrawtext(tft, text, ST77XX_WHITE);
    delay(1000);

    // tft print function!
    tftPrintTest(tft);
    delay(4000);

    // a single pixel
    tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
    delay(500);

    // line draw test
    testlines(tft, ST77XX_YELLOW);
    delay(500);

    // optimized lines
    testfastlines(tft, ST77XX_RED, ST77XX_BLUE);
    delay(500);

    testdrawrects(tft, ST77XX_GREEN);
    delay(500);

    testfillrects(tft, ST77XX_YELLOW, ST77XX_MAGENTA);
    delay(500);

    tft.fillScreen(ST77XX_BLACK);
    testfillcircles(tft, 10, ST77XX_BLUE);
    testdrawcircles(tft, 10, ST77XX_WHITE);
    delay(500);

    testroundrects(tft);
    delay(500);

    testtriangles(tft);
    delay(500);

    mediabuttons(tft);
    delay(500);
    return 0;
}
llc::err_t  initDisplayST7735(tno::STempApp & app) {
    if_null_fe(app.ST7735.create(&SPI2, (s0_t)app.ST7735CS, (s0_t)app.ST7735DC, (s0_t)app.ST7735Reset));
    app.ST7735->initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
    ::testDisplayST7735(*app.ST7735);
    //display.display();  // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
    return 0;
}

//llc::err_t  initDisplaySSD1306(tno::STempApp & app) {
//    Adafruit_SSD1306 & display = *app.SSD1306.create((u0_t)app.SSD1306Width, (u0_t)app.SSD1306Height, &Wire, (s0_t)-1);
//    if_zero_fe(display.begin(SSD1306_SWITCHCAPVCC, app.SSD1306Address));
//    display.display();  // Show initial display buffer contents on the screen -- the library initializes this with an Adafruit splash screen.
//    return 0;
//}

llc::err_t  initDisplay(tno::STempApp & app) {
    if_fail_fe(initDisplayST7735(app));
    return 0;
}

//llc::err_t  initDS18B20(tno::STempApp & app) {
//    app.ApiDS18B20.create(app.ApiOneWire);
//    //llc::pobj<Adafruit_SSD1306>     ;
//    DallasTemperature   & ds18b20   = *app.ApiDS18B20;
//    ds18b20.begin();
//    info_printf("Scanning for DS18B20 sensors...");
//    uint8_t         deviceAddress[8]  = {};
//    while (app.ApiOneWire->search(deviceAddress)) {
//        if_fail_e(app.DS18B20Addresses.push_back(*(const u3_t*)deviceAddress));
//        info_printf("Sensor %u address: 0x%X%X.", app.DS18B20Addresses.size(), *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]));
//    }
//    app.ApiOneWire->reset_search();
//    info_printf("DS18B20 sensors connected: %u.", app.DS18B20Addresses.size());
//    return 0;
//}
llc::err_t  initIRReceiver(tno::STempApp & app, bool useFast) {
    info_printf("Using TiniIR library version %s", VERSION_TINYIR);
    if_zero_fef(initPCIInterruptForTinyReceiver(), "No interrupt available for pin %i.", IR_RECEIVE_PIN);    // Enables the interrupt generation on change of IR input signal
    info_printf("Ready to receive %s IR signals at pin %i.", useFast ? "Fast" : "NEC", IR_RECEIVE_PIN);
    return 0;
}
llc::err_t  initSensors(tno::STempApp & app) {
    //if_fail_fe(initDS18B20(tno::STempApp & app));
    if_fail_fe(initIRReceiver(app, 
#if defined(USE_FAST_PROTOCOL)
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
    SPI2.begin(app.HSPISCL, app.HSPIMISO, app.HSPIMOSI);
    SPI3.begin(app.VSPISCL, app.VSPIMISO, app.VSPIMOSI); 

	//g_App.Servos.Board1.begin();
	//g_App.Servos.Board1.setPWMFreq(60);


		es_if_failed(llc::setupNetwork(app, app.Filenames.WiFi, app.Filenames.HTTP, app.Folders.Setup));
    if_fail_e(initDisplay(app));
    if_fail_e(initSensors(app));
    info_printf("setup() end.");
}

llc::err_t tickIRReceiver   () {
    if (false == TinyReceiverDecode()) 
        return 0;
    info_printf("Flags:0x%x.", (u2_t)TinyIRReceiverData.Flags);
#ifndef USE_FAST_PROTOCOL
    info_printf("Address:0x%x.", (u2_t)TinyIRReceiverData.Address); // We have no address at FAST protocol
#endif
    info_printf("Command:0x%x.", (u2_t)TinyIRReceiverData.Command);
    if_true_i(TinyIRReceiverData.Flags == IRDATA_FLAGS_IS_REPEAT);
    if_true_fe(TinyIRReceiverData.Flags == IRDATA_FLAGS_PARITY_FAILED); //  Parity failed. Try defining USE_EXTENDED_NEC_PROTOCOL or USE_ONKYO_PROTOCOL.
    return TinyIRReceiverData.Address | (TinyIRReceiverData.Command << (sizeof(TinyIRReceiverData.Address)*8));
}

void loop() { 
    //DallasTemperature   & ds18b20   = *g_App.ApiDS18B20;
    //ds18b20.requestTemperatures();
    //for(u2_t i=0; i < g_App.DS18B20Addresses.size(); ++i) {
    //    u0_c                * deviceAddress         = (u0_c*)&g_App.DS18B20Addresses[i];
    //    f2_c tempC          = ds18b20.getTempC(deviceAddress);  // 
    //    info_printf("DS18B20 with id 0x%X%X measured temperature: %f.", *(const uint32_t*)(&deviceAddress[4]), *(const uint32_t*)(&deviceAddress[0]), tempC);
    //}
    tickIRReceiver();
}
