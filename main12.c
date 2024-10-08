////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Lab 2
//** NAME: Andrii Bonenberger
//** RIN: 662051521
//** This is the base project for several activities and labs throughout
//** the course.  The outline provided below isn't necessarily *required*
//** by a C program; however, this format is required within ENGR-2350
//** to ease debugging/grading by the staff.
////////////////////////////////////////////////////////////////////////

// We'll always add this include statement. This basically takes the
// code contained within the "engr_2350_msp432.h" file and adds it here.
#include "engr2350_msp432.h"

// Add function prototypes here as needed.
void Timer1Init();
void GPIOInit();
void GetInputs();
void BMPLogic();
void game();
void timeInc();
void timer();
// Add global variables here as needed.
Timer_A_UpModeConfig clock;
uint8_t PB1;
uint8_t BMP0;
uint8_t BMP1;
uint8_t BMP2;
uint8_t BMP3;
uint8_t BMP4;
uint8_t BMP5;
uint8_t array[10];
uint8_t BMPs[];
uint8_t game_end = 1;
uint8_t counter = 0; //time counter


int main( void ) {    /** Main Function ****/
    // We always call the SysInit function first to set up the 
    // microcontroller for how we are going to use it.
    SysInit();
    int i;
        for(i = 0;i<10;i++){
            array[i] = rand()%6;
            printf("value = %u , i = %u\r\n",array[i],i);//debug to figure out whether the list of the patterns is working correctly
        }
    // Place initialization code (or run-once) code here

    GPIOInit();
    Timer1Init();
    printf("Wait for lighting sequence to end and match the lights to the associated bumber \r\f");
        while( 1 ) {
            // Place code that runs continuously in here

            GetInputs();

            if(PB1==0){
                BMPLogic();
            }else{
                game_end = 1;
                game();
        }
    }
}    /** End Main Function ****/   

// Add function declarations here as needed
void Timer1Init() {
    clock.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    clock.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
    clock.timerPeriod = 3750; // if I understand it correctly this should count once cycle 1/100 a second (10ms)

    Timer_A_configureUpMode(TIMER_A0_BASE,&clock); // Apply the configuration
    Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);
}


void GPIOInit(){
    //P2DIR |= 0x06; // this is the same as line below minus the pin0
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN0 | GPIO_PIN2);
    //P4DIR &= 0xFD;  // this is the same as the line below
    GPIO_setAsInputPinWithPullUpResistor( GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN6);
}


void GetInputs(){
    BMP0 = GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN0);
    BMP1 = GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN2);
    BMP2 = GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN3);
    BMP3 = GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN5);
    BMP4 = GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN6);
    BMP5 = GPIO_getInputPinValue(GPIO_PORT_P4,GPIO_PIN7);
    PB1  = GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN6);
}


void BMPLogic(){
    if (BMP0 != 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
    }else if(BMP1 != 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
    }else if(BMP2 != 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
    }else if(BMP3 != 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
    }else if(BMP4 != 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
    }else if(BMP5 != 1){
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
    }else{

        GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
    }
}
void timer(ms){
    uint8_t tm = 0;
    while((tm*10) <= ms){ //while the internal counter is less than the desired time, done this way so that we can still update the global timer in case we want to use it
        timeInc();
        tm++;
    }
}

