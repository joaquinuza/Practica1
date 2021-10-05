//EJC5
//MPU-9250 accelerometer 
//I2C communication at 400Khz max
//Logic low or logic high SDO
//slave addres b110100X (X depends on the logic)

#include <MPU9250_asukiaaa.h> //Library to interface with sensor
MPU9250_asukiaaa motionSensor;
float aX, aY, aZ, aSqrt;
uint8_t t200 = 0;

hw_timer_t * timer = NULL;  //Pointer of hw_timer_t type
// Timer ISR
void IRAM_ATTR timer0_isr() {
  t200 +=1;
  if(t200 == 2){
    t200 = 0;
  }
}

void setup() {
  Wire.begin(21, 22); //default i2c pins of esp32 are pin 21 and 22
  Serial.begin(9600);
  motionSensor.setWire(&Wire);
  motionSensor.beginAccel();
  timer = timerBegin(0, 40000, true);
  //tick of 0.5ms -> APB_CLK = 80MHZ -> Divider (16 bit) = 40000
  timerAttachInterrupt(timer, &timer0_isr, true);
  timerAlarmWrite(timer, 200, true);  //Obatain data every 100ms
  timerAlarmEnable(timer);
  //start timer with alarm
  pinMode(32, output); //Pin to connect the led
}

void loop() {
  if(t200 == 1){
    motionSensor.accelUpdate();
    aX = motionSensor.accelX();
    aY = motionSensor.accelY();
    aZ = motionSensor.accelZ();
    aSqrt = motionSensor.accelSqrt();
    Serial.println(aZ);   
  }
  if(t200 == 2){
    digitalWrite(32, !digitalRead(32));  // toggle state
  }
  
}
