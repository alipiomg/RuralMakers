#include <MKRWAN.h>
//variables para leer humedad
const int aire = 720;       //valor en vacio
const int sumergido = 310;  //valor sumergido
int sensorHumedad = 0;      //valor para el sensor
int humedadPorcentaje=0;    //conversion a % de humedad
int pinSensor = 6;          //pin al que esta conectado el sensor
//variables para conexion lora
LoRaModem modem;
String appEui;
String appKey;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Welcome to MKR WAN 1300/1310 first configuration sketch");
  Serial.println("Register to your favourite LoRa network and we are ready to go!");
  // eleccion de la banda del modulo LoRa
  if (!modem.begin(EU868)) {
    Serial.println("Failed to start module");
    while (1) {}
  };
  Serial.print("Your device EUI is: ");
  Serial.println(modem.deviceEUI());

  
  int connected;
  /*
  Borramos el codigo correspondiente a la conexion ABP
  porque usamos la conexion OTAA y guardamos las variables que 
  conseguimos de la primera vez para no tener que repetirlas
  */
  Serial.println("Enter your APP EUI");
  appEui = "0000000000000000"; 
  appEui.trim();
  appKey = "FF115F61BB254A1435074ABA0A0FD818";
  appKey.trim();
  //fin configuracion OTAA

  connected = modem.joinOTAA(appEui, appKey); //conexion a TTN mediante OTAA
  
  //codigo si falla la conexion
  if (!connected) {
    Serial.println("Something went wrong; are you indoor? Move near a window and retry");
    while (1) {}
  }
  //Fin codigo conexion a TTN 
}

void loop() {
  //codigo lectura sensor
  sensorSuelo = analogRead(pinSensor); //comando para leer el valor del pin del sensor
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

  //codigo envio de datos
  int err;
  modem.setPort(3); //eleccion de puerto para mandar TTN (numero en TTN)
  modem.beginPacket();
  modem.print(humedadPorcentaje); //envio TTN
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Message sent correctly!");
  } else {
    Serial.println("Error sending message :(");
  }
  delay(5000);
}
