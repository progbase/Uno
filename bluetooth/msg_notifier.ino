#include <SoftwareSerial.h>
int mg = 0;
const int ledPin = LED_BUILTIN;
int ledState = LOW;
char data = 0;
SoftwareSerial btSerial(2, 3); // RX, TX

void  messanger()
{
  char data = 0;
  if (Serial.available() > 0)
  {
    data = Serial.read();
    btSerial.print(data);
    mg = 0;
  }else if (btSerial.available() > 0)
  {
    data = btSerial.read();
    Serial.print(data);
    mg = 1;
  }
}
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  btSerial.begin(9600);
}

void loop()
{
  messanger();
  if (mg == 1)
    digitalWrite(ledPin, HIGH);
  else if (mg == 0)
    digitalWrite(ledPin, LOW);
}
