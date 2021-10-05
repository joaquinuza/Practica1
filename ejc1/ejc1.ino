//Lectura cada segundo de un valor analogico generado
//por un potenciometro y mostrado por pantalla

const int aPin = 36; //ESP32-DevKit ADC1_CH0
int value = 0;      //Value read from ADC1_CH0

void setup() {
  Serial.begin(9600);
}

void loop() {
  value = analogRead(aPin); 
  Serial.println(value);
  delay(1000);

}
