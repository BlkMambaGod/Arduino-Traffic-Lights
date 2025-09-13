#include <pitches.h>


// Pin des LED
const int pedestrian_White = 2;
const int pedestrian_Red = 3;
const int car_Green = 4;
const int car_Yellow = 5;
const int car_Red = 6;
// Pin bouton et buzzer
const int buzzer = 23;
const int button = 12;
// Variables d'etats
// bool pedestrian_WhiteState = true;
bool pedestrian_RedState = true;
// bool car_GreenState = true;
// bool car_YellowState = ;
// bool car_RedState = false;
bool buttonState;
// Longueur d'un buzz = 500 ms
int buzzTime = 500;
// controle de temps
unsigned long start;
unsigned long blink;
// Selection lumiere
unsigned long greenStart = 10000;
unsigned long yellowStart = 13000; // duree plus courte que les autres
unsigned long redStart = 23000;
const int timeMult = 23000;
//duree de rouge et vert
int duration = redStart - yellowStart;

// Integration d'interruption par detection de présence
const int trigPin = 7;
const int echoPin = 8;



void setup() {
  // Mode des pins
  pinMode(pedestrian_White, OUTPUT);
  pinMode(pedestrian_Red, OUTPUT);
  pinMode(car_Green, OUTPUT);
  pinMode(car_Yellow, OUTPUT);
  pinMode(car_Red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
// Compteur d'horloge debut
  start = millis();
  blink = millis();

// Integration d'interruption par detection de présence
}
 
void loop() {  
  unsigned long now = millis();
  /*Pour une durée de temps juste après le début de cycle, on active la lumière verte.
    Si l'intervalle de temps est dépassé, on passe au jaune, puis au rouge. Lorsqu'il 
    ne reste que quelque seconde au cycle du rouge, on fait clignoté la lumière de pie-
    ton rouge."if...else" est utilisé pour éviter que toutes les conditions ne jouent 
    en même temps. Lorsque la différence de temps dépasse la durée du cycle, on remet
    à zéro.*/
  if(now - start < 50000) {
    digitalWrite(car_Green, true);
    digitalWrite(car_Red, false);
    digitalWrite(car_Yellow, false);

    digitalWrite(pedestrian_Red, true);
    digitalWrite(pedestrian_White, false);
    buttonState = digitalRead(button);
    bool presence = getPresence(trigPin, echoPin);
    if(!buttonState || presence) { // Protocole d'interruption
      tone(buzzer, NOTE_C5, 500);
      tone(buzzer, NOTE_F5, 100);
      start = now - 40000;
    }
  }
  else 
    if(now - start < 55000){
      digitalWrite(car_Green, false);
      digitalWrite(car_Yellow, true);
    }
    else
      if(now - start < 95000) {
        digitalWrite(car_Yellow, false);
        digitalWrite(car_Red, true);

        pedestrian_RedState = false;
        digitalWrite(pedestrian_Red, pedestrian_RedState);
        digitalWrite(pedestrian_White, true);
      }
      else
        if(now - start < 115000) {
          if(now - blink >= 1000) {
            blink = now;
            if(pedestrian_RedState == true)
              pedestrian_RedState = false;
            else
              pedestrian_RedState = true;
            digitalWrite(pedestrian_Red, pedestrian_RedState);
            tone(buzzer, NOTE_C6, 100);
          }
        }
        else {
          start = now;
          blink = now;
        }
}

bool getPresence(const int trigPin, const int echoPin) {
  /*J'ai modifié la fonction de distance pour simplement recevoir 
    si une présence est détecté ou pas. Idéalement, dès qu'on détecte
    un objet au loin qui s'approche, on commence l'interruption du
    feu vert. C'est juste pour m'amuser ici, plus tard ce sera à remplacer
    par détection à l'infrarouge.*/
  float distance;
  
  digitalWrite(trigPin, true);
  delayMicroseconds(10);
  digitalWrite(trigPin, false);
  
  float time = pulseIn(echoPin, true, 50200); 
  /*3rd argument is the window in which signaled are captured, 
    any signal after that window will not be treated*/

  if (time  == 0) // This allows to discard interval between signals where nothing is detected
    return false;
  distance = time * 0.343 / 2; 
  Serial.println(distance);
  return bool(distance);
}