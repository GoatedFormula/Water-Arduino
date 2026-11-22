
int sensorPin = A0;
int greenLED = 2;
int yellowLED = 3;
int redLED = 4;
int buzzer = 5;

int trig = 13;

void setup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int waterLevel = analogRead(sensorPin);
  Serial.println(waterLevel);

  if (waterLevel < 233)
  {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

    digitalWrite(trig, LOW);
  }
  else if (waterLevel < 350)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzer, LOW);

    digitalWrite(trig, LOW);
  }
  else if (waterLevel > 650)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, HIGH);

    digitalWrite(trig, HIGH);
  }
}

a0U21GD5uK8nCOzNk8KDgnG6VLCYjqZ2
