

void initClock() {
  
  timeClient.begin();
  delay(20);
  checkCorners();
  checkTime();
}

void checkCorners()
{
  const int cornerID = (timeClient.getMinutes() % 5) - 1;

  if (cornerID >= 0)
  {
    for (int i = 0; i <= cornerID; i++)
    {
       turnOnLed(CORNER_LEDS[i]);
    }
   
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      pixels.setPixelColor(CORNER_LEDS[i][0], pixels.Color(0, 0, 0));
    }
  }

  pixels.show();
}

void checkTime() {

  checkCorners();

  
    minutes = timeClient.getMinutes();
    minutes = minutes - (minutes % 5);
    hours = timeClient.getHours()+1;
    if(timeClient.getMinutes() > 19) {
      hours += 1;
    }
    if(hours > 12) {
      hours = hours - 12;
    }
    processTime();
     

  Serial.println(timeClient.getEpochTime());

  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

}

void processTime()
{


  clearAll();
  
  turnOnLed(ES);
  turnOnLed(IST);
  switch (minutes)
  {
  case 5:

    turnOnLed(FUENF);
    turnOnLed(NACH);
    break;
  case 10:
    turnOnLed(ZEHN);
    turnOnLed(NACH);
 
    break;
  case 15:
    turnOnLed(VIERTEL);
    turnOnLed(NACH);

    break;
  case 20:
    turnOnLed(ZWANZIG);
    turnOnLed(NACH);

    break;
  case 25:
    turnOnLed(FUENF);
    turnOnLed(VOR);
    break;
  case 30:
    turnOnLed(HALB);
    break;
  case 35:
    turnOnLed(FUENF);
    turnOnLed(NACH);
    turnOnLed(HALB);
    break;
  case 40:
    turnOnLed(ZEHN);
    turnOnLed(NACH);
    turnOnLed(HALB);
    break;
  case 45:
    turnOnLed(VIERTEL);
    turnOnLed(VOR);
    break;
  case 50:
    turnOnLed(ZEHN);
    turnOnLed(VOR);
    break;
  case 55:
    turnOnLed(FUENF);
    turnOnLed(VOR);
    break;
  default:
    break;
  }

  switch (hours)
  {
  case 1:
     turnOnLed(EINS);
    break;
  case 2:
    turnOnLed(ZWEI);
    break;
  case 3:
  turnOnLed(DREI);
    break;
  case 4:
  turnOnLed(VIER);
    break;
  case 5:
  turnOnLed(FUENF_STUNDE);
    break;
  case 6:
  turnOnLed(SECHS);
    break;
  case 7:
  turnOnLed(SIEBEN);
    break;
  case 8:
  turnOnLed(ACHT);
    break;
  case 9:
  turnOnLed(NEUN);

    break;
  case 10:
  turnOnLed(ZEHN_STUNDE);

    break;
  case 11:
  turnOnLed(ELF);
 
    break;
  case 12:
  turnOnLed(ZWOELF);
    
    break;
  default:
    break;
  }
  pixels.show();
}
