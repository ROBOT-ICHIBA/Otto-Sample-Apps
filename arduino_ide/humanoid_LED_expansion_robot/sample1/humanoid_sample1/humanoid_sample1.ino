
#include "OttoHumanoid.h"
#include "Arduino.h"

#define NoiseLevel        300 /* define noise sensitivity from 0 - 1023 */

#define LeftLeg           2  /* left leg pin, servo[0] */
#define RightLeg          3  /* right leg pin, servo[1] */
#define LeftFoot          4  /* left foot pin, servo[2] */
#define RightFoot         5  /* right foot pin, servo[3] */
#define LeftArm           6   /* left arm */
#define RightArm          7   /* right arm */
#define Buzzer            13 /*buzzer pin */
#define NoiseSensor       A6
#define UltraSonicTrigger 8
#define UltraSonicEcho    9
#define CLK               A1  /* Clock pin*/
#define CS                A2  /* Chip Select pin*/
#define DIN               A3  /* Data In pin*/
#define Orientation       0   /* 8x8 LED Matrix orientation  Top  = 1, Bottom = 2, Left = 3, Right = 4*/

OttoHumanoid ottoHumanoid;
int p = 1;

void setup() {
  ottoHumanoid.initHUMANOID(LeftLeg, RightLeg, LeftFoot, RightFoot,LeftArm, RightArm, true, NoiseSensor, Buzzer, UltraSonicTrigger, UltraSonicEcho);
  ottoHumanoid.initMATRIX( DIN, CS, CLK, Orientation);
  ottoHumanoid.putMouth(23);
  ottoHumanoid.home();
}

void loop() {
    if (analogRead(A6) >= NoiseLevel) {
      switch (p) {        
        case 1:
          ottoHumanoid.putMouth(happyOpen);
          ottoHumanoid.sing(S_happy);
          ottoHumanoid.sing(S_happy);
          ottoHumanoid.walk(3,1000,1);
          p++;
          break;
        case 2:
          ottoHumanoid.putMouth(happyClosed);
          ottoHumanoid.sing(S_cuddly);
          ottoHumanoid.sing(S_cuddly);
          ottoHumanoid.moonwalker(3, 1000, 25, -1);
          p++;
          break;
        case 3:
          ottoHumanoid.putMouth(smile);
          ottoHumanoid.sing(S_OhOoh2);
          ottoHumanoid.sing(S_OhOoh2);
          ottoHumanoid.tiptoeSwing(5, 1000, 25);
          p++;
          break;
        case 4:
          ottoHumanoid.putMouth(heart);
          ottoHumanoid.sing(S_surprise);
          ottoHumanoid.sing(S_surprise);
          ottoHumanoid.walk(3,1000,-1);
          ottoHumanoid.updown(1, 1000, 25);
          ottoHumanoid.writeText ( "THANK YOU",80);
          p = 1;
          break;
        default:
          p = 1;
          break;
      }
      delay(1*1000);
      ottoHumanoid.putMouth(23);
    }
}
