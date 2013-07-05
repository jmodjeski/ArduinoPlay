
// pin constants
const int DIO2 = 2;
const int DIO3 = 3;
const int DIO4 = 4;
const int DIO5 = 5;

// program configuration
const int LED0 = DIO2;
const int LED1 = DIO3;
const int LED2 = DIO4;
const int LED3 = DIO5;

int pinState = 0x00;

int leds[] = {LED0, LED1, LED2, LED3 };


void setup()
{
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop()
{
  int ledCount = (sizeof(leds) / sizeof(LED0));
  for(int i = 0; i < ledCount; i++)
  {
    toggle(leds[i]);
    delay(500);
    toggle(leds[i]);
    delay(500);
  }
}

void toggle(int pin)
{
  if(bitRead(pinState, pin))
  {
    off(pin);
  }
  else
  {
    on(pin); 
  }
}

void off(int pin)
{
  digitalWrite(pin, 0);
  bitClear(pinState, pin); // tag state as off
}

void on(int pin)
{
  digitalWrite(pin, 1);
  bitSet(pinState, pin); // tag state as on
}
