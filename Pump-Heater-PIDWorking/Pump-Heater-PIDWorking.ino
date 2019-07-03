
int PUMP = 13;
int HEATER = 12;
float SetPoint = 6400;
float KU=0.0008;
float TU=1000.0;
float KI=1.2*KU/TU;
float KP=0.6*KU;
float KD=3*KU*TU/40;

float lastDR;
float DR;
float P=0.0;
float I=0.0;
float D=0.0;
float dOutput;
float Output=150.0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  analogReference(DEFAULT);
  pinMode(PUMP, OUTPUT);
  pinMode(HEATER, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  // read the input on analog pin 0:
  int monitorValue = analogRead(A0);
  int sensorValue = analogRead(A1);
  long naverage;
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float resistance =  resistance+(1023.0/sensorValue-1.0)*6767.00;
  float resistanceM = resistanceM+(1023.0/monitorValue-1.0)*9984.00;
  naverage++;
  
  // print out the value you read:

  unsigned long lastmillis=0;
  float lastDR;

  if( millis() % 1000 == 0  ) 
  {
   resistance = resistance/naverage;
   resistanceM = resistanceM/naverage;
   naverage=0;
   lastDR=DR;
   DR=resistance-SetPoint;
   P=DR;
   I=I+DR;
   D=DR-lastDR;

    dOutput=KP*P+KD*D+KI*I;
  
    Output = Output+dOutput;

   if(Output>255.0) Output=255.0;
    if(Output<0.0) Output=0.0;
  
    analogWrite(HEATER, Output);
    digitalWrite(PUMP, HIGH);   // turn the LED on (HIGH is the voltage level  

    Serial.print(resistance); 
    Serial.print(" ");
    //Serial.print(Output*20) ;
    //Serial.print(" ");
    Serial.println(SetPoint);
    //Serial.print(" ");
    //Serial.println(resistanceM);
    lastmillis=millis();
  }
  
// delay(10);  // wait
}
