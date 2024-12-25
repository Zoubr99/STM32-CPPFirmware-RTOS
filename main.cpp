/* 
 * Filename: main.cpp
 * Author: Zubair Almaghribi
 * Student Number: 10743942
 * Institution: Plymouth University
 * Date: 13/12/2024
 * Description: ELEC351 Coursework 24/25
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

#include "functions.hpp"
extern terminal trmnl;
// ticker for a timed interupt to check sensor's readings
Ticker _measTicker, _cnsmrTicker, _trshldTicker;
extern Semaphore _cnsmrSemaphore;
// declaring object of type Thread to be used when writing to an sd card
Thread prod(osPriorityHigh6), cons, sampling(osPriorityHigh7), term;
extern struct tm* t;
extern uint64_t now;

int main()
{
    // Set output enable on the latched LEDs.
    latchedLEDs.enable(true);
    // Set the time on the RTC (You can use https://www.epochconverter.com/ for testing) 
    set_time(now);

    prod.start(producer_w2Buffer);
    cons.start(consumer_Buffer2SD);
    sampling.start(sampling_thread);
    term.start(terminal_thread);

    _measTicker.attach(&measurments_tickISR, 10000ms);
    _cnsmrTicker.attach(&consumer_tickISR, 60000ms);

    while (true) {
        // since there are no restrictions in the main thread it better to be used for the menu functions and some extra features
        if(trmnl.flush == true){_cnsmrSemaphore.release(); trmnl.flush = false;};
        lcd();
        
    }
}
