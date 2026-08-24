#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define BUTTON_PIN 4
#define LED_PIN    2

int currentScreen = 0; // 0: Temp, 1: Humidity, 2: Pressure, 3: Motion
bool lastBtnState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;);
  }

  bmp.begin();
  mpu.begin();
  dht.begin();

  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  
  bool btnState = digitalRead(BUTTON_PIN);
  if (lastBtnState == HIGH && btnState == LOW) {
    currentScreen = (currentScreen + 1) % 4;
    delay(50);
  }
  lastBtnState = btnState;

  
  float tempC = bmp.readTemperature();
  float humidity = dht.readHumidity();
  float pressureHPa = bmp.readPressure() / 100.0;

  sensors_event_t a, g, tempMPU;
  mpu.getEvent(&a, &g, &tempMPU);

  float accelMag = sqrt(a.acceleration.x * a.acceleration.x +
                        a.acceleration.y * a.acceleration.y +
                        a.acceleration.z * a.acceleration.z) / 9.81;

  float gyroMag = sqrt(g.gyro.x * g.gyro.x +
                       g.gyro.y * g.gyro.y +
                       g.gyro.z * g.gyro.z) * (180.0 / 3.14159);

 
  bool alert = false;

  // CHANGE PARAMETERS HERE
  if (tempC < 18 || tempC > 28 ) alert = true;
  if (humidity < 25 || humidity > 75 ) alert = true;
  if (pressureHPa < 300 || pressureHPa > 1050) alert = true;
  if (accelMag < 0 || accelMag > 4) alert = true;
  if (gyroMag > 60) alert = true;

  digitalWrite(LED_PIN, alert ? HIGH : LOW);

  
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);

  if (alert) {
    display.setCursor(85, 0);
    display.print("[ALERT]");
  }

  switch (currentScreen) {
    case 0: 
      display.setCursor(0, 0);
      display.println("--- TEMPERATURE ---");
      display.setTextSize(2);
      display.setCursor(10, 25);
      display.print(tempC, 1);
      display.print(" C");
      break;

    case 1: 
      display.setCursor(0, 0);
      display.println("--- HUMIDITY ---");
      display.setTextSize(2);
      display.setCursor(10, 25);
      display.print(humidity, 1);
      display.print(" %");
      break;

    case 2: 
      display.setCursor(0, 0);
      display.println("--- PRESSURE ---");
      display.setTextSize(2);
      display.setCursor(0, 25);
      display.print(pressureHPa, 0);
      display.print(" hPa");
      break;

    case 3: 
      display.setCursor(0, 0);
      display.println("--- MOTION ---");
      display.setTextSize(1);
      display.setCursor(0, 20);
      display.print("Accel: "); display.print(accelMag, 2); display.println(" g");
      display.setCursor(0, 40);
      display.print("Gyro:  "); display.print(gyroMag, 1); display.println(" deg/s");
      break;
  }

  display.display();
  delay(50);
}
