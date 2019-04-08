void step_setup(int powPin)
{
  pinMode(powPin, OUTPUT);
}

void poweron(int powPin)
{
  digitalWrite(powPin, 1);
}

void poweroff(int powPin)
{
  digitalWrite(powPin, 0);
}
