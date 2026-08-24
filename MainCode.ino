{\rtf1\ansi\ansicpg1252\cocoartf2870
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;\f1\fnil\fcharset0 Menlo-Bold;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue255;\red255\green255\blue254;\red0\green0\blue0;
\red144\green1\blue18;\red19\green118\blue70;\red225\green92\blue84;\red95\green105\blue110;\red17\green134\blue138;
\red76\green92\blue5;\red35\green22\blue178;}
{\*\expandedcolortbl;;\cssrgb\c0\c0\c100000;\cssrgb\c100000\c100000\c99608;\cssrgb\c0\c0\c0;
\cssrgb\c63922\c8235\c8235;\cssrgb\c3529\c52549\c34510;\cssrgb\c91373\c45098\c40000;\cssrgb\c44706\c48627\c50588;\cssrgb\c0\c59216\c61176;
\cssrgb\c36863\c42745\c1176;\cssrgb\c18824\c18824\c75294;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\partightenfactor0

\f0\fs24 \cf2 \cb3 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 Wire.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 Adafruit_GFX.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 Adafruit_SSD1306.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 Adafruit_BMP085.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 Adafruit_MPU6050.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 Adafruit_Sensor.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf0 \strokec4  \cf2 \strokec2 <\cf5 \strokec5 DHT.h\cf2 \strokec2 >\cf0 \cb1 \strokec4 \
\
\cf2 \cb3 \strokec2 #define\cf0 \strokec4  SCREEN_WIDTH \cf6 \strokec6 128\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #define\cf0 \strokec4  SCREEN_HEIGHT \cf6 \strokec6 64\cf0 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf0 \cb3 Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &
\f1\b \cf7 \strokec7 Wire
\f0\b0 \cf0 \strokec4 , -\cf6 \strokec6 1\cf0 \strokec4 );\cb1 \
\
\cb3 Adafruit_BMP085 bmp;\cb1 \
\cb3 Adafruit_MPU6050 mpu;\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 \strokec2 #define\cf0 \strokec4  DHTPIN \cf6 \strokec6 13\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #define\cf0 \strokec4  DHTTYPE DHT22\cb1 \
\pard\pardeftab720\partightenfactor0
\cf0 \cb3 DHT dht(DHTPIN, DHTTYPE);\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 \strokec2 #define\cf0 \strokec4  BUTTON_PIN \cf6 \strokec6 4\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #define\cf0 \strokec4  LED_PIN    \cf6 \strokec6 2\cf0 \cb1 \strokec4 \
\
\cf2 \cb3 \strokec2 int\cf0 \strokec4  currentScreen = \cf6 \strokec6 0\cf0 \strokec4 ; \cf8 \strokec8 // 0: Temp, 1: Humidity, 2: Pressure, 3: Motion\cf0 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 bool\cf0 \strokec4  lastBtnState = \cf9 \strokec9 HIGH\cf0 \strokec4 ;\cb1 \
\
\cf2 \cb3 \strokec2 void\cf0 \strokec4  \cf10 \strokec10 setup\cf0 \strokec4 () \{\cb1 \
\pard\pardeftab720\partightenfactor0
\cf0 \cb3   
\f1\b \cf7 \strokec7 Serial
\f0\b0 \cf0 \strokec4 .\cf7 \strokec7 begin\cf0 \strokec4 (\cf6 \strokec6 115200\cf0 \strokec4 );\cb1 \
\cb3   \cf7 \strokec7 pinMode\cf0 \strokec4 (BUTTON_PIN, \cf9 \strokec9 INPUT_PULLUP\cf0 \strokec4 );\cb1 \
\cb3   \cf7 \strokec7 pinMode\cf0 \strokec4 (LED_PIN, \cf9 \strokec9 OUTPUT\cf0 \strokec4 );\cb1 \
\
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (!display.\cf7 \strokec7 begin\cf0 \strokec4 (SSD1306_SWITCHCAPVCC, \cf11 \strokec11 0x3C\cf0 \strokec4 )) \{\cb1 \
\cb3     \cf2 \strokec2 for\cf0 \strokec4 (;;);\cb1 \
\cb3   \}\cb1 \
\
\cb3   bmp.\cf7 \strokec7 begin\cf0 \strokec4 ();\cb1 \
\cb3   mpu.\cf7 \strokec7 begin\cf0 \strokec4 ();\cb1 \
\cb3   dht.\cf7 \strokec7 begin\cf0 \strokec4 ();\cb1 \
\
\cb3   display.clearDisplay();\cb1 \
\cb3   display.setTextColor(WHITE);\cb1 \
\cb3 \}\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 \strokec2 void\cf0 \strokec4  \cf10 \strokec10 loop\cf0 \strokec4 () \{\cb1 \
\pard\pardeftab720\partightenfactor0
\cf0 \cb3   \cb1 \
\cb3   \cf2 \strokec2 bool\cf0 \strokec4  btnState = \cf7 \strokec7 digitalRead\cf0 \strokec4 (BUTTON_PIN);\cb1 \
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (lastBtnState == \cf9 \strokec9 HIGH\cf0 \strokec4  && btnState == \cf9 \strokec9 LOW\cf0 \strokec4 ) \{\cb1 \
\cb3     currentScreen = (currentScreen + \cf6 \strokec6 1\cf0 \strokec4 ) % \cf6 \strokec6 4\cf0 \strokec4 ;\cb1 \
\cb3     \cf7 \strokec7 delay\cf0 \strokec4 (\cf6 \strokec6 50\cf0 \strokec4 );\cb1 \
\cb3   \}\cb1 \
\cb3   lastBtnState = btnState;\cb1 \
\
\cb3   \cb1 \
\cb3   \cf2 \strokec2 float\cf0 \strokec4  tempC = bmp.readTemperature();\cb1 \
\cb3   \cf2 \strokec2 float\cf0 \strokec4  humidity = dht.readHumidity();\cb1 \
\cb3   \cf2 \strokec2 float\cf0 \strokec4  pressureHPa = bmp.readPressure() / \cf6 \strokec6 100.0\cf0 \strokec4 ;\cb1 \
\
\cb3   sensors_event_t a, g, tempMPU;\cb1 \
\cb3   mpu.getEvent(&a, &g, &tempMPU);\cb1 \
\
\cb3   \cf2 \strokec2 float\cf0 \strokec4  accelMag = \cf7 \strokec7 sqrt\cf0 \strokec4 (a.acceleration.x * a.acceleration.x +\cb1 \
\cb3                         a.acceleration.y * a.acceleration.y +\cb1 \
\cb3                         a.acceleration.z * a.acceleration.z) / \cf6 \strokec6 9.81\cf0 \strokec4 ;\cb1 \
\
\cb3   \cf2 \strokec2 float\cf0 \strokec4  gyroMag = \cf7 \strokec7 sqrt\cf0 \strokec4 (g.gyro.x * g.gyro.x +\cb1 \
\cb3                        g.gyro.y * g.gyro.y +\cb1 \
\cb3                        g.gyro.z * g.gyro.z) * (\cf6 \strokec6 180.0\cf0 \strokec4  / \cf6 \strokec6 3.14159\cf0 \strokec4 );\cb1 \
\
\cb3  \cb1 \
\cb3   \cf2 \strokec2 bool\cf0 \strokec4  alert = \cf2 \strokec2 false\cf0 \strokec4 ;\cb1 \
\
\cb3   \cf8 \strokec8 // CHANGE PARAMETERS HERE\cf0 \cb1 \strokec4 \
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (tempC < \cf6 \strokec6 18\cf0 \strokec4  || tempC > \cf6 \strokec6 28\cf0 \strokec4  ) alert = \cf2 \strokec2 true\cf0 \strokec4 ;\cb1 \
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (humidity < \cf6 \strokec6 25\cf0 \strokec4  || humidity > \cf6 \strokec6 75\cf0 \strokec4  ) alert = \cf2 \strokec2 true\cf0 \strokec4 ;\cb1 \
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (pressureHPa < \cf6 \strokec6 300\cf0 \strokec4  || pressureHPa > \cf6 \strokec6 1050\cf0 \strokec4 ) alert = \cf2 \strokec2 true\cf0 \strokec4 ;\cb1 \
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (accelMag < \cf6 \strokec6 0\cf0 \strokec4  || accelMag > \cf6 \strokec6 4\cf0 \strokec4 ) alert = \cf2 \strokec2 true\cf0 \strokec4 ;\cb1 \
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (gyroMag > \cf6 \strokec6 60\cf0 \strokec4 ) alert = \cf2 \strokec2 true\cf0 \strokec4 ;\cb1 \
\
\cb3   \cf7 \strokec7 digitalWrite\cf0 \strokec4 (LED_PIN, alert ? \cf9 \strokec9 HIGH\cf0 \strokec4  : \cf9 \strokec9 LOW\cf0 \strokec4 );\cb1 \
\
\cb3   \cb1 \
\cb3   display.clearDisplay();\cb1 \
\cb3   display.setTextSize(\cf6 \strokec6 1\cf0 \strokec4 );\cb1 \
\cb3   display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\
\cb3   \cf2 \strokec2 if\cf0 \strokec4  (alert) \{\cb1 \
\cb3     display.setCursor(\cf6 \strokec6 85\cf0 \strokec4 , \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\cb3     display.\cf7 \strokec7 print\cf0 \strokec4 (\cf5 \strokec5 "[ALERT]"\cf0 \strokec4 );\cb1 \
\cb3   \}\cb1 \
\
\cb3   \cf2 \strokec2 switch\cf0 \strokec4  (currentScreen) \{\cb1 \
\cb3     \cf2 \strokec2 case\cf0 \strokec4  \cf6 \strokec6 0\cf0 \strokec4 : \cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 println\cf0 \strokec4 (\cf5 \strokec5 "--- TEMPERATURE ---"\cf0 \strokec4 );\cb1 \
\cb3       display.setTextSize(\cf6 \strokec6 2\cf0 \strokec4 );\cb1 \
\cb3       display.setCursor(\cf6 \strokec6 10\cf0 \strokec4 , \cf6 \strokec6 25\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (tempC, \cf6 \strokec6 1\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (\cf5 \strokec5 " C"\cf0 \strokec4 );\cb1 \
\cb3       \cf2 \strokec2 break\cf0 \strokec4 ;\cb1 \
\
\cb3     \cf2 \strokec2 case\cf0 \strokec4  \cf6 \strokec6 1\cf0 \strokec4 : \cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 println\cf0 \strokec4 (\cf5 \strokec5 "--- HUMIDITY ---"\cf0 \strokec4 );\cb1 \
\cb3       display.setTextSize(\cf6 \strokec6 2\cf0 \strokec4 );\cb1 \
\cb3       display.setCursor(\cf6 \strokec6 10\cf0 \strokec4 , \cf6 \strokec6 25\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (humidity, \cf6 \strokec6 1\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (\cf5 \strokec5 " %"\cf0 \strokec4 );\cb1 \
\cb3       \cf2 \strokec2 break\cf0 \strokec4 ;\cb1 \
\
\cb3     \cf2 \strokec2 case\cf0 \strokec4  \cf6 \strokec6 2\cf0 \strokec4 : \cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 println\cf0 \strokec4 (\cf5 \strokec5 "--- PRESSURE ---"\cf0 \strokec4 );\cb1 \
\cb3       display.setTextSize(\cf6 \strokec6 2\cf0 \strokec4 );\cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 25\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (pressureHPa, \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (\cf5 \strokec5 " hPa"\cf0 \strokec4 );\cb1 \
\cb3       \cf2 \strokec2 break\cf0 \strokec4 ;\cb1 \
\
\cb3     \cf2 \strokec2 case\cf0 \strokec4  \cf6 \strokec6 3\cf0 \strokec4 : \cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 0\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 println\cf0 \strokec4 (\cf5 \strokec5 "--- MOTION ---"\cf0 \strokec4 );\cb1 \
\cb3       display.setTextSize(\cf6 \strokec6 1\cf0 \strokec4 );\cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 20\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (\cf5 \strokec5 "Accel: "\cf0 \strokec4 ); display.\cf7 \strokec7 print\cf0 \strokec4 (accelMag, \cf6 \strokec6 2\cf0 \strokec4 ); display.\cf7 \strokec7 println\cf0 \strokec4 (\cf5 \strokec5 " g"\cf0 \strokec4 );\cb1 \
\cb3       display.setCursor(\cf6 \strokec6 0\cf0 \strokec4 , \cf6 \strokec6 40\cf0 \strokec4 );\cb1 \
\cb3       display.\cf7 \strokec7 print\cf0 \strokec4 (\cf5 \strokec5 "Gyro:  "\cf0 \strokec4 ); display.\cf7 \strokec7 print\cf0 \strokec4 (gyroMag, \cf6 \strokec6 1\cf0 \strokec4 ); display.\cf7 \strokec7 println\cf0 \strokec4 (\cf5 \strokec5 " deg/s"\cf0 \strokec4 );\cb1 \
\cb3       \cf2 \strokec2 break\cf0 \strokec4 ;\cb1 \
\cb3   \}\cb1 \
\
\cb3   display.display();\cb1 \
\cb3   \cf7 \strokec7 delay\cf0 \strokec4 (\cf6 \strokec6 50\cf0 \strokec4 );\cb1 \
\cb3 \}\cb1 \
}
