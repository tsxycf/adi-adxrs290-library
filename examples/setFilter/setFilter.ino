/*
    ADI ADXRS290 Library - Gyroscope band-pass filter setting example

    The ADXRS290 exhibits a low noise floor of 0.004�/s/vHz and 
    features programmable high-pass and low- pass filters.

    This Sketch reads the Gyroscope values after having modified the Gyroscope
    sensitivity. This is done changing the high-pass low-pass values
    of the programmable filter.

    Created 27 Jan 2017 by Seve (seve@ioteam.it)

    This example is in the public domain

    https://github.com/axelelettronica/adi-adxrs290-library

    Analog Device ADX-RS290 more information available here:
    http://www.analog.com/en/products/mems/gyroscopes/adxrs290.html
*/



#include <Arduino.h>
#include <SPI.h>

#include <ADXRS290.h>

bool led = false;
#define TRIGGER_LED  digitalWrite(PIN_LED, led ? 225 : 0); \
                     led =!led
char inChar;
typedef struct {
    int freq;
    String str;
} freqArray_t;
    
#define FREQ_ARRAY_NUM       19
#define FREQ_ARRAY_HP_OFFSET  8

freqArray_t freqArray[FREQ_ARRAY_NUM] = {
  {ADXRS_LPF_480_HZ, "480 Hz"},
  {ADXRS_LPF_320_HZ, "320 Hz"},
  {ADXRS_LPF_160_HZ, "160 Hz"},
  {ADXRS_LPF_80_HZ, "80 Hz"},
  {ADXRS_LPF_56_6_HZ, "56.6 Hz"},
  {ADXRS_LPF_40_HZ, "40 Hz"}, 
  {ADXRS_LPF_28_3_HZ, "28.3 Hz"},
  {ADXRS_LPF_20_HZ, "20 Hz"}, 
  {ADXRS_HPF_ALL_HZ, "All Pass"}, 
  {ADXRS_HPF_0_011_HZ, "0.011 Hz"},
  {ADXRS_HPF_0_022_HZ, "0.022 Hz"},
  {ADXRS_HPF_0_044_HZ, "0.044 Hz"},
  {ADXRS_HPF_0_087_HZ, "0.087 Hz"},
  {ADXRS_HPF_0_175_HZ, "0.175 Hz"},
  {ADXRS_HPF_0_350_HZ, "0.35 Hz"},
  {ADXRS_HPF_0_700_HZ, "0.7 Hz"},
  {ADXRS_HPF_1_400_HZ, "1.4 Hz"},
  {ADXRS_HPF_2_800_HZ, "2.8 Hz"},
  {ADXRS_HPF_11_30_HZ, "11.3 Hz"}
};  

 
/* The Available Filters values are:
 *
 * Low-Pass Filter Pole Locations: 
 *
 * ADXRS_LPF_480_HZ     //  480_HZ is Default
 * ADXRS_LPF_320_HZ     //  320_HZ
 * ADXRS_LPF_160_HZ     //  160_HZ
 * ADXRS_LPF_80_HZ      //  80_HZ
 * ADXRS_LPF_56_6_HZ    //  56.6_HZ
 * ADXRS_LPF_40_HZ      //  40 HZ
 * ADXRS_LPF_28_3_HZ    //  28.3_HZ
 * ADXRS_LPF_20_HZ      //  20_HZ
 *
 *
 * High-Pass Filter Pole Locations: 
 *
 * ADXRS_HPF_ALL_HZ     //  All Pass Default
 * ADXRS_HPF_0_011_HZ   //  0.011_Hz
 * ADXRS_HPF_0_022_HZ   //  0.022_Hz
 * ADXRS_HPF_0_044_HZ   //  0.044_Hz  
 * ADXRS_HPF_0_087_HZ   //  0.087_Hz  
 * ADXRS_HPF_0_175_HZ   //  0.187_Hz   
 * ADXRS_HPF_0_350_HZ   //  0.350_Hz
 * ADXRS_HPF_0_700_HZ   //  0.700_Hz
 * ADXRS_HPF_1_400_HZ   //  1.400_Hz 
 * ADXRS_HPF_2_800_HZ   //  2.800_Hz 
 * ADXRS_HPF_11_30_HZ   // 11.300_Hz 
 * 
 */


void filterSelection()
{
    volatile int low = adiGyroscope.getLowPassFilter();
    volatile int high = adiGyroscope.getHighPassFilter();

    Serial.print("\nCurrent Band pass filter [High Pass - Low Pass] : [ ");
    Serial.print(freqArray[high+FREQ_ARRAY_HP_OFFSET].str);
    Serial.print(" - ");
    Serial.print(freqArray[low].str);
    Serial.println(" ]");   
        
    Serial.println("\nSelect the new Low or High filtering frequency");
    Serial.println("----------------------------------------------\n");
    
 

    Serial.println("  to set Low-Pass filter:"); 
    Serial.println("\t a  : 480   Hz (default)");
    Serial.println("\t b  : 320   Hz");
    Serial.println("\t c  : 160   Hz");
    Serial.println("\t d  :  80   Hz");
    Serial.println("\t e  :  56.6 Hz");
    Serial.println("\t f  :  40   Hz");
    Serial.println("\t g  :  28.3 Hz");
    Serial.println("\t h  :  20   Hz\n");
 
    Serial.println("  to set High-Pass filter:"); 
    Serial.println("\t i  :  All pass (default)");
    Serial.println("\t j  :  0.011 Hz");
    Serial.println("\t k  :  0.022 Hz");
    Serial.println("\t l  :  0.044 Hz");
    Serial.println("\t m  :  0.087 Hz");
    Serial.println("\t n  :  0.187 Hz");
    Serial.println("\t o  :  0.35  Hz");
    Serial.println("\t p  :  0.70  Hz");
    Serial.println("\t q  :  1.4   Hz");
    Serial.println("\t r  :  2.8   Hz");
    Serial.println("\t s  : 11.3   Hz\n");

    Serial.println("\tAny other key to exit ...\n");

    while (Serial.available() <= 0) {
        delay(10);
    }
    inChar = Serial.read();

    if ((inChar < 'a') || (inChar > 's')) {
        return;
    }
    if (inChar < 'i') {
        // Setting Low-pass filter
        adiGyroscope.setLowPassFilter(freqArray[inChar-'a'].freq);
        Serial.print("Selected Low-pass Freq: "); 
    } else {
        // Setting High-pass filter
        adiGyroscope.setHighPassFilter(freqArray[inChar-'a'].freq);
        Serial.print("Selected High-pass Freq: "); 
    }
    Serial.println(freqArray[inChar-'a'].str); 
    
    Serial.println("Press a key to set band-pass filters"); 
}

void setup(void)
{
    Serial.begin(115200);
    
    SPI1.begin();
    adiGyroscope.begin(ADXRS290_CS, &SPI1, ADXRS290_EINT);  

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);
    
    // Waiting for the console to continue
    while (!Serial) {
   	;
    }

    Serial.println("Press a key to set band-pass filters"); 
}


volatile uint32_t i = 0;
float x, y, z;

void loop(void)
{    
    if (!(i%5)) {
        TRIGGER_LED;
        
        adiGyroscope.setMeasurementMode();

        if (Serial.available() > 0) {
            inChar = Serial.read();
            filterSelection();
        }
        
        adiGyroscope.readXY(&x, &y);
        Serial.print("\tX / Y =   ");
        Serial.print(x);
        Serial.print(" / ");
        Serial.print(y); 
        Serial.println("  deg/s");

        adiGyroscope.setStandbyMode();
    }   
    ++i;
    delay(5);
}

