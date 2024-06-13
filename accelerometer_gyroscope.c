/*
    Project name : Accelerometer gyroscope module
    Modified Date: 13-06-2024
    Code by : Projectslearner
    Website : https://projectslearner.com/learn/arduino-mega-accelerometer-gyroscope-module
*/

const int redLEDPin = 9;    // Pin connected to the red LED
const int greenLEDPin = 10; // Pin connected to the green LED
const int delayTime = 1000; // Delay time in milliseconds

void setup() {
  pinMode(redLEDPin, OUTPUT);    // Set the red LED pin as OUTPUT
  pinMode(greenLEDPin, OUTPUT);  // Set the green LED pin as OUTPUT
  Serial.begin(9600);            // Initialize serial communication
}

void loop() {
  switchColors(); // Call the function to switch colors
  delay(delayTime); // Wait for a second before switching again
}

// Function to switch between red and green colors
void switchColors() {
  static bool isRedOn = true; // Static variable to keep track of the current color state

  if (isRedOn) {
    turnOnRedLED();
    Serial.println("Red LED is ON");
  } else {
    turnOnGreenLED();
    Serial.println("Green LED is ON");
  }

  isRedOn = !isRedOn; // Toggle the color state
}

// Function to turn on the red LED and turn off the green LED
void turnOnRedLED() {
  digitalWrite(redLEDPin, HIGH);   // Turn on red LED
  digitalWrite(greenLEDPin, LOW);  // Turn off green LED
}

// Function to turn on the green LED and turn off the red LED
void turnOnGreenLED() {
  digitalWrite(redLEDPin, LOW);    // Turn off red LED
  digitalWrite(greenLEDPin, HIGH); // Turn on green LED
}


#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+-250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+-500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+-1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+-2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("Accel X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Gyro X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  delay(500);
}
