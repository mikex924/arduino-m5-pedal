#include <EEPROM.h>
#include <MIDI.h>
#include <JC_Button.h>

MIDI_CREATE_DEFAULT_INSTANCE();
Button buttonUp(2, 25, false, false);
Button buttonDown(3, 25, false, false);
Button buttonExp(4, 25, false, false);

const int presetMemAddr = 0;

const int maxExp = 127;
const int maxPreset = 23;

int preset = 0;

void setup()
{
  MIDI.begin(1);
  buttonUp.begin();
  buttonDown.begin();
  buttonExp.begin();

  int savedPreset = EEPROM.read(presetMemAddr);
  if (0 <= savedPreset && savedPreset <= maxPreset) {
    preset = savedPreset;
  }

  // wait for M5 to power up
  delay(2000);

  changeToPreset();
}

void loop()
{
  buttonUp.read();
  buttonDown.read();
  buttonExp.read();

  if (buttonUp.wasPressed()) {
    up();
  } else if (buttonDown.wasPressed()) {
    down();
  } else if (buttonExp.wasPressed()) {
    expMax();
  } else if (buttonExp.wasReleased()) {
    expMin();
  }

  delay(10);
}

void up()
{
  preset = preset == 0 ? maxPreset : preset - 1;
  changeToPreset();
}

void down()
{
  preset = preset == maxPreset ? 0 : preset + 1;
  changeToPreset();
}

void changeToPreset() {
  MIDI.sendProgramChange(preset, 1);
  EEPROM.write(presetMemAddr, preset);
}

void expMin()
{
  MIDI.sendControlChange(1, 0, 1);
}

void expMax()
{
  MIDI.sendControlChange(1, maxExp, 1);
}
