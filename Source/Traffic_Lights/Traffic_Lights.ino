#include <pitches.h>

class Beeper {
  private:
  int pin;

  public:
  Beeper(int pin) : pin(pin) {}

  void setup() {
    pinMode(pin, OUTPUT);
  }

  void beep(int note, int freq) {
    tone(pin, note, freq);
  }
};

class Countdown {
  private: 
  int pin1, pin2, pin3;
  
  
  public:
  Countdown(int pin1, int pin2, int pin3) :
            pin1(pin1), pin2(pin2), pin3(pin3) {}
  
  void setup() {
    pinMode(pin1, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin1, OUTPUT);
  }
      
  //getters
  
  //setters

  //count

  //hurry
};

class Car_lights {
  private:
  int green, yellow, red;
  
  public:
  Car_lights(int green, int yellow, int red) : green(green), yellow(yellow), red(red) {
  }

  void setup() {
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(red, OUTPUT);
  }

  //getters
  
  //setters

  void go() {
    digitalWrite(green, true);
    digitalWrite(yellow, false);
    digitalWrite(red, false);
  }

  void hurry() {
    digitalWrite(green, false);
    digitalWrite(yellow, true);
    digitalWrite(red, false);
  }

  void stop() {
    digitalWrite(green, false);
    digitalWrite(yellow, false);
    digitalWrite(red, true);
  }

  void freak_on() {
    digitalWrite(green, true);
    digitalWrite(yellow, true);
    digitalWrite(red, true);
  }

  void freak_off() {
    digitalWrite(green, false);
    digitalWrite(yellow, false);
    digitalWrite(red, false);
  }
};

class Ped_lights {
  private:
  int white, red;
  static Countdown timer;
  static Beeper beep;
  unsigned long start;
  unsigned long blink;
  bool red_state;

  
  public:
  Ped_lights(int white, int red) : white(white), red(red) {
    red_state = false;
  }
  
  void setup() {
    pinMode(white, OUTPUT);
    pinMode(red, OUTPUT);
    timer.setup();
    blink = millis();
  }
  //getters
  unsigned long getStart() const {
    return start;
  }

  int getWhite() const { return white; }

  int getRed() const { return red; }
  
  //setters
  unsigned long setStart(unsigned long time) {
    start = time;
  }

  void go() const {
    digitalWrite(white, true);
    digitalWrite(red, false);
  }

  void hurry() {
    digitalWrite(white, false);
      unsigned long now = millis();
      if (now - blink >= 500) {
        blink = now;
        if (red_state == true)
          red_state = false;
        else
          red_state = true;
        digitalWrite(red, red_state);
        beep.beep(NOTE_C6, 100);
      }

  }

  void stop() const {
    digitalWrite(white, false);
    digitalWrite(red, true);
  }
};


class Traffic_lights {
  private:
  Car_lights c_alpha;
  Ped_lights p_alpha;
  Car_lights c_beta;
  Ped_lights p_beta;
 
  public:
  Traffic_lights(Car_lights c_alpha, Ped_lights p_alpha, Car_lights c_beta,
                  Ped_lights p_beta) : c_alpha(c_alpha),
                  p_alpha(p_alpha), c_beta(c_beta), p_beta(p_beta) {}
    
  //getters
  
  //setters

  //go

  //hurry

  //stop
};

unsigned long start;
unsigned long blink;
Beeper Ped_lights::beep(10);
Countdown Ped_lights::timer(9, 12, 13);
Car_lights c_verti(49, 50, 51);
Ped_lights p_verti(52, 53);
// bool red_state = false;


void setup() {
  start = millis();
  // unsigned long Ped_lights::blink = millis();
  c_verti.setup();
  p_verti.setup();
}
 
void loop() { 
  unsigned long now = millis();

  if (now - start < 5000) {
    c_verti.go();
    // p_verti.go();
    //beta = stop
  }
  else
    if (now - start < 8000) {
      c_verti.hurry();
      p_verti.hurry();
      //beta = stop
    }
    else
      if (now - start < 13000) {
        c_verti.stop();
        // p_verti.stop();
        //beta = go
      }
      else
        if ( now - start < 16000) {
          c_verti.freak_on();
          //beta = hurry
        }
        else {
          // restart the process
          c_verti.freak_off();
          start = now;
        }
}




