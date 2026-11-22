
#define BLYNK_TEMPLATE_ID "TMPL6lZHByZAh"
#define BLYNK_TEMPLATE_NAME "Alert"
#define BLYNK_AUTH_TOKEN "a0U21GD5uK8nCOzNk8KDgnG6VLCYjqZ2"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiManager.h>

const int sensorPin = 8;
const int greenLED = 13;
const int yellowLED = 12;
const int redLED = 11;

char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

bool alertSent = false;

void checkSensor()
{
    int waterLevel = analogRead(sensorPin);

    Serial.println(waterLevel);

    if (waterLevel < 233)
    {
        digitalWrite(greenLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);

        alertSent = false;
    }
    else if (waterLevel < 350)
    {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED, LOW);

        alertSent = false;
    }
    else if (waterLevel > 650)
    {
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, HIGH);

        if (!alertSent && Blynk.connected())
        {
            Blynk.logEvent("alert", "Water level is too high!");
            alertSent = true;
        }
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(sensorPin, INPUT);

    pinMode(greenLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(redLED, OUTPUT);

    WiFi.mode(WIFI_STA);

    WiFiManager wm;

    if (!wm.autoConnect("wifi setup", "12345678"))
    {
        ESP.restart();
    }

    Blynk.config(auth);

    timer.setInterval(500L, checkSensor);
}

void loop()
{
    Blynk.run();
    timer.run();
}
