
float railVoltage = 5.00;

void setup() {
    Serial.begin(9600);
}



void loop() {
    float voltage = (railVoltage / 1023) * analogRead(A0);
    Serial.println(voltage, 2);
}
