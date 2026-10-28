#ifndef DISPLAYY_H
#define DISPLAYY_H

#include "pins.h"
#include <SPI.h>
#include "ILI9341_t3.h"

// MISO not used, D_OUT not present on display module
ILI9341_t3 tft = ILI9341_t3(PIN_LCD_CS, PIN_LCD_DC, PIN_LCD_RST, PIN_LCD_MOSI, PIN_LCD_SCK, 255);

void display_init() {
  analogWriteResolution(10);
  pinMode(PIN_LCD_BL, OUTPUT);
  analogWrite(PIN_LCD_BL, 256); // 1/4 brightness
  
  tft.begin();
  tft.setClock(30000000);
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}

void print_msg(int line, const char * text) {
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 1 + line * 30);
  tft.fillRect(10, 1 + line * 30, 310, 30, ILI9341_BLACK);
  tft.print(text);
}

void print_msg_i(int line, const char *t, uint32_t n) {
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 1 + line * 30);
  tft.fillRect(10, 1 + line * 30, 310, 30, ILI9341_BLACK);
  tft.printf("%s%d", t, n); 
}

void print_msg_f(int line, const char *t, float n) {
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 1 + line * 30);
  tft.fillRect(10, 1 + line * 30, 310, 30, ILI9341_BLACK);
  tft.printf("%s%5.2f", t, n); 
}

#endif
