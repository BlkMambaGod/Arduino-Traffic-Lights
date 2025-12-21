#include <pitches.h>

/* alpha     : 49 - 53
   beta      : 22 - 26
   7-segment : 11 - 13
   buzzer    : 10
   */

// LED Pins
int c_alpha_g = 22;
int c_alpha_y = 23;
int c_alpha_r = 24;
int p_alpha_w = 25;
int p_alpha_r = 26;


int c_beta_g = 49;
int c_beta_y = 50;
int c_beta_r = 51;
int p_beta_w = 52;
int p_beta_r = 53;


int buzzer = 10;

// 7 segment 
int dataPin = 11;
int latchPin = 12;
int clockPin = 13;

const int digits[10] = {0B11111100, 0B01100000, 0B11011010, 0B11110010, 0B01100110, 0B10110110, 0B10111110, 0B11100000, 0B11111110, 0B11110110};

// Light variables
int photores = A15;
int lux;
const int treshold = 50;

// Control variables
unsigned long blink;
bool state = false;
int i = 9; // for tracking the digits index
bool cycle_over;


void setup() {
  pinMode(c_alpha_g, OUTPUT);
  pinMode(c_alpha_y, OUTPUT);
  pinMode(c_alpha_r, OUTPUT);
  pinMode(p_alpha_w, OUTPUT);
  pinMode(p_alpha_r, OUTPUT);

  pinMode(c_beta_g, OUTPUT);
  pinMode(c_beta_y, OUTPUT);
  pinMode(c_beta_r, OUTPUT);
  pinMode(p_beta_w, OUTPUT);
  pinMode(p_beta_r, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  cycle_over = true;

  blink = millis();
}

void loop() {
  lux = analogRead(photores);
  if(cycle_over && lux > treshold)
    day_cycle();
  else
    if(cycle_over && lux < treshold)
      night_cycle();
}

/*******************************************************************METHODS************************************************************************************/

void blinking(int red_light) {
  if (millis() - blink > 1000) { // blinking speed
    blink = millis();
    if (state == true)
      state = false;
    else
      state = true;
    digitalWrite(red_light, state);
    tone(buzzer, NOTE_C6, 100);
    digitalWrite(latchPin, false);
    shiftOut(dataPin, clockPin, MSBFIRST, digits[i--]);
    digitalWrite(latchPin, true);
  }
}

void day_cycle() {
  // cycle start
  cycle_over = false;
  if (millis() % 40000 < 10000) { // alpha go
    i = 9; //resetting the index
    digitalWrite(c_alpha_g, true);
    digitalWrite(c_alpha_y, false);
    digitalWrite(c_alpha_r, false);
    digitalWrite(p_alpha_w, true);
    digitalWrite(p_alpha_r, false);

    digitalWrite(c_beta_g, false);
    digitalWrite(c_beta_y, false);
    digitalWrite(c_beta_r, true);
    digitalWrite(p_beta_w, false);
    digitalWrite(p_beta_r, true);

    digitalWrite(latchPin, false);
    shiftOut(dataPin, clockPin, MSBFIRST, 0B00000000);
    digitalWrite(latchPin, true);
  }
  else
    if (millis() % 40000 < 20000) {
      if (millis() % 40000 < 15000) { // pedestrian countdown starts
        digitalWrite(p_alpha_w, false); // turn of pedestrian go light
        blinking(p_alpha_r);
      }
      else { // alpha turns yellow
        digitalWrite(c_alpha_g, false);
        digitalWrite(c_alpha_y, true);
        blinking(p_alpha_r);
      }
    }
    /***********************************************************END OF FIRST HALF***********************************************************************/
    else
      if (millis() % 40000 < 30000) { // alpha stop & beta go
        i = 9; //resetting the index
        digitalWrite(c_alpha_g, false);
        digitalWrite(c_alpha_y, false);
        digitalWrite(c_alpha_r, true);
        digitalWrite(p_alpha_w, false);
        digitalWrite(p_alpha_r, true);

        digitalWrite(c_beta_g, true);
        digitalWrite(c_beta_y, false);
        digitalWrite(c_beta_r, false);
        digitalWrite(p_beta_w, true);
        digitalWrite(p_beta_r, false);

        digitalWrite(latchPin, false);
        shiftOut(dataPin, clockPin, MSBFIRST, 0B00000000);
        digitalWrite(latchPin, true);
      }
      else
        if (millis() % 40000 < 40000) {
          if (millis() % 40000 < 35000) { // pedestrian countdown starts
            digitalWrite(p_beta_w, false); // turn of pedestrian go light
            blinking(p_beta_r);
          }
          else { // beta turns yellow
            digitalWrite(c_beta_g, false);
            digitalWrite(c_beta_y, true);
            blinking(p_beta_r);
          }
        }
        /***********************************************************END OF CYCLE***********************************************************************/
        cycle_over = true;
}

void night_cycle() {
  cycle_over = false;
  digitalWrite(c_alpha_g, false);
  digitalWrite(c_alpha_y, false);
  digitalWrite(c_alpha_r, false);
  digitalWrite(p_alpha_w, false);
  digitalWrite(p_alpha_r, false);

  digitalWrite(c_beta_g, false);
  digitalWrite(c_beta_y, false);
  digitalWrite(c_beta_r, false);
  digitalWrite(p_beta_w, false);
  digitalWrite(p_beta_r, false);
  cycle_over = true;
}