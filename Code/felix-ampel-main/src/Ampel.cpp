#include "Ampel.hpp"
#include "interface.hpp"

const uint8_t Detect[17] = {53, 52, 51, 50, 49, 48, 47, 46, 45, 43, 41, 39, 37, 35, 33, 31, 29};
const uint8_t FR[12] = {44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22};


uint8_t FROUT[12] = {};
uint8_t FRPressed[12] = {};
uint8_t DetectOUT[17] = {};
uint8_t DetectPressed[17] = {};

// K1
const uint16_t MaxTimeK1 = 60000;
const uint16_t DefaultTimeK1 = 40000;
uint32_t ActualDurationK1 = 40000;

// K3
const uint16_t MaxTimeK3 = 60000;
const uint16_t DefaultTimeK3 = 42000;
uint32_t ActualDurationK3 = 42000;

// K4
const uint16_t MaxTimeK4 = 30000;
const uint16_t DefaultTimeK4 = 17000;
uint32_t ActualDurationK4 = 17000;

// k
uint32_t ActualDurationK1uK3;

// Pfeil
uint32_t ActualTimePfeil = 17000;
bool AnimatPfeil = false;


// FR
const uint16_t MinFR = 2000;
const uint16_t MaxFR = 7000;

// FR 1
bool TraffiFR1 = false;
bool EnableFR1 = false;
bool AnimatFR1 = false;
uint32_t ActualDurationFR1 = 10000;
uint16_t TraffiK1 = 0;

// FR 3
bool TraffiFR3 = false;
bool EnableFR3 = false;
bool AnimatFR3 = false;
uint32_t ActualDurationFR3 = 10000;
uint16_t TraffiK3 = 0;

// FR 4
bool TraffiFR4 = false;
bool EnableFR4 = false;
bool AnimatFR4 = false;
uint32_t ActualDurationFR4 = 25000;
uint16_t TraffiK4 = 0;

const uint16_t VerlustT = 500;
const uint16_t DefaultTimePfeil = 1000;
const uint16_t TraffikNoise = 5;
const uint16_t AutoZeit = 500;
uint16_t SafeTime = 10000;
uint32_t Relative0 = 0;
uint32_t OldRelative0 = 0;
uint32_t cleanFRgreen = 1000;
int Loop = 0;

void setup()
{
  Serial.begin(9600);

  Serial.println("OK Lets go!");

  // output pins ***klug*** Definieren
  for (int index = 0; index < ELEMENTCOUNT(Lampen); index++)
  {
    pinMode(Lampen[index], OUTPUT);
  }

  for (int index = 0; index < ELEMENTCOUNT(Detect); index++)
  {
    pinMode(Detect[index], OUTPUT);
  }

  for (int index = 0; index < ELEMENTCOUNT(FR); index++)
  {
    pinMode(FR[index], OUTPUT);
  }

  for (int index = 0; index < ELEMENTCOUNT(DetectPressed); index++)
  {
    DetectPressed[index] = false;
    DetectOUT[index] = 0;
  }

  for (int index = 0; index < ELEMENTCOUNT(FRPressed); index++)
  {
    FRPressed[index] = false;
    FROUT[index] = 0;
  }
  setFR1(false);
  setFR3(false);
  setFR4(false);
}