void game(){
    uint8_t j;
    uint8_t k;
    while (game_end){
        for(j = 0; j<10 ; j++){     //for all the 10 members of the array
            if (!game_end){break;}    //terminating the main loop if the nested loop signals that the game was lost

                for(k =0; k<j;k++){ // for all members of array with max length j
                 if(array[k] == 0){ //red
                     GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);    //turn red
                     timer(500); // 500 ms timer before turning lights off
                     GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 ); // turn the light off
                 }
                 else if(array[k] == 1){ //green
                     GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
                     timer(500);
                     GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                 }

                else if(array[k] == 2){  //blue
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
                    timer(500);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                }

                else if(array[k] == 3){    //yellow
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
                    timer(500);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);
                }

                else if(array[k] == 4){    //pink
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
                    timer(500);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                }

                else if(array[k] == 5){    //cyan
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
                    timer(500);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );

                }
                 timer(500);//500 ms timer after turning the lights off but before turning the next set of lights on
            }
            uint8_t input;
            uint8_t finish;
            for(k =0; k<j;k++){
                input = 10; //I wasn't sure if it starts as null or 0 so I just set it to a value that is not one of the inputs
                finish = 0;
                counter = 0;
                while ((counter <=300) && !finish) {
                    timeInc();
                    GetInputs();
                    if (BMP0 != 1){
                            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);  //all of these need to have a mechanism to turn the lights off after either 3 seconds or when you release
                            input = 0;
                            while(!BMP0 && game_end){ //while game is still active and button pressed
                                GetInputs();//makes sure BMP is still pressed by updating the registers
                                timeInc(); //increases timer every 10ms
                                if (counter >= 300){ // if more than 3 seconds passed
                                    game_end = 0;
                                }
                            }
                            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );//turns the lights off after the button is released

                        }else if(BMP1 != 1){
                            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
                            input = 1;
                            while(!BMP1 && game_end){ //while game is still active and button pressed
                                GetInputs();//makes sure BMP is still pressed by updating the registers
                                timeInc(); //increases timer every 10ms
                                if (counter >= 300){ // if more than 3 seconds passed
                                    game_end = 0;
                                    }
                            }
                            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );//turns the lights off after the button is released

                        }else if(BMP2 != 1){
                            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
                            input = 2;
                            while(!BMP2 && game_end){ //while game is still active and button pressed
                                GetInputs();//makes sure BMP is still pressed by updating the registers
                                timeInc(); //increases timer every 10ms
                                if (counter >= 300){ // if more than 3 seconds passed
                                    game_end = 0;
                                    }
                            }
                            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );//turns the lights off after the button is released


                        }else if(BMP3 != 1){
                            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
                            input = 3;
                            while(!BMP3 && game_end){ //while game is still active and button pressed
                                GetInputs();//makes sure BMP is still pressed by updating the registers
                                timeInc(); //increases timer every 10ms
                                if (counter >= 300){ // if more than 3 seconds passed
                                    game_end = 0;
                                    }
                            }
                            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );//turns the lights off after the button is released


                        }else if(BMP4 != 1){
                            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
                            input = 4;
                            while(!BMP4 && game_end){ //while game is still active and button pressed
                                GetInputs();//makes sure BMP is still pressed by updating the registers
                                timeInc(); //increases timer every 10ms
                                if (counter >= 300){ // if more than 3 seconds passed
                                    game_end = 0;
                                    }
                            }
                            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );//turns the lights off after the button is released


                        }else if(BMP5 != 1){
                            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
                            input = 5;
                            while(!BMP5 && game_end){ //while game is still active and button pressed
                                GetInputs();//makes sure BMP is still pressed by updating the registers
                                timeInc(); //increases timer every 10ms
                                if (counter >= 300){ // if more than 3 seconds passed
                                    game_end = 0;
                                    }
                            }
                            GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );//turns the lights off after the button is released
                        }

                     if((array[k] == input)){
                         finish = 1;
                     }else if(input != 10){
                        game_end = 0;
                        printf("You lost, skill issue, your score is %u \n\r",j);
                        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);//set the light to red
                        break;
                }
            }}
        }
    }
}

void timeInc(){  // increments the counter every 10 ms when its being called actively
    if(Timer_A_getEnabledInterruptStatus(TIMER_A0_BASE) == TIMER_A_INTERRUPT_PENDING){
            Timer_A_clearInterruptFlag(TIMER_A1_BASE);
            counter++;
    }

}
// Add interrupt functions last so they are easy to find
