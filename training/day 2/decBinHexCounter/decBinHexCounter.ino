int out[4] = { 12, 11, 10, 9 };
byte count = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(out[3], OUTPUT);
  pinMode(out[2], OUTPUT);
  pinMode(out[1], OUTPUT);
  pinMode(out[0], OUTPUT);

  for(int i = 0; i < 4; i++){
      digitalWrite(out[i], LOW);
  }

  Serial.println("\n\nDECIMAL\tBINARY\tHEX");
}

void loop() {
  // put your main code here, to run repeatedly:

  switch(count){
      case 0:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], LOW);
        break;

      case 1:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], HIGH);
        break;

      case 2:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], LOW);
        break;

      case 3:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], HIGH);
        break;

      case 4:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], LOW);
        break;

      case 5:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], HIGH);
        break;

      case 6:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], LOW);
        break;

      case 7:
        digitalWrite(out[3], LOW);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], HIGH);
        break;

      case 8:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], LOW);
        break;

      case 9:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], HIGH);
        break;

      case 10:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], LOW);
        break;

      case 11:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], LOW);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], HIGH);
        break;

      case 12:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], LOW);
        break;

      case 13:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], LOW);
        digitalWrite(out[0], HIGH);
        break;

      case 14:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], LOW);
        break;

      case 15:
        digitalWrite(out[3], HIGH);
        digitalWrite(out[2], HIGH);
        digitalWrite(out[1], HIGH);
        digitalWrite(out[0], HIGH);
        break;

      default:
        for(int i = 0; i < 4; i++){
          digitalWrite(out[i], LOW);
        }
        break;
  }

  Serial.print(count, DEC);
  Serial.print("\t");
//  Serial.print(count, BIN);
  printBits(count);
  Serial.print("\t0x");
  Serial.print(count, HEX);

  Serial.println();

  if(count == 15){
    count = 0;
    Serial.println();
  }
  else count++;
  
  delay(3000);
}






void printBits(byte myByte){
 for(byte mask = 0x08; mask; mask >>= 1){
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
 }
}
