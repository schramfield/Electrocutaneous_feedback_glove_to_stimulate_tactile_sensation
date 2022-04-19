// This is all arranged assuming the BYB Spikershields from Neuro
#define WhiteButton 7 // White button: begin/end calibration
#define RedButton 4 // Red button -> STIM up
#define g1 8 // first green light
#define g2 9
#define y1 10
#define y2 11
#define r1 12
#define r2 13
#define ohm5 2
#define ohm10 3
#define ohm20 5
#define ohm25 6
#define flsh 100 // this way I can change the flash time easily
#define tap 10 // let's work out what feels natural...


int i = 0; // i will be our STIM value, it goes 1-12, each step representing 5kohms
int sustain = 0;
int maximum = 0;
bool calib = false; // toggles calibration mode
bool touch = false; // once a touch initiates, touch becomes true- that way new touches and sustained touches are different

void setup()
{
  // set all the lights
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(y1, OUTPUT);  
  pinMode(y2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  // set all the relays
  pinMode(ohm5, OUTPUT); // 5kohms
  pinMode(ohm10, OUTPUT); // 10kohms
  pinMode(ohm20, OUTPUT); // 20kohms
  pinMode(ohm25, OUTPUT); // 25 kohms

  // start at max resistance and flash the lights a couple of times
  set60();
  flashALL();
  delay(flsh);
  rainbow();
  delay(flsh);
  flashALL();
  digitalWrite(g1, HIGH);

  // get the serial port working
  Serial.begin(9600);  
}

void loop(){
  if (calib == true) {
    updateI(i);
  }
  if (calib == false) {
    if (fromUnity() == 1) {
      if (touch == false) {
        updateI(maximum);
        digitalWrite(r1, HIGH);
        digitalWrite(y2, HIGH);
        delay(tap);
        updateI(sustain);
        digitalWrite(r1, LOW);
        delay(10);
      }
      else {
        delay(10);
      }
    }
    else if (fromUnity() == 0){
      set60();
      touch = false;
      digitalWrite(y2, LOW);
    }
    else {
      delay(10);
    }
  }
  if (digitalRead(WhiteButton) == HIGH && calib == false) {
    calib = true;
    i = 0;
    allOFF();
    flash2(g1, g2);
    delay(500);
  }
  if (digitalRead(RedButton) == HIGH && calib == true && i < 12) {
    i = i+1;
    delay(1000);
  }
  if (digitalRead(WhiteButton) == HIGH && calib == true) {
    maximum = i;
    sustain = i-2;
    calib = false;
    rainbow();
    allOFF();
    digitalWrite(r2, HIGH);
    delay(500);
  }
}

// LIGHT RELATED FUNCTIONS
bool flash(int LED) {
  digitalWrite(LED, HIGH);
  delay(flsh);
  digitalWrite(LED, LOW);
  return true;
}
bool flash2(int LED1, int LED2) {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(flsh);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  return true;
}
bool flashALL() {
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  delay(flsh);
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
}
bool rainbow() {
  for(int j = 8; j < 14; j++) {
    digitalWrite(j, HIGH);
    delay(flsh);
    digitalWrite(j, LOW);
  }
}
bool allOFF() {
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
}


// UNITY RELATED FUNCTIONS
int fromUnity(){
  if(Serial.available() > 0 ){
    int data = Serial.read();

    switch(data){
      case '2':{
        return 2;
        break;
      }
      case '1':{
        return 1;
        break;
      }
      case '0':{
        return 0;
        break;
      }
      default:{
        return -1;}
    }
  }
  return 7;
}

// RESISTANCE RELATED FUNCTIONS
bool updateI(int i) {
  if (i <= 0) { // 60 kOhms
  set60();
  }
  if (i == 1) { // 55 kOhms
   set55();
   }
  if (i == 2) { // 50 kOhms
    set50();
  }
  if (i == 3) { // 45 kOhms
    set45();
  }
  if (i == 4) { // 40 kOhms
    set40();
  }
  if (i == 5) { // 35 kOhms
    set35();
  }
  if (i == 6) { // 30 kOhms
    set30();
  }
  if (i == 7) { // 25 kOhms
    set25();
  }
  if (i == 8) { // 20 kOhms
    set20();
  }
  if (i == 9) { // 15 kOhms
    set15();
  }
  if (i == 10) { // 10 kOhms
    set10();
  }
  if(i == 11) { // 5 kOHMS
    set5();
  }
  if(i >= 12) { // 0 kOHMS
    set0();
  }  
  return true;
}

bool set60() {
  // set the resistance level
  digitalWrite(ohm5, LOW);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, LOW);
  digitalWrite(ohm25, LOW);
  // set the lights
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);    
  return true;
}
bool set55() {
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, LOW);
  digitalWrite(ohm25, LOW); 
  // set the lights
  digitalWrite(g1, LOW);
  digitalWrite(g2, LOW);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);  
  return true;
}
bool set50() {
  digitalWrite(ohm5, LOW);
  digitalWrite(ohm10, HIGH);
  digitalWrite(ohm20, LOW);
  digitalWrite(ohm25, LOW);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, LOW);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set45(){
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, HIGH);
  digitalWrite(ohm20, LOW);
  digitalWrite(ohm25, LOW);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, LOW);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set40() {
  digitalWrite(ohm5, LOW);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, LOW);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set35() {
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, LOW);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, LOW);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set30() {
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, LOW);
  digitalWrite(ohm25, HIGH);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set25() {
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, HIGH);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, LOW);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set20() {
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, HIGH);
  digitalWrite(ohm20, LOW);
  digitalWrite(ohm25, HIGH);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set15() {
  digitalWrite(ohm5, LOW);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, HIGH);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  return true;
}
bool set10() {
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, LOW);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, HIGH);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  return true;
}
bool set5() {
  digitalWrite(ohm5, LOW);
  digitalWrite(ohm10, HIGH);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, HIGH);
  // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);  
  return true;
}
bool set0() { //MAX STIM
  digitalWrite(ohm5, HIGH);
  digitalWrite(ohm10, HIGH);
  digitalWrite(ohm20, HIGH);
  digitalWrite(ohm25, HIGH);
 // set the lights
  digitalWrite(g1, HIGH);
  digitalWrite(g2, HIGH);
  digitalWrite(y1, HIGH);
  digitalWrite(y2, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);

  return true;
}  
