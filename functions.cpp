/* 
 * Filename: functions.cpp
 * Author: Zubair Almaghribi
 * Student Number : 10743942
 * Institution: Plymouth University
 * Date: 13/12/2024
 * Description: functions file - encapsulates all the functions used in main.cpp
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

//These objects have already been created for you in uop_msb.h
extern EnvSensor env;
//extern LatchedLED latchedLEDs;
extern SDCard sd;
extern LCD_16X2_DISPLAY disp;
uint32_t sample_num = 0;




terminal trmnl(USBTX,USBRX);

DigitalOut led (PE_2);

DigitalOut Buzzer (PB_13);



Semaphore _measSemaphore(1), _cnsmrSemaphore, _thrshldSemaphore(1);



// declaring an object of type meas to store and manipulate the data

meas d;
StripLEDs leds;


// mutex object for the sd card opertaions
Mutex sd_rw_key;

struct tm* t;

int i;

uint64_t now = 1733544615;

terminal* flush_ptr;

// Mail here saves time and code rather than using explicit semaphores , mail accounts for the consuming and producing of data
// making sure that the consumer does not read an empty data , nor let the producer exceed the availible slots in memmory
Mail<meas, 10> letter;




void sd_write (float t, float p, float l, uint64_t dt){
        // Print the time and date
        time_t time_now = time(NULL);   // Get a time_t timestamp from the RTC
        struct tm* tt;                  // Create empty tm struct
        tt = localtime(&time_now);      // Convert time_t to tm struct using localtime
        printf("%s\n",asctime(tt));     // Print in human readable format
        ++i;
            // store the size of the string to write to the sd card and then create a char array of that size
            long long size = snprintf(nullptr, 0, "\nTemperature:\t%3.1fC\nPressure:\t%4.1fmbar\nLight Level:\t%1.2f\nDate and Time:\t%s\n ", t, p, l, asctime(tt)) + 1;
            char sample[size];
            // now format the text as needed
            snprintf(sample, sizeof(sample), "\nTemperature:\t%3.1fC\nPressure:\t%4.1fmbar\nLight Level:\t%1.2f\nDate and Time:\t%s\n ", t, p, l, asctime(tt));
        if(sd.card_inserted()){
            // aquire the key to the sd card 
            sd_rw_key.lock();
                // first attempt to write to the sd card , and check if it returns -1 ie. error or a 0 ie. no error.
                int err1 = sd.write_file("test2.txt", sample);    // Attempt to write text to file

                if(err1 == 0){   // If is successful, read the content of the file back
                printf("Successfully written to SD card2\n");
                printf("---------------------------\nFile contents:\n");
                //sd.print_file("test2.txt",false);
                printf("---------------------------\n");
                }
                else{
                printf("Error Writing to SD card\n");
                }

            // release the key to the sd card to be used if needed by other threads
            sd_rw_key.unlock();
        }
        else{
            printf("No SD Card Detected\n");
           }
};


void producer_w2Buffer (){

    while (true) {
        _measSemaphore.acquire();
        // declare a pointer of the type measure , this pointer could be used to pass memmory location of measure class data
        // meas * pntr_msr;
        // this allocates memmory for the class "meas" inside the mailbox internal memmory, and passes a ponter to that address to the meas class poniter.
        // think of it like connecting adresses of 2 poniters to pass data.    
        /////////////////// Note: so here if the buffer gets full it is not being handled automatically ///////////////////
        /////////////////// therfore, returns a null pointer. ///////////////////
        /////////////////// so, letter.put(): Can fail and return an error if the message wasn't allocated properly ///////////////////
        // If pntr_msr is nullptr, it means the Mailbox is full, and no new data can be stored.
        meas* pntr_msr = letter.alloc(); 
        if (pntr_msr) {
        printf("Producer: Allocation finished succesfully, key retrieved.\n");
 
        *pntr_msr = d;

        // this passes the meas class address to the mailbox so it could retrieve data
        // and it reyurns some information regarding the process using some mbed APIs
        osStatus status = letter.put(pntr_msr);
            if (status == osOK) {
                printf("Producer: letter successfully sent to mailbox.\n");
                // print out menu after ever case scenario 
                _thresholds(); // check thresholds
                time();
                trmnl.main_menu();
            } else {
                printf("Producer: Failed to put letter in mailbox (status: %d).\n", status);

                // print out menu after ever case scenario 
                _thresholds(); // check thresholds
                time();
                trmnl.main_menu();
                letter.free(pntr_msr); // Free the mail if put fails
            };
        } 
        else{ // for debugging if pntr_msr is null
            printf("Producer: Mailbox is full, Waiting for consumer to retrieve letters.\n");
            _thresholds(); // check thresholds
            time();
            // print out menu after ever case scenario 
            trmnl.main_menu();
        }
    };

        
};


float_t consumer_Buffer2SD () {
    while (true) {    
            _cnsmrSemaphore.acquire();
            while (!letter.empty()) {
                 
                // from the Mbed Studio API Docs.
                // we use letter.get(); , to block the thread until a msg is availible in the buffer
                // osEvent is an Event structure that contains detailed information about an event
                // so here , letter.get() tries to get a letter from the mailbox, and then assigns it to evnt
                // if the operation of retrieving the letter was succeful the next condition would be met
                printf("getting letters from Mailbox\n");
                osEvent evnt  = letter.get(100);
                printf("Consumer: event status: %d\n", evnt.status);

                // here we check the status of our letter retrieving opertaion
                // therfore this condition would be met if a letter was retrieved succesfully by letter.get();
                // if this condition is met, osEvent would be containing a pointer to the retrieved message stored in its value.p field.
                if(evnt.status == osEventMail){
                // change the pointer to the letter in mailbox, into a meas type pointer and connect it to the meas class poniter
                printf("letters were retrieved from the Mailbox succesfully\n");
                meas * pntr_msr = (meas *)evnt.value.p;
                
                sd_write(pntr_msr->temperature , pntr_msr->pressure, pntr_msr->lightlevel, now);
                // print out menu after ever case scenario 
                trmnl.main_menu();
                // free up the allocated memmory in the mailbox
                letter.free(pntr_msr);
                
                }
                else if (evnt.status != osEventMail) { // if for any reason the consumer failed to get the letters it will print a warning
                printf("getting the letters from the Mailbox failed\n");
                // print out menu after ever case scenario 
                trmnl.main_menu();
                ThisThread::sleep_for(std::chrono::milliseconds(1000));
                };
                
            };    
    };
};

void _thresholds () {

            if (d.pressure > 1025) {
                //Buzzer = true;
                buzz.playTone("C");
                //ThisThread::sleep_for(250ms);
                printf("Warning------pressure beyond threshold------Warning\n");
            }
            else if(d.pressure < 1022){ // hysteresis
                //Buzzer = false;
                buzz.rest();
            };
            if (d.temperature > 24) {
                //Buzzer = true;
                buzz.playTone("C");
                //ThisThread::sleep_for(250ms);
                printf("Warning------temp beyond threshold------Warning\n");
            }
            else if(d.temperature < 23){ // hysteresis
                //Buzzer = false;
                buzz.rest();
            };
            if (d.lightlevel> 0.90) {
                //Buzzer = true;
                buzz.playTone("C");
                //ThisThread::sleep_for(250ms);
                printf("Warning------light beyond threshold------Warning\n");    
            }
            else if(d.lightlevel < 0.85){ // hysteresis
                //Buzzer = false;
                buzz.rest();
            
            }
};


void sampling_thread () {
    //using signaling
    while (true) {
        // get the semaphore
        _measSemaphore.acquire();

        sample_num++; // increase the sampling count
        
        // read the data from the sensors
        if(trmnl.sampling == true){
        d.read(env.getTemperature(), env.getPressure(), ldr.read());
        } else if (trmnl.sampling == false) {
        d.read(0, 0, 0); // if sampling was dissabled, set the data to 0 and stop reading sensors
        };

        // release the semaphore for use by other threads
        _measSemaphore.release();

        printf("\n----- Sample %d -----\nTemperature:\t%3.1fC\nPressure:\t%4.1fmbar\nLight Level:\t%1.2f\n", sample_num,d.temperature,d.pressure,d.lightlevel);

    }
};


void terminal_thread() {
    while (true) {

        trmnl.terminalIn(); // get user inputs

    }
}

// this is using signaling for the sampling process , this isr gets processed every 10 seconds by the tikcer interrupt
// sampling thread blocked untill this semaphore has been released
void measurments_tickISR () {
    _measSemaphore.release(); // release first semaphore
};
// this is using signaling with the consumer to retrieve the data from the mailbox , this isr gets processed every 60 seconds by the tikcer interrupt
// consumer thread blocked untill this semaphore has been released
void consumer_tickISR(){
    _cnsmrSemaphore.release();
};

void time ()
{
        time_t time_now = time(NULL);   // Get a time_t timestamp from the RTC
        t = localtime(&time_now);      // Convert time_t to tm struct using localtime
        printf("%s\n",asctime(t));     // Print in human readable format
}


void lcd (){


        // Write the time and date on the LCD
        disp.cls();                     // Clear the LCD                 
        char lcd_line_buffer[17];           
        
        strftime(lcd_line_buffer, sizeof(lcd_line_buffer), "%a %d-%b-%Y", t);  // Create a string DDD dd-MM-YYYY
        disp.locate(0,0);                                                       // Set LCD cursor to (0,0)
        disp.printf("%s",lcd_line_buffer);                                      // Write text to LCD
        
        strftime(lcd_line_buffer, sizeof(lcd_line_buffer), "     %H:%M", t);   // Create a string HH:mm
        disp.locate(1,0);                                                       // Set LCD cursor to (0,0)
        disp.printf("%s",lcd_line_buffer);        
                                     // Write text to LCD


}