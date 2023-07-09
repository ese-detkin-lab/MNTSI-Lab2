#define trigPin 2
#define echoPin 3

void setup () {
  pinMode (trigPin , OUTPUT );
  pinMode (echoPin , INPUT );
  Serial.begin (9600);
}

void loop () {
  long duration , distance;
  digitalWrite (trigPin , LOW ); // start trig at 0
  delayMicroseconds (2);
  digitalWrite (trigPin , HIGH ); //The rising edge of trig pulse
  delayMicroseconds (10); // decides duration of trig pulse
  digitalWrite (trigPin , LOW ); //falling edge of the trig pulse
  // NOTE: echo pin reads HIGH till it receives the reflected signal
  duration = pulseIn (echoPin , HIGH ); // Reading the duration for which echoPin was HIGH gives
  //you the time the sensor receives a reflected signal at the echo pin
  distance = (duration / 2) / 29.1; //Calculate the distance of the reflecting surface in cm

  Serial.print("distance:");
  Serial.println(distance);
  delay(500);
}


