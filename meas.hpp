#ifndef _MEAS_H_INCLUDED
#define _MEAS_H_INCLUDED

class meas {

    private:


    public:

    float temperature;
    float pressure;
    float lightlevel;
        // constructur, when an object is created it initializes all the member variables to 0
        meas() : temperature(0), pressure(0), lightlevel(0) {}
        // member function that takes the readings from the specified inputs.
        void read (float t, float p, float l);
};


#endif