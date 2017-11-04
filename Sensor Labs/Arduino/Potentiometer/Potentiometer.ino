// Potentiometer calibration practice

float offset = 0.0;   //volts at 0 degrees
float scale = 0.0;    //degrees per volt

float inputFloat(String message) {
  int inChar;
  String inString;
  Serial.print(message);
  while (inChar != '\n') { 
    while (Serial.available() > 0) {
      inChar = Serial.read();
      if (inChar != '\n') {
        inString += (char)inChar;
      }
    }
  }
  float f = inString.toFloat();
  Serial.println(f);
  return f;
}

void getCalibrations() {
  Serial.println("");
  offset = inputFloat("Press Enter to begin calibration or enter an Offset value: ");
  if (offset > 0) {
    scale = inputFloat("Enter a Scale factor: ");
  } else {
    scale = 0.0;
  }
}

void setup() {
  Serial.begin(115200);
  getCalibrations();
}

void loop() {
  float volts = analogRead(A1) / 1024.0 * 5.0;
  Serial.print(volts);
  Serial.print("    ");
  int degrees = (volts-offset) * scale;
  Serial.println(degrees);
  if (Serial.available() > 0) {
    Serial.flush();
    getCalibrations();
  }
}
