//Lectura cada segundo de un valor analogico generado
//por un potenciometro y mostrado por pantalla

const int aPin = 36; //ESP32-DevKit ADC1_CH0
int value = 0;      //Value read from ADC1_CH0
float value_volts = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  value = analogRead(aPin); 
  value_volts = (value * 3.3)/4095;   //Vref = 3.3V, ADC -> 12 bits
  Serial.println(value);
  Serial.println(value_volts);
  delay(1000);

}
