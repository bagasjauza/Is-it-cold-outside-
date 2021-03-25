#include "DHT.h"
#include <LCD_I2C.h>

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LCD_I2C lcd(0x27);
char auth[] = "your_token";
char ssid[] = "your_SSID_Wifi";
char pass[] = "your_password_Wifi";
float h, t;

void setup()
{
  Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
    lcd.begin(); 
    lcd.backlight();
    dht.begin();
}

void loop()
{
  Blynk.run();
  t = dht.readTemperature();
  h = dht.readHumidity();

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print(" C");
    lcd.setCursor(0,1);
    lcd.print("Humid: ");
    lcd.print(h);
    lcd.print(" %");
    delay(500);
    lcd.clear();
}
