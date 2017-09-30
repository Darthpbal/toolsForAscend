#include <SoftwareSerial.h>

SoftwareSerial mcu_A_port(4,5); // rx, tx
SoftwareSerial mcu_B_port(6,7); // rx, tx


int mcu_A_sel = 2; // slave controller A
int mcu_B_sel = 3; // slave controller B


// these timeouts should be slightly longer than the sensor response time. ie if this sensor takes 2.5 seconds to report data, wait 2.75 to 3 sec
int timeout_A = 3000;
int timeout_B = 3000;

const bool on = LOW, off = HIGH; // english definition of logic state

unsigned long selTime = 0; // used to make sure an accidental disconnect doesn't cause the code to freeze


void setup() {
    Serial.begin(9600);     // hardware serial connected to computer

    mcu_A_port.begin(9600);
    mcu_B_port.begin(9600);

    Serial.println("Startup Finished");
}



void loop() {
    String logLine = "";

    // read slave A
    mcu_A_port.listen();    // required when using multiple software serial ports
    selTime = millis();     // time before checking sensor
    digitalWrite(mcu_A_sel, on); //select controller

    while(!mcu_A_port.available() && (millis() - selTime < timeout_A));     // while no incoming data and while (nowTime - select time) is less than timeout, do nothing.

    if(millis() - selTime < timeout_A) logLine += mcu_A_port.readStringUntil('\n');   // we passed the while loop, check why. If we didn't pass the while loop because of a timeout, then read a string until newline character.
    else logLine += "fault_A,";  // if timeout detected, then add fault to logline instead of data

    digitalWrite(mcu_A_sel, off);  // deselect controller
    // read slave A


    // read slave B
    mcu_B_port.listen();    // required when using multiple software serial ports
    selTime = millis();     // time before checking sensor
    digitalWrite(mcu_B_sel, on); //select controller

    while(!mcu_B_port.available() && (millis() - selTime < timeout_B));     // while no incoming data and while (nowTime - select time) is less than timeout, do nothing.

    if(millis() - selTime < timeout_B) logLine += mcu_B_port.readStringUntil('\n');   // we passed the while loop, check why. If we didn't pass the while loop because of a timeout, then read a string until newline character.
    else logLine += "fault_B,";  // if timeout detected, then add fault to logline instead of data

    digitalWrite(mcu_B_sel, off);  // deselect controller
    // read slave B


    Serial.println(logLine);    // print log line

    delay(2000); // for sanity
}
