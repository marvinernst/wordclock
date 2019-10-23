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
const char *localPassword = "clock";

const long utcOffsetInSeconds = 3600;

const int NEOPIXEL_PIN = 5;
const long INTERVAL = 1000;

long color[] = {254, 0, 0};
float brightness = 1;
unsigned long lastTime = 0;
int minutes = 0;
int hours = 0;
// Define Timeserver
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "0.de.pool.ntp.org", 3600);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
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
void wifiConnect();

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  if (SPIFFS.begin())
  {
    Serial.println(F("\nSPIFFS mounted"));
  }
  else
  {
    Serial.println(F("\nFailed to mount SPIFFS"));
  }

  Serial.println();
  Serial.print("Starting Clock ... ");
  wifiConnect();
  /**
   * Erstellt den Server für die LED Steuerung
   */
  initServer();

  /**
   * Eigenlicher Code für die Uhr
   */
  delay(1000);

  initClock();

  //pixels.begin();
  //pixels.clear();
  // pixels.show();
}

void loop()
{
  server.handleClient();
  unsigned long currentTime = millis();

  if (currentTime - lastTime > INTERVAL)
  {

    timeClient.update();

    checkTime();

    lastTime = millis();
  }
}
