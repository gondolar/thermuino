#include "tno_main.h"
#include "Adafruit_GFX.h"

void testlines(Adafruit_GFX & tft, uint16_t color) {
  tft.fillScreen(0);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(0);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(0);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(0);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

static void testdrawtext(Adafruit_GFX & tft, char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

static void testfastlines(Adafruit_GFX & tft, uint16_t color1, uint16_t color2) {
  tft.fillScreen(0);
  for (int16_t y=0; y < tft.height(); y+=5) tft.drawFastHLine(0, y, tft.width(), color1);
  for (int16_t x=0; x < tft.width(); x+=5)  tft.drawFastVLine(x, 0, tft.height(), color2);
}

static void testdrawrects(Adafruit_GFX & tft, uint16_t color) {
  tft.fillScreen(0);
  for (int16_t x=0; x < tft.width(); x+=6) 
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
}

static void testfillrects(Adafruit_GFX & tft, uint16_t color1, uint16_t color2) {
  tft.fillScreen(0);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

static void testfillcircles(Adafruit_GFX & tft, uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) 
      tft.fillCircle(x, y, radius, color);    
  }
}

static void testdrawcircles(Adafruit_GFX & tft, uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2)
      tft.drawCircle(x, y, radius, color);
  }
}

static void testtriangles(Adafruit_GFX & tft) {
  tft.fillScreen(0);
  uint16_t color = 0xF800;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(int t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

static void testroundrects(Adafruit_GFX & tft) {
  tft.fillScreen(0);
  uint16_t color = 100;
  for(int t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(int i = 0 ; i <= 16; i+=1) {
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

using namespace tno;

static void tftPrintTest(Adafruit_GFX & tft) {
    tft.setTextWrap(false);
    tft.fillScreen(0);
    tft.setCursor(0, 30);
    tft.setTextColor(U1_RED);
    tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(U1_YELLOW);
    tft.setTextSize(2);
    tft.println("Hello World!");
    tft.setTextColor(U1_GREEN);
    tft.setTextSize(3);
    tft.println("Hello World!");
    tft.setTextColor(U1_BLUE);
    tft.setTextSize(4);
    tft.print(1234.567);
    delay(0);
    tft.setCursor(0, 0);
    tft.fillScreen(0);
    tft.setTextColor(U1_WHITE);
    tft.setTextSize(0);
    tft.println("Hello World!");
    tft.setTextSize(1);
    tft.setTextColor(U1_GREEN);
    tft.print(3.14159, 6);
    tft.println(" Want pi?");
    tft.println(" ");
    tft.print(8675309, HEX); // print 8,675,309 out in HEX!
    tft.println(" Print HEX!");
    tft.println(" ");
    tft.setTextColor(U1_WHITE);
    tft.println("Sketch has been");
    tft.println("running for: ");
    tft.setTextColor(U1_MAGENTA);
    tft.print(millis() / 1000);
    tft.setTextColor(U1_WHITE);
    tft.print(" seconds.");
}

static void mediabuttons(Adafruit_GFX & tft) {
    // play
    tft.fillScreen(0);
    tft.fillRoundRect(10, 10, 78, 60, 8, U1_WHITE);
    tft.fillTriangle(22, 20, 42, 60, 90, 40, U1_RED);
    delay(0);
    // pause
    tft.fillRoundRect(10, 90, 78, 60, 8, U1_WHITE);
    tft.fillRoundRect(19, 98, 20, 45, 5, U1_GREEN);
    tft.fillRoundRect(49, 98, 20, 45, 5, U1_GREEN);
    delay(0);
    // play color
    tft.fillTriangle(22, 20, 42, 60, 90, 40, U1_BLUE);
    delay(0);
    // pause color
    tft.fillRoundRect(19, 98, 20, 45, 5, U1_RED);
    tft.fillRoundRect(49, 98, 20, 45, 5, U1_RED);
    // play color
    tft.fillTriangle(22, 20, 42, 60, 90, 40, U1_GREEN);
}

llc::err_t  testDisplayST77XX(Adafruit_GFX & tft) {
    uint16_t time = millis();
    tft.fillScreen(0);
    time = millis() - time;

    info_printf("time:%u", time);
    delay(0);

    // large block of text
    tft.fillScreen(0);
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ";
    testdrawtext(tft, text, U1_WHITE);
    delay(0);

    // tft print function!
    tftPrintTest(tft);
    delay(0);

    // a single pixel
    tft.drawPixel(tft.width()/2, tft.height()/2, U1_GREEN);
    delay(0);

    // line draw test
    testlines(tft, U1_YELLOW);
    delay(0);

    // optimized lines
    testfastlines(tft, U1_RED, U1_BLUE);
    delay(0);

    testdrawrects(tft, U1_GREEN);
    delay(0);

    testfillrects(tft, U1_YELLOW, U1_MAGENTA);
    delay(0);

    tft.fillScreen(0);
    testfillcircles(tft, 10, U1_BLUE);
    testdrawcircles(tft, 10, U1_WHITE);
    delay(0);

    testroundrects(tft);
    delay(0);

    testtriangles(tft);
    delay(0);

    //mediabuttons(tft);
    //delay(0);
    return 0;
}