// Motion Lab — HC-SR04 Ultrasonic Sensor
// TRIG -> Pin 5  |  ECHO -> Pin 6
// Upload this sketch, then open index.html in Chrome or Edge.

#define TRIG_PIN 5
#define ECHO_PIN 6

const int INTERVAL_MS = 200;  // 5 Hz — change to match app setting
unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  unsigned long now = millis();
  if (now - lastTime >= INTERVAL_MS) {
    lastTime = now;

    // 1. Fire a 10µs pulse on TRIG
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // 2. Measure echo duration (30ms timeout = 400cm max range)
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    // 3. Convert to cm and send over Serial
    if (duration > 0) {
      float cm = (duration * 0.0343) / 2.0;
      if (cm >= 2 && cm <= 400) {
        Serial.println(cm, 2);
      }
    }
  }
}
