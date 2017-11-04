// HC-SR04 Ultrasonic Range Finder testing

// Pinouts
#define ECHO 3     //HC-SR04, echo response (interrupt driven)
#define TRIGGER 4  //HC-SR04, trigger

// Note: this device requires an interrupt pin for the echo signal
// Echo must be pin 2 or pin 3, as they are the
// are the only pins that can service the interrupt handler
int sonicEchoPin = ECHO;              //To enable sensor, echoPin must be set to DIO0 or DIO1. See sonicEnable(echo,trigger)
int sonicTriggerPin = TRIGGER;        //This pin can be setup to be any other available DIO.
int sonicCycleTime = 1000/20;         //milliseconds between pings (1000/20 = 50ms = 20hz)
long sonicCycleTimer = 0;             //time to next ping
volatile long sonicPingStart = 0;     //The start time of a ping in microseconds
volatile int sonicPingTime = 0;       //Last measured ping time in microseconds


void setup() {
  Serial.begin(115200);
  pinMode(sonicEchoPin,INPUT);
  pinMode(sonicTriggerPin,OUTPUT);
  digitalWrite(sonicTriggerPin,LOW);
  //Enable interrupt routine to capture falling edge in trigger pin
  attachInterrupt(digitalPinToInterrupt(sonicEchoPin),sonicInterrupt,FALLING);
}


// Initiate a ping at a steady periodic rate
void sonicUpdate() {
  if (sonicCycleTimer < millis()) {
    //Time to ping.  Set timer ahead for next ping.
    sonicCycleTimer += sonicCycleTime;
    //Mark start time of the ping.  Interrupt handler uses this value.
    sonicPingStart = micros();
    //Send a 10us pulse to trigger ping
    digitalWrite(sonicTriggerPin,HIGH);
    delayMicroseconds(10);  
    digitalWrite(sonicTriggerPin,LOW);
  }
}

// Interrupt occurs whenever sonic echo pin FALLs. Calcs echo time.
void sonicInterrupt() {
  sonicPingTime = micros() - sonicPingStart;  
}


// Sonic distance calculation in centimeters
int sonicCentimeters() {
  // calibrated based on observed measurements
  //return sonicPingTime * 0.017391 - 8.23478;  
  return sonicPingTime * 0.017391 - 9.5;  
}


void loop() {
  sonicUpdate();       // Update the HC-SR04 sonic sensor
  int distance = sonicCentimeters();
  delay(10);
  Serial.println(sonicCentimeters());
}
