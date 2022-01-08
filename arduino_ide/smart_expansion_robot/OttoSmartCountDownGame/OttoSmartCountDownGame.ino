#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "OttoMin.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET  -1 // sharing Arduino reset pin

#define LeftLeg   2 // left leg pin, servo[0]
#define RightLeg  3 // right leg pin, servo[1]
#define LeftFoot  4 // left foot pin, servo[2]
#define RightFoot 5 // right foot pin, servo[3]
#define Buzzer    13 //buzzer pin

OttoMin           Otto;
DHT               dht_1(10,DHT11);
Adafruit_SSD1306  display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long     timer = 0;
int               time_final;
enum              Mode {SENSOR, GAME_INTRO_0, GAME_INTRO_1, GAME_COUNT_DOWN_DISPLAY, GAME_SCORE } mode = SENSOR;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  dht_1.begin();
  pinMode(A0,INPUT);
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer);
  Otto.enableServoLimit();
  Otto.home();
}

void loop() {
  switch (mode) {
    case SENSOR:
    {
      
      char buf[8];
      int temp = round(dht_1.readTemperature());
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(3);
      display.setCursor(24,16);
      sprintf(buf, "%d.C", temp);
      display.println(buf);
      display.display();
      if (digitalRead(A0)) {
        mode = GAME_INTRO_0;
      }
      break;
    }
    case GAME_INTRO_0:
    {
      Otto.sing(S_surprise);
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(2);
      display.setCursor(0,16);
      display.println("Count Down   Game");
      display.display();
      mode = GAME_INTRO_1;
      timer = millis();
      break;
    }
    case GAME_INTRO_1:
    {
      if (timer + (long)3000 < millis()) {
        mode = GAME_COUNT_DOWN_DISPLAY;
        timer = millis();
      }
      break;
    }
    case GAME_COUNT_DOWN_DISPLAY:
    {
      int t = 10000 - ((millis() - timer));
      if (digitalRead(A0)) {
        time_final = t;
        mode = GAME_SCORE;
      } else {
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setTextSize(3);
        display.setCursor(16,16);
        if (t > 5000) {
          display.println(t);
        } else {
          display.println("-----");
          if (t < - 10000) {
            time_final = t;
            mode = GAME_SCORE;        
          }
        }
        display.display();
      }
      break;
    }
    case GAME_SCORE:
    {
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(2);
      display.setCursor(16,10);
      display.println(time_final);
      if (abs(time_final) <= 500) {
        display.setCursor(8,32);
        display.println("Good job!");
        display.display();     
        Otto.playGesture(OttoSuperHappy);
      } else {
        display.setCursor(8,32);
        display.println("Fail!!");
        display.display();     
        Otto.playGesture(OttoSad);
      }
      delay(3000);
      mode = SENSOR;
      break;
    }
  }
}
