#include <pitches.h>

/* alpha     : 49 - 53
   beta      : 22 - 26
   7-segment : 11 - 13
   buzzer    : 10
   */

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

int dataPin = 11;
int latchPin = 12;
int clockPin = 13;

unsigned int start;
unsigned int blink;

const int digits[10] = {0B11111100, 0B01100000, 0B11011010, 0B11110010, 0B01100110, 0B10110110, 0B10111110, 0B11100000, 0B11111110, 0B11110110};

bool state = false;

int i = 9; // for tracking the digits index


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

  start = millis();
  blink = millis();
}

void loop() {
  unsigned long now = millis(); // timer initialization

  // cycle start
  if (now - start < 10000) { // alpha go
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
    //resetting the index
    if (i < 0)
      i = 9;
  }
  else
    if (now - start < 20000) {
      if (now - start < 15000) { // pedestrian countdown starts
        if (now - blink > 1000) { // blinking speed
          blink = now;
          digitalWrite(p_alpha_w, false); // turn of pedestrian go light
          if (state == true)
            state = false;
          else
            state = true;
          digitalWrite(p_alpha_r, state);
          tone(buzzer, NOTE_C6, 100);
          digitalWrite(latchPin, false);
          shiftOut(dataPin, clockPin, MSBFIRST, digits[i--]);
          digitalWrite(latchPin, true);
        }
      }
      else { // alpha turns yellow
        digitalWrite(c_alpha_g, false);
        digitalWrite(c_alpha_y, true);
        if (now - blink > 1000) { // pedestrian countdown continues
          blink = now;
          // digitalWrite(p_alpha_w, false); // turn of pedestrian go light
          if (state == true)
            state = false;
          else
            state = true;
          digitalWrite(p_alpha_r, state);
          tone(buzzer, NOTE_C6, 100);
          digitalWrite(latchPin, false);
          shiftOut(dataPin, clockPin, MSBFIRST, digits[i--]);
          digitalWrite(latchPin, true);
        }
      }
    }
    /***********************************************************END OF FIRST CYCLE***********************************************************************/
    else
      if (now - start < 30000) { // alpha stop & beta go
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
        //resetting the index
        if (i < 0)
          i = 9;
      }
      else
        if (now - start < 40000) {
          if (now - start < 35000) { // pedestrian countdown starts
            if (now - blink > 1000) { // blinking speed
              blink = now;
              digitalWrite(p_beta_w, false); // turn of pedestrian go light
              if (state == true)
                state = false;
              else
                state = true;
              digitalWrite(p_beta_r, state);
              tone(buzzer, NOTE_C6, 100);
              digitalWrite(latchPin, false);
              shiftOut(dataPin, clockPin, MSBFIRST, digits[i--]);
              digitalWrite(latchPin, true);
            }
          }
          else { // beta turns yellow
            digitalWrite(c_beta_g, false);
            digitalWrite(c_beta_y, true);
            if (now - blink > 1000) { // pedestrian countdown continues
              blink = now;
              // digitalWrite(p_beta_w, false); // turn of pedestrian go light
              if (state == true)
                state = false;
              else
                state = true;
              digitalWrite(p_beta_r, state);
              tone(buzzer, NOTE_C6, 100);
              digitalWrite(latchPin, false);
              shiftOut(dataPin, clockPin, MSBFIRST, digits[i--]);
              digitalWrite(latchPin, true);
            }
          }
        }
        /***********************************************************END OF SECOND CYCLE***********************************************************************/
        else { // start over
          start = now;
        }

}