void loop()
{
  TasterCheck();
  //Serial.println(TasterCheckString());
  TasterParser();
  // Serial.println(TasterParserString());
  FRCheck();
  // Serial.println(FRCheckString());
  FRParser();
  //Serial.println(FRParserString());


// ############################################ K
  if (Relative0 + SafeTime + cleanFRgreen + ActualDurationK4 + SafeTime + cleanFRgreen + ActualDurationK1uK3  < millis() && Loop >= 3)
  {
    setK3(false);
    setK1(false);
    if (getDoneK3() && getDoneK3())
    {
      SafeTime = 10000;
      TimingSet();
    }
  }

  if (Relative0 + SafeTime + cleanFRgreen + ActualDurationK4 + SafeTime + cleanFRgreen < millis() && Loop == 2)
  {
    setK3(true);
    setK1(true);
    if (getDoneK3())
      Loop++;
  }

  if (Relative0 + SafeTime + cleanFRgreen + ActualDurationK4 < millis() && Loop == 1)
  {
    SafeTime = 2000;
    setK4(false);
    setPfeil(false);
    if (getDoneK4())
      Loop++;
  }
  if (Relative0 + SafeTime + cleanFRgreen< millis() && Loop == 0)
  {
    setK4(true);
    if (getDoneK4())
      Loop++;
  }

  if(Relative0 + ActualTimePfeil < millis() && !AnimatPfeil){
    setPfeil(true);
    AnimatPfeil = true;
  }


//######################### FR
  if (EnableFR1){
    if (Relative0 < millis() && !getFR1() && !AnimatFR1){
      Serial.println("FR1 on");
      setFR1(true);
    AnimatFR1 = true;
    }
    if (Relative0 + ActualDurationFR1 < millis() && AnimatFR1){
      Serial.println("FR1 off");
      setFR1(false);
      EnableFR1 = false;
    }
  }
  if (EnableFR3){
    if (Relative0 < millis() && !getFR3() && !AnimatFR3){
      Serial.println("FR3 on");
      setFR3(true);
      AnimatFR3 = true;
    }
    if (Relative0 + ActualDurationFR3 < millis() && AnimatFR3){
      Serial.println("FR3 off");
      setFR3(false);
      EnableFR3 = false;
    }
  }
  if (EnableFR4){
    if (Relative0 + ActualDurationK4 + SafeTime < millis()  && !AnimatFR4) {
      Serial.println("FR4 on");
      setFR4(true);
      AnimatFR4 = true;
      OldRelative0 = Relative0;

    }
    if (OldRelative0 + ActualDurationFR4 < millis() && AnimatFR4){
      Serial.println("FR4 off");
      setFR4(false);
      EnableFR4 = false;
      AnimatFR4 = false;
      TraffiFR4 = false;
    }     
  }
}

//######################################## Time Math #########################
void TimingSet()
{
  Serial.println(".");
  // ####################### adaptive K Zeiten
ActualDurationK1 = DefaultTimeK1;
ActualDurationK3 = DefaultTimeK3;
ActualDurationK4 = DefaultTimeK4;

if (TraffiK1 > TraffikNoise)
{
  TraffiK1 -= TraffikNoise;
  ActualDurationK1 += (TraffiK1 * AutoZeit) + VerlustT;
}
if (TraffiK3 > TraffikNoise)
{
  TraffiK3 -= TraffikNoise;
  ActualDurationK3 += (TraffiK3 * AutoZeit) + VerlustT;
}
if (TraffiK4 > TraffikNoise)
{
  TraffiK4 -= TraffikNoise;
  ActualDurationK4 += (TraffiK4 * AutoZeit) + VerlustT;
}
if (ActualDurationK1 > MaxTimeK1) ActualDurationK1 = MaxTimeK1;
if (ActualDurationK3 > MaxTimeK3) ActualDurationK3 = MaxTimeK3;
if (ActualDurationK4 > MaxTimeK4) ActualDurationK4 = MaxTimeK4;

ActualDurationK1uK3 = (ActualDurationK1 + ActualDurationK3)/2;
//ActualDurationK1 = ActualDurationK1uK3;
//ActualDurationK3 = ActualDurationK1uK3;
Serial.println(ActualDurationK4);

  // ############################# FR
EnableFR1 = false;
EnableFR3 = false;
EnableFR4 = false;

if((TraffiFR1)){
  //ActualDurationFR1 = MaxFR;
  EnableFR1 = true;
}
if((TraffiFR3)){
  //ActualDurationFR3 = MaxFR;
  EnableFR3 = true;
}
if((TraffiFR4)){
  //ActualDurationFR4 = MaxFR;
  EnableFR4 = true;
}

TraffiFR1 = false;
TraffiFR3 = false;
//TraffiFR4 = false;

  // Rset / Werte löschen
  Loop = 0;
  Relative0 = millis();
  //AnimatFR4 = false;
  AnimatFR3 = false;
  AnimatFR1 = false;
  AnimatPfeil = false;
}

