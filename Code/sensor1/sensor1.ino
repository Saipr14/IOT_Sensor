#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define ANALOG_PIN A2  
#define LED_PIN_GREEN 4       // Green LED for sound > 100
#define LED_PIN_YELLOW 7      // Yellow LED for sound > 250
#define LED_PIN_RED 8         // Red LED for sound > 400

//Pin configurations can vary on your circuit(these are my pin configurations)

Adafruit_ADXL345_Unified soundSensor = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_YELLOW, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
  soundSensor.begin();
  soundSensor.setRange(ADXL345_RANGE_16_G);
}

void loop() {
  sensors_event_t event;
  soundSensor.getEvent(&event);
  int soundValue = analogRead(ANALOG_PIN);
  float soundDB = 20 * log10(soundValue);
  Serial.print("Sound Level (dB): ");
  Serial.println(soundDB);

  // Turn off all LEDs initially
  digitalWrite(LED_PIN_GREEN, LOW);
  digitalWrite(LED_PIN_YELLOW, LOW);
  digitalWrite(LED_PIN_RED, LOW);

  // Set LEDs based on sound level
  if (soundDB > 0 || soundDB < 100) {
    digitalWrite(LED_PIN_GREEN, HIGH);  // Green LED for sound > 400
  } else if (soundDB > 101 || soundDB < 300) {
    digitalWrite(LED_PIN_YELLOW, HIGH);  // Yellow LED for sound > 250
  } else if (soundDB > 300) {
    digitalWrite(LED_PIN_RED, HIGH);  // Red LED for sound > 100
  }

  delay(1000);  
}