const int aire = 720;       //valor en vacio
const int sumergido = 310;  //valor sumergido
int sensorHumedad = 0;      //valor para el sensor
int humedadPorcentaje=0;    //conversion a % de humedad
int pinSensor = 6;          //pin al que esta conectado el sensor

void setup() {
  Serial.begin(9600); 
}

void loop() {
  sensorSuelo = analogRead(pinSensor); //comando para leer el valor del pin del sensor
  Serial.print("Humedad 1: ");  //Escribir por pantalla
  Serial.println(sensorSuelo);  //Escribir por pantalla el valor del sensor

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
    delay(500);
}