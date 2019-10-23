void createConnection()
{
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (millis() - startTime > 10000)
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
        String gateway = jObject["gateway"];
      
        
        WiFi.config(clock_ip, clock_ip, subnet);
        WiFi.begin(ssid, password);
        createConnection();
        // if(gateway) {
        //   WiFi.mode(WIFI_STA);
        //   WiFi.config("192.168.0.112", gateway, subnet);
        //   WiFi.begin(ssid, password);
        //   createConnection();
        // } else {
        //   WiFi.mode(WIFI_STA);
        //   WiFi.begin(ssid, password);
        //   createConnection();
        //   String nGateway = WiFi.gatewayIP();
        //   String nSubnet = WiFi.subnetMask();
        //   Serial.println(nGateway);
        //   Serial.println(nGateway);
        //   jObject["gateway"] = nGateway;
        //   jObject["subnet"] = nSubnet;
        //   WiFi.config("192.168.0.112", nGateway, nSubnet);
        //   WiFi.reconnect();
        // }
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
    }
  }
  Serial.println("");
  WiFi.printDiag(Serial);
}
