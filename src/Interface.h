#include "config.h"
#include <Arduino.h>

bool statK4 = false;
int pinStartK4 = 3;
int goTimeK4 = 0;
int animatK4 = 0;
bool statK3 = false;
int pinStartK3 = 0;
int goTimeK3 = 0;


//send 'R''G' to change the light
void setK4(bool out) {
  if (out == statK4)goTimeK4 = millis();
  else {
    if (goTimeK4 < millis() )
      if (out) {
        if (animatK4 == 0) {
          digitalWrite(Lampen[pinStartK4 + 1], HIGH);
          goTimeK4 += SchaltZeit;
          animatK4 ++;
        }
        else if (animatK4 == 1) {
          digitalWrite(Lampen[pinStartK4 + 2], LOW);
          digitalWrite(Lampen[pinStartK4 + 1], LOW);
          digitalWrite(Lampen[pinStartK4], HIGH);
          statK4 = true;
          goTimeK4 = 0;
          animatK4 = 0;
        }
        else ;
        }
      else {
        if (animatK4 == 0) {
        digitalWrite(Lampen[pinStartK4], LOW);
        digitalWrite(Lampen[pinStartK4 + 1], HIGH);
        goTimeK4 += SchaltZeit;
        animatK4 ++;
        }
        else if (animatK4 == 1) {
        digitalWrite(Lampen[pinStartK4 + 1], LOW);
        digitalWrite(Lampen[pinStartK4 + 2], HIGH);
        statK4 = false;
        animatK4 = 0;
        goTimeK4 = 0;
        }
      };
  };
}

void setK3(char out) {
  if (out == statK3) {}
  else {
    if (out == 'G') {
      digitalWrite(Lampen[pinStartK3 + 1], HIGH);
      delay(300);
      digitalWrite(Lampen[pinStartK3 + 2], LOW);
      digitalWrite(Lampen[pinStartK3 + 1], LOW);
      delay(300);
      digitalWrite(Lampen[pinStartK3], HIGH);
      statK3 = 'G';
    }
    else {
      digitalWrite(Lampen[pinStartK3], LOW);
      digitalWrite(Lampen[pinStartK3 + 1], HIGH);
      delay(300);
      digitalWrite(Lampen[pinStartK3 + 1], LOW);
      digitalWrite(Lampen[pinStartK3 + 2], HIGH);
      statK3 = 'R';

    };
  };
}

void test() {
  setK3('R');
}

char getK4() {
  return statK4;
}
char getK3() {
  return statK3;
}
