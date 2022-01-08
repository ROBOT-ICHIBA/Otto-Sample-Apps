#define MIN_TEMP_THRESHOLD 20
#define MAX_TEMP_THRESHOLD 28
#define MIN_HUMIDITY_THRESHOLD 30
#define MAX_HUMIDITY_THRESHOLD 70

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "OttoMin.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET  -1 // sharing Arduino reset pin

#define LeftLeg 2 // left leg pin, servo[0]
#define RightLeg 3 // right leg pin, servo[1]
#define LeftFoot 4 // left foot pin, servo[2]
#define RightFoot 5 // right foot pin, servo[3]
#define Buzzer 13 //buzzer pin

OttoMin           Otto;
DHT               dht_1(10,DHT11);
Adafruit_SSD1306  display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long     timer = 0;

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
  char buf[8];    
  int temp = round(dht_1.readTemperature());
  int hum = round(dht_1.readHumidity());
  bool isTempOver = temp >= MAX_TEMP_THRESHOLD || temp <= MIN_TEMP_THRESHOLD ;
  bool isHumOver = hum >= MAX_HUMIDITY_THRESHOLD || hum <= MIN_HUMIDITY_THRESHOLD;
  
  display.clearDisplay();
  if (isTempOver) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE);
  }
  display.setTextSize(3);
  display.setCursor(0,0);
  sprintf(buf, "T %d.C", temp);
  display.println(buf);
  
  if (isHumOver) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE);
  }
  display.setCursor(0,32);      
  sprintf(buf, "H %d%%", hum);
  display.println(buf);
  display.display();
  if (isTempOver || isHumOver) {
    if (digitalRead(A0)) {
      timer = millis() + (60 * (unsigned long)1000);
      Otto.home();
    } else {
      if (timer < millis()) {
        Otto.sing(S_surprise);
      }
    }

    if (digitalRead(A0)) {
      timer = millis() + (60 * (unsigned long)1000);
      Otto.home();
    } else {
      if (timer < millis()) {
        Otto.updown();
        timer = millis() + (1 * (unsigned long)1000);        
      }
    }
  }
}
