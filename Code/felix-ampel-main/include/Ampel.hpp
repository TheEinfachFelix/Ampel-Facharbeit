#pragma once

#include <Arduino.h>

#define ELEMENTCOUNT(x) (sizeof(x) / sizeof(x[0]))

// Taster Analyse und Auswertung
void TasterCheck();
String TasterParserString();
void TasterParser();
String TasterCheckString();

// FR
void FRParser();
String FRParserString();
void FRCheck();
String FRCheckString();

// logic
void TimingSet();

void Flush();