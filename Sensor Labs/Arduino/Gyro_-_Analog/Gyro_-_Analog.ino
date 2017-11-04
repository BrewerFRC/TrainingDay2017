// Gyro demonstration

float center = 0.0;  //calibrated center voltage
float accum = 0.0;   //accumulated gyro angle
float scale = 0.717; //Multiplier to convert readings to degrees

void setup() {
  Serial.begin(115200);
  pinMode(2,INPUT_PULLUP);
}

float calibrate() {
  Serial.println("Calibration started...");
  int count = 0;
  float cal = 0;
  float center = 0;
  
  while (count < 300) {
    long loopTime = micros() + 10000;  //10ms
    cal += (analogRead(A0));
    count += 1;
    while (micros() < loopTime) {}
  }
  
  center = cal / 300.0;
  Serial.println(center,4);
  Serial.println("...Calibration complete");
  delay(5000);
  
  return (center);
}


void loop() {
  center = calibrate(); 
  accum = 0;
  while (true) {
    long loopTime = micros() + 10000;  //10ms
    accum += (analogRead(A0) - center) / 100.0;  //Add the velocity divided for 1/100th of a sec
    if (digitalRead(2) == 0) {
      center = calibrate();
      accum = 0;
    }
    Serial.println(accum * scale);
    while (micros() < loopTime) {}
  }
}

