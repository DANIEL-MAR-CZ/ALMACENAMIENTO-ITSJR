#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

int distancia;
long tiempo;
int c_distancia;
String server = "";

const char *ssid     = "N9PRO";
const char *password = "holaequipo1";

const int buttonPin = 2; //D4     // Pin del interruptor1
const int buttonPin2 = 4; //D2    // Pin del interruptor2


int antes = 0;
int ahora = 0;
int antes2 = 0;
int ahora2 = 0;


//------------------------------------------------------------------------

void setup() {
  // Iniciamos el monitor serie
  Serial.begin(115200);
  pinMode(16, OUTPUT); //Configuracion  D0 como salida: Trigger - Disparo9
  pinMode(5, INPUT); //Configuracion D1 como entrada: Recibira el Echo10
  pinMode(LED_BUILTIN, OUTPUT);

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
        c_distancia=obtenerdistancia();
        post(1,"on",c_distancia);
        delay(1000);
        antes = 1;
      }

    }
    else {
      antes = 0;
      if (antes != ahora) {
        Serial.println("INTERRUPTOR1 1 OFF IZQUIERDA ");
        c_distancia=obtenerdistancia();
        post(1, "off",c_distancia);
        delay(1000);
        ahora=0;
      }
    }
    // SEGUNDO BOTON
    if (digitalRead(buttonPin2) == HIGH) {
      ahora2 = 1;
      if (antes2 != ahora2) {
        Serial.println("2INTERRUPTOR2 ON DERECHA");
        c_distancia=obtenerdistancia();
        post(2, "on",c_distancia);
        delay(1000);
        antes2 = 1;
      }

    }
    else {
      antes2 = 0;
      if (antes2!=ahora2) {
        Serial.println("2INTERRUPTOR 2 OFF IZQUIERDA ");
        c_distancia=obtenerdistancia();
        post(2, "off",c_distancia);
        delay(1000);
        ahora2=0;
      }
    }
    
  }

  delay(2000);

}

//-------------------------------------------------------------------------------------

void post(int boton, String posicion,int distancia) {
  Serial.println("Inicio post");
  HTTPClient http;
  String json;
  server = "http://144.202.34.148:3003/api/botones";

  StaticJsonDocument<256> doc;
  doc["boton"] = int(boton);
  doc["posicion"] = String(posicion);
  doc["distancia"] = int(distancia);
  serializeJson(doc, json);

  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println("Termino post");

}

//-------------------------------------------------------------------------------------

int obtenerdistancia() {

  digitalWrite(16,LOW); //Para darle estabilización al sensor
  delayMicroseconds(5); //Tiempo de 5 micro segundos
  digitalWrite(16, HIGH); //Enviamos el pulso ultrasónico para activar el sensor
  delayMicroseconds(5); //Con una duracion de 10 micro segundos
  tiempo=pulseIn(5, HIGH); //Función para medir la longitud del pulso entrante, mide el tiempo transcurrido de ida y vuelta
  distancia= int(0.017*tiempo); //Fórmula para calcular la distancia obteniendo un valor entero
  //Monitorización en centímetros por el monitor serial
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); //Cada que Tiempo se imprimira el valor de la distancia

      Serial.println("Distancia: "); //Imprimimos "Distancia" sobre el Monitor Serial
      Serial.print(distancia); //Mostramos el Valor de la distancia real sobre el Monitor Serial 
      Serial.print(" cm"); //Imprimimos " cm" sobre el Monitor Serial
      Serial.println("-------------------------------------------------------");

      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      return(distancia); 

}
