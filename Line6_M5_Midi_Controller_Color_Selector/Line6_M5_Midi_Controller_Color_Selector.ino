#include <JC_Button.h>

Button b1(2, 25, false, false);
Button b2(3, 25, false, false);
Button b3(4, 25, false, false);
Button b4(5, 25, false, false);

const int redPin = 8;
const int greenPin = 9;
const int bluePin = 10;

int r = 0;
int g = 0;
int b = 0;

void setup()
{
  b1.begin();
  b2.begin();
  b3.begin();
  b4.begin();

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  b1.read();
  b2.read();
  b3.read();
  b4.read();

  if (b1.isPressed()) {
    if (b2.isPressed()) {
      r = r == 0 ? 255 : r - 1;
    } else if (b3.isPressed()) {
      g = g == 0 ? 255 : g - 1;
    } else if (b4.isPressed()) {
      b = b == 0 ? 255 : b - 1;
    }
  } else {
    if (b2.isPressed()) {
      r = r == 255 ? 0 : r + 1;
    } else if (b3.isPressed()) {
      g = g == 255 ? 0 : g + 1;
    } else if (b4.isPressed()) {
      b = b == 255 ? 0 : b + 1;
    }
  }

  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);

  delay(10);
}
