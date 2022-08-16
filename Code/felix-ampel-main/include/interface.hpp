#pragma once

#include <inttypes.h>

extern const uint8_t Lampen[16];

void setK4(bool out);
void setK3(bool out);
void setK1(bool out);

void setPfeil(bool inp);

void setFR4(bool inp);
void setFR3(bool inp);
void setFR1(bool inp);

bool getFR3();
bool getFR1();

bool getDoneK4();
bool getDoneK3();