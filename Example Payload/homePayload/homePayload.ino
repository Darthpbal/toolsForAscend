/*

Here's another go at making a mock payload electronics system as an educational example of how one could go from an empty text file to a filled launch file.

This should be interpreted as a sort of timeline/mission log of decisions made and why and in what order.


 - STarting from an empty text file, I add empty setup and loop functions.

 - Sometimes the text logging gets weird (especially recently!) so lets get basic logging of our header out of the way first.
 - I've filled an extra large breadboard with as many sensors as I could cram into it, and I'll try to get all of them working quickly as a demo. I don't know yet if I'll run out of program space.
    The sensorset (grouped by interface type) includes a SPI altimeter, gyro, LCD screen, and sd logger.
    A temp and humidity sensor that use the ONEWIRE protocol.
    Analog light sensor and triple axis accel.
    I2C based magnetometer and real time clock
    UART based bluetooth
    Swithing power regulator is implemented in the breadboard with the output connected to a switch and then to the rest of the circuit with the input being just a 9V battery snap connector. This means that when the battery is connected, the regulator is energized, but seperated from the rest of the system through the switch, allowing me to test the voltage without the circuit connected. This also allows me to connect the system to my laptop using USB without crossing power streams between the battery and my laptop because that is VERY bad form and could break something.
    At this point, I've laid out all these on one board, connected all the power, and connected only the SPI pins for the gyro and the sd card. The connections are on the gyro only to bridge further to the sd logger board since that's what I want to start with this time so I can incrementally add more and more stuff to the sd card file.


 - Now that I know the sensors I'm using, I can lay out the sd card stuff up to the header. I add the SPI and sd includers. I add the sd card globals like the File object and the card detect and filename stuff.
 - I'm experiencing some weird behavior where sometimes the card detect doesn't work and I get several initialization errors, but after more testing it seemed to just go away.
 - Now that my program is built up to the header log, I can finish my sensor connections and test the sensors individually.
 - I've finished stepping through all of the sensors aside from the bluetooth, LCD screen, and photocell because I'm not sure how much their use is affecting power consumption, and I think power consumption could be related to the weird behavior I was experiencing earlier. I'm going to start adding the libraries and globals to the launch day program and start checking program space.
 - I've finished putting all the stuff into the startup and ran the program to see if it would compile and all sensors would checkout. I only had an issue with one sensor and that was because I accidentally put the wrong pin. I ran the test code again to double check and corrected the pin.
 - I just finished filling the loop with all of the sensor data and I'm printing all of it minus the photocell data to the serial monitor. The photocell is not hooked up at this point, and the bluetooth/LCD are hooked up but not being used, so they're probably not sucking as much power as they eventually will. I'm not logging anything yet. I'm only printing to the monitor at this point and I'm compiling to 80% program space and 72% dynamic memory for my UNO. I'll not try actually logging to see how it goes. Also the powerup for this test went well. No faulty weird behavior, it went directly to waiting for the sd card, created a new file, checked and passed all the sensors, and then went on collecting data.
 - So I'm hitting the same problem I was having before that I though was due to some kind of string overflow memory related problem where my string might get concatenated too much to get logged to the sd card somehow. SO I tried moving the header (which fails as a string) to use more direct SD open and printing formatting and it works just fine. And I also reduced program space from 80% to 50%. So at this point the loop is making that problem as well. SO my next step is to move all of my string concatenations to store floats locally and then simply print in my header order to the sd all at once later. This way I don't lose the benefit of my sd card only being open a breif moment.
 - Just finished moving all the data to their own variables and then just log it all at the end of the loop. It looks like it works perfectly. So I'm gonna lower the delays to see if any weird behaviors arise, and eventually remove the delay all together. At this point I'm compiling at 70% program space and 72% dynamic memory and have full functionality with no delays
 - I'm just doing more long term testing and checking the data using GLUE. I found a trailing delimiter in the header that messed up GLUE's CSV alignment. So I removed that. And It also looks like my GYRO data is not coming through. The original gyro functions are slightly modified, and I already tested this jazz with the gyro functions, so i know that the board should work. The next things to do will be to find the problem and fix the gyro data, and then convert the accel data to be in meters per second or in Gs
 - Looks like the only thing missing from the gyro code was a spi.begin. That's it. I haven't fixed the accel stuff since the raw data gives me acceleration feedback. So maybe I'll push back the accell stuff until after I add the photocell back.
 - It looks like the gyro misbehaves sometimes regardless. I realized I didn't have a gyro SPI status check in the code, so I added it and realized that the address check for the gyro fails. But it will sometimes still read a rotation value. But I can't really get a consistency. When it works, it works a good while, and when it doesn't I have a very hard time finding anything that triggers it to work. Even the example code would not work properly. But at this point I got the gyro working, added a photocell, was unsatisfied with the range I was seeing when using the photocell at 5V so I switched to using one of the sensors 3.3V out pin to provide a smaller less noisy (hopefully, it's on the sd card so I dunno) power for the photocell voltage reading. Now I believe I have all sensors incoming.
 - Test is done. Gyro didn't work again. Don't know why. Don't know if I care. Light worked. Battery got so cold it died. i made a foam enclosure with duct tape, used a temp sensor with a different package to reach outside the enclosure and added an RGB led for status indication. The system died around 3 degrees F. And the humidity spiked as well. My hope is that the enclosure provides a significant difference in insulation and longevity of lifetime since the battery shouldn't get too cold. I'll use and altimeter temp sensors to imply the batt temp.
 - Okay, so I started getting more weird behavior after I started getting past the 75% program size for the UNO and I start getting those program space warnings. I start to get a DHT failure. I couldn't track down any code related to the DHT itself that was triggering the error, especially since the only consistent behavior I had was that the DHT would fail and never be able to connect only on launch configuration. ENUM shouldn't affect the DHT, though the compile size was drastically different and under the warning threshold, so that could affect it. After re-downloading a previous version I had send to edwin that had the indicator lights implemented which still worked. I was then able to track the error down to the line where I log a c-string containing the header line to the sd card. I don't know why this would cause the problem, but it's the only consistent thing I have right now. I'm running the old file built back up to most recent, and the only line that I had that is messing up is that one. The char array still exists, and I'm still serial printing it when in debug model. So I don't know why this would be a problem. But If I simply switch to sd printing a string literal instead of a stored c-string, it works fine.
 - At this point I've pretty much fixed the launch DHT problem, though I don't understand the underlying problem that caused it. But since it's only occuring from this particular program, and possibly is linked to the large program size, I might just not care enough to dive too much deeper.
 - Since I've added the second temp sensor, along with the ability to check for them and identify them individually and then fixed the stupid DHT error, and also the indicator light, I don't know what else to do. So I might just stop here.
 - I just want to note here that I DIDN'T use git or github to manage development of this project. If I did, I believe that finding the source of that DHT issue and recovering a previous working version of the program would have been a lot easier. It took a couple hours because I can't justify why the line that causes the problem does that. If I used git, I would create "commits" for every major milestone of the program like adding indicator lights, and you can rollback your edits to any previous commit. So I wouldn't have to rely on the fact that I happen to send a version to someone to get a working version back to track down the specific changes I made since then. Git is complicated at first, but after you learn it, you don't know what you'd do without it. Thanks Linus Torvalds.
 - I have 1 pin left, and it's a digital pin. I have a buzzer on the breadboard, but it isn't wired up, and it isn't programed. I could however use the digital pin to drive the buzzer to make a sound beacond so the payload can be heard. This should be easy to implement, but I don't know if the DHT problems came from the program size, so I don't know if other weird stuff will pop up from the slight addition of code. Playing specific notes could take significantly more memory, but use of the EEPROM could make the tones not impact the program size too much, especially if other global constants are moved to EEPROM like for example the large C-string header. This would however mean that if you want to change the header, you need to write a new header to the EEPROM. But that's an uncommon action, and therefore could be not that much of an issue. That would mean the header is read from EEPROM instead of program memory.
 - I could improve the quality of measurment of acceleration and light by using one of the board 3.3V out as the analogReference. This would make the ADC resolution scale to 3.3V instead of the possibly fluctuating 5V rail. I also never actually put in the work to get correct acceleration values from this sensor. So that would probably be an improvement. It seems like it has sensible responses, but I hadn't gotten the values to convert to ~1g correctly. They're usually sitting at 1/2g. I think I had the sensor working previously, but since this response is good enough for graphing, I don't really care.



 FEATURES IMPLEMENTED:
    - Data aquisition of internal/external temp, baro pressure, humidity, relative light levels, acceleration, magnetometer, and a RTC clock for tracking time. Gyro is physically implemented, but has consistent failures. I've left this since I couldn't keep it working with the example library. In the end, this is convenient for educational purposes since I always have mostly sensor passes but one gyro failure. This means you have a consistent startup sequence to expect.
    - Single breadboard (small footprint) implementation
    - Switching power regulator for varying battery supply voltage with a power switch placed to seperate the regulator from the system while adjusting for new battery levels.
    - High logging speed at ~13Hz tested.
    - Easy switching between modes using the SD card and serial printing for debuggin, live plotting, and cutting the Serial Printing time out of the launch program. Serial printing is relatively slow, and this amounts to gains in log speed. The ability to switch modes also means that debug and graphing mode don't require the SD card to be inserted. Since formatting is different for logging vs plotting, this also makes quickly switching the format easy as well. This is controled by a single "mode" variable.
    - Indicator light, 3X white/purple/cyan blinks signaling startup and launch/debug/plot modes, blue and red blinks sensor status checks, yellow solid waiting for SD card status, and periodic lower power green blinking for logging. If the sd card is removed, the system goes back into the yellow state and when reinserted the system goes back into green.
*/


