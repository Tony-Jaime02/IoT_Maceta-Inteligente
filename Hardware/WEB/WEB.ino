#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"
#define DHTTYPE DHT11 // DHT 11

uint8_t DHTPin = D4; 
const int tierra = A0;              // Sensor de humedad en tierra (Pin analogo A0)
const int foto = 1;                 // Sensor de luz (Pin digital 1)
const char* ssid = "INFINITUM3A86_2.4";
const char* password =  "joLDjD9H8x";
const char* url = "https://iot.omarquintero.com/equipo3/api/lectura";
const uint8_t fingerprint[20] = {0xF1, 0x11, 0xBD, 0x7C, 0x19, 0x46, 0x0F, 0xC8, 0x8A, 0xEC, 0x83, 0x5F, 0x58, 0x90, 0x46, 0x41, 0x19, 0x7D, 0x52, 0x65};


DHT dht(DHTPin, DHTTYPE);
float Temperature=0;
float Humidity=0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float humedad = analogRead(tierra);
  float value = digitalRead(foto);
  Temperature = dht.readTemperature();
  Humidity = dht.readHumidity();
  
  Serial.print("Humedad de tierra: ");
  Serial.println(humedad);
  Serial.print("Nivel de Luz: ");
  Serial.println(value);
  if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println("Falla al leer el sensor DHT11!");
    //return;
    Humidity = 0;
    Temperature = 0;
  }
    Serial.print("Temperatura: ");
    Serial.print(Temperature);
    Serial.print(" Humedad: ");
    Serial.print(Humidity);
    Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    String datos_a_enviar = "{\"id_lectura\":" + String(0) + "," +
                            "\"sens_luz\":" + String(value) + "," +
                            "\"sens_humA\":" + String(Humidity) + "," +
                            "\"sens_tempA\":" + String(Temperature) + "," +
                            "\"sens_humT\":" + String(humedad) + "," +
                            "\"planta_id_planta\":" + String(1) +
                            "}";
    Serial.println(datos_a_enviar);
    //WiFiClient client;
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    HTTPClient http;
    if (http.begin(*client, url )) {
      http.addHeader("Content-Type", "application/json"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.
      int codigo_respuesta = http.POST(datos_a_enviar);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)
      Serial.println(codigo_respuesta);
      if(codigo_respuesta > 0 && codigo_respuesta == HTTP_CODE_OK)
        Serial.println(http.getString());
      http.end();  //libero recursos  
    } else {
      Serial.println("Error en conexion http");
    }
  } else {
    Serial.println("Error en la conexión WIFI");
  }
  delay(600000);
}
