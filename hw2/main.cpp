#include "mbed.h"
#include <bits/stdc++.h> 

Serial pc( USBTX, USBRX );  // debug printing

BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// I/O
DigitalIn Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

AnalogOut Aout(DAC0_OUT);
AnalogIn Ain(A0);

// main

int main() {
    Timer t;
    int FFTpy = 1;
    double start, end;      // record the start and end time
    float prevData, newData = 0;       // record input data
    float ADCdata;         // input data
    int sample = 500;         // how many samples are there?
    float sample_data[sample];
    // float sample_data[300];     // sampling data
    int freq;               // the frequency
    int temp, factor = 1;   // for displaying
    int cnt = 0;             // will count the period. cnt == 0 means not start
    while (1) {
        // start the timer
        t.start();
        greenLED = 0;
        redLED = 1;
        factor = 1;
        // for FFT.py
        while (FFTpy) {
            for (int i = 0; i < sample; i++){
                // Aout = Ain;
                sample_data[i] = Ain;
                wait(1./sample);
            }
            for (int i = 0; i < sample; i++){
                pc.printf("%1.3f\r\n", sample_data[i]);
                wait(0.01);
            }
            FFTpy = 0;
        }
        ADCdata = Ain;
        prevData = newData; //store previous value
        newData = ADCdata;  //get value from A0
        // calculate freq using sampling
        if (prevData < 0.2 && newData >= 0.2) { //if increasing and crossing midpoint
            if (cnt == 0)   // cnt == 0 means new period
                start = t.read_us();
            cnt++;
            if (cnt == 10 && Switch == 0) {
                end = t.read_us();
                greenLED = 1;
                redLED = 0;
                freq = round(9. / double(end - start) * 1000000);
                // display on ssd
                temp = freq;
                while(temp) {
                    temp = temp / 10;
                    factor = factor * 10;
                }
                while(factor > 1){
                    factor = factor / 10;
                    if (factor == 1)    // the last digit should display a dot
                        display = table[freq / factor] + 0x80;
                    else
                        display = table[freq / factor];
                    wait(1);
                    freq = freq % factor;
                }
                display = 0x00;
                redLED = 1;
                cnt = 0;
            }
            else if (cnt == 10) {
                end = t.read_us();
                freq = round(9. / double(end - start) * 1000000);
                for (float i  = 0; Switch; i += 0.0002) {
                    Aout = 0.5 + 0.5 * sin(2 * 3.1415 * freq * i);
                    wait(0.0002);
                }
                cnt = 0;
            }    
        }
    }
} 