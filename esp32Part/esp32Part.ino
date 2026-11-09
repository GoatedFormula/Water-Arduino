#define BLYNK_TEMPLATE_ID "TMPL3u97bDpbM"
#define BLYNK_TEMPLATE_NAME "Alert"
#define BLYNK_AUTH_TOKEN "a0U21GD5uK8nCOzNk8KDgnG6VLCYjqZ2"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

bool ringed = false;

char ssid[] = "HONOR 600 LITE"; //wifi name
char pass[] = "teseyivjgq"; //wifi psw
char auth[] = BLYNK_AUTH_TOKEN;

char msg[] = "water over"; //mesej

void setup() {
  Serial.begin(9600);

  pinMode(18, INPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  if(digitalRead(18) == HIGH && ringed == false){
    Blynk.logEvent("alerting");
    ringed = true;
  }

  if(digitalRead(18) == LOW){
    ringed = false;
  }
}