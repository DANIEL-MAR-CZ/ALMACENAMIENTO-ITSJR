#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String server = "";

const char *ssid     = "N9PRO";
const char *password = "holaequipo1";

const int buttonPin = 2; //D4     // Pin del interruptor1
const int buttonPin2 = 4; //D2    // Pin del interruptor2

//String boton = "";
//String posicion = "";
int antes = 0;
int ahora = 0;
int antes2 = 0;
int ahora2 = 0;


//------------------------------------------------------------------------

void setup() {
  // Iniciamos el monitor serie
  Serial.begin(115200);

  // Los pines de LED en modo salida
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin2, INPUT_PULLUP);

  Serial.println("WiFi connected");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }


  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

//------------------------------------------------------------------------------

void loop() {


  if (WiFi.status() == WL_CONNECTED) {
    if (digitalRead(buttonPin) == HIGH) {
      ahora = 1;
      if (antes != ahora) {
        Serial.println("INTERRUPTOR1 1 ON DERECHA");
        post("1APAGADOR1", "ON DERECHA");
        delay(1000);
        antes = 1;
      }

    }
    else {
      antes = 0;
      if (antes != ahora) {
        Serial.println("INTERRUPTOR1 1 OFF IZQUIERDA ");
        post("1APAGADOR1", "OFF IZQUIERDA");
        delay(1000);
        ahora=0;
      }
    }
    // SEGUNDO BOTON
    if (digitalRead(buttonPin2) == HIGH) {
      ahora2 = 1;
      if (antes2 != ahora2) {
        Serial.println("2INTERRUPTOR2 ON DERECHA");
        post("2APAGADOR2", "ON DERECHA");
        delay(1000);
        antes2 = 1;
      }

    }
    else {
      antes2 = 0;
      if (antes2!=ahora2) {
        Serial.println("2INTERRUPTOR 2 OFF IZQUIERDA ");
        post("2APAGADOR2", "OFF IZQUIERDA");
        delay(1000);
        ahora2=0;
      }
    }
    
  }

  delay(2000);

}

//-------------------------------------------------------------------------------------

void post(String boton, String posicion) {
  Serial.println("Inicio post");
  HTTPClient http;
  String json;
  server = "http://192.168.43.179:3003/api/botones";

  StaticJsonDocument<256> doc;
  doc["boton"] = String(boton);
  doc["posicion"] = String(posicion);
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("Termino post");

}
