#include <MIDI.h>
#include <JC_Button.h>

MIDI_CREATE_DEFAULT_INSTANCE();

Button buttonUp(2, 25, false, false);
Button buttonDown(3, 25, false, false);
Button buttonExp(4, 25, false, false);

const int maxPreset = 23;

int preset;

void setup()
{
  MIDI.begin(1);
  buttonUp.begin();
  buttonDown.begin();
  buttonExp.begin();

  // TODO: save to memory
  preset = 0;
  changeToPreset();

  // FOR TESTING
  // Serial.begin(9600);
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
}

void expMin()
{
  // Serial.println("exp min");
  MIDI.sendControlChange(1, 0, 1);
}

void expMax()
{
  // Serial.println("exp max");
  MIDI.sendControlChange(1, 127, 1);
}
