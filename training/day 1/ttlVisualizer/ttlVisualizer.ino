int pin = A0;

float railVoltage = 5.00;

int inputHighMin = 614,
    inputLowMax = 307;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}



void loop() {
    int adcLvl = averageAnalogRead(pin);

    if(adcLvl > inputHighMin) Serial.print(F("1.00"));
    else if(adcLvl < inputLowMax) Serial.print(F("0.00"));
    else Serial.print(F("0.50"));

    Serial.print(F("\t"));

    Serial.print(digitalRead(2));

    Serial.print(F("\t"));

    Serial.println(calcVolt(adcLvl), 2);
}





//calculated and scaled to the same size as the digital graph
float calcVolt(int adcLvl){
    return (1.0 / 1023) * adcLvl;
}




//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead){
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);
}








/*

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(2));
  Serial.print('\t');
  float lvl = (1.0 / 1023) * analogRead(A0);
  Serial.println(lvl, 2);
}

*/
