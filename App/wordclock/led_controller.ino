
void turnOnLed(const int ids[])
{
  long r = color[0] * brightness;
  long g = color[1] * brightness;
  long b = color[2] * brightness;

  long pixelColor = pixels.Color(r, g, b);
  int count = ids[0];
  for (int i = 1; i <= count; i++)
  {
    pixels.setPixelColor(ids[i], pixelColor);
  }
  pixels.show();
}

void led_controller_fade()
{
  Serial.println("FADEEEE");
  if (currentColor >= 20)
  {
    fadeDir = -1;
  }
  if (currentColor <= 5)
  {
    fadeDir = 1;
  }
  currentColor = currentColor + fadeDir;
  uint32_t cColor = pixels.Color(255, 255, 255);
  pixels.setBrightness(currentColor);
  pixels.fill(cColor);
  pixels.show();
}
void led_controller_count()
{
  pixels.clear();
  for (int i = 0; i < 115; i++)
  {
    pixels.setBrightness(25);
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    delay(100);
    pixels.show();
  }
}
void clearAll()
{
  for (int i = 0; i < 116; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}
