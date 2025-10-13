
const int buttonPin = 2;
const int RledPin = 9;
const int GledPin = 11;
const int BledPin = 10;

int mode = 0; 
bool buttonPressed = false;
unsigned long lastButtonTime = 0;
unsigned long longPressThreshold = 600;
bool longPressActive = false;


unsigned long previousMillis = 0;
unsigned long colorInterval = 1000; 
unsigned long fastInterval = 200; 
int colorIndex = 0;

int brightness = 0;
int fadeAmount = 5;

int colors[5][3] = {
  {255, 0, 0},     // Red
  {0, 255, 0},     // Green
  {0, 0, 255},     // Blue
  {255, 0, 255},   // Purple
  {0, 255, 255}    // Cyan
};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  bool buttonState = digitalRead(buttonPin) == LOW;


  if (buttonState && !buttonPressed) {
    buttonPressed = true;
    lastButtonTime = currentMillis;
  }

  if (!buttonState && buttonPressed) {
    if (longPressActive) {
      longPressActive = false;
    } else {
      
      mode = 1 - mode;
    }
    buttonPressed = false;
  }

  
  if (buttonState && (currentMillis - lastButtonTime > longPressThreshold)) {
    longPressActive = true;
  }

 
  if (mode == 0) { 
    unsigned long interval = longPressActive ? fastInterval : colorInterval;

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      colorIndex = (colorIndex + 1) % 5;
    }

    setColor(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
  }

  else if (mode == 1) { 
    if (currentMillis - previousMillis >= 30) {
      previousMillis = currentMillis;
      brightness += fadeAmount;
      if (brightness <= 0 || brightness >= 255) fadeAmount = -fadeAmount;
    }

   
    int r = map(brightness, 0, 255, 0, 255);
    int g = map(brightness, 0, 255, 0, 180);
    int b = map(brightness, 0, 255, 0, 50);
    setColor(r, g, b);
  }
}


void setColor(int r, int g, int b) {
  analogWrite(RledPin, 255 - r);
  analogWrite(GledPin, 255 - g);
  analogWrite(BledPin, 255 - b);
}
