#include <pitches.h>
int alpha_car_green, alpha_car_yellow, alpha_car_red;
int alpha_ped_white, alpha_ped_red;
int beta_car_green, beta_car_yellow, beta_car_red;
int beta_ped_white, beta_ped_red;

unsigned long start;

void setup() {
  start = millis();
}
 
void loop() {  
  unsigned long now = millis();
  if (now - start < 5000) {
    //alpha = go
    //beta = stop
  }
  else
    if (now - start < 8000) {
      //alpha = hurry
      //beta = stop
    }
    else
      if (now - start < 13000) {
        //alpha = stop
        //beta = go
      }
      else
        if ( now - start < 16000) {
          //alpha = stop
          //beta = hurry
        }
        else {
          // restart the process
          start = now;
        }
}

class Car_lights {
  private:
  int green, yellow, red;
  
  public:
  Car_lights(int green, int yellow, int red) : green(green), yellow(yellow), red(red) {
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(red, OUTPUT);
  }

  //getters
  
  //setters

  //go

  //hurry

  //stop
};

class Ped_lights {
  private:
  int white, red;
  
  public:
  Ped_lights(int white, int red) : white(white), red(red) {
    pinMode(white, OUTPUT);
    pinMode(red, OUTPUT);
  }
  
  //getters
  
  //setters

  //go

  //hurry

  //stop
};

class Beeper {
  private:
  //pin

  public:
  Beeper() {

  }
};

class Countdown {
  private: 
  int pin1, pin2, pin3;
  Beeper beep;
  
  public:
  Countdown(int pin1, int pin2, int pin3, Beeper beep) :
            pin1(pin1), pin2(pin2), pin3(pin3), beep(beep) {
    pinMode(pin1, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin1, OUTPUT);
  }
      
  //getters
  
  //setters

  //coun

  //hurry
};


class Traffic_lights {
  private:
  Car_lights c_alpha;
  Ped_lights p_alpha;
  Car_lights c_beta;
  Ped_lights p_beta;
  Countdown timer;
 
  public:
  Traffic_lights(Car_lights c_alpha, Ped_lights p_alpha, Car_lights c_beta,
                  Ped_lights p_beta, Countdown timer) : c_alpha(c_alpha),
                  p_alpha(p_alpha), c_beta(c_beta), p_beta(p_beta), timer(timer) {

  }
    
  //getters
  
  //setters

  //go

  //hurry

  //stop
};


