#define BLYNK_TEMPLATE_ID "TMPL6lZHByZAh"
#define BLYNK_TEMPLATE_NAME "Alert"
#define BLYNK_AUTH_TOKEN "a0U21GD5uK8nCOzNk8KDgnG6VLCYjqZ2"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiManager.h>

const int trig = 13;
const int wifiResetPin = 46;

char auth[] = BLYNK_AUTH_TOKEN;
char msg[] = "Alert triggered";

BlynkTimer timer;
bool alertSent = false;

void checkSensor()
{
    int sensorValue = digitalRead(trig);

    if (sensorValue == HIGH && !alertSent)
    {
        Blynk.logEvent("Alert", msg);
        alertSent = true;
    }

    if (sensorValue == LOW)
    {
        alertSent = false;
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(trig, INPUT);
    pinMode(wifiResetPin, INPUT);
    pinMode(4 , OUTPUT);

    WiFi.mode(WIFI_STA);

    WiFiManager wm;

    if (digitalRead(wifiResetPin) == HIGH)
    {
        wm.resetSettings();

        if (!wm.startConfigPortal("wifi setup", "12345678"))
        {
            ESP.restart();
        }
    }
    else
    {
        if (!wm.autoConnect("wifi setup", "12345678"))
        {
            ESP.restart();
        }
    }

    Blynk.config(auth);

    timer.setInterval(500L, checkSensor);
}

void loop()
{
    digitalWrite(4 , HIGH);
    Blynk.run();
    timer.run();
}