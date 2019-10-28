
void initServer()
{
  server.on("/", handleRoot);
  server.on("/setup", handleSetup);
  server.on("/setColor", handleSetColor);
  server.on("/setLED", handleSetLED);
  server.on("/login", HTTP_POST, handleLogin);
  server.on("/style.css", []() {
    File file = SPIFFS.open("/style.css", "r");
    server.streamFile(file, "text/css");
    file.close();
  });
  server.on("/login.js", []() {
    File file = SPIFFS.open("/login.js", "r");
    server.streamFile(file, "text/javascript");
    file.close();
  });

  server.on("/inline", []() {
    server.send(200, "text/html", "<h1>this works as well</h1>");
  });
  server.onNotFound(handleNotFound);
  server.begin();
}
void handleRoot()
{
  File file = SPIFFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
  //server.send_P(200, "text/html", formPage);
}

void handleSetup()
{
  File file = SPIFFS.open("/login.html", "r");
  server.streamFile(file, "text/html");
  file.close();
  //server.send_P(200, "text/html", formPage);
}
void handleSetLED()
{
  clearAll();
  long r = color[0] * brightness;
  long g = color[1] * brightness;
  long b = color[2] * brightness;
  long pixelColor = pixels.Color(r, g, b);
  int id = server.arg("id").toInt();
  pixels.setPixelColor(id, pixelColor);
}

void handleLogin()
{
  String data = server.arg("plain");
  Serial.println("data:");
  Serial.print(data);

  DynamicJsonBuffer jBuffer;
  JsonObject &jObject = jBuffer.parseObject(data);
  String ssid = jObject["ssid"];
  String password = jObject["password"];

  File configFile = SPIFFS.open("/config.json", "w");
  if (configFile)
  {
    jObject.printTo(configFile);
    configFile.close();
    server.send(200, "application/json", "{\"status\":\"ok\"}");
  }
  else
  {
    server.send(200, "application/json", "{\"status\":\"error\"}");
  }
  delay(500);

  wifiConnect();
}
void handleSetColor()
{
  Serial.println(server.arg("r"));
  Serial.println(server.arg("g"));
  Serial.println(server.arg("b"));
  color[0] = server.arg("r").toInt();
  color[1] = server.arg("g").toInt();
  color[2] = server.arg("b").toInt();

  server.send(200, "text/html", "<h1>Hallo, ich bins</h1>");
}

void handleNotFound()
{
  if (server.method() == HTTP_OPTIONS)
  {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "*");
    server.send(204);
  }
  else
  {
    server.send(404, "text/plain", "");
  }
}
