#include "interface.hpp"
#include <Arduino.h>

const uint8_t Lampen[16] = {2, 3, 4, 5, 6, 7, 8, 9, A0, A1, A2, A3, A4, A5, A6, A7};
const uint16_t SchaltZeit = 300;

// K4
bool statK4 = true;
bool animatDoneK4 = false;
uint32_t pinStartK4 = 3;
uint32_t goTimeK4 = 0;
uint32_t animatK4 = 0;

// K3
bool statK3 = false;
bool animatDoneK3 = false;
uint32_t pinStartK3 = 0;
uint32_t goTimeK3 = 0;
uint32_t animatK3 = 0;

// K1
bool statK1 = false;
bool animatDoneK1 = false;
uint32_t pinStartK1 = 9;
uint32_t goTimeK1 = 0;
uint32_t animatK1 = 0;

// Pfeil
bool statPfeil = false;

// FR4
bool statFR4 = false;
bool animatDoneFR4 = false;
uint32_t pinStartFR4 = 14;

// FR3
bool statFR3 = false;
bool animatDoneFR3 = false;
uint32_t pinStartFR3 = 12;

// FR 1
bool statFR1 = false;
bool animatDoneFR1 = false;
uint32_t pinStartFR1 = 6;


// send true to set green
void setK4(bool out)
{
  if (goTimeK4 < millis())
  {
    animatDoneK4 = false;
    if (out)
    {
      if (animatK4 == 0)
      {
        digitalWrite(Lampen[pinStartK4 + 1], HIGH);
        goTimeK4 = SchaltZeit + millis();
        animatK4++;
      }
      else if (animatK4 == 1)
      {
        digitalWrite(Lampen[pinStartK4 + 2], LOW);
        digitalWrite(Lampen[pinStartK4 + 1], LOW);
        digitalWrite(Lampen[pinStartK4], HIGH);
        statK4 = true;

        animatDoneK4 = true;
        goTimeK4 = 0;
        animatK4 = 0;
      }
    }
    else
    {
      if (animatK4 == 0)
      {
        digitalWrite(Lampen[pinStartK4], LOW);
        digitalWrite(Lampen[pinStartK4 + 1], HIGH);
        goTimeK4 = SchaltZeit + millis();
        animatK4++;
      }
      else if (animatK4 == 1)
      {
        digitalWrite(Lampen[pinStartK4 + 1], LOW);
        digitalWrite(Lampen[pinStartK4 + 2], HIGH);
        statK4 = false;
        animatDoneK4 = true;
        animatK4 = 0;
        goTimeK4 = 0;
      }
    }
  }
}

void setK3(bool out)
{
  if (goTimeK3 < millis())
  {
    animatDoneK3 = false;
    if (out)
    {
      if (animatK3 == 0)
      {
        digitalWrite(Lampen[pinStartK3 + 1], HIGH);
        goTimeK3 = SchaltZeit + millis();
        animatK3++;
      }
      else if (animatK3 == 1)
      {
        digitalWrite(Lampen[pinStartK3 + 2], LOW);
        digitalWrite(Lampen[pinStartK3 + 1], LOW);
        digitalWrite(Lampen[pinStartK3], HIGH);
        statK3 = true;
        animatDoneK3 = true;
        goTimeK3 = 0;
        animatK3 = 0;
      }
    }
    else
    {
      if (animatK3 == 0)
      {
        digitalWrite(Lampen[pinStartK3], LOW);
        digitalWrite(Lampen[pinStartK3 + 1], HIGH);
        goTimeK3 = SchaltZeit + millis();
        animatK3++;
      }
      else if (animatK3 == 1)
      {
        digitalWrite(Lampen[pinStartK3 + 1], LOW);
        digitalWrite(Lampen[pinStartK3 + 2], HIGH);
        statK3 = false;
        animatDoneK3 = true;
        animatK3 = 0;
        goTimeK3 = 0;
      }
    }
  }
}

void setK1(bool out)
{
  if (goTimeK1 < millis())
  {
    animatDoneK1 = false;
    if (out)
    {
      if (animatK1 == 0)
      {
        digitalWrite(Lampen[pinStartK1 + 1], HIGH);
        goTimeK1 = SchaltZeit + millis();
        animatK1++;
      }
      else if (animatK1 == 1)
      {
        digitalWrite(Lampen[pinStartK1 + 2], LOW);
        digitalWrite(Lampen[pinStartK1 + 1], LOW);
        digitalWrite(Lampen[pinStartK1], HIGH);
        statK1 = true;

        animatDoneK1 = true;
        goTimeK1 = 0;
        animatK1 = 0;
      }
    }
    else
    {
      if (animatK1 == 0)
      {
        digitalWrite(Lampen[pinStartK1], LOW);
        digitalWrite(Lampen[pinStartK1 + 1], HIGH);
        goTimeK1 = SchaltZeit + millis();
        animatK1++;
      }
      else if (animatK1 == 1)
      {
        digitalWrite(Lampen[pinStartK1 + 1], LOW);
        digitalWrite(Lampen[pinStartK1 + 2], HIGH);
        statK1 = false;
        animatDoneK1 = true;
        animatK1 = 0;
        goTimeK1 = 0;
      }
    }
  }
}
 // ################################### pfeil ######################
void setPfeil(bool inp)
{
  if (inp)
  {
    digitalWrite(Lampen[pinStartK1 -1], HIGH);
    statPfeil = true;
  }
  else
  {
    digitalWrite(Lampen[pinStartK1 -1], LOW);
    statPfeil = false;
  }
}

//########################################### FR ##################################
void setFR4(bool inp)
{
  if (inp)
  {
    digitalWrite(Lampen[pinStartFR4 + 1], LOW);
    digitalWrite(Lampen[pinStartFR4], HIGH);
    statFR4 = true;
    animatDoneFR4 = true;
  }
  else
  {
    digitalWrite(Lampen[pinStartFR4], LOW);
    digitalWrite(Lampen[pinStartFR4 + 1], HIGH);
    statFR4 = false;
    animatDoneFR4 = true;
  }
}

void setFR3(bool inp)
{
  if (inp)
  {
    digitalWrite(Lampen[pinStartFR3 + 1], LOW);
    digitalWrite(Lampen[pinStartFR3], HIGH);
    statFR3 = true;
    animatDoneFR3 = true;
  }
  else
  {
    digitalWrite(Lampen[pinStartFR3], LOW);
    digitalWrite(Lampen[pinStartFR3 + 1], HIGH);
    statFR3 = false;
    animatDoneFR3 = true;
  }
}

void setFR1(bool inp)
{
  if (inp)
  {
    digitalWrite(Lampen[pinStartFR1 + 1], LOW);
    digitalWrite(Lampen[pinStartFR1], HIGH);
    statFR1 = true;
    animatDoneFR1 = true;
  }
  else
  {
    digitalWrite(Lampen[pinStartFR1], LOW);
    digitalWrite(Lampen[pinStartFR1 + 1], HIGH);
    statFR1 = false;
    animatDoneFR1 = true;
  }
}

//############################ stat return ##############################
bool getFR3()
{
  return statFR3;
}

bool getFR1()
{
  return statFR1;
}

//########################### Done return ##########################
bool getDoneK4()
{
  return animatDoneK4;
}

bool getDoneK3()
{
  return animatDoneK3;
}
