#include <ENGR111_Lib.h>

//MSD(project, buttonpin, maxDisp, interruptpin, trigger, echo)
//MSD.setDisplay(DispNum, TopMessage, BottomMessage)
ENGR111_Lib MSD(2, 3, 4, 2, 11, 12);

const int pumpP = 4;
const int pumpN = 5;
const int valveP = 7;
const int valveN = 6;
float TC = 0;
float x = 0;
float TT = 0;
float vol1 = 277.19;
float vol2 = 0;
String Valve;
float r = 8;
float t1 = 0;
float t2 = 0;
float tt = 0;
float h = 0;
float p = 0;
float TU = 0;
int pumpFlag = 0;
float y = 0;
float z = 0;
float currentTime = 0;

void setup() {
  MSD.begin();
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(pumpP, LOW);
  pinMode(valveP, HIGH);
  pinMode(pumpN, LOW);
  pinMode(valveN, LOW); 
}

void loop() {
  x = MSD.distance();
  h = (13.92 - x) * cos(5 * (PI / 180));
  vol2 = 26.035 * h * 15.8;
  TC = vol1 + vol2;
  if(TC >= 453.41 && pumpFlag == 0){
    digitalWrite(4, HIGH);
    t1 = millis();
    pumpFlag = 1;
    z += t1;
  }
  else if(TC < 453.41 && pumpFlag == 1){
    digitalWrite(4, LOW);
    pumpFlag = 0;
  }
  if(digitalRead(4) == HIGH){
    currentTime = millis();
    tt = (currentTime - y) / 1000;
    TT = (133.333333333333) * tt;
  }
  else if(digitalRead(4) == LOW && pumpFlag == 1){
    t2 = millis();
    y += t2;
    tt = (y - z) / 1000;
    TT = (133.333333333333) * tt;
  }
  p = MSD.getCount();
  TU = (p / 410) * 1000;
  if(TC < 3245.19){
    digitalWrite(7, HIGH);
    Valve = "OPEN";
  }
  else if(TC >= 3245.19) {
    digitalWrite(7, LOW);
    Valve = "CLOSE";
  }
  MSD.setDisplay(1, "TC Volume", String(TC,2) + "mL");
  MSD.setDisplay(2, "Total Treated", String(TT,2) + "mL");
  MSD.setDisplay(3, "Total Untreated", String(TU,2) + "mL");
  MSD.setDisplay(4, "Valve State", Valve);
  MSD.displayLCD();
}