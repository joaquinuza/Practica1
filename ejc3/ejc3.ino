uint16_t test = 0, value = 0;
void setup() {
  //LED_PWM controller used to generate PWM signals
  ledcSetup(0, 5000, 12); 
  //Group 0, channel 0, Timer = 0, f = 5Khz
  //bit_num == duty_resolution = 12bit
  ledcAttachPin(32, 0);
  //Associate timer to GPIO32
  Serial.begin(9600);
}

void loop() {
  value = analogRead(36);   //Pin 36 
  ledcWrite(0, value);      //Duty in this case is Ton
  delay(1000);
}
