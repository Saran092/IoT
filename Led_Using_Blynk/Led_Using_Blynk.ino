#define BLYNK_TEMPLATE_ID "TMPL3rygqpQCe"
#define BLYNK_TEMPLATE_NAME "LED"
#define BLYNK_AUTH_TOKEN "762whP4_7XGC8gCwgfqGGj7XhdkdRSgo"
#define BLYNK_PRINT Serial    // Enable serial print for debugging
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "762whP4_7XGC8gCwgfqGGj7XhdkdRSgo";

// Your WiFi credentials.
char ssid[] = "Saran";
char pass[] = "1234567890_-!";

#define LED_PIN D4 // GPIO pin connected to the LED

void setup() {
  // Debug console
  Serial.begin(9600);
  delay(10);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pass);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(auth, ssid, pass);

  pinMode(LED_PIN, OUTPUT); // Set LED pin as an output
}

void loop() {
  Blynk.run();
}

// This function will be called every time the Button Widget
// in the Blynk app writes a value to Virtual Pin V1
BLYNK_WRITE(V1) {
  int ledState = param.asInt(); // Get the value from the Blynk app
  digitalWrite(LED_PIN, ledState); // Turn the LED on or off depending on the value received
}
