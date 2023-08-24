#include <MKRWAN.h>
#include <LoraEncoder.h>
#include <ArduinoLowPower.h>

const int HUMEDAD_1 = A2;   // Pin sensor humedad
const int HUMEDAD_2 = A5;   // Pin sensor humedad
const int PUERTO = 3;       // Puerto envio de datos
const int TAMANO = 2;       // Tamaño envio de datos
const int TIME_TRY = 5000;  // 5 segundos
const int SIESTA = 900000;  // 15 minutos

LoRaModem modem;
String appEui, appKey;

float hum_dry, hum_wet; //valores a mandar a ttn
int sensor1, sensor2; //valores a recoger por los sensores de tierra
int water_value1=710, water_value2=710, air_value1=860, air_value2=860; //valores para calibrar los sensores
boolean enviado = false;

void setup() {
  //Codigo inicio conexion con ttn
  Serial.begin(115200);
  //while (!Serial); //Solo para desarrollo, si no hay usb conectado a un IDE no avanzaría de aqui
  Serial.println("Iniciando el modulo LoRa...");
  while (!modem.begin(EU868)) {
    Serial.println("Fallo al iniciar el modulo. Intentando de nuevo.");
    delay(5000);
  } 
  appEui = "0000000000000000"; 
  appEui.trim();
  appKey = "FF115F61BB254A1435074ABA0A0FD818";
  appKey.trim();
  //intento de conexion con ttn
  Serial.println("Comenzando la conexion con TTN...");
  while (!modem.joinOTAA(appEui, appKey)) {
    Serial.println("Error al conectar con TTN, intentando de nuevo");
    delay(5000);
  }
  Serial.println("Conexion establecida...");
}

void loop() {
  //Lectura sensores suelo
  sensor1 = analogRead(HUMEDAD_1);
  sensor2 = analogRead(HUMEDAD_2);
  //Humedad suelo en %
  hum_dry = map(sensor1, air_value1, water_value1, 0, 100);
  hum_wet = map(sensor2, air_value2, water_value2, 0, 100);
  //Correccion 0-100
  if (hum_dry > 100) hum_dry = 100;
  if (hum_dry < 0) hum_dry = 0;
  if (hum_wet > 100) hum_wet = 100;
  if (hum_wet < 0) hum_wet = 0;
  //Codificacion de datos
  byte datos [TAMANO]; 
  LoraEncoder encoder(datos);
  encoder.writeUint8(hum_dry);
  encoder.writeUint8(hum_wet);
  //Envio datos, si hay fallo reintentar a los 5s
  while(!enviado){
    Serial.println("Intentando enviar datos a TTN...");
    if (enviar(datos,TAMANO,PUERTO) > 0){
      enviado = true;
      Serial.println("Mensaje enviado correctamente");
    } 
    LowPower.sleep(TIME_TRY);
  }
  enviado = false;
  Serial.println("Datos enviados");
  LowPower.sleep(SIESTA);
} 

int enviar(byte mydata [], int size, int port){
  int err;
  modem.setPort(port);
  modem.beginPacket();
  modem.write(mydata, size);
  return err = modem.endPacket(true);
}
