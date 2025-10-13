#include <pitches.h>

class Beeper { // The beeping module class
  private:
  static const int pin = 10;
  int button;

  public:
  Beeper(int button) : button(button) {}
  
  // getters & setters
  int getPin() const { return pin; }

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
  
  public:
  //Constructor
  Countdown(int dataPin, int latchPin, int clockPin) :
            dataPin(dataPin), latchPin(latchPin), clockPin(clockPin) {}
  
  //getters
  int getDataPin() const { return dataPin; }

  int getLatchPin() const { return latchPin; }

  int getClockPin() const { return clockPin; }
  
  //setters
  void setDataPin(int dataPin) { this->dataPin = dataPin; }

  void setLatchPin(int latchPin) { this->latchPin = latchPin; }

  void setClockPin(int clockPin) { this->clockPin = clockPin; }

  //methods
  void setup() {
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
  }

  void display(int digit) {
    digitalWrite(latchPin, false);
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    digitalWrite(latchPin, true);
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
  int getGreen() const { return green;}

  int getYellow() const { return yellow; }

  int getRed() const { return red; }
  
  //setters
  void setGreen(int green) { this->green = green; }

  void setYellow(int yellow) { this->yellow = green; }

  void setRed(int red) { this->red = red; }

  //methods
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
  Beeper beep;
  bool red_state = false;

  
  public:
  Ped_lights(int white, int red, Beeper beep) : white(white), red(red), beep(beep) {}
  
  //getters
  int getWhite() const { return white; }

  int getRed() const { return red; }

  Beeper getBeep() const { return beep; }

  bool getRed_state() const { return red_state; }


  
  //setters
  void setWhite(int white) { this->white = white; }

  void setRed(int red) { this->red = red; }

  void setRed_state(bool state) { this->red_state = state; }


  //Methods
  void setup() {
    pinMode(white, OUTPUT);
    pinMode(red, OUTPUT);
    beep.setup();
  }

  void go() const {
    digitalWrite(white, true);
    digitalWrite(red, false);
  }


  void stop() const {
    digitalWrite(white, false);
    digitalWrite(red, true);
  }
};


class Traffic_lights { // Contains all element for a direction light system
  private:
  Car_lights car;
  Ped_lights ped;
  static Countdown timer;
  unsigned long blink;
  const int DIGITS[10] = {0B11111100, 0B01100000, 0B11011010, 0B11110010, 0B01100110, 0B10110110, 0B10111110, 0B11100000, 0B11111110, 0B11110110};
 
  public:
  //Constructor
  Traffic_lights(Car_lights car, Ped_lights ped) : car(car), ped(ped) {
  }
    
  //getters
  Car_lights getCar() const { return car; }

  Ped_lights getPed() const { return ped; }

  Countdown getTimer() const { return timer; }

  unsigned long getBlink() const { return blink; }

  //setters
  void setcar(Car_lights car) { this->car = car; }

  void setped(Ped_lights ped) { this->ped = ped; }

  void setBlink(unsigned long blink) { this->blink = blink; }

  //Methods
  void setup() {
    car.setup();
    ped.setup();
    timer.setup();
    blink = millis();
  }

  void go() const {
    car.go();
    ped.go();
  }

  void hurry() {
    // put the ped light to red
    digitalWrite(ped.getWhite(), false);
    bool state = true;
    int i = 0;

    // blinking the light
    unsigned long now = millis();

    if (now - blink >= 1000) {
      blink = now;
      if (state == true)
        state = false;
      else 
        state = true;
      
      digitalWrite(ped.getRed(), state);
      ped.getBeep().beep(NOTE_C6, 100);
      
      // timer.count();
      timer.display(DIGITS[i++]);
    }
  }
  
  void stop() const {
    car.stop();
    ped.stop();
  }
};




unsigned long start;
// Initialize static element
Countdown Traffic_lights::timer(9, 12, 13);
Beeper beep(9);

// Initializing objects ==> Pin declaration
Car_lights c_alpha(49, 50, 51);
Ped_lights p_alpha(52, 53, beep);

Car_lights c_beta(22, 23, 24);
Ped_lights p_beta(25, 26, beep);

// Aggregation to two direction
Traffic_lights alpha(c_alpha, p_alpha);
Traffic_lights beta(c_beta, p_beta);


void setup() {
  start = millis();
  alpha.setup();
  beta.setup();
}
 
void loop() { 
  unsigned long now = millis();
  alpha.hurry();

  // if (now - start < 5000) { // 1-> Vert, 2-> Rouge
  //   alpha.go();
  //   beta.stop();
  // }
  // else
  //   if (now - start < 8000) { // 1-> Jaune, 2-> Rouge
  //     alpha.getCar().hurry();
  //     // alpha.getPed().hurry();
  //     // beta = stop
  //   }
  //   else
  //     if (now - start < 13000) { // 1-> Rouge, 2-> Vert
  //       alpha.stop();
  //       beta.go();
  //     }
  //     else
  //       if ( now - start < 16000) { // 1-> Rouge, 2-> Yellow
  //         beta.getCar().hurry();
  //         // beta.getPed().hurry();
  //       } else { // Reset and Restart
  //         start = now;
  //       }
}