const byte selPin = 8;

const bool on = LOW, off = HIGH;

void setup() {
    Serial.begin(9600);  // transmits to master controller
    pinMode(selPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}



void loop() {
    float voltage = analogRead(A0) * 5 / 1023;


    bool selState = digitalRead(selPin);
    if(selState == on){
        digitalWrite(LED_BUILTIN, HIGH);

        Serial.print(voltage); Serial.print(',');
        Serial.print('\n');

        while(digitalRead(selPin) == off);

        digitalWrite(LED_BUILTIN, LOW);
    }
}
