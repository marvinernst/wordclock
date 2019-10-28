void createConnection()
{
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    led_controller_count();
    Serial.print(".");
    if (millis() - startTime > 20000)
    {
      Serial.println("Connection Timeout");
      break;
    }
  }
}
void wifiConnect()
{
  Serial.println("Try to connect");
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);
  if (SPIFFS.exists("/config.json"))
  {
    Serial.println("File exists");

    File configFile = SPIFFS.open("/config.json", "r+");

    if (configFile)
    {
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      configFile.close();

      DynamicJsonBuffer jsonBuffer;
      JsonObject &jObject = jsonBuffer.parseObject(buf.get());

      if (jObject.success())
      {
        String ssid = jObject["ssid"];
        String password = jObject["password"];
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        createConnection();
        IPAddress nGateway = WiFi.gatewayIP();
        IPAddress nSubnet = WiFi.subnetMask();
        IPAddress nIP = WiFi.gatewayIP();
        nIP[3] = 77;
        Serial.println(nGateway);
        Serial.println(nSubnet);
        Serial.println(nIP);
        WiFi.config(nIP, nGateway, nSubnet);
        WiFi.reconnect();
        createConnection();
        Serial.println(WiFi.localIP());
      }
    }
  }
  else
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println('CONNECTED');
    }
    else
    {
      Serial.println("AccesPointMode");
      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(local_ip, gateway, subnet);
      WiFi.softAP("cl{}ck", "123456789");
      Serial.println(WiFi.gatewayIP());
    }
  }
  Serial.println("");
  WiFi.printDiag(Serial);
}
