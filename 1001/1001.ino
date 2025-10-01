const int buttonPin=2;
const int rLED=3;
const int bLED=4;
const int gLED=5;

int state=0;
int ledcolor=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin,INPUT);
  pinMode(rLED,OUTPUT);
  pinMode(bLED,OUTPUT);
  pinMode(gLED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  state=digitalRead(buttonPin);
  if(state==0){
    ledcolor = ledcolor + 1;
    delay(100);
  }
  if(ledcolor==0){
    digitalWrite(rLED,1);
    digitalWrite(bLED,1);
    digitalWrite(gLED,1);
  }
  else if(ledcolor==1){
    digitalWrite(rLED,0);
    digitalWrite(bLED,1);
    digitalWrite(gLED,1);
  }
  else if(ledcolor==2){
    digitalWrite(rLED,1);
    digitalWrite(bLED,0);
    digitalWrite(gLED,1);
  }
  else if(ledcolor==3){
    digitalWrite(rLED,1);
    digitalWrite(bLED,1);
    digitalWrite(gLED,0);
  }
  else if(ledcolor==4){
    digitalWrite(rLED,0);
    digitalWrite(bLED,0);
    digitalWrite(gLED,1);
  }
  else if(ledcolor==5){
    digitalWrite(rLED,0);
    digitalWrite(bLED,1);
    digitalWrite(gLED,0);
  }
  else if(ledcolor==6){
    digitalWrite(rLED,1);
    digitalWrite(bLED,0);
    digitalWrite(gLED,0);
  }
  else if(ledcolor==7){
    digitalWrite(rLED,0);
    digitalWrite(bLED,0);
    digitalWrite(gLED,0);
  }
  else if(ledcolor==8){
    ledcolor=0;
  }
}
