#ifndef PINDEF_H
#define PINDEF_H

// LCD (SPI0)
#define PIN_LCD_SCK  13
#define PIN_LCD_MOSI 11
#define PIN_LCD_MISO 12
#define PIN_LCD_CS   0
#define PIN_LCD_DC   10 // teensy optimized ILI9341 lib prefers to use hardware CS control for DC pin
#define PIN_LCD_RST  1
#define PIN_LCD_BL   6
#define PIN_SD_CS    9  // optional SD card on same SPI bus 

// Audio (SAI2)
#define PIN_I2S2_MCLK  33
#define PIN_I2S2_BCLK  4
#define PIN_I2S2_LRCLK 3
#define PIN_I2S2_IN    5
#define PIN_I2S2_OUT   2
// these are the default pins used by the I2S2 blocks in the audio lib

// Buttons
#define PIN_BTN_MODE 16
#define PIN_BTN_FREQ 17
#define PIN_SW_PLAY  15

// Analog
#define PIN_POTI 14

#endif