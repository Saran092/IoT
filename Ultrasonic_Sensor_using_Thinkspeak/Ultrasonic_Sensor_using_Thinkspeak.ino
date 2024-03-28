#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char *ssid = "Saran";
const char *password = "1234567890_-!";
const unsigned long THINGSPEAK_CHANNEL_ID = 2489165;
const char *thingSpeakApiKey = "RH8S3ABAMJI18BKC";
const int updateInterval = 15 * 1000; // Update interval in milliseconds (15 seconds)
const int trigPin = D6; // Change to the GPIO pin connected to the trigger pin of the ultrasonic sensor
const int echoPin = D7; // Change to the GPIO pin connected to the echo pin of the ultrasonic sensor
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ThingSpeak.begin(client);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long duration, distance_cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance_cm = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (WiFi.status() == WL_CONNECTED) {
    if (ThingSpeak.writeField(THINGSPEAK_CHANNEL_ID, 1, (int)distance_cm, thingSpeakApiKey)) {
      Serial.println("ThingSpeak update successful.");
    } else {
      Serial.println("Error updating ThingSpeak.");
    }
  } else {
    Serial.println("WiFi not connected.");
  }

  delay(updateInterval);
}
