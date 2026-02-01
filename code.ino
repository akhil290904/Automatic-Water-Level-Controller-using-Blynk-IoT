#define TRIGPIN D6
#define ECHOPIN D7
#define RELAYPIN D5

int emptyTankDistance = 150;  // Distance when tank is empty (cm)
int fullTankDistance = 40;    // Distance when tank is full (cm)
int triggerPer = 10;          // Relay ON when water below this %

void setup() {
  Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW); // relay off initially
}

void loop() {
  long duration, distance;
  // Trigger the sensor
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  // Read echo time
  duration = pulseIn(ECHOPIN, HIGH);

  // Calculate distance in cm
  distance = (duration * 0.0343) / 2;

  // Map distance to water level percentage
  int waterLevel = map(distance, emptyTankDistance, fullTankDistance, 0, 100);
  waterLevel = constrain(waterLevel, 0, 100);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Water level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // Relay control based on water level
  if(waterLevel < triggerPer){
    digitalWrite(RELAYPIN, HIGH); // Pump ON
    Serial.println("Pump ON");
  }else{
    digitalWrite(RELAYPIN, LOW);  // Pump OFF
    Serial.println("Pump OFF");
  }

  delay(1000);
}
