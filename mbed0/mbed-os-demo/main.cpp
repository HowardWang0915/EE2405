#include "mbed.h"

DigitalOut redLED(LED_RED);
DigitalOut greenLED(LED_GREEN);

int main() {
   	redLED = 1;
   	greenLED = 1;
   	while (true) {
      	for(int i = 0; i < 6; ++i) { //blink for 3 times
       		redLED = !redLED; // toggle led
       		wait(0.2f);
   		}
      	for(int i = 0; i < 4; ++i) { //blink for 2 times
       		greenLED = !greenLED; // toggle led
       		wait(0.2f);
   		}
   	}
}