// µC: Teensy4.0

#include "pins.h"
#include "display.h"
#include "audioSetup.h"
#include "math.h"

#define SYNTH_MODE_SINE    0
#define SYNTH_MODE_SINE_X3 1
#define SYNTH_MODE_BASS    2

uint16_t freq_A = 440;
uint8_t mode = SYNTH_MODE_SINE;
uint8_t playState = 0;

void setup() {
  
  display_init();

  pinMode(PIN_BTN_MODE, INPUT_PULLUP);
  pinMode(PIN_BTN_FREQ, INPUT_PULLUP);
  pinMode(PIN_SW_PLAY, INPUT);
  analogReadResolution(12);

  audio_init();

  print_msg(0, "F synth");
  print_msg(1, "MODE: SINE");
  print_msg_i(2, "A freq: ", freq_A);
  print_msg(3, digitalRead(PIN_SW_PLAY) ? "PLAYING" : "SILENT");
  print_msg_f(4, "VOL: ", analogRead(PIN_POTI) / 41.0);

  sine1(get_F_freq());
}

unsigned long lastUpdateTime = 0;

uint16_t potVal = 0;
uint8_t modeBtnState = 1;
uint8_t freqBtnState = 1;

void loop() {

  // read buttons and poti
  if ((millis() -  lastUpdateTime) > 10UL) {
    lastUpdateTime = millis();

    uint16_t potVal1 = analogRead(PIN_POTI);
    if (abs(potVal1 - potVal) > 5) {
      potVal = potVal1;
      set_vol(potVal / 2730.0);  // adjust from 0.0 to 1.5
      print_msg_f(4, "VOL: ", potVal / 41.0); // show from 0 to 100
    }

    uint8_t modeBtn = digitalRead(PIN_BTN_MODE);
    if (modeBtn != modeBtnState) {
      modeBtnState = modeBtn;
      if (!modeBtn) {
        mode++;
        if (mode > 2) mode = 0;
        if (mode == SYNTH_MODE_SINE) {
          print_msg(1, "MODE: SINE");
          sine1(get_F_freq()); 
        }
        if (mode == SYNTH_MODE_SINE_X3) {
          print_msg(1, "MODE: SINE 3 OVT");
          sine3(get_F_freq());
        }
        if (mode == SYNTH_MODE_BASS) {
          print_msg(1, "MODE: BASS");
          bass(get_F_freq());
        }
      }
    }

    uint8_t freqBtn = digitalRead(PIN_BTN_FREQ);
    if (freqBtn != freqBtnState) {
      freqBtnState = freqBtn;
      if (!freqBtn) {
        freq_A++;
        if (freq_A > 445) freq_A = 439;
        if (mode == SYNTH_MODE_SINE) {
          sine1(get_F_freq()); 
        }
        if (mode == SYNTH_MODE_SINE_X3) {
          sine3(get_F_freq()); 
        }
        if (mode == SYNTH_MODE_BASS) {
          bass(get_F_freq());
        }
        print_msg_i(2, "A freq: ", freq_A);
      }
    }

    uint8_t sw_play = digitalRead(PIN_SW_PLAY);
    if (sw_play != playState) {
      playState = sw_play;
      sound_ctl(playState);
      print_msg(3, playState ? "PLAYING" : "SILENT");
    }
  }

}

float get_F_freq() {
  float f = (float)freq_A;
  return f * exp2f(-10.0/3.0);
}

