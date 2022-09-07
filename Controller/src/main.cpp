#include "main.hpp"

#define RED_PIN 19
#define GREEN_PIN 21
#define BLUE_PIN 5

const char *mqtt_server = "mqtt.timb.one";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

long lastMsg = 0;
int sensorValue;

void setup()
{
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);

  digitalWrite(BLUE_PIN, false);
  digitalWrite(GREEN_PIN, false);
  digitalWrite(RED_PIN, false);

  Serial.begin(115200);
  setup_wifi();
  setup_mqtt();
}

void loop()
{
  // Serial.print("Value: ");
  // Serial.println(analogRead(34));
  if (!client.connected())
  {
    // reconnect_mqtt();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 500)
  {
    lastMsg = now;

    sensorValue = analogRead(34);

    char valueString[8];
    dtostrf(sensorValue, 1, 2, valueString);
    Serial.print("Value: ");
    Serial.println(valueString);

    client.publish("esp32/testSensor", valueString);
  }

  // delay(1000);
}

void setup_wifi()
{
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PW);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_mqtt()
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback_mqtt);
  while (!client.connected())
  {
    if (client.connect("ESP32", MQTT_USER, MQTT_PW))
    {
      client.subscribe("esp32/testColor/#");
    }
  }
}

void callback_mqtt(const char *topic, byte *message, unsigned int length)
{
  Serial.print("Message received: ");
  Serial.println(topic);
  Serial.print("Message: ");

  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == "esp32/testColor/R")
  {
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(RED_PIN, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(RED_PIN, LOW);
    }
  }

  if (String(topic) == "esp32/testColor/G")
  {
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(GREEN_PIN, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(GREEN_PIN, LOW);
    }
  }

  if (String(topic) == "esp32/testColor/B")
  {
    if (messageTemp == "on")
    {
      Serial.println("on");
      digitalWrite(BLUE_PIN, HIGH);
    }
    else if (messageTemp == "off")
    {
      Serial.println("off");
      digitalWrite(BLUE_PIN, LOW);
    }
  }
}