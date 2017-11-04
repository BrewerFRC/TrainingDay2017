// Conversion Factor
#define COUNTS_PER_INCH 0.0 
float countsPerInch = 0.0; 


// Pin assignments
#define ENC0_CHA 2    
#define ENC0_CHB 4
#define ENC1_CHA 3  
#define ENC1_CHB 5

volatile long counter0 = 0;
volatile long counter1 = 0;


//ASR for encoder0 counting
void encoder0() {
  if (digitalRead(ENC0_CHB)) {
    counter0 ++;
  } else {
    counter0 -= 1;
  }
}

//ASR for encoder0 counting
void encoder1() {
  if (digitalRead(ENC1_CHB)) {
    counter1 ++;
  } else {
    counter1 -= 1;
  }
}

float inputFloat(String prompt) {
  int inChar;
  String inString;
  Serial.print(prompt);
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

void setup() {
  // setup for encoders 0 and 1
  pinMode(ENC0_CHA,INPUT);
  pinMode(ENC0_CHB,INPUT);
  pinMode(ENC1_CHA,INPUT);
  pinMode(ENC1_CHB,INPUT);
  attachInterrupt(0,encoder0,RISING);
  attachInterrupt(1,encoder1,RISING);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(counter0);
  Serial.print("  ");
  //Serial.print(counter0 / COUNTS_PER_INCH);
  Serial.print(counter0 / countsPerInch);
  //Serial.print(counter1);
  Serial.println("");
  if (Serial.available() > 0) {
    countsPerInch = inputFloat("Enter calibration factor in counts/inch: ");
    counter0 = 0;
  }
  delay(100);
}


