
int measurePin = A0;   // Connect dust sensor to Arduino A0 pin
int ledPower = 3;      // Connect dust sensor LED driver pin to Arduino D2

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPower, OUTPUT);
}

void loop() {
  digitalWrite(ledPower, LOW);    // Turn on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);   // Read dust value

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);   // Turn off the LED
  delayMicroseconds(sleepTime);

  // Map 0-5V to 0-1023 integer values and recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);

  // Calculate dust density
  dustDensity = 170 * calcVoltage - 0.1;

  // Print voltage and dust density to Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(calcVoltage);
  Serial.print(" V, ");
  Serial.print("Dust Density: ");
  Serial.print(dustDensity);
  Serial.println(" µg/m3");   // Output in µg/m3

  delay(1000);
}
