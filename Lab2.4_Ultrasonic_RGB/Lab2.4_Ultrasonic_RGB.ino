#define trigPin 13
#define echoPin 12
#define LED_red 4
#define LED_green 2
#define LED_blue 7

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_blue, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  long duration, distance;
  digitalWrite(trigPin, LOW); // start trig at 0
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // The rising edge of trig pulse
  delayMicroseconds(10);       // decides duration of trig pulse
  digitalWrite(trigPin, LOW);  // falling edge of the trig pulse
  // NOTE: echo pin reads HIGH till it receives the reflected signal
  duration = pulseIn(echoPin, HIGH); // Reading the duration for which echoPin was HIGH gives
  // you the time the sensor receives a reflected signal at the echo pin
  distance = (duration / 2) / 29.1; // Calculate the distance of the reflecting surface in cm

  Serial.print("distance:");
  Serial.println(distance);
  if (distance <= 10)
  {
    digitalWrite(LED_red, HIGH);
    digitalWrite(LED_green, LOW);
    digitalWrite(LED_blue, LOW);
  }
  else if (distance >= 10 && distance <= 30)
  {
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_green, HIGH);
    digitalWrite(LED_blue, LOW);
  }
  else
  {
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_green, LOW);
    digitalWrite(LED_blue, HIGH);
  }
  delay(500);
}
