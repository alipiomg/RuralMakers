#include <MKRWAN.h>
#include <LoraEncoder.h>

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
const int TAMANO = 1; //Tamaño de los datos a mandar
const int PUERTO = 3; 
//El puerto es un numero para ordenar en TTN los datos, no un puerto de conexion

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
  if(humedadPorcentaje > 100){
    humedadPorcentaje = 100;//sustituimos el valor si se pasa del rango
  }
  else if(humedadPorcentaje <0){
    humedadPorcentaje = 0; //sustituimos el valor si se pasa del rango
  }

  //codificacion de datos  se tendría que cambiar tb en Console ttn / payload formatter  cambiando el formatter code
  byte datos [TAMANO]; //Hay que calcular a mano cual va a ser el tamaño dependiendo de los datos a mandar  en este caso 1 porque 1Uint8 es 1 si fueran 2 sensores podríamos 2
  LoraEncoder encoder(datos);
  //el dato sera un int de 8 bytes (rango 0-255)
  encoder.writeUint8(humedadPorcentaje);
  enviarDatos(datos,TAMANO,PUERTO);//envio de datos en una nueva funcion
  delay(5000);
}

void enviarDatos(byte datos [], int tamano, int puerto){
  int err;
  modem.setPort(puerto);
  modem.beginPacket();
  modem.write(datos, tamano);
  err = modem.endPacket(true);
  if (err > 0) {
    Serial.println("Mensaje enviado correctamente");
  } else {
    Serial.println("Error enviando el mensaje");
  }
}

