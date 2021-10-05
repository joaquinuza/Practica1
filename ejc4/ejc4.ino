#include <string.h>   //to use the strcpy function
uint16_t number = 0, tmr = 0;
const int aPin = 36; //ESP32-DevKit ADC1_CH0
int val = 0;      //Value read from ADC1_CH0
bool setT = false;
String received;
//To stop main loop when a variable is used in both main and ISR interrupt
hw_timer_t * timer = NULL;  //Pointer of hw_timer_t type

//Function that extracts a number from a string
int string2num(String str){
  int i = str.length(); //length of the string
  int num = 0, mul = 1;
  char c;
  for(int s = i; s >= 0; s--){
     c = str.charAt(s);
     if(c >= '0' and c <= '9'){
      num = num + (c-'0')*mul;
      mul = mul*10;
     }
  }
  return num;
}


// Timer ISR
void IRAM_ATTR timer0_isr() {
  if(setT){
    timerAlarmWrite(timer, tmr*2000, true);
    //tick 0.5 ms
    val = analogRead(aPin); 
    Serial.print("ADC VALUE: ");
    Serial.println(val); 
  }
}

void setup() {
  Serial.begin(9600);
  //Timer Setup
  timer = timerBegin(0, 40000, true);
  //tick of 0.5ms -> APB_CLK = 80MHZ -> Divider (16 bit) = 40000
  timerAttachInterrupt(timer, &timer0_isr, true);
  timerAlarmWrite(timer, 2000, true);
  //tick * 20000 = 1s, default value
  timerAlarmEnable(timer);  //start timer with alarm
  //LED_PWM controller used to generate PWM signals
  ledcSetup(2, 5000, 12); 
  //Group 0, channel 2, Timer = 1, f = 5Khz
  ledcAttachPin(32, 2); //Timer 1 channel 2
}

void loop() {
  // reply when data is received
  if(Serial.available() > 0){
    received = Serial.readString();
    received.trim();                //Trim to remove special characters
    number = string2num(received);
    if(received.indexOf("ADC(" + String(number) + ')') >= 0)
    {
      if(number > 0){
        setT = true; 
        tmr = number;
      }
      else{
        setT = false;
      }
    }
    else if(received.equals("ADC"))
    {
      val = analogRead(aPin); 
      Serial.print("ADC VALUE: ");
      Serial.println(val);
    }
   else if(received.indexOf("PWM(" + String(number) + ')') >= 0)
    {
      if(number <= 9){
        ledcWrite(2, (number*4096)/9);      //Duty in this case is Ton 
        Serial.println("Duty changed");
      }
      else{
        ledcWrite(2, 0);      //Duty in this case is Ton 
        Serial.println("Duty not valid");
      } 
    }
    else{
      ;  
    }
  }

}
