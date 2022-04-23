/*
 * File:   main.c
 * Author: Atzu2
 *
 * Created on March 29, 2022, 1:32 PM
 */


#include <xc.h>
#include <math.h>
#include "device_config.h"
//+++++++++++++++++++++++++++++++++++++| DIRECTIVES |+++++++++++++++++++++++++++++++++++++
#define _XTAL_FREQ 1000000
#define DELAYFIVE 500
#define DELAYTWO 250
#define DELAY 300

//+++++++++++++++++++++++++++++++++++++| DATA TYPES |+++++++++++++++++++++++++++++++++++++
enum exponent {bbase=2, limit=8};
enum por_dir{ output, input };              // output = 0, input = 1
enum por_ACDC { digital, analog };          // digital = 0, analog = 1
enum resistor_state { set_ON, res_ON };     // set_ON = 0, res_ON = 1
enum led_state { led_OFF, led_ON };         // led_OFF = 0, led_ON = 1
enum butto_state { pushed, no_pushed };     // pushed = 0, no_pushed = 1
unsigned char molePosition, buttonStatus, LED_rand;
int i;


//+++++++++++++++++++++++++++++++++++++| ISRs |+++++++++++++++++++++++++++++++++++++
// ISR for high priority
void __interrupt ( high_priority ) high_isr( void );
// ISR for low priority
void __interrupt ( low_priority ) low_isr( void ); 

//+++++++++++++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++++++++++++++++++++++++
void portsInit( void );


//+++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++
void main( void ){
    portsInit();
    //variable con el valor del puerto oprimido
    //variable con el valor del led encendido 
    //^^^^Compararlos^^^
    
    while(1){
        LED_rand = rand() % 8;
        molePosition = (unsigned char) pow(2, LED_rand);
        LATB = molePosition; 
        
        __delay_ms(DELAYFIVE);
                
       
        //if(PORTBbits.RB4 == pushed)         // If button is pushed then
         //   LATAbits.LATA6 = led_OFF;       // turn off RA4 LED
        //else                                // Otherwise
          //  LATAbits.LATA6 = led_ON;        // turn on RA4 LED
        //LATAbits.LATA7 = led_ON;            // Turn on RA4 LED   
        //__delay_ms(ONE_SECOND);             // Delay function XC8 compiler
        //LATAbits.LATA7 = led_OFF;           // Turn off RA4 LED
        //__delay_ms(ONE_SECOND);             // Delay function XC8 compiler
        
             //Deberia ser con el B por los LEDS
        //__delay_ms(1000);
        buttonStatus = ~PORTD;              // ~Por que negado?
        //////////////////////////////
      
        
        if (molePosition == buttonStatus) //Knight rider effect
        {
            for ( i = 0; i < 7; i++){
                LATB = (unsigned char) pow(bbase, i);
                __delay_ms(DELAY);
            }
            for ( i = 7; i > 0; i--){
                LATB = (unsigned char) pow(bbase, i);
                __delay_ms(DELAY);
            }   
            LATB = 0x01;
            __delay_ms(DELAY);

    }
        else {
            __delay_ms(DELAYTWO);
            buttonStatus = ~PORTD;              // ~Por que negado?
        //////////////////////////////
      
        
            if (molePosition == buttonStatus) //Knight rider effect
            {
                for (unsigned char i = 0; i < 7; i++){
                    LATB = (unsigned char) pow(bbase, i);
                    __delay_ms(DELAY);
                }
                for (unsigned char i = 7; i > 0; i--){
                    LATB = (unsigned char) pow(bbase, i);
                    __delay_ms(DELAY);
                }   
                LATB = 0x01;
                __delay_ms(DELAY);
            
        }
            
        }
    }
        
  }

//+++++++++++++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++++++++++++
void portsInit( void ){
    TRISB  = 0b00000000;
    
    ANSELB = 0b00000000;  
    
    PORTB = 0b00000000;
    
    TRISD = 0b11111111;                      
                  
    ANSELD = 0b00000000;
    
    PORTD = 0b11111111;

}
