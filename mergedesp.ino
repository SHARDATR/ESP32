/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save spac
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLDIrWFrQI"
#define BLYNK_TEMPLATE_NAME "soil moisture and dht11"
#define BLYNK_AUTH_TOKEN "7-fk23MI7P9O2G-ZbjbEGJqNlLHPxSjK"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define DHTPIN  4        // DHT data pin
#define DHTTYPE DHT11    // DHT sensor type (DHT11 or DHT22)
#define SOIL_MOISTURE_PIN 34 // analog pin for soil moisture sensor
#define PUMP_PIN 26 
DHT dht(DHTPIN, DHTTYPE);
int soilMoistureValue = 0;

BlynkTimer timer;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Airtelzerotouch";
char pass[] = "Airtel@123";

void setup()
{
  // Debug console
  Serial.begin(9600);
   delay(10);

  dht.begin();

  Blynk.begin("7-fk23MI7P9O2G-ZbjbEGJqNlLHPxSjK"
, "Airtelzertouch", "Airtel@123");
}

void loop()
{
  Blynk.run();
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V0, humidity);
  
  delay(5000);
}

void soil()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin("YHFgRE3qo2M8fw7eztNt7jR2FsLL-xqN", "Airtelzerotouch", "Airtel@123");
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN , LOW);
  timer.setInterval(1000L, checkSoilMoisture);
}
void sensor()
{
  Blynk.run();
  timer.run();
}

void checkSoilMoisture() {
  soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  if (soilMoistureValue < 500) {
    digitalWrite(PUMP_PIN, HIGH);
    //Blynk.notify("Water pump turned ON");
  } else {
    digitalWrite(PUMP_PIN, LOW);
    //Blynk.notify("Water pump turned OFF");
  }
}


