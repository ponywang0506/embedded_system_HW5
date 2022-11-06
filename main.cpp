#include "mbed.h"

#define PERIOD 0.05f

char data[] = "10241040124040402102410240124004";
#define DATASIZE 32

 
//PWM pin
PwmOut led(PA_15);       //might have to change PwmPin
 
 
//Ticker to update the PWM dutycycle
Ticker pwm_ticker;
 
float encode(char c) {
    switch (c)
    {
        case '0':   return 0.2f;
        case '1':   return 0.4f;
        case '2':   return 0.6f;
        case '4':   return 0.8f;
    }
    return -1;
}


//Ticker calls this fucntion to update the PWM dutycycle
void pwm_duty_updater() {
  static int idx=0;
  
  led.write(encode(data[idx]));  // Set the dutycycle % to next value in array //PwmPin
  idx++;                         // Increment the idx
  if (idx == DATASIZE) idx=0;  // Reset the idx when teh end has been reached  

}
  
int main() {
    

  // Set PWM frequency to 200 KHz (period = 5 us)
  led.period(PERIOD);      //PwmPin
 
  // Init the Ticker to call the dutycyle updater at the required interval
  // The update should be at (SINE_STEPS * SINE_OUT_FREQ) 
  pwm_ticker.attach(&pwm_duty_updater, PERIOD);
 
  while(1){ //infinite loop
    // myled = !myled;     //myled 
    ThisThread::sleep_for(0);  
   }
       
}