
#include "LED_Guess_The_Light_Game.h"

// program configuration
const int LED0 = 3; // LEDS on IO
const int LED1 = 4;
const int LED2 = 5;
const int LED3 = 6;
const int LED_WIN = 8;
const int LED_LOSE = 9;
const int SWITCH = 2; // Switch is on IO2 - need interrupt
const int TOLERANCE = 500;

int leds[] = {LED0, LED1, LED2, LED3 };
int ledCount = sizeof(leds)/sizeof(LED0);
int game_led = 0;
const int NO_PICK = -1;
int volatile picked_led = NO_PICK;
int current_led = NO_PICK;


void setup()
{
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED_WIN, OUTPUT);
  pinMode(LED_LOSE, OUTPUT);
  
  pinMode(SWITCH, INPUT);
  attachInterrupt(0, hook_switch, CHANGE); 
  
  Serial.begin(9600);
}

void apply_all(toggleFunc_t func)
{
  for(int i = 0; i < ledCount; i++)
  {
    func(i);
  }
}

void loop()
{
  initialize_game();
  game_loop();
}

void initialize_game()
{
  // seed with a read from an unconnected pin
  //randomSeed(analogRead(0));
  
  off(LED_WIN);
  off(LED_LOSE);
  off(LED0);
  off(LED1);
  off(LED2);
  off(LED3);
  delay(1000);
  
  picked_led = NO_PICK;
  current_led = NO_PICK;
  game_led = leds[random(0, ledCount)];
  // turn everything off
  off(LED0);
  off(LED1);
  off(LED2);
  off(LED3);
  delay(1000); // delay 1 second
  // all on to show we are resetting
  on(LED0);
  on(LED1);
  on(LED2);
  on(LED3);
  delay(TOLERANCE * 2);
  off(LED0);
  off(LED1);
  off(LED2);
  off(LED3);
  // game on!
}

void game_loop()
{
  do
  {
    for(int i = 0; i < ledCount; i++)
    {
      on(leds[i]);
      current_led = leds[i];
      delay(TOLERANCE * 2);
      // break the loop before we turn off the led
      if(picked_led != NO_PICK)
        break;
      off(leds[i]);
    }
  }while(picked_led == NO_PICK);
  
  int final_led = LED_LOSE;
  if(picked_led == game_led)
  {
   final_led = LED_WIN; 
  }
  
  off(LED0);
  off(LED1);
  off(LED2);
  off(LED3);
  delay(10);
  on(game_led);
  on(picked_led);
  for(int i = 0; i < 5; i++)
  {
    on(final_led);
    on(game_led);
    delay(TOLERANCE);
    off(final_led);
    off(game_led);
    delay(TOLERANCE);
  }
}

void hook_switch()
{
  int value = digitalRead(SWITCH);
  if(HIGH == value && picked_led == NO_PICK)
  {
    Serial.print("Picked led ");
    picked_led = current_led;
    Serial.println(picked_led);
  }
}

void off(int pin)
{
  digitalWrite(pin, 0);
}

void on(int pin)
{
  digitalWrite(pin, 1);
}
