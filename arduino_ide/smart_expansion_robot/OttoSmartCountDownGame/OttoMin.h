#ifndef OttoMin_h
#define OttoMin_h

#ifdef ARDUINO_ARCH_ESP32
#include <ESP32Servo.h>
#else
#include <Servo.h>
#endif
#include "Oscillator.h"
#include <EEPROM.h>
#include "Otto_sounds.h"
#include "OttoMin_gestures.h"

//-- Constants
#define FORWARD     1
#define BACKWARD    -1
#define LEFT        1
#define RIGHT       -1
#define SMALL       5
#define MEDIUM      15
#define BIG         30

// -- Servo delta limit default. degree / sec
#define SERVO_LIMIT_DEFAULT 240

class OttoMin
{
  public:

    //-- Otto initialization
    void init(int YL, int YR, int RL, int RR, bool load_calibration, int Buzzer);
    //-- Attach & detach functions
    void attachServos();
    void detachServos();

    //-- Predetermined Motion Functions
    void _moveServos(int time, int  servo_target[]);
    void _moveSingle(int position,int  servo_number);
    void oscillateServos(int A[4], int O[4], int T, double phase_diff[4], float cycle);

    //-- HOME = Otto at rest position
    void home();
    bool getRestState();
    void setRestState(bool state);

    //-- Predetermined Motion Functions
    void jump(float steps=1, int T = 2000);

    void walk(float steps=4, int T=1000, int dir = FORWARD);
    void turn(float steps=4, int T=2000, int dir = LEFT);
    void bend (int steps=1, int T=1400, int dir=LEFT);
    void shakeLeg (int steps=1, int T = 2000, int dir=RIGHT);

    void updown(float steps=1, int T=1000, int h = 20);
    void swing(float steps=1, int T=1000, int h=20);
    void tiptoeSwing(float steps=1, int T=900, int h=20);
    void jitter(float steps=1, int T=500, int h=20);
    void ascendingTurn(float steps=1, int T=900, int h=20);

    void moonwalker(float steps=1, int T=900, int h=20, int dir=LEFT);
    void crusaito(float steps=1, int T=900, int h=20, int dir=FORWARD);
    void flapping(float steps=1, int T=1000, int h=20, int dir=FORWARD);

    //-- Sounds
    void _tone (float noteFrequency, long noteDuration, int silentDuration);
    void bendTones (float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
    void sing(int songName);

    //-- Gestures
    void playGesture(int gesture);

    // -- Servo limiter
    void enableServoLimit(int speed_limit_degree_per_sec = SERVO_LIMIT_DEFAULT);
    void disableServoLimit();

  private:

    Oscillator servo[4];
    int servo_pins[4];

    int pinBuzzer;

    bool isOttoResting;

    void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps);

};

#endif
