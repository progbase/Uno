#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3);
int BluetoothData;

void bt_setup(int ledPin) {
  // put your setup code here, to run once:
  BT.begin(9600);
  BT.println("Bluetooth On please press 1 or blink LED ...");
  pinMode(ledPin, OUTPUT);
}

int bt_loop(int ledPin) {
  // put your main code here, to run repeatedly:
  if (BT.available() )
  {
    BluetoothData = BT.read();
    if (BluetoothData == '1')
    {
      // if number 1 pressed ....
      digitalWrite(ledPin, 1);
      BT.println("LED On D13 ON ! ");
      return 1;
    }
    else if (BluetoothData == '0')
    {
      digitalWrite(ledPin, 0);
      BT.println("LED On D13 Off ! ");
      return 0;
    }
    else
    {
       return -1;
    }
  }
}
