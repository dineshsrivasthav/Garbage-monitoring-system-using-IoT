
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SimpleTimer.h>
char auth[] = "MFidRmlFa2wBWnbYXuSmligC-BrEYfN7";
char ssid[] = "Dinesh";
char pass[] = "5*******";
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(11, 10); // RX, TX
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);
#define trigPin  8
#define echoPin  9
BlynkTimer timer;


void myTimerEvent()
{
 
}
void CheckDistance()
{
long cm,duration, inches;
pinMode(trigPin, OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
Serial.print(inches);
Serial.print("in ");
Serial.println(cm);
Blynk.virtualWrite(V5, inches);
//Check whether Bin is full or not
if(inches < 2)
{
Blynk.virtualWrite(V3, 255);
Blynk.notify(" Overflow!!");
}
delay(1000);
}
long microsecondsToCentimeters(long microseconds) {

  return microseconds / 29 / 2;
}

long microsecondsToInches(long microseconds) {
 
  return microseconds / 74 / 2;
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

  timer.setInterval(3000, CheckDistance);
}



void loop()
{
  Blynk.run();
  timer.run();
}