enum configuration { debug, plot, launch };
const configuration mode = launch;



#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <MS5xxx.h>
#include <OneWire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <RTClib.h>
/* 
 *  this RTC lib also contains methods for keeping real time using the millis function. 
 *  A hardware RTC will keep accurate time significantly longer because it uses a higher frequency clock 
 *  to approximate 1 second much closer than the arduino clock that is only meant really for controller and calculating oeprations.
 *  I've never tested this internal clock based RTC library, because I only realized it existed when working on this project because I was
 *  wasting time reading RTC library documentation instead of programming the RTC itself.
 *  https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/overview
*/
int redPin = 3, greenPin = 2, bluePin = 7;
enum color {RED, GREEN, BLUE, YELLOW, CYAN, PURPLE, WHITE, LEDOFF};
int blinkDel = 500, logBlinkDel = 5000;
unsigned long lastBlinkTime = 0;
bool ledOn = false;

RTC_DS3231 rtc;


Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// gyro definitions
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_TSH_XH 0x32
#define INT1_TSH_XL 0x33
#define INT1_TSH_YH 0x34
#define INT1_TSH_YL 0x35
#define INT1_TSH_ZH 0x36
#define INT1_TSH_ZL 0x37
#define INT1_DURATION 0x38


const int gyroSel = 6;

