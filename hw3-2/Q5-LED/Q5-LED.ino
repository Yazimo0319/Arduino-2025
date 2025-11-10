const int buttonPin = 2;
const int ledPin = 3;

int buttonState = HIGH;
bool buttonPressed = false;
int mode = 0; // 0=恆亮,1=慢閃,2=中閃,3=快閃
bool ledOn = false;

unsigned long previousMillis = 0;
unsigned long interval = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && !buttonPressed) {
    mode++;
    if (mode > 3) mode = 0;
    buttonPressed = true;
    delay(200);
  }
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
  }

  if (mode == 0) {
    interval = 0;       // 恆亮
  } else if (mode == 1) {
    interval = 1000;    // 慢閃
  } else if (mode == 2) {
    interval = 500;     // 中閃
  } else if (mode == 3) {
    interval = 250;     // 快閃
  }

  if (mode == 0) {
    digitalWrite(ledPin, HIGH);  // 恆亮
  } else {
    if (currentMillis - previousMillis >= interval / 2) { 
      previousMillis = currentMillis;
      ledOn = !ledOn;
      digitalWrite(ledPin, ledOn ? HIGH : LOW);
    }
  }
}
