#include <WiFiNINA.h>
#include <BH1750.h>
#include <Wire.h>

char ssid[] = "Pardeep_4g";
char password[] = "25141810";

WiFiClient client;
BH1750 lightMeter;

char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME = "/trigger/sunlight/with/key/eF4h04_aJjosUfI7tzeUZ1CvZsh9ZeK6im927MYtbb5";
String queryString = "?value1=57&value2=25";

void setup() {
  Serial.begin(9600);
  Serial.print("START");
  while(!Serial);
  WiFi.begin(ssid, password);
  Wire.begin();
  while(true)
  {
    if(client.connect(HOST_NAME, 80))
    {
      Serial.println("Connected to the Server.");
      break;
    }
    else
    {
      Serial.println("Connection failed.");
    }
    delay(500);
  }
  lightMeter.begin();
  Serial.println("Connected to server");
}

void loop() {
  Serial.print("START");
  float intensity = lightMeter.readLightLevel();
  queryString += "?value1=";
  queryString += intensity;
  Serial.println(queryString);

  if(intensity > 500)
  {
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();

    while(client.connected())
    {
      if(client.available())
      {
        char response = client.read();
        Serial.print(response);
      }
    }
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  }
  queryString = "";
  delay(3000);
}
