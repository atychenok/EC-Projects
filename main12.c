////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Lab 2
//** NAME: Jourdon Willett
//** RIN: 662058549
//** This is the base project for several activities and labs throughout
//** the course.  The outline provided below isn't necessarily *required*
//** by a C program; however, this format is required within ENGR-2350
//** to ease debugging/grading by the staff.
////////////////////////////////////////////////////////////////////////

// We'll always add this include statement. This basically takes the
// code contained within the "engr_2350_msp432.h" file and adds it here.
#include "engr2350_msp432.h"

// Add function prototypes here as needed.
//void TimerInit();
void GPIOInit();
void GetInputs();
void BMPLogic();
// Add global variables here as needed.

Timer_A_UpModeConfig timerconfig;

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


void game(){
    uint8_t j;
    uint8_t k;
    while (game_end){
        for(j = 0; j<10 ; j++){     //for all the 10 members of the array
            if (game_end == 0){    //terminating just in case
                break;
            }
                for(k =0; k<j;k++){ // for all members of array with max length j
                                                      //all of these need a timer after color setting but before turning off
                 if(array[k] == 0){ //red
                     GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);    //turn red
                     
                     GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 ); // turn the light off
                
                     
                 }else if(array[k] == 1){ //green                     
                     GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);

                     GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                 }
                         
                else if(array[k] == 2){  //blue            
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
        
                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                }
                
                else if(array[k] == 3){    //yellow      
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);

                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2);
                }
                
                else if(array[k] == 4){    //pink                 
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);

                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                }
                
                else if(array[k] == 5){    //cyan             
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);

                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0|GPIO_PIN1|GPIO_PIN2 );
                
                }
 
        }for(k =0; k<j;k++){
            GetInputs();
            uint8_t input;
            if (BMP0 != 1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);  //all of these need to have a mechanism to turn the lights off after either 3 seconds or when you release
                    input = 0;
                    
                }else if(BMP1 != 1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
                    input = 1;
                }else if(BMP2 != 1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
                    input = 2;
                }else if(BMP3 != 1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
                    input = 3;
                }else if(BMP4 != 1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
                    input = 4;
                }else if(BMP5 != 1){
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
                    input = 5;
                }
               }
             if(array[k] == input){
                 
            }else{
            game_end = 0; 
            printf("You lost, skill issue, your score is %u \n\r",j)
            break;
            }
            }
        }
        
        
    }
    
    
    

}

int main( void ) {    /** Main Function ****/
  
    // Add local variables here as needed.

    // We always call the SysInit function first to set up the 
    // microcontroller for how we are going to use it.
    SysInit();
    int i;
    for(i = 0;i<10;i++){
        array[i] = rand()%6 ;
        printf("value = %u , i = %u\r\n",array[i],i);
    }
    // Place initialization code (or run-once) code here
    GPIOInit();
//    TimerInit();

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
//void TimerInit() {
//    timer.clocksource = TIMER_A_CLOCKSOURCE_SMCLK;
//}

void GPIOInit(){
    P2DIR |= 0x06;
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN0 | GPIO_PIN2);
    P4DIR &= 0xFD;
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
// Add interrupt functions last so they are easy to find
