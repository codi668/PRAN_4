
#include <WiFi.h>  // Für ESP32
#include <Arduino.h>
#include <PubSubClient.h>

// Definiere den DHT11-Typ
//#define DHTTYPE DHT11
//#define DHTPIN 14  // GPIO-Pin, an den der DHT11-Datenpin angeschlossen ist
#define ledPin 2

// WLAN und MQTT Konfiguration
const char* ssid = "HTL-WLAN-IoT";       // Dein WLAN-SSID (Netzwerkname)
const char* password = "HTL2IoT!";   // Dein WLAN-Passwort
const char* hostname = "ESP32_thomas";  // Dein Hostname
const char* mqtt_server = "10.115.32.14";  // MQTT-Broker IP-Adresse
const int mqtt_port = 1883;
const char* mqtt_user = "mqttuser";   // MQTT-Benutzername
const char* mqtt_pass = "mqttpass";   // MQTT-Passwort

// MQTT-Client
WiFiClient esp32thomas;
PubSubClient client(esp32thomas);

// DHT-Sensor Objekt
//DHT dht(DHTPIN, DHTTYPE);

// Funktionen zur Initialisierung von WLAN und MQTT
#include <stdio.h>
#include "esp_system.h"

// Funktion zur Erzeugung einer Zufallszahl im Bereich [min, max]
// Rückgabetyp ist jetzt int
int generate_random_value_in_range(int min, int max) {
    return (esp_random() % (max - min + 1)) + min; // Zufallszahl im gewünschten Bereich
}
void initWifi() {
  Serial0.begin(115200);
  WiFi.setHostname(hostname);
  WiFi.mode(WIFI_STA);
  Serial0.println("Verbindung zum WLAN wird hergestellt...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial0.println("Verbindung wird hergestellt...");
  }

  Serial0.println("WLAN verbunden!");
  Serial0.print("IP-Adresse: ");
  Serial0.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial0.println("Verbindung zum MQTT-Broker wird hergestellt...");
    if (client.connect("ESP32_thomas","", "")) {
      Serial0.println("Verbunden mit MQTT-Broker!");
      client.subscribe("ESP32/LED");
    } else {
      Serial0.print("Fehler beim Verbinden mit MQTT-Broker, rc=");
      Serial0.print(client.state());
      Serial0.println(" Warte 5 Sekunden...");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial0.print("Nachricht empfangen [");
  Serial0.print(topic);
  Serial0.print("] ");
  for (int i = 0; i < length; i++) {
    Serial0.print((char)payload[i]);
  }
  Serial0.println();

  if(String(topic) == "ESP32/LED"){
    String messageTemp = "";
    for(int i=0; i<length; i++)
    {
      messageTemp += (char)payload[i];
      Serial0.println(messageTemp);
    }

    
    if(messageTemp == "ON"){
      digitalWrite(ledPin, HIGH);
      Serial0.println("LED eingeschaltet");
    }
    else if(messageTemp == "OFF"){
      digitalWrite(ledPin, LOW);
      Serial.println("LED ausgeschaltet");
    }
  }
}

void setup() {
  // WLAN- und MQTT-Verbindung initialisieren
  initWifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // Initialisiere den DHT-Sensor
  //dht.begin();
  //reconnect();
}

void loop() {
  // Stelle sicher, dass der Client verbunden bleibt
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Lese Temperatur und Luftfeuchtigkeit vom DHT11-Sensor
  //float humidity = dht.readHumidity();
  //float temperature = dht.readTemperature();

  // Überprüfe, ob die Messungen gültig sind
  //if (isnan(humidity) || isnan(temperature)) {
    //Serial0.println("Fehler beim Auslesen des DHT11-Sensors!");
    //return;
  //}

  // Gebe die Werte auf der seriellen Konsole aus
  //Serial0.print("Luftfeuchtigkeit: ");
 // Serial0.print(humidity);
 // Serial0.println(" %");

  //Serial0.print("Temperatur: ");
  //Serial0.print(temperature);
  //Serial0.println(" °C");

  // Erstelle MQTT-Nachrichten und sende sie
  //char temperatureStr[8];
  //char humidityStr[8];
  //dtostrf(temperature, 6, 2, temperatureStr);
  //dtostrf(humidity, 6, 2, humidityStr);

  //client.publish("W014/akt/LED1/thomas", "ON");
  //client.publish("W014/hum/celina", humidityStr);

  // Warte 5 Sekunden, bevor eine neue Messung durchgeführt wird
}
