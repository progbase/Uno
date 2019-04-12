void step_setup(int powPin)
{
  pinMode(powPin, OUTPUT);
}

void drop_card(int powPin)
{
	digitalWrite(powPin, 1);
	delay(200);
	digitalWrite(powPin, 0);
}

void poweroff(int powPin)
{
  digitalWrite(powPin, 0);
}

void poweron(int powPin)
{
  digitalWrite(powPin, 1);
  delay(100);
  poweroff(powPin);
}
