const int aire = 720;       //valor en vacio
const int sumergido = 310;  //valor sumergido
int sensorHumedad = 0;      //valor para el sensor
int humedadPorcentaje=0;    //conversion a % de humedad
int pinSensor = A5;          //pin al que esta conectado el sensor

const int aire2 = 720;       //valor en vacio
const int sumergido2 = 310;  //valor sumergido
int sensorHumedad2 = 0;      //valor para el sensor
int humedadPorcentaje2=0;    //conversion a % de humedad
int pinSensor2 = A6;          //pin al que esta conectado el sensor

void setup() {
  Serial.begin(9600); 
}

void loop() {
  sensorHumedad = analogRead(pinSensor); //comando para leer el valor del pin del sensor
  Serial.print("Humedad 1: ");  //Escribir por pantalla
  Serial.println(sensorHumedad);  //Escribir por pantalla el valor del sensor

  //map crea un rango de valores definido dando los valores minimo y maximo
  humedadPorcentaje = map(sensorHumedad, aire, sumergido, 0, 100); 
  if(humedadPorcentaje >= 100){
    Serial.println("100 %");
  }
  else if(humedadPorcentaje <=0){
    Serial.println("0 %");
  }
  else{
    Serial.print(humedadPorcentaje);
    Serial.println("%");
  }

  sensorHumedad2 = analogRead(pinSensor2); //comando para leer el valor del pin del sensor
  Serial.print("Humedad 2: ");  //Escribir por pantalla
  Serial.println(sensorHumedad2);  //Escribir por pantalla el valor del sensor

  humedadPorcentaje2 = map(sensorHumedad2, aire2, sumergido2, 0, 100); 
  if(humedadPorcentaje2 >= 100){
    Serial.println("100 %");
  }
  else if(humedadPorcentaje2 <=0){
    Serial.println("0 %");
  }
  else{
    Serial.print(humedadPorcentaje2);
    Serial.println("%");
  }

    delay(500);
}