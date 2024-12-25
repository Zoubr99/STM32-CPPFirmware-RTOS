#ifndef _FUNCTIONS_H_INCLUDED
#define _FUNCTIONS_H_INCLUDED

#include "mbed.h"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include "terminal.hpp"


void sd_write(float t, float p, float l, uint64_t dt);


float_t consumer_Buffer2SD (void);
void producer_w2Buffer (void);

void sampling_thread ();

void terminal_thread();

void measurments_tickISR ();
void consumer_tickISR();

void _thresholds();

void time ();

void lcd ();

#endif