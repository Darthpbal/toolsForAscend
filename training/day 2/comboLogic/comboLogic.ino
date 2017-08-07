int andPort[3] = {2, 3, 4},
    orPort[3] = {5, 6, 7},
    xorPort[3] = {8, 9, 10},
    notPort[2] = {11, 12};

void setup() {
    for(int i = 0; i < 2; i++){
        pinMode(andPort[i], INPUT);
        pinMode(orPort[i], INPUT);
        pinMode(xorPort[i], INPUT);
    }
    pinMode(andPort[2], OUTPUT);
    pinMode(orPort[2], OUTPUT);
    pinMode(xorPort[2], OUTPUT);

    pinMode(notPort[0], INPUT);
    pinMode(notPort[1], OUTPUT);
}



void loop() {

    if(!digitalRead(andPort[0]) && !digitalRead(andPort[1])) digitalWrite(andPort[2], HIGH);
    else digitalWrite(andPort[2], LOW);

    if(!digitalRead(orPort[0]) || !digitalRead(orPort[1])) digitalWrite(orPort[2], HIGH);
    else digitalWrite(orPort[2], LOW);

    if( (!digitalRead(xorPort[0]) && digitalRead(xorPort[1])) || (digitalRead(xorPort[0]) && !digitalRead(xorPort[1])) ) digitalWrite(xorPort[2], HIGH);
    else digitalWrite(xorPort[2], LOW);

    if(digitalRead(notPort[0])) digitalWrite(notPort[1], HIGH);
    else digitalWrite(notPort[1], LOW);

}