void flush();




//################################ Taster ############################################
void TasterParser()
{
  // K1
  if (!DetectOUT[0] == 0)
  {
    TraffiK1 += DetectOUT[0];
    DetectOUT[0] = 0;
  }
  if (!DetectOUT[6] == 0){
    if(!TraffiK1 == 0) TraffiK1 -= DetectOUT[6];
    DetectOUT[6] = 0;
  }
  if (!DetectOUT[8] == 0){
    if(!TraffiK1 == 0) TraffiK1 -= DetectOUT[8];
    DetectOUT[8] = 0;
  }

  // K3
  if (!DetectOUT[11] == 0)
  {
    TraffiK3 += DetectOUT[11];
    DetectOUT[11] = 0;
  }
  if (!DetectOUT[12] == 0){
    if(!TraffiK3 == 0) TraffiK3 -= DetectOUT[12];
    DetectOUT[12] = 0;
  }
  if (!DetectOUT[14] == 0){
    if(!TraffiK3 == 0) TraffiK3 -= DetectOUT[14];
    DetectOUT[14] = 0;
  }

  // K4
  if (!DetectOUT[1] == 0)
  {
    TraffiK4 += DetectOUT[1];
    DetectOUT[1] = 0;
  }
  if (!DetectOUT[5] == 0){
    if(!TraffiK4 == 0) TraffiK4 -= DetectOUT[5];
    DetectOUT[5] = 0;
  }
}

String TasterParserString()
{
  String out = "";
  out += String(TraffiK1);
  out += String(TraffiK3);
  out += String(TraffiK4);
  return out;
}

// hier noch halt und push detektion hinzufügen
void TasterCheck()
{
  for (int index = 0; index < ELEMENTCOUNT(Detect); index++)
  {
    if (digitalRead(Detect[index]) == 1 && !DetectPressed[index])
    {
      DetectOUT[index]++;
      DetectPressed[index] = true;
    }
    else if (digitalRead(Detect[index]) == 0)
    {
      DetectPressed[index] = false;
    }
  }
}

String TasterCheckString()
{
  String out = "";
  for (int index = 0; index < ELEMENTCOUNT(Detect); index++)
  {
    out += String(DetectOUT[index]);
  }
  return out;
}

//#################################### FR ########################################
void FRParser()
{
  // FR1
  if (!FROUT[1] == 0 || !FROUT[3] == 0)
  {
    TraffiFR1 = true;
    FROUT[3] = 0;
    FROUT[1] = 0;
  }

  // FR3
  if (!FROUT[8] == 0 || !FROUT[11] == 0)
  {
    TraffiFR3 = true;
    FROUT[11] = 0;
    FROUT[8] = 0;
  }

  // FR4
  if (!FROUT[7] == 0 || !FROUT[4] == 0)
  {
    TraffiFR4 = true;
    FROUT[7] = 0;
    FROUT[4] = 0;
  }
}

String FRParserString()
{
  String out = "";
  out += String(TraffiFR1);
  out += String(TraffiFR3);
  out += String(TraffiFR4);
  return out;
}

void FRCheck()
{
  for (int index = 0; index < ELEMENTCOUNT(FR); index++)
  {
    if (digitalRead(FR[index]) == 1 && !FRPressed[index])
    {
      FROUT[index]++;
      FRPressed[index] = true;
    }
    else if (digitalRead(FR[index]) == 0)
    {
      FRPressed[index] = false;
    }
  }
}

String FRCheckString()
{
  String out = "";
  for (int index = 0; index < ELEMENTCOUNT(FR); index++)
  {
    out += String(FROUT[index]);
  }
  return out;
}