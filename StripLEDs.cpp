/* 
 * Filename: StripLEDs.cpp
 * Author: Zubair Almaghribi
 * Student Number : 10743942
 * Institution: Plymouth University
 * Date: 13/12/2024
 * Description: StripLEDs file - a class for configuring the strip leds based on the 10 seconds samples of data
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


#include "StripLEDs.hpp"

StripLEDs::StripLEDs() {}




void StripLEDs::StripControl(char input) {


float lvl;
        // depending on the input assign the corresponding array to the placeholder buffer, generic buffer
        switch (input) {
            
        case 'l':
        lvl = d.lightlevel;
        memcpy(generic_buff, l_buff, sizeof(l_buff)); // copying the light buffer values to the generic one, so it could then be used for
        break;                                        // comparisons

        case 't':
        lvl = d.temperature;
        memcpy(generic_buff, t_buff, sizeof(t_buff)); // copying the temperature buffer values to the generic one, so it could then be used for
        break;                                        // comparisons

        case 'p':
        lvl = d.pressure;
        memcpy(generic_buff, p_buff, sizeof(p_buff)); // copying the pressure buffer values to the generic one, so it could then be used for
        break;                                        // comparisons

        };

                        if (lvl < generic_buff[0]) { // depending on the user input the lvl will store the sampling values and turn leds on accordingly 
                        latchedLEDs.write_strip(0x00,RED);
                        }
                        else if (lvl > generic_buff[0] && lvl < generic_buff[1]) {
                        latchedLEDs.write_strip(0x01,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[1] && lvl < generic_buff[2]) {
                        latchedLEDs.write_strip(0x03,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }
                        else if (lvl > generic_buff[2] && lvl < generic_buff[3]) {
                        latchedLEDs.write_strip(0x07,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }
                        else if (lvl > generic_buff[3] && lvl < generic_buff[4]) {
                        latchedLEDs.write_strip(0x0F,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }                        
                        else if (lvl > generic_buff[4] && lvl < generic_buff[5]) {
                        latchedLEDs.write_strip(0x1F,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }
                        else if (lvl > generic_buff[5] && lvl < generic_buff[6]) {
                        latchedLEDs.write_strip(0x3F,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }                        
                        else if (lvl > generic_buff[6] && lvl < generic_buff[7]) {
                        latchedLEDs.write_strip(0x7F,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }
                        else if (lvl > generic_buff[7] && lvl < generic_buff[8]) {
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,GREEN);
                        latchedLEDs.write_strip(0x00,BLUE);                        
                        }
                        else if (lvl > generic_buff[8] && lvl < generic_buff[9]) {
                        latchedLEDs.write_strip(0x01,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[9] && lvl < generic_buff[10]) {
                        latchedLEDs.write_strip(0x03,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[10] && lvl < generic_buff[11]) {
                        latchedLEDs.write_strip(0x07,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[11] && lvl < generic_buff[12]) {
                        latchedLEDs.write_strip(0x0F,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[12] && lvl < generic_buff[13]) {
                        latchedLEDs.write_strip(0x1F,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }                        
                        else if (lvl > generic_buff[13] && lvl < generic_buff[14]) {
                        latchedLEDs.write_strip(0x3F,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[14] && lvl < generic_buff[15]) {
                        latchedLEDs.write_strip(0x7F,RED);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }                        
                        else if (lvl > generic_buff[15] && lvl < generic_buff[16]) {
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x00,BLUE);
                        }
                        else if (lvl > generic_buff[16] && lvl< generic_buff[17]) {
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        latchedLEDs.write_strip(0x01,BLUE);
                        }
                        else if (lvl > generic_buff[17] && lvl < generic_buff[18]) {
                        latchedLEDs.write_strip(0x03,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        }
                        else if (lvl > generic_buff[18] && lvl < generic_buff[19]) {
                        latchedLEDs.write_strip(0x07,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        }
                        else if (lvl > generic_buff[19] && lvl < generic_buff[20]) {
                        latchedLEDs.write_strip(0x0F,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);  
                        }
                        else if (lvl > generic_buff[20] && lvl < generic_buff[21]) {
                        latchedLEDs.write_strip(0x1F,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);                      
                        }
                        else if (lvl > generic_buff[21] && lvl < generic_buff[22]) {
                        latchedLEDs.write_strip(0x3F,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        }
                        else if (lvl > generic_buff[22] && lvl < generic_buff[23]) {
                        latchedLEDs.write_strip(0x7F,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        }
                        else if(lvl > generic_buff[23]) {
                        latchedLEDs.write_strip(0xFF,BLUE);
                        latchedLEDs.write_strip(0xFF,GREEN);
                        latchedLEDs.write_strip(0xFF,RED);
                        }                    
};
