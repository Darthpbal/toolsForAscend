int pCellPin = A0;

void setup() {
    Serial.begin(9600);
    Serial.println("adcVal\tvoltage\tlight level");
}



void loop() {
    int adcVal = analogRead(pCellPin);
    Serial.print(adcVal);
    Serial.print("\t");
    Serial.print(adcVal * 5.0 / 1023);
    Serial.print("\t");
    Serial.println(1023 - adcVal);

    delay(1000);
}
