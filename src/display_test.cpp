#include "tno_main.h"

void testlines(Adafruit_ST77xx & tft, uint16_t color) {
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

void testdrawtext(Adafruit_ST77xx & tft, char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(Adafruit_ST77xx & tft, uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) tft.drawFastHLine(0, y, tft.width(), color1);
  for (int16_t x=0; x < tft.width(); x+=5)  tft.drawFastVLine(x, 0, tft.height(), color2);
}

void testdrawrects(Adafruit_ST77xx & tft, uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) 
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
}

void testfillrects(Adafruit_ST77xx & tft, uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(Adafruit_ST77xx & tft, uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) 
      tft.fillCircle(x, y, radius, color);    
  }
}

void testdrawcircles(Adafruit_ST77xx & tft, uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2)
      tft.drawCircle(x, y, radius, color);
  }
}

void testtriangles(Adafruit_ST77xx & tft) {
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

void testroundrects(Adafruit_ST77xx & tft) {
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

void tftPrintTest(Adafruit_ST77xx & tft) {
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
  delay(0);
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

void mediabuttons(Adafruit_ST77xx & tft) {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(10, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(22, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(0);
  // pause
  tft.fillRoundRect(10, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(19, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(49, 98, 20, 45, 5, ST77XX_GREEN);
  delay(0);
  // play color
  tft.fillTriangle(22, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(0);
  // pause color
  tft.fillRoundRect(19, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(49, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(22, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

llc::err_t  testDisplayST77XX(Adafruit_ST77xx & tft) {
    uint16_t time = millis();
    tft.fillScreen(ST77XX_BLACK);
    time = millis() - time;

    info_printf("time:%u", time);
    delay(0);

    // large block of text
    tft.fillScreen(ST77XX_BLACK);
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ";
    testdrawtext(tft, text, ST77XX_WHITE);
    delay(0);

    // tft print function!
    tftPrintTest(tft);
    delay(0);

    // a single pixel
    tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
    delay(0);

    // line draw test
    testlines(tft, ST77XX_YELLOW);
    delay(0);

    // optimized lines
    testfastlines(tft, ST77XX_RED, ST77XX_BLUE);
    delay(0);

    testdrawrects(tft, ST77XX_GREEN);
    delay(0);

    testfillrects(tft, ST77XX_YELLOW, ST77XX_MAGENTA);
    delay(0);

    tft.fillScreen(ST77XX_BLACK);
    testfillcircles(tft, 10, ST77XX_BLUE);
    testdrawcircles(tft, 10, ST77XX_WHITE);
    delay(0);

    testroundrects(tft);
    delay(0);

    testtriangles(tft);
    delay(0);

    //mediabuttons(tft);
    //delay(0);
    return 0;
}