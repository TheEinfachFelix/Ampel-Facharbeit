#include "interface.h"
#include <Arduino.h>

#define ELEMENTCOUNT(x)  (sizeof(x) / sizeof(x[0]))
//dekleration
void TasterParser();
String TasterParserString();
void TasterCheck();
String TasterCheckString();
void TasterRset();



void setup() {
  Serial.begin(9600);
// output pins klug Definieren
for(int index = 0; index < ELEMENTCOUNT(Lampen); index++){
    pinMode(Lampen[index], OUTPUT);
  };
for(int index = 0; index < ELEMENTCOUNT(Detect); index++){
    pinMode(Detect[index], OUTPUT);
  };


for(int index = 0; index < ELEMENTCOUNT(DetectPressed); index++){
    DetectPressed[index] = false;
    DetectOUT[index] = 0;
  };

  Serial.println("OK Lets go!");
}

void loop() {
  //TasterCheck();
  //Serial.println(TasterCheckString());
  //TasterParser();
  //Serial.println(TasterParserString());

      
    setK4(true);    
    setK4(true);
    setK4(true);

    setK4(false);
    setK4(false);
    setK4(false);


  //Serial.println(goTimeK4);  
  //Serial.println(statK4);
  //Serial.println(millis());
  
}
void TasterParser(){
      //K1
  if (!DetectOUT[0] == 0){
    TraffiK1 += DetectOUT[0];
    DetectOUT[0] = 0;
  };  //K3
  if (!DetectOUT[11] == 0){
    TraffiK3 += DetectOUT[11];
    DetectOUT[11] = 0;
  };  //K4
  if (!DetectOUT[1] == 0){
    TraffiK4 += DetectOUT[1];
    DetectOUT[1] = 0;
  };
}
String TasterParserString(){
  String out = "";
  out += String(TraffiK1);
  out += String(TraffiK3);
  out += String(TraffiK4);
  return out;
}


// hier noch halt und push detektion hinzufügen
void TasterCheck(){
  for(int index = 0; index < ELEMENTCOUNT(Detect); index++){
    if (digitalRead(Detect[index]) == 1  && !DetectPressed[index]) {
      DetectOUT[index] ++;
      DetectPressed[index] = true;
    };
    if (!digitalRead(Detect[index]) == 1) {
      DetectPressed[index] = false;
    }
  }; 
};
String TasterCheckString(){
  String out = "";
  for(int index = 0; index < ELEMENTCOUNT(Detect); index++){
    out += String(DetectOUT[index]);
  };
  return out;
};
void TasterRset(){
    for(int index = 0; index < ELEMENTCOUNT(Detect); index++){
    DetectOUT[index] = 0;
  };
}
