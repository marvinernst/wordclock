#include <Adafruit_NeoPixel.h>
#include "Led_Definitions.h"
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char *localSSID = "cl{}ck";
const char *localPassword = "12345678";

const long utcOffsetInSeconds = 3600;

const int NEOPIXEL_PIN = 5;
const long INTERVAL = 1000;

long color[] = {255, 255, 255};
float brightness = 0.75;
unsigned long lastTime = 0;
int minutes = 0;
int lastMinute = 0;
int hours = 0;
int lastHour = 0;
float currentColor = 0;
int fadeDir;
// Define Timeserver
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.de.pool.ntp.org", 3600);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(130, D1, NEO_GRB + NEO_KHZ800);
IPAddress clock_ip(192, 168, 1, 54);
IPAddress clock_gateway(192, 168, 1, 1);
IPAddress local_ip(192, 168, 4, 54);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

void initServer();
void handleRoot();
void handleNotFound();
void handleSetColor();
void handleLogin();
void handleSetLED();
void handleSetup();
void wifiConnect();
void led_controller_fade();
void led_controller_fade();
void setup()
{
  Serial.begin(9600);

  if (SPIFFS.begin())
  {
    Serial.println(F("\nSPIFFS mounted"));
  }
  else
  {
    Serial.println(F("\nFailed to mount SPIFFS"));
  }
  pixels.begin();
  pixels.clear();

  Serial.println();
  Serial.print("Starting Clock ... ");
  wifiConnect();
  /**
   * Erstellt den Server für die LED Steuerung
   */
  initServer();
  Serial.println("--------------");
  Serial.println(WiFi.getMode());
  Serial.println("--------------");
  /**
   * Eigenlicher Code für die Uhr
   */
  delay(1000);

  initClock();
}

void loop()
{
  server.handleClient();
  unsigned long currentTime = millis();

  if (currentTime - lastTime > INTERVAL && WiFi.status() == WL_CONNECTED)
  {
    timeClient.update();
    checkTime();
    lastTime = millis();
  }
  if (WiFi.status() != WL_CONNECTED || WiFi.getMode() == 2)
  {
    if (currentTime - lastTime > 60)
    {
      led_controller_fade();

      lastTime = millis();
    }
  }
}
