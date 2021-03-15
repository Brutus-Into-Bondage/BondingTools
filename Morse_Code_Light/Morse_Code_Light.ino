int pin = 13;

void setup() 
{
  pinMode(pin, OUTPUT);
}

void loop() 
{
  dash(); dot(); dash(); dot();
  delay(1000);
  dot(); dash(); dot(); dot();
  delay(1000);
  dash(); dash(); dash();
  delay(1000);
  dash(); dot(); dash(); dot();
  delay(1000);
  dash(); dot(); dash();
  delay(3000);
}

void dot()
{
  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  delay(250);
}

void dash()
{
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(250);
}
