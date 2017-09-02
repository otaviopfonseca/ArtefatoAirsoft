/********************************************************************/
/*                                                                  */
/*                                                                  */
/* PROJECT: Shield LCD 4 Bits                                       */
/* AUTHOR:  BLOGEMBARCADO.BLOGSPOT.COM                              */
/* DATE:    12/01/2012                                              */
/* EDITOR:  gVIM / Notepad++                                        */
/* IDE:     ARDUINO IDE v1.0.1                                      */
/*                                                                  */
/********************************************************************/

/*
  Simulino / Shield LCD 4 Bits - Demo
 
 In this project we are demonstrates how to use a 
 LiquidCrystal Library with a Shield LCD 4 bits.
  
 The LiquidCrystal library works with all 16x2 LCD displays that are 
 compatible with the Hitachi HD44780 driver. There are many of them
 out there, and you can usually tell them by the 16-pin interface.
 
 This sketch prints the button's labels of the Shield LCD 4 bits.

********************************
 Mods of the shield: MODEL:_01
********************************
 * LCD RS: pin 12
 * LCD En: pin 11
 * LCD D4: pin  5
 * LCD D5: pin  4
 * LCD D6: pin  3
 * LCD D7: pin  2
 
******************************** 
 Mods of the shield: MODEL:_02
********************************
 * LCD RS: pin  8
 * LCD En: pin  9
 * LCD D4: pin  4
 * LCD D5: pin  5
 * LCD D6: pin  6
 * LCD D7: pin  7
 
********************************
 Mods of the shield: MODEL:_03
********************************
 * LCD RS: pin 12
 * LCD En: pin  2
 * LCD D4: pin  7
 * LCD D5: pin  8
 * LCD D6: pin  9
 * LCD D7: pin 10
 

Credits:

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal

 */


/*********************************************************************
        OPTIONS
*********************************************************************/

#define DEBUG_SERIAL    1


/*********************************************************************
        LIBRARY
*********************************************************************/

#include <LiquidCrystal.h>



/*********************************************************************
        INITIAL CONFIG
*********************************************************************/

/* initialize the library with the numbers of the interface pins    */
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // MODEL_01
LiquidCrystal lcd( 8,  9, 4, 5, 6, 7);  // MODEL_02
//LiquidCrystal lcd(12,  2, 7, 8, 9,10);  // MODEL_03


/* constants for the number of rows and columns in the LCD          */
const int numRows = 2;
const int numCols = 16;


/* define of commands of LCD                                        */
#define LINE_UP         0
#define LINE_DOWN       1
#define LINE_BEGIN      0

/* define pin to read buttons of the shield                         */
const int Analog_Button_Pin = A0; 

#define NUM_KEYS 6



/*********************************************************************
        DEFINE MESSAGES
*********************************************************************/

/* Key Messages */
char messages[][17] =
{
        "                ",
        " RIGHT  Key OK  ",
        " UP     Key OK  ",
        " DOWN   Key OK  ",
        " LEFT   Key OK  ",
        " SELECT Key OK  "
};



/*********************************************************************
        DEFINE REFERENCE
*********************************************************************/

/* Maybe this values need some adjusts    
int adc_key_values[] =
{ 
         30,    // button RIGHT     0.00V
        150,    // button UP        0.65V
        360,    // button DOWN      1.50V
        535,    // button LEFT      2.35V
        760,    // button SELECT    3.52V
       1023     // button NOT_PRESS 5.00V
};

*/

// Values for Simulation
int adc_key_values[] =
{ 
          0,    // button RIGHT     0.00V
        134,    // button UP        0.65V
        309,    // button DOWN      1.50V
        481,    // button LEFT      2.35V
        722,    // button SELECT    3.52V
       1023     // button NOT_PRESS 5.00V
};



/*********************************************************************
        SETUP - FUNCTION
*********************************************************************/

void setup() {

        lcd.begin( numCols, numRows );
        lcd.print( "LCD Shield ");
        delay(400);
        
#ifdef DEBUG_SERIAL
        
        Serial.begin( 9600 );
        Serial.println( "Arduino - Button LCD shield");

#endif
        delay(1000);

        lcd.setCursor( LINE_BEGIN, LINE_UP );
        lcd.print( "Press any KEY  ");


#ifdef DEBUG_SERIAL

        Serial.println( "Press any KEY  ");

#endif

}

/*********************************************************************
        LOOP - FUNCTION
*********************************************************************/

void loop() {

 int iPinValue;
 int iKey;

        iPinValue = analogRead( Analog_Button_Pin );
        
        iKey = get_key( iPinValue );

        lcd.setCursor( LINE_BEGIN, LINE_DOWN );
      //lcd.clear();
        lcd.print( "                ");
        lcd.setCursor( LINE_BEGIN, LINE_DOWN );
      //lcd.print( iPinValue );
        lcd.print( messages[iKey] );

#ifdef DEBUG_SERIAL
        
        Serial.print( " : " );
        Serial.print( iPinValue );
        Serial.print( " : " );
        Serial.print( iKey );
        Serial.print( " : " );
        Serial.print( messages[iKey] );
        Serial.println( " " );

#endif

        delay(500);
}

/*********************************************************************
        SUBROTINES
*********************************************************************/

int get_key( int input ) {

 int k;

 for ( k=1; k<NUM_KEYS; k++) {
        if ( input < adc_key_values[k]) {
                return k;
        }
 }

 if ( k>= NUM_KEYS ) {
         k = 0;
 }

 return k;

 }


/*********************************************************************
        MAIN - FUNCTION
*********************************************************************/
/*
int main(void){

        init();
        
        setup();

        for (;;){
          loop();
        }

        return 0;
}
*/

/*********************************************************************
        END
*********************************************************************/

