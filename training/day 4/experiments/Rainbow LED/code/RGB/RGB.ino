/*************************************************************************
 * name:Rainbow LED
 * Function:you can see RGB LED flash red, green and blue first, and then change to red, orange, yellow, green, blue, indigo and purple.
 * Note:because the RGB module is common anode,so when you want to turn on a color ,you need to set it as 0
 ********************************************************************/
const int redPin = 11;  // R petal on RGB LED module connected to digital pin 11
const int greenPin = 10;  // G petal on RGB LED module connected to digital pin 10
const int bluePin = 9;  // B petal on RGB LED module connected to digital pin 9

const int buzzerPin = 7;//the buzzer pin attach to
int fre;//set the variable to store the frequence value
/**************************************************************************/
void setup()
{
  pinMode(redPin, OUTPUT); // sets the redPin to be an output
  pinMode(greenPin, OUTPUT); // sets the greenPin to be an output
  pinMode(bluePin, OUTPUT); // sets the bluePin to be an output
  pinMode(buzzerPin,OUTPUT);//set buzzerPin as OUTPUT
}
/***************************************************************************/
void loop()  // run over and over again
{
  // Basic colors:
  color(0,255,255); // turn the RGB LED red
  delay(1000); // delay for 1 second
  color(255,0,255); // turn the RGB LED green
  delay(1000); // delay for 1 second
  color(255,255,0); // turn the RGB LED blue
  delay(1000); // delay for 1 second
  // Example blended colors:
  color(0,255,255); // turn the RGB LED red
  delay(1000); // delay for 1 second
  color(0,128,255); // turn the RGB LED orange
  delay(1000); // delay for 1 second
  color(0,0,255); // turn the RGB LED yellow
  delay(1000); // delay for 1 second
  color(255,0,255); // turn the RGB LED green
  delay(1000); // delay for 1 second
  color(255,255,0); // turn the RGB LED blue
  delay(1000); // delay for 1 second
  color(255,0,0); // turn the RGB LED  indigo
  delay(1000); // delay for 1 second
  color(128,255,0); // turn the RGB LED purple
  delay(1000); // delay for 1 second

color(0,0,0); // turn the RGB LED purple

  for(int i = 200;i <= 800;i++)   //frequence loop from 200 to 800
  {
    tone(buzzerPin,i);   //in pin7 generate a tone,it frequence is i
    delay(5);    //wait for 5 milliseconds
  }
  delay(1000);   //wait for 4 seconds on highest frequence
  for(int i = 800;i >= 200;i--)  //frequence loop from 800 downto 200
  {
    tone(buzzerPin,i);  //in pin7 generate a tone,it frequence is i
    delay(10);  //delay 10ms
  }
  noTone(buzzerPin);
}
/******************************************************/
void color (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function
{
  analogWrite(redPin, red);
  analogWrite(bluePin, blue);
  analogWrite(greenPin, green);
}
/******************************************************/
