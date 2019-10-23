  
void turnOnLed(const int id[])
{
  long r = color[0] * brightness;
  long g = color[1] * brightness;
  long b = color[2] * brightness;

  long pixelColor = pixels.Color(r, g, b);
  for (int i = 0; i < 1; i++)
  {
    pixels.setPixelColor(id[i], pixelColor);
  }
}


void clearAll()
{
  for (int i = 4; i < 28; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}
