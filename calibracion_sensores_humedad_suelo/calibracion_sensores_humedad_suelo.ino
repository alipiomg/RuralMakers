int sensorSuelo = 0; //variable donde se va a guardar el valor del sensor
int pinSensor = 6; //pin al que esta conectado el sensor y que es donde manda los datos

void setup() {// el codigo que ejecuta al encender
  Serial.begin(9600); //comando para abrir la terminal y leer los datos desde el ordenador
}
void loop() { // el codigo que ejecuta todo el  en bucle
  
  sensorSuelo = analogRead(pinSensor); //comando para leer el valor del pin del sensor
  Serial.print("Humedad 1: ");  //Escribir por pantalla
  Serial.println(sensorSuelo);  //Escribir por pantalla el valor del sensor
  delay(500);                   //Espera para que no este mandando constantemente, esperar 500ms
}

