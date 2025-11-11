const int buttonPin = 2;
const int Rled = 9;
const int Gled = 10;
const int Bled = 11;

int mode = 0; // 0=關, 1=呼吸, 2=漸層, 3=閃爍
bool buttonPressed = false;
int buttonState;
int lastButtonState = HIGH;

unsigned long lastPressTime = 0;
unsigned long pressStartTime = 0;
unsigned long previousMillis = 0;
unsigned long blinkMillis = 0;

int brightness = 0;
int fadeAmount = 5;

int colorValue = 0;

bool blinkState = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(Bled, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  buttonState = digitalRead(buttonPin);


  if (buttonState == LOW && lastButtonState == HIGH) {
    pressStartTime = currentMillis;
  }


  if (buttonState == HIGH && lastButtonState == LOW) {
    unsigned long pressDuration = currentMillis - pressStartTime;


    if (pressDuration > 1000) {
      mode = 3;
    } else {
      if (currentMillis - lastPressTime < 500) {
        mode = 2; 
      } else {
        mode = (mode == 1) ? 0 : 1;
      }
      lastPressTime = currentMillis;
    }
  }

  lastButtonState = buttonState;

  if (mode == 0) {
    setColor(0, 0, 0);
  }

  else if (mode == 1) {
    if (currentMillis - previousMillis >= 30) {
      previousMillis = currentMillis;
      brightness += fadeAmount;
      if (brightness <= 0 || brightness >= 255) fadeAmount = -fadeAmount;
      int val = 255 - brightness;
      analogWrite(Rled, val);
      analogWrite(Gled, val);
      analogWrite(Bled, val);
    }
  }

  else if (mode == 2) {
    if (currentMillis - previousMillis >= 30) {
      previousMillis = currentMillis;
      colorValue++;
      if (colorValue > 765) colorValue = 0;

      int r, g, b;
      if (colorValue < 255) { r = 255 - colorValue; g = colorValue; b = 0; }
      else if (colorValue < 510) { r = 0; g = 510 - colorValue; b = colorValue - 255; }
      else { r = colorValue - 510; g = 0; b = 765 - colorValue; }

      setColor(r, g, b);
    }
  }

  else if (mode == 3) {
    if (currentMillis - blinkMillis >= 250) {
      blinkMillis = currentMillis;
      blinkState = !blinkState;
      if (blinkState) setColor(255, 255, 255);
      else setColor(0, 0, 0);
    }
  }
}

void setColor(int r, int g, int b) {
  analogWrite(Rled, 255 - r);
  analogWrite(Gled, 255 - g);
  analogWrite(Bled, 255 - b);
}
