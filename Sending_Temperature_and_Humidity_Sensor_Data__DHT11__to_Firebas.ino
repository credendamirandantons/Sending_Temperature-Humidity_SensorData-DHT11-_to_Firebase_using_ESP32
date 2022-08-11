//library arduino json version 5.13.5
//arduino IOXhop_FirebaseESP32.h

#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>


#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht (DHTPIN, DHTTYPE);


// Set these to run example
#define FIREBASE_HOST "https://dgt11nfirebase-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Qj6Hi5ykNP9iL9e9dvcyix0XRXvfm2oWj5rzdX66"
#define WIFI_SSID "N"
#define WIFI_PASSWORD "12345678"

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11 test");
  dht.begin();

  
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

int n = 0;

void loop() {
  //Read temperature and humidity sensors
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C ");

  // Set value
  Firebase.setFloat("Temperature", t);
  // Handle Error
  if (Firebase.failed()) {
    Serial.print("Setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  delay(1000);

  Firebase.setFloat ("Humidity", h);
  // Handle Error
  if (Firebase.failed()) {
    Serial.print("Setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.println ("Temperature and Humidity Data Sent Successfully");
  delay(1000);
}
