#include <EEPROM.h>
#include <MIDI.h>
#include <JC_Button.h>

MIDI_CREATE_DEFAULT_INSTANCE();

Button tunerButton(2, 25, false, false);
Button upButton(3, 25, false, false);
Button downButton(4, 25, false, false);
Button expButton(5, 25, false, false);

const int redPin = 8;
const int greenPin = 9;
const int bluePin = 10;

const int presetMemAddr = 0;

const int expChannel = 1;
const int tunerChannel = 69;
const int maxValue = 127;
const int maxPreset = 23;

int preset = 0;
bool tunerMode = false;

void setup()
{
  MIDI.begin(1);

  tunerButton.begin();
  upButton.begin();
  downButton.begin();
  expButton.begin();

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  int savedPreset = EEPROM.read(presetMemAddr);
  if (0 <= savedPreset && savedPreset <= maxPreset) {
    preset = savedPreset;
  }

  // wait for M5 to power up
  delay(2000);

  changeToPreset();
  ledNormal();
}

void loop()
{
  tunerButton.read();
  upButton.read();
  downButton.read();
  expButton.read();

  if (tunerMode) {
    if (tunerButton.wasPressed() || upButton.wasPressed() || downButton.wasPressed() || expButton.wasPressed()) {
      tunerOff();
    }
  } else {
    if (tunerButton.wasPressed()) {
      tunerOn();
    } else if (upButton.wasPressed()) {
      up();
    } else if (downButton.wasPressed()) {
      down();
    } else if (expButton.wasPressed()) {
      expMax();
    } else if (expButton.wasReleased()) {
      expMin();
    }
  }

  delay(10);
}

void tunerOn() {
  MIDI.sendControlChange(tunerChannel, maxValue, 1);
  tunerMode = true;
  ledTuner();
}

void tunerOff() {
  MIDI.sendControlChange(tunerChannel, 0, 1);
  tunerMode = false;
  ledNormal();
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
  MIDI.sendControlChange(expChannel, 0, 1);
  ledNormal();
}

void expMax()
{
  MIDI.sendControlChange(expChannel, maxValue, 1);
  ledExp();
}

void ledNormal() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 50);
  analogWrite(bluePin, 25);
}

void ledExp() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 70);
  analogWrite(bluePin, 15);
}

void ledTuner() {
  analogWrite(redPin, 150);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 25);
}
