#ifndef _STRIPLEDS_H_INCLUDED
#define _STRIPLEDS_H_INCLUDED

#include "meas.hpp"
#include "uop_msb.h"

extern meas d;

class StripLEDs {

    private:


    public:


        // constructur, when an object is created it initializes all the member variables to 0
        StripLEDs();

        // 24 levels quantizations
        float t_buff[24] = {0.00, 1.39, 2.78, 4.17, 5.57, 6.96, 8.35, 9.74,
                            11.13, 12.52, 13.91, 15.30, 16.70, 18.09, 19.48, 20.87,
                            22.26, 23.65, 25.04, 26.43, 27.83, 29.22, 30.61, 32.00};

        float p_buff[24] = {1000.00, 1001.30, 1002.61, 1003.91, 1005.22, 1006.52, 1007.83, 1009.13,
                            1010.43, 1011.74, 1013.04, 1014.35, 1015.65, 1016.96, 1018.26, 1019.57,
                            1020.87, 1022.17, 1023.48, 1024.78, 1026.09, 1027.39, 1028.70, 1030.00};

        float l_buff[24] = {0.00, 0.04, 0.09, 0.13, 0.17, 0.22, 0.26, 0.30,
                            0.35, 0.39, 0.43, 0.48, 0.52, 0.57, 0.61, 0.65,
                            0.70, 0.74, 0.78, 0.83, 0.87, 0.91, 0.96, 1.00};

        // used for comparisons
        float generic_buff[24];


        void StripControl(char input);
};


#endif