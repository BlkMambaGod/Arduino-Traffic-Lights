#include <pitches.h>

class Beeper { // The beeping module class
  private:
  static const int pin = 10;
  int button;

  public:
  Beeper(int button) : button(button) {}
  
  // getters & setters
  int getPin() const { return pin; }

  // void setPin(int pin) { this->pin = pin; }

  int getButton() const { return button; }

  void setButton(int button) { this->button = button; }

  // methods
  void setup() const {
    pinMode(pin, OUTPUT);
    pinMode(button, INPUT);
  }

  void beep(int note, int freq) const {
    tone(pin, note, freq);
  }

  void signal(int note, int freq) const {
    tone(pin, note, freq);
  }
};

class Countdown { // The 7 segment module fot the countdown
  private: 
  int dataPin, latchPin, clockPin;
  static const int DIGITS[10] = {0B11111100, 0B01100000, 0B11011010, 0B11110010, 0B01100110, 0B10110110, 0B10111110, 0B11100000, 0B11111110, 0B11110110};
  
  public:
  Countdown(int dataPin, int latchPin, int clockPin) :
            dataPin(dataPin), latchPin(latchPin), clockPin(clockPin) {}
  
  //getters
  int getDataPin() const { return dataPin; }

  int getLatchPin() const { return latchPin; }

  int getClockPin() const { return clockPin; }
  
  //setters
  void setDataPin(int dataPin) { this->dataPin = dataPin; }

  void setLatchPin(int latchPin) { this->latchPin = latchPin; }

  void setClockPin(int clockPin) { this->clockPin = clockPin;}

  //methods

  void count() {}


  void setup() {
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
  }
      

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
  Beeper beep;
  unsigned long blink;
  bool red_state;

  
  public:
  Ped_lights(int white, int red, Beeper beep) : white(white), red(red), beep(beep) {
    red_state = false;
  }
  
  void setup() {
    pinMode(white, OUTPUT);
    pinMode(red, OUTPUT);
    timer.setup();
    blink = millis();
  }
  //getters
  int getWhite() const { return white; }

  int getRed() const { return red; }

  Beeper getBeep() const { return beep; }

  Countdown getTimer() const { return timer; }

  unsigned long getBlink() const { return blink; }

  bool getRed_state() const { return red_state; }


  
  //setters
  void setBlink(unsigned long time) { blink = time; }

  void setWhite(int white) { this->white = white; }

  void setRed(int red) { this->red = red; }

  void setRed_state(bool state) { red_state = state; }


  //Methods
  void go() const {
    digitalWrite(white, true);
    digitalWrite(red, false);
  }

  void hurry() {
    digitalWrite(white, false);

    // blinking the light
      unsigned long now = millis();
      if (now - blink >= 1000) {
        blink = now;
        if (red_state == true)
          red_state = false;
        else
          red_state = true;
        digitalWrite(red, red_state);
        beep.beep(NOTE_C6, 100);
        
        // timer.count();
      }


  }

  void stop() const {
    digitalWrite(white, false);
    digitalWrite(red, true);
  }
};


class Traffic_lights {
  private:
  Car_lights car;
  Ped_lights ped;

 
  public:
  Traffic_lights(Car_lights car, Ped_lights ped) : car(car), ped(ped) {}
    
  //getters
  Car_lights getcar() const { return car; }

  Ped_lights getped() const { return ped; }

  //setters
  void setcar(Car_lights car) { this->car = car; }

  void setped(Ped_lights ped) { this->ped = ped; }

  //Methods
  void setup() {
    car.setup();
    ped.setup();
  }

  void go() const {
    car.go();
    ped.go();
  }

  void hurry() const {
    car.hurry();
    ped.hurry();
  }

  void stop() const {
    car.stop();
    ped.stop();
  }
};




unsigned long start;

Beeper beep_one(9);
Beeper beep_two(8);

Countdown Ped_lights::timer(9, 12, 13);
// Car_lights c_verti(49, 50, 51);
// Ped_lights p_verti(52, 53);
// bool red_state = false;


void setup() {
  start = millis();
  // unsigned long Ped_lights::blink = millis();
  // c_verti.setup();
  // p_verti.setup();
}
 
void loop() { 
  unsigned long now = millis();

  if (now - start < 5000) {
    // c_verti.go();
    // p_verti.go();
    //beta = stop
  }
  else
    if (now - start < 8000) {
      // c_verti.hurry();
      // p_verti.hurry();
      //beta = stop
    }
    else
      if (now - start < 13000) {
        // c_verti.stop();
        // p_verti.stop();
        //beta = go
      }
      else
        if ( now - start < 16000) {
          // c_verti.freak_on();
          //beta = hurry
        }
        else {
          // restart the process
          // c_verti.freak_off();
          start = now;
        }
}