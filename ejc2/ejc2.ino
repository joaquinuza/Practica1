volatile bool test = false;
const int aPin = 36; //ESP32-DevKit ADC1_CH0
int value = 0;      //Value read from ADC1_CH0
int totalInterruptCounter;
 
hw_timer_t * timer = NULL;  //Pointer of hw_timer_t type
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; //to synchronise a variable between main loop and ISR when is modified 

// Timer ISR
void IRAM_ATTR timer0_isr() {
  value = analogRead(aPin); 
  Serial.print("ADC VALUE: ");
  Serial.println(value);
}
 
void setup() {
 
  Serial.begin(9600); //Start serial communication at 9600bps
  timer = timerBegin(0, 40000, true);
  //tick of 0.5ms -> APB_CLK = 80MHZ -> Divider (16 bit) = 40000
  timerAttachInterrupt(timer, &timer0_isr, true);
  timerAlarmWrite(timer, 20000, true);
  //tick * 20000 = 10s
  timerAlarmEnable(timer);
  //start timer with alarm
 
}
 
void loop() {
}
