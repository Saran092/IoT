const int trigPin = D6; // Change to the GPIO pin connected to the trigger pin of the ultrasonic sensor
const int echoPin = D7; // Change to the GPIO pin connected to the echo pin of the ultrasonic sensor

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo duration
  unsigned long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance_cm = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(1000); // Delay for stability and to avoid rapid readings
}
