/* 
 * Filename: meas.cpp
 * Author: Zubair Almaghribi
 * Institution: Plymouth University
 * Date: 13/12/2024
 * Description: measurments file - a class for the sampled data
 * 
 * Notes:
 *
 * For documentation regarding the use of the code please go back to the readme file
 *
 * You will need to set the module support board version that you have in MSB_Config.h
 * The default if V4. If you are using a V2 comment out "#define MSB_VER 4" and uncomment "#define MSB_VER 2"
 * 
 * 
 */

#include "meas.hpp"

    void meas::read (float t, float p, float l) {
        temperature = t;
        pressure = p;
        lightlevel = l;
    }


