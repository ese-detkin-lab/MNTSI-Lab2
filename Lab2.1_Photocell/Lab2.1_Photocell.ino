const int analogPin = A0;
const int LED = 9;

// Function prototypes
// (functions defined at the end of the file)
double adcToVoltage(int adcVal);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  double sensorVoltage = adcToVoltage(sensorValue);
  Serial.print("Measured value: ");
  Serial.println(sensorValue);
  Serial.print("Measured voltage: ");
  Serial.println(sensorVoltage);
  
  digitalWrite(LED, HIGH);
  delay(sensorValue);
  digitalWrite(LED, LOW);
  delay(sensorValue);
}

// Function to convert an ADC value to a 0 to 5 volt voltage
double adcToVoltage(int adcValue){
  return ((double) map(adcValue, 0, 1023, 0, 5000)) / 1000.0D;
}

