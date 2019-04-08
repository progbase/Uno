int servoPin = 9;
int stepperPin = 8;

int bt_check = -1;
int color_check = -1;
void setup() {
    servo_setup(servoPin);
    bt_setup(LED_BUILTIN);
    step_setup(stepperPin);
    color_setup();
}

void loop() {
  bt_check = bt_loop(LED_BUILTIN);
//  if (bt_check == 1)
//  {
//    poweron(stepperPin);
//    delay(10);
//    poweroff(stepperPin);
//    bt_check = 0;
//  }
//  else if (bt_check == 0)
//    poweroff(stepperPin);
//  poweron(stepperPin);
//  delay(100);
//  poweroff(stepperPin);
//  delay(500);
  color_check = color_read();
  switch (color_check){
//    case -1:
//      Serial.println("NO CARD DETECTED");
//      break;
    case 0:
      Serial.println("Black color??");
      break;
    case 1:
      Serial.println("Red color??");
      break;
    case 2:
      Serial.println("Green color??");
      break;
    case 3:
      Serial.println("Blue color??");
      break;
    case 4:
      Serial.println("Yellow maybe??");
      break;
    default:
      Serial.println("No Card Detected");
      break;
  }
}