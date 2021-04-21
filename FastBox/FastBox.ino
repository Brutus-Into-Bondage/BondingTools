#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <time.h>

#define TRIG_FRONT 7
#define ECHO_FRONT 6
#define TRIG_BACK 5
#define ECHO_BACK 4
#define FRONT_SERVO 3
#define BACK_SERVO 2
#define BUTTON 9
#define CLOSE 0
#define OPEN 100

#define IR_PIN 3
#define HEX_0 0xE916FF00
#define HEX_1 0xF30CFF00
#define HEX_2 0xE718FF00
#define HEX_3 0xA15EFF00
#define HEX_4 0xF708FF00
#define HEX_5 0xE31CFF00
#define HEX_6 0xA55AFF00
#define HEX_7 0xBD42FF00
#define HEX_8 0xAD52FF00
#define HEX_9 0xB54AFF00

LiquidCrystal myLCD(8,9,10,11,12,13);

Servo backServo;

int state = 3;
int fDist;
int bDist;

int chars = 0;

long dur;
int dist;

int numRow = 0;
int detectRow = 0;
int trigRow = 0;

int startTime = 0;

int pass[] = {1,9,0,2};

bool valid = true;

int getDist(int TRIG, int ECHO) {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(1);
  digitalWrite(TRIG, LOW);
  
  dur = pulseIn(ECHO, HIGH);
  dist = dur * 0.034 / 2;

  if (dist == 0) dist = 42;

  return dist;
}

bool checkClose(int TRIG, int ECHO) {
  int dist = getDist(TRIG, ECHO);

  if (dist > 5) {
    return false;
  } else {
    return true;
  }
}

void setup() {
  
  backServo.attach(BACK_SERVO);
  
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_BACK, OUTPUT);
  pinMode(ECHO_BACK, INPUT);

  Serial.begin(9600);

  backServo.write(CLOSE);

  myLCD.begin(16,2);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  myLCD.setCursor(0,0);

  myLCD.write("ENTER PASSCODE");
  chars = 0;
}

void loop() {
  //int distBack = getDist(TRIG_BACK, ECHO_BACK);
  //int distFront = getDist(TRIG_FRONT, ECHO_FRONT);

  if (state == 0 or state == 2) {
    fDist = getDist(TRIG_FRONT, ECHO_FRONT);
    bDist = 0;
  } else if (state == 1) {
    fDist = 0;
    bDist = getDist(TRIG_BACK, ECHO_BACK);
  } else {
    fDist = 0;
    bDist = 0;
  }
  
  Serial.println(fDist);
  Serial.println(bDist);
  if (state == 3) {
    if (IrReceiver.decode()) {
      if (IrReceiver.decodedIRData.decodedRawData != 0) {

        int in = 0;

        switch (IrReceiver.decodedIRData.decodedRawData) {
          case HEX_0:
            in = 0;
            break;
          case HEX_1:
            in = 1;
            break;
          case HEX_2:
            in = 2;
            break;
          case HEX_3:
            in = 3;
            break;
          case HEX_4:
            in = 4;
            break;
          case HEX_5:
            in = 5;
            break;
          case HEX_6:
            in = 6;
            break;
          case HEX_7:
            in = 7;
            break;
          case HEX_8:
            in = 8;
            break;
          case HEX_9:
            in = 9;
            break;
        }

        myLCD.clear();
        myLCD.setCursor(0,0);
        myLCD.print(in);
        if (in != pass[chars]) {
          valid = false;
        }

        Serial.println(in);

        chars++;
      }
      IrReceiver.resume();
    }

    if (chars == 4) {
      state = 4;
    }
  } else if (state == 4) {
    Serial.println(valid);
    if (valid) {
      myLCD.setCursor(0,0);
      myLCD.print("CORRECT GRAB KEY");
      state = 0;
      backServo.write(OPEN);
    } else {
      myLCD.setCursor(0,0);
      myLCD.print("TRY AGAIN");
      state = 3;
      valid = true;
      chars = 0;
    }
    chars = 0;
    valid = true;
  } else if (state == 0) {
    //int dist = getDist(TRIG_FRONT, ECHO_FRONT);
    //Serial.println(detectRow);
    //Serial.println(dist);
    if (fDist < 6) {
      detectRow++;
    } else {
      detectRow = 0;
    }
    
    if (detectRow > 19) {
      state = 1;
      detectRow = 0;
      //backServo.write(OPEN);
      startTime = millis();
      
      Serial.println("HAND DETECTED");

      //delay(400);
    }
  } else if (state == 1) {
    //int dist = getDist(TRIG_BACK, TRIG_BACK);
    //Serial.println(trigRow);
    //Serial.println(dist);
    dist = 7;
    if (bDist < 6) {
      trigRow++;
    } else {
      trigRow = 0;
    }

    if (trigRow > 0) {
      int timeDiff = millis() - startTime;
      state = 2;

      Serial.println(timeDiff);

      if (timeDiff < 500) {
        backServo.write(CLOSE);
        Serial.println("TOO FAST");
      } else {
        backServo.write(OPEN);
        Serial.println("SLOW ENOUGH");
      }
      trigRow = 0;
    }
  } else if (state == 2) {
    //int dist = getDist(TRIG_FRONT, ECHO_FRONT);
    //Serial.println(numRow);
    //Serial.println(dist);
    if (fDist > 5) {
      numRow++;
    } else {
      numRow = 0;
    }
    
    if (numRow > 79) {
      state = 0;
      numRow = 0;

      Serial.println("RESET");
      delay(5000);

      backServo.write(OPEN);
    }
  }
}
