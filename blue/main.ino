const int ledPin = LED_BUILTIN;

void	setup()
{
	bt_setup(ledPin);
}

void	loop()
{
	bt_loop(ledPin);
}
