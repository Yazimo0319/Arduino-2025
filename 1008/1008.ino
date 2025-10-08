const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 10;
const int BledPin = 11;

int ledcolor = 0;                // this variable stores the LED color
int buttonState = 0;             // the button is currently pressed or not
bool ButtonPressed = false;      // the button has been pressed or not
unsigned long previousMillis = 0; // store the last time LED color updated
const long interval = 1000;      // the timer for blinking the LED
bool ledColorOrder = true;       // store whether we increase or decrease the ledcolor

void setup() {
  // initialize the button pin as input
  pinMode(buttonPin, INPUT);

  // initialize LED digital pins as output
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  // Detect the button state
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !ButtonPressed) {
    ledColorOrder = !ledColorOrder;   // reverse color order
    ButtonPressed = true;
  }
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  // Switch the LED color if the time from the last update is longer than interval
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledColorOrder == true) {
      ledcolor = ledcolor + 1;
      if (ledcolor > 3) ledcolor = 0;
    } else {
      ledcolor = ledcolor - 1;
      if (ledcolor < 0) ledcolor = 3;
    }
  }

  // Set the LED Module Color
  if (ledcolor == 0) {
    // Red
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
  } else if (ledcolor == 1) {
    // Green
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
  } else if (ledcolor == 2) {
    // Blue
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
  } else if (ledcolor == 3) {
    // White
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
  }
}
