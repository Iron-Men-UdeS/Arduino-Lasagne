#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>

void initUART1(void);
bool litUART1(uint8_t *trame, uint8_t sizeTrame);
void envoieTrameUART1(uint8_t *trame);

void initUART2(void);
bool litUART2(uint8_t *trame, uint8_t sizeTrame);
void envoieTrameUART2(uint8_t *trame);

#endif
