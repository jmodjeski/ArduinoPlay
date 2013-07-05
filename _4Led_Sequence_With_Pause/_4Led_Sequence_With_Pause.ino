

// program configuration
const int LED0 = 6; // LEDS on IO
const int LED1 = 3;
const int LED2 = 4;
const int LED3 = 5;
const int SWITCH = 2; // Switch is on IO2 - need interrupt

int pinState = 0x00;
boolean paused;

int leds[] = {LED0, LED1, LED2, LED3 };


void setup()
{
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  pinMode(SWITCH, INPUT);
  attachInterrupt(0, hook_switch, CHANGE); 
  
  Serial.begin(9600);
}

void loop()
{
  int ledCount = (sizeof(leds) / sizeof(LED0));
  for(int i = 0; i < ledCount; i++)
  {
    handle_pause();
    toggle(leds[i]);
    delay(500);
    handle_pause();
    toggle(leds[i]);
    delay(500);
  }
}

void hook_switch()
{
  int value = digitalRead(SWITCH);
  Serial.print("Button State is ");
  Serial.println(value);
  if(HIGH == value)
  {
    paused = 1 ^ paused;
  }
}

void handle_pause()
{
  while(paused)
  {
    delay(10);
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
