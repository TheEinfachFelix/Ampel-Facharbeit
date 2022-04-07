#include <Arduino.h>

const char Lampen[16] = {2,3,4,5,6,7,8,9,A0,A1,A2,A3,A4,A5,A6,A7};
const char Detect[17] = {53,52,51,50,49,48,47,46,45,43,41,39,37,35,33,31,29};

const int SchaltZeit = 300;

int DetectOUT[17] = {};
bool DetectPressed[17] = {};

int TraffiK1 = 0;
int TraffiK3 = 0;
int TraffiK4 = 0;
