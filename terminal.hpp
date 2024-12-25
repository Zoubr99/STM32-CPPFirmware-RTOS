#ifndef _TERMINAL_H_INCLUDED
#define _TERMINAL_H_INCLUDED

#include "mbed.h"
#include "StripLEDs.hpp"

extern StripLEDs leds;


class terminal {

    private:

        UnbufferedSerial serial_terminal;
        

    public:
    
    bool flush;
    bool sampling;

    terminal(PinName tx,PinName rx);

    char main_menu ();

    // create a poniter to point to the inputs storing buffer 
    char inBuffer; // single char input buffer used in terminal in 

    

    int mday, mon, year, hour, min, sec;

    float command_processing (char command, char sub_command);


    char terminalIn ();
    int iterminalIn ();
};


#endif