////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Template Project 
//** NAME: XXXX
//** RIN: XXXX
//** This is the base project for several activities and labs throughout
//** the course.  The outline provided below isn't necessarily *required*
//** by a C program; however, this format is required within ENGR-2350
//** to ease debugging/grading by the staff.
////////////////////////////////////////////////////////////////////////

#include "engr2350_msp432.h"
#include "lab1lib.h"

void GPIOInit();
void TestIO();
void ControlSystem();

uint8_t LEDFL = 0; // Two variables to store the state of
uint8_t LEDFR = 0; // the front left/right LEDs (on-car)
uint8_t BMP0;
uint8_t BMP1;
uint8_t BMP2;
uint8_t BMP3;
uint8_t BMP4;
uint8_t BMP5;
int main(void) {    /** Main Function ****/

    SysInit(); // Basic car initialization
    init_Sequence(); // Initializes the Lab1Lib Driver
    GPIOInit();

    printf("\r\n\n"
           "===========\r\n"
           "Lab 1 Start\r\n"
           "===========\r\n");

    while(1) {
        TestIO(); // Used in Part A to test the IO
        //ControlSystem(); // Used in Part B to implement the desired functionality
    }
}    /** End Main Function ****/

void GPIOInit() {
    P4DIR &= 0xFD;
    GPIO_setAsInputPin( GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    P6DIR |= 0x03;
    GPIO_setAsOutputPin( GPIO_PORT_P6, GPIO_PIN0 | GPIO_PIN1 );
    P8DIR |= 0x21;
    GPIO_setAsOutputPin( GPIO_PORT_P8, GPIO_PIN0 | GPIO_PIN5 );
    P3DIR |= 0b11000000;
    GPIO_setAsOutputPin( GPIO_PORT_P3, GPIO_PIN6 | GPIO_PIN7 );

}

void TestIO() {
    // Add printf statement(s) for testing inputs

    // Example code for testing outputs
    while(1){
        uint8_t cmd = getchar();
        if(cmd == 'a'){
            P8OUT |= 0x01;
        printf("LEDFL is on.\r\n");
        }else if(cmd == 'z'){
            P8OUT &= ~0x01;
            printf("LEDFL is off. \r\n");
        }else if(cmd == 's'){
            P8OUT |= 0x20;
            printf("LEDFR is on.\r\n");
        }else if(cmd == 'x'){
            P8OUT &= ~0x20;
            printf("LEDFR is off.\r\n");
        }else if(cmd == 'q'){
            P6OUT |= 0x01;
            P6OUT &= ~0x02;
            printf("BiLED is red.\r\n");
        }else if(cmd == 'e'){
            P6OUT |= 0x02;
            P6OUT &= ~0x01;
            printf("BiLED is green.\r\n");
        }else if(cmd == 'w'){
              P6OUT &= ~0x03;
              printf("BiLED is off.\r\n");
        }

    }
}

void ControlSystem() {

}
