#include "Adafruit_ST77xx.h"
#include "llc_string.h"

void testlines(Adafruit_ST77xx & tft, uint16_t color);
void testdrawtext(Adafruit_ST77xx & tft, char *text, uint16_t color);
void testfastlines(Adafruit_ST77xx & tft, uint16_t color1, uint16_t color2);
void testdrawrects(Adafruit_ST77xx & tft, uint16_t color);
void testfillrects(Adafruit_ST77xx & tft, uint16_t color1, uint16_t color2);
void testfillrects(Adafruit_ST77xx & tft, uint16_t color1, uint16_t color2);
void testfillcircles(Adafruit_ST77xx & tft, uint8_t radius, uint16_t color);
void testdrawcircles(Adafruit_ST77xx & tft, uint8_t radius, uint16_t color);
void testtriangles(Adafruit_ST77xx & tft);
void testroundrects(Adafruit_ST77xx & tft);
void tftPrintTest(Adafruit_ST77xx & tft);
void mediabuttons(Adafruit_ST77xx & tft);
llc::err_t  testDisplayST77XX(Adafruit_ST77xx & tft);