// gyro readings
int xGyro, yGyro, zGyro;
// end gyro definitions



MS5xxx altimeter(&Wire);



OneWire  thermometer(5);  // on pin 10 (a 4.7K resistor is necessary)
byte tempAddr[8],
    tempExt[8] = {0x28, 0x9C, 0x59, 0x4, 0x0, 0x0, 0x80, 0x36},
    tempInt[8] = {0x28, 0xF2, 0x91, 0xAB, 0x5, 0x0, 0x0, 0x70};




#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);



File logFile;
char fileName[] = "logFile.csv";
const uint8_t logSelect = 10;
const uint8_t cardDetect = 9;
bool alreadyBegan = false;




char delim;



void setup() {
    Serial.begin(9600);
    delay(100); // Sometimes the serial monitor is clipped in the beginning, so this helps. 
    Serial.println(F("Starting up..."));

    // setup LED
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    setColor(LEDOFF);

    // signal startup & mode
    for(int i = 0; i < 3; i++){
        if(mode == launch) setColor(WHITE);
        else if(mode == debug) setColor(PURPLE);
        else if(mode == plot) setColor(CYAN);

        delay(blinkDel);
        setColor(LEDOFF);
        delay(blinkDel);
    }



    Serial.print(F("mode = "));
    if(mode == launch)  Serial.println(F("launch"));
    else if(mode == debug)  Serial.println(F("debug"));
    else if(mode == plot)  Serial.println(F("plot"));



    // Set delimiter type. Normal logging and debugging calls for comma but the plotter needs tabs
    if(mode == plot) delim = '\t';
    else delim = ',';


    //Start system check. The arduino steps through all sensors to check if they are responsive. If yes, the system blinks blue, if no response, blink red.
    // Currently there is no system check for my analog sensors being the 3 axis accel and the photocell. 
    //However if I wanted to make a system check for that, I might examine the waveform of the disconnected analog pins. From memory and expectations I'd think you'd see a wide range of high frequency measured voltages. 
    //I also happen to have a photocell and an accel that have relatively low noise responses, so I could possibly make a check that tests the analog pin for a duration of time and gets an average change in voltage. And if the magnitude is above a threshold for that sensor, then it would be interpretted as either disconnected or misbehaving. So that could be a redblink condition. 
    //That functionality could be abstracted to a function that checks an arbitrary pin for an arbitrary noise level threshold, which could call for creating a function for measuring that value for an unconnected pin and any new analog sensor one might want.


    if(altimeter.connect() > 0) {
        Serial.println("alt fail...");
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    else {
        Serial.println(F("alt pass"));
        setColor(BLUE);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    delay(100);


    bool extPass = FALSE;
    bool intPass = FALSE;
    while(thermometer.search(tempAddr)){
        bool extCheck = TRUE;
        bool intCheck = TRUE;
        for(int i = 0; i < 8; i++){
            if( tempAddr[i] != tempExt[i] ) {
                extCheck = FALSE;
            }
            if( tempAddr[i] != tempInt[i] ) {
                intCheck = FALSE;
            }
        }
        if(intCheck){
            Serial.println(F("internal temp pass"));
            setColor(BLUE);
            delay(blinkDel);
            setColor(LEDOFF);
            intPass = TRUE;
        }

        if(extCheck){
            Serial.println(F("external temp pass"));
            setColor(BLUE);
            delay(blinkDel);
            setColor(LEDOFF);
            extPass = TRUE;
        }
    }
    if(!extPass) {
        Serial.println(F("external temp fail..."));
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
        delay(100);
    }
    if(!intPass) {
        Serial.println(F("internal temp fail..."));
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
        delay(100);
    }
    if(extPass && intPass) delay(100);


    dht.begin();

    float tempCHum = dht.readTemperature();
    if( isnan(tempCHum)){
        Serial.println(F("humidity fail"));
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    else{
        Serial.println(F("humidity pass"));
        setColor(BLUE);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    delay(100);




    // gyro
    // not sure if these three lines are needed yet.
    SPI.begin();
    // SPI.setDataMode(SPI_MODE3);
    // SPI.setClockDivider(SPI_CLOCK_DIV8);
    pinMode(gyroSel, OUTPUT);
    digitalWrite(gyroSel, HIGH);
    delay(100);
    if(setupL3G4200D(2) == -1) {
        Serial.println("gyro fail");
        Serial.print("0x");
        Serial.println(readRegister(WHO_AM_I), HEX);
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    else{
        Serial.println("gyro pass");
        setColor(BLUE);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    delay(100);
    // end gyro






    // compass
    if(!mag.begin())
    {
        Serial.println("mag fail...");
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    else {
        Serial.println(F("mag pass"));
        setColor(BLUE);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    delay(100);
    // end compass



    if (!rtc.begin()) {
        Serial.println("rtc fail...");
        setColor(RED);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    else {
        Serial.println(F("rtc pass"));
        setColor(BLUE);
        delay(blinkDel);
        setColor(LEDOFF);
    }
    delay(100);
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    pinMode(cardDetect, INPUT);
    if(mode == launch) initializeCard();

    char header[] = "temp(alt),press(alt),tempExt(dalas),tempInt(dalas),temp(dht11),humid(dht11),lightLvl(photCel),X(acel),Y(acel),Z(acel),X(gyro),Y(gyro),Z(gyro),X(mag),Y(mag),Z(mag),heaDeg(mag),compas(mag),date,time,millis\n";

    if(mode == launch){
        logFile = SD.open(fileName, FILE_WRITE);
        if (logFile){
            // For some reason printing the c-string version of the header here will cause the DHT sensor to fail the sensor check and never successfully connect. I have no idea why. This represents kind of an outlier behavior event for me, unless someone more experienced can confirm that this is from the large program space stability warnings coming from the arduino ide.
            // logFile.print(header);
            logFile.print("temp(alt),press(alt),tempExt(dalas),tempInt(dalas),temp(dht11),humid(dht11),lightLvl(photCel),X(acel),Y(acel),Z(acel),X(gyro),Y(gyro),Z(gyro),X(mag),Y(mag),Z(mag),heaDeg(mag),compas(mag),date,time,millis\n");
            logFile.close();
        }
        else {
            Serial.println(F("Error opening logFile"));
        }
    }
    else if(mode == debug){
        Serial.print(header);
    }


    Serial.println(F("Startup finished"));
}



void loop() {
    if (!digitalRead(cardDetect) && mode == launch){
        initializeCard();
    }


    if( millis() - lastBlinkTime >= logBlinkDel ){
        setColor(GREEN);
        ledOn = TRUE;
        lastBlinkTime = millis();
    }
    else if( millis() - lastBlinkTime >= 100 && ledOn ){
        setColor(LEDOFF);
        ledOn = FALSE;
        lastBlinkTime = millis();
    }


    altimeter.ReadProm();
    altimeter.Readout();
    float tempCAlt = altimeter.GetTemp() / 100;
    float presAlt = altimeter.GetPres();


    byte data[12];
    thermometer.reset();
    thermometer.select(tempExt);
    thermometer.write(0x44, 1);
    thermometer.reset();
    thermometer.select(tempExt);
    thermometer.write(0xBE);
    for (int i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = thermometer.read();
    }
    int16_t raw = (data[1] << 8) | data[0];
    float tempCExtThermometer = (float)(raw / 16.0) * 1.8 + 32.0;

    thermometer.reset();
    thermometer.select(tempInt);
    thermometer.write(0x44, 1);
    thermometer.reset();
    thermometer.select(tempInt);
    thermometer.write(0xBE);
    for (int i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = thermometer.read();
    }
    raw = (data[1] << 8) | data[0];
    float tempCIntThermometer = (float)(raw / 16.0) * 1.8 + 32.0;


    float tempCHum = dht.readTemperature();
    float humidity = dht.readHumidity();



    int lightLvl = analogRead(3) * 5.0 / 1023;


    int xAccel = analogRead(0);
    int yAccel = analogRead(1);
    int zAccel = analogRead(2);


    getGyroValues();  // This will update x, y, and z with new gyro values





    sensors_event_t event;
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    float declinationAngle = 0.182;
    heading += declinationAngle;
    if(heading < 0) heading += 2*PI;
    if(heading > 2*PI) heading -= 2*PI;
    float headingDegrees = heading * 180/M_PI;


    DateTime now = rtc.now(); // update the time variable.



    if(mode == launch){
        logFile = SD.open(fileName, FILE_WRITE);
        if (logFile){
            logFile.print(tempCAlt);
            logFile.print(delim);
            logFile.print(presAlt);
            logFile.print(delim);

            logFile.print(tempCExtThermometer);
            logFile.print(delim);

            logFile.print(tempCIntThermometer);
            logFile.print(delim);

            logFile.print(tempCHum);
            logFile.print(delim);
            logFile.print(humidity);
            logFile.print(delim);

            logFile.print(lightLvl);
            logFile.print(delim);

            logFile.print(xAccel);
            logFile.print(delim);
            logFile.print(yAccel);
            logFile.print(delim);
            logFile.print(zAccel);
            logFile.print(delim);

            logFile.print(xGyro);
            logFile.print(delim);
            logFile.print(yGyro);
            logFile.print(delim);
            logFile.print(zGyro);
            logFile.print(delim);

            logFile.print(event.magnetic.x);
            logFile.print(delim);
            logFile.print(event.magnetic.y);
            logFile.print(delim);
            logFile.print(event.magnetic.z);
            logFile.print(delim);
            logFile.print(headingDegrees);
            logFile.print(delim);
            if(int(headingDegrees) > 315 || int(headingDegrees) < 45) logFile.print("north");
            else if(int(headingDegrees) > 135 && int(headingDegrees) < 255) logFile.print("south");
            else if(int(headingDegrees) > 45 && int(headingDegrees) < 135) logFile.print("east");
            else if(int(headingDegrees) > 255 && int(headingDegrees) < 315) logFile.print("west");
            logFile.print(delim);


            if(now.day() < 10) logFile.print('0');
            logFile.print(now.day());
            logFile.print('/');
            if(now.month() < 10) logFile.print('0');
            logFile.print(now.month());
            logFile.print('/');
            if(now.year() < 10) logFile.print('0');
            logFile.print(now.year());
            logFile.print(delim);


            if(now.hour() < 10) logFile.print('0');
            logFile.print(now.hour());
            logFile.print(':');
            if(now.minute() < 10) logFile.print('0');
            logFile.print(now.minute());
            logFile.print(':');
            if(now.second() < 10) logFile.print('0');
            logFile.print(now.second());
            logFile.print(delim);


            logFile.println(millis());

            logFile.close();
        }
    }
    else{ // uncomment what you want to see.
        // Serial.print(tempCAlt);
        // Serial.print(delim);
        // Serial.print(presAlt);
        // Serial.print(delim);
        //
//        Serial.print(tempCExtThermometer);
//        Serial.print(delim);

//        Serial.print(tempCIntThermometer);
        // Serial.print(delim);
        //
        // Serial.print(tempCHum);
        // Serial.print(delim);
        // Serial.print(humidity);
        // Serial.print(delim);
        //
        // Serial.print(lightLvl);
        // Serial.print(delim);
        //
        // Serial.print(xAccel);
        // Serial.print(delim);
        // Serial.print(yAccel);
        // Serial.print(delim);
        // Serial.print(zAccel);
        // Serial.print(delim);
        //
        // Serial.print(xGyro);
        // Serial.print(delim);
        // Serial.print(yGyro);
        // Serial.print(delim);
        // Serial.print(zGyro);
        // Serial.print(delim);
        //
        // Serial.print(event.magnetic.x);
        // Serial.print(delim);
        // Serial.print(event.magnetic.y);
        // Serial.print(delim);
        // Serial.print(event.magnetic.z);
        // Serial.print(delim);
        // Serial.print(headingDegrees);
        // Serial.print(delim);
        // if(int(headingDegrees) > 315 || int(headingDegrees) < 45) Serial.print("north");
        // else if(int(headingDegrees) > 135 && int(headingDegrees) < 255) Serial.print("south");
        // else if(int(headingDegrees) > 45 && int(headingDegrees) < 135) Serial.print("east");
        // else if(int(headingDegrees) > 255 && int(headingDegrees) < 315) Serial.print("west");
        // Serial.print(delim);



        // if(now.day() < 10) Serial.print('0');
        // Serial.print(now.day());
        // Serial.print('/');
        // if(now.month() < 10) Serial.print('0');
        // Serial.print(now.month());
        // Serial.print('/');
        // if(now.year() < 10) Serial.print('0');
        // Serial.print(now.year());
        // Serial.print(delim);
        //
        //
        // if(now.hour() < 10) Serial.print('0');
        // Serial.print(now.hour());
        // Serial.print(':');
        // if(now.minute() < 10) Serial.print('0');
        // Serial.print(now.minute());
        // Serial.print(':');
        // if(now.second() < 10) Serial.print('0');
        // Serial.print(now.second());
        // Serial.print(delim);


         Serial.print(millis());

        Serial.println();

        if(mode == debug) delay(1 * 500);
    }




}




void initializeCard(void){
    Serial.print(F("Initializing SD card..."));

    // Is there even a card?
    if (!digitalRead(cardDetect)){
        Serial.println(F("No card detected. Waiting for card."));
        setColor(YELLOW);
        while (!digitalRead(cardDetect));
        delay(250); // 'Debounce insertion'
        setColor(LEDOFF);
    }

    // Card seems to exist.  begin() returns failure
    // even if it worked if it's not the first call.
    if (!SD.begin(logSelect) && !alreadyBegan){  // begin uses half-speed...
        Serial.println(F("Initialization failed!"));
        initializeCard(); // Possible infinite retry loop is as valid as anything
    }
    else{
        alreadyBegan = true;
    }
    Serial.println(F("Initialization done."));

    Serial.print(fileName);
    if (SD.exists(fileName)){
        Serial.println(F(" exists."));
    }
    else{
        Serial.println(F(" doesn't exist. Creating."));
    }

    Serial.print("Opening file: ");
    Serial.println(fileName);
}









int readRegister(byte address)
{
  int toRead;

  address |= 0x80;  // This tells the L3G4200D we're reading;

  digitalWrite(gyroSel, LOW);
  SPI.transfer(address);
  toRead = SPI.transfer(0x00);
  digitalWrite(gyroSel, HIGH);

  return toRead;
}

void writeRegister(byte address, byte data)
{
  address &= 0x7F;  // This to tell the L3G4200D we're writing

  digitalWrite(gyroSel, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(gyroSel, HIGH);
}

int setupL3G4200D(byte fullScale)
{
  // Let's first check that we're communicating properly
  // The WHO_AM_I register should read 0xD3
  if(readRegister(WHO_AM_I)!=0xD3)
    return -1;

  // Enable x, y, z and turn off power down:
  writeRegister(CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:
  fullScale &= 0x03;
  writeRegister(CTRL_REG4, fullScale<<4);

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(CTRL_REG5, 0b00000000);
}

void getGyroValues()
{
  xGyro = (readRegister(0x29)&0xFF)<<8;
  xGyro |= (readRegister(0x28)&0xFF);

  yGyro = (readRegister(0x2B)&0xFF)<<8;
  yGyro |= (readRegister(0x2A)&0xFF);

  zGyro = (readRegister(0x2D)&0xFF)<<8;
  zGyro |= (readRegister(0x2C)&0xFF);
}








void setColor(color ledColor){
    switch(ledColor){
        case RED:
            //redPin
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, HIGH);
            digitalWrite(bluePin, HIGH);
        break;
        case GREEN:
            //greenPin
            digitalWrite(redPin, HIGH);
            digitalWrite(greenPin, LOW);
            digitalWrite(bluePin, HIGH);
        break;
        case BLUE:
            //bluePin
            digitalWrite(redPin, HIGH);
            digitalWrite(greenPin, HIGH);
            digitalWrite(bluePin, LOW);
        break;
        case YELLOW:
            //yellow
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, LOW);
            digitalWrite(bluePin, HIGH);
        break;
        case CYAN:
            //cyan
            digitalWrite(redPin, HIGH);
            digitalWrite(greenPin, LOW);
            digitalWrite(bluePin, LOW);
        break;
        case PURPLE:
            //purple.
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, HIGH);
            digitalWrite(bluePin, LOW);
        break;
        case WHITE:
            // white
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, LOW);
            digitalWrite(bluePin, LOW);
        break;
        default:
            // off
            digitalWrite(redPin, HIGH);
            digitalWrite(greenPin, HIGH);
            digitalWrite(bluePin, HIGH);
        break;
    }

}
