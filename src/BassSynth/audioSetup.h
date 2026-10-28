#ifndef AUDIOSETUP_H
#define AUDIOSETUP_H

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine_fundamental; //xy=170,600
AudioSynthWaveformSine   sine_2nd;          //xy=178,675
AudioSynthWaveformSine   sine_3rd;          //xy=178,749
AudioSynthWaveformSine   sine_4th;          //xy=178,949
AudioMixer4              mixer1;         //xy=550,675
AudioEffectFade          fade;           //xy=800,676
AudioAmplifier           volume_knob;    //xy=971,676
AudioOutputI2S2          i2s2_out;       //xy=1189,677
AudioConnection          patchCord1(sine_fundamental, 0, mixer1, 0);
AudioConnection          patchCord2(sine_2nd, 0, mixer1, 1);
AudioConnection          patchCord3(sine_3rd, 0, mixer1, 2);
AudioConnection          patchCord8(sine_4th, 0, mixer1, 3);
AudioConnection          patchCord4(mixer1, fade);
AudioConnection          patchCord5(fade, volume_knob);
AudioConnection          patchCord6(volume_knob, 0, i2s2_out, 0);
AudioConnection          patchCord7(volume_knob, 0, i2s2_out, 1);
// GUItool: end automatically generated code

void audio_init() {
  AudioMemory(50);

  fade.fadeOut(1UL);
  volume_knob.gain(0.1);
  mixer1.gain(0, 1.0);
  mixer1.gain(1, 1.0);
  mixer1.gain(2, 1.0);
  mixer1.gain(3, 1.0);
}

void sound_ctl(uint8_t on) {
  if (on) {
    fade.fadeIn(300UL);
  } else {
    fade.fadeOut(400UL);
  }
}

void set_vol(float v) {
  volume_knob.gain(v);
}

void sine1(float freq) {
  sine_fundamental.amplitude(0.7);
  sine_fundamental.frequency(freq);
  sine_2nd.amplitude(0.0);
  sine_3rd.amplitude(0.0);
  sine_4th.amplitude(0.0);
}

void sine3(float freq) {
  sine_fundamental.amplitude(0.7);
  sine_fundamental.frequency(freq);
  sine_2nd.amplitude(0.22);
  sine_2nd.frequency(2 * freq);
  sine_3rd.amplitude(0.03);
  sine_3rd.frequency(3 * freq);
  sine_4th.amplitude(0.0);
}

// emulating actual bass spectrum with first 4 sine waves
void bass(float freq) {
  sine_fundamental.amplitude(0.252);
  sine_fundamental.frequency(freq);
  sine_2nd.amplitude(0.45);
  sine_2nd.frequency(2 * freq);
  sine_3rd.amplitude(0.225);
  sine_3rd.frequency(3 * freq);
  sine_4th.amplitude(0.17);
  sine_4th.frequency(4 * freq);
}

#endif
