// (c) 2020 University of Plymouth
// Nicholas Outram
// nicholas.outram@plymouth.ac.uk
//
//
// Added support for SPL06-001 environmental sensor
// updated 14 09 2021

#ifndef __UOP_MSB__
#define __UOP_MSB__

#include "MSB_Config.h"
#include "Buttons.h"
#include "LatchedLED.h"
#include "Buzzer.h"
#include "LCD.h"
#include "EnvSensor.h"
#include "MotionSensor.h"
#include "MSB_Utils.h"
#include "Matrix.h"
#include "TrafficLights.h"


// SD Card (RTOS ONLY)
//#ifdef USE_SD_CARD  //RTOS Only
#include "SDCard.h"
extern SDCard sd;//(SD_MOSI,SD_MISO,SD_SCLK,SD_CS,SD_DETECT);


// Precreated library objects for you to use
extern AnalogIn pot;//(AN_POT_PIN);
extern AnalogIn ldr;// (AN_LDR_PIN);
extern AnalogIn signal_in ;//(BNC_AN_PIN);
extern AnalogIn mic ;//(MIC_AN_PIN);
extern AnalogOut dac_out_1 ;//(DAC1_AN_PIN);
extern AnalogOut dac_out_2 ;//(DAC2_AN_PIN);
extern LatchedLED latchedLEDs;//(LEDMODE::STRIP);     
extern Buttons buttons;
extern LCD_16X2_DISPLAY disp;
extern EnvSensor env;// (ENV_MOSI,ENV_MISO,ENV_SCLK,ENV_CS);
extern Buzzer buzz;
extern DIPSwitches dipSwitches ;//(DIP0_PIN,DIP1_PIN,DIP2_PIN,DIP3_PIN);
extern MotionSensor motion ;//(MEMS_SDA,MEMS_SCL,MEMS_FREQ);
extern Matrix matrix ;//(MATRIX_MOSI,MATRIX_MISO,MATRIX_SCLK,MATRIX_CS,MATRIX_OE);
extern TrafficLights traffic;//(TRAF_RED1_PIN,TRAF_YEL1_PIN,TRAF_GRN1_PIN,TRAF_RED2_PIN,TRAF_YEL2_PIN,TRAF_GRN2_PIN,TRAF_WHITE_PIN);
#endif
