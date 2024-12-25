/* 
 * Filename: terminal.cpp
 * Author: Zubair Almaghribi
 * Student Number : 10743942
 * Institution: Plymouth University
 * Date: 13/12/2024
 * Description: terminal file - a class for configuring the terminal inputs and processing them 
 *                                  configures the : Date and Time, LEDs, sampling off and on, flushing to sd card.
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

#include "terminal.hpp"
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "StripLEDs.hpp"



terminal::terminal (PinName tx, PinName rx) : serial_terminal(tx,rx,9600){

    serial_terminal.set_blocking(true);

};



char terminal::main_menu (){

    int buffer = inBuffer- 48;

// create a pointer to point to a buffer location in memmory to write to terminal from
char *port_out ="\r\n--- Menu ---\r\n"
                "1. Edit Date and Time - [dd/mm/yy hh:mm:ss] \r\n"
                "2. Flush - Write all samples to the SD card\r\n"
                "3. select [x] - Set parameter for LED strip where x :\r\n"
                "  -  'T' for Temperature \r\n"
                "  -  'P' for pressure \r\n"
                "  -  'L' for Light \r\n"
                "4. Sampling [x] - where 'x' is 'on' or 'off' sampling\r\n";;
    if(inBuffer == 0){ // if the user input buffer was empty , print out main menu otherwise print last menu user chose
    serial_terminal.write(port_out,strlen(port_out));
    } else {
        switch(buffer){ // this case statment is used to keep displaying the sub menu

        case 1:
        printf("Enter date and time in the following format - [dd/mm/yy hh:mm:ss]\r\n");
    
        printf("D&T: %02d/%02d/%04d %02d:%02d:%02d\n", mday, mon, year, hour, min, sec);

        break;

        case 2:
        break;

        case 3:
        printf("Enter 't' for temperature\r\n");
        printf("Enter 'p' fore pressure\r\n");
        printf("Enter 'l' for ligh\r\n");
        break;

        case 4:
        printf("Enter 'e' to enable sampling or 'd' to disable it\r\n");
        break;

        };
    };
    return *port_out;
};
struct tm tt;
float terminal::command_processing (char command, char sub_command) {

    //bool flush;
    int com = command;
    com = com - 48;
    printf("you chose %c\r\n",com);
    switch(com){

        case 1: 
            //serial_terminal.write(d_t,strlen(d_t));
            printf("Enter date and time in the following format - [dd/mm/yy hh:mm:ss]\r\n");
            
            //int index;
            while (true) {
                    if (scanf("%02d/%02d/%04d %02d:%02d:%02d", &mday, &mon, &year, &hour, &min, &sec) == 6) {
                                              // Create empty tm struct
                            tt.tm_mday = mday;
                            tt.tm_mon = mon -1;
                            tt.tm_year = year - 1900;
                            tt.tm_hour = hour;
                            tt.tm_min = min;
                            tt.tm_sec = sec;
                            set_time(mktime(&tt)); // Set RTC with the time value
                            printf("Date and time set to: %02d/%02d/%04d %02d:%02d:%02d\n", mday, mon, year, hour, min, sec);
                            inBuffer = 0;
                            break;
                    } else {
                    printf("Invalid input format.\n");
                    break;
                    }       
            };
            inBuffer = 0;
            break;
        case 2:
            printf("Flushing all samples to sd card\r\n");
            // logic fur flushing
            // easiest way is to release the consumer semaphore.
            flush = true;
            inBuffer = 0;
            break;
        case 3:
            //serial_terminal.write(t_p_l,strlen(t_p_l));
            printf("Enter 't' for temperature\r\n");
            printf("Enter 'p' fore pressure\r\n");
            printf("Enter 'l' for light\r\n");
            char t_p_l;
                if (serial_terminal.read(&t_p_l, 1) == 1) {
                    // Echo the character back to the terminal
                    serial_terminal.write(&t_p_l, 1);

                    if (t_p_l == 't') {
                        printf("\nYou entered: %c\n", t_p_l);
                        leds.StripControl(t_p_l);
                        inBuffer = 0;
                        break;
                    }
                    else if (t_p_l == 'p') {
                        printf("\nYou entered: %c\n", t_p_l);
                        leds.StripControl(t_p_l);
                        inBuffer = 0;
                        break;
                    }
                    else if (t_p_l == 'l') {
                        printf("\nYou entered: %c\n", t_p_l);
                        leds.StripControl(t_p_l);
                        inBuffer = 0;
                        break;
                    }
                    else { // keep recieving inputs
                        printf("\nInvalid input\n");
                        inBuffer = 0;
                        break;
                    }
                }
            inBuffer = 0;
            break;
        case 4:
            //serial_terminal.write(dis_sampling,strlen(dis_sampling));
            printf("Enter 'e' to enable sampling or 'd' to disable it\r\n");
            char dis_sampling;
            if (serial_terminal.read(&dis_sampling, 1) == 1) {
                    // Echo the character back to the terminal
                    serial_terminal.write(&dis_sampling, 1);

                    if (dis_sampling == 'e') {
                        printf("\nYou entered: %c, Sampling enabled\n", dis_sampling);
                        // logic for enabling the sampling
                        // same as the flush logic
                        sampling = true;
                        inBuffer = 0;
                        break;
                    }
                    else if (dis_sampling == 'd') {
                        printf("\nYou entered: %c, Sampling disabled\n", dis_sampling);
                        // logic for disabling the sampling
                        // same as the flush logic
                        sampling = false;
                        inBuffer = 0;
                        break;
                    }
                    else { // keep recieving inputs
                        printf("\nInvalid input\n");
                        inBuffer = 0;
                        break;
                    }
                }
            inBuffer = 0;
            break;
        default:
            printf("invalid choice, please choose a number between 1 and 4\r\n");
            inBuffer = 0;
            break;
    }
    inBuffer = 0;
    return 0;
};


char terminal::terminalIn () {

// give the pointer address as an arg + the number of bytes to read as the second arg 1 = 8 bits
serial_terminal.read(&inBuffer, 1);
printf("%c\r\n",inBuffer);
    
    command_processing(inBuffer, 0);
        return inBuffer - 48 ;
        //inBuffer = 0;

};